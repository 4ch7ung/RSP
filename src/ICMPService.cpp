
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <unistd.h> // read, write, close
#include <arpa/inet.h>
#include <netdb.h>
#include <cerrno>
#include <stdexcept>
#include <system_error>
#include <stdio.h>

#include "ICMPService.h"
#include "ICMPStructs.h"

#define TRUE 1
#define FALSE 0

uint16_t crc2 (uint16_t * addr, int count) { //http://www.ietf.org/rfc/rfc1071.txt
    register long sum = 0;

    while (count > 1) {
        /*  This is the inner loop */
        sum += *(unsigned short*) addr++;
        count -= 2;
    }

    /*  Add left-over byte, if any */
    if (count > 0) {
        sum += *(unsigned char *) addr;
    }

    /*  Fold 32-bit sum to 16 bits */
    while (sum >> 16 != 0) {
        sum = (sum & 0xffff) + (sum >> 16);
    }

    return (uint16_t)(~sum);
}

// Analyze response packet
uint32_t analize(char* data, sockaddr_in* adr) {
	char* ip;
	IPHeader *pHe = (IPHeader*)data;
	char name[NI_MAXHOST] = {0};
	char servInfo[NI_MAXSERV] = {0};

	getnameinfo((struct sockaddr *) adr, sizeof(struct sockaddr), name, NI_MAXHOST, servInfo, NI_MAXSERV, NI_NUMERICSERV);
	ip = inet_ntoa(adr->sin_addr);

//	int ttl = (int)pHe->timeToLive;
	data += sizeof(IPHeader);

	ICMPHeader *ic = (ICMPHeader*)data;
//	cout << "Reply from " << ip << " TTL=" << ttl << "\n";
	return pHe->sourceAddress;
}

void startPingWithHost(sockaddr * addr, uint8_t type = AF_INET) {
	int fd = 0;
	switch (type) {
	case AF_INET:
		fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_ICMP);
		break;
	case AF_INET6:
		fd = socket(AF_INET6, SOCK_DGRAM, IPPROTO_ICMPV6);
		break;
	default:
		throw std::system_error(EAFNOSUPPORT, std::generic_category());
	}

	if (fd < 0) {
		throw std::system_error(errno, std::generic_category());
	}

	int opt = TRUE;
	if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)) < 0) {
		throw std::system_error(errno, std::generic_category());
	}

	int timeout = 3000;
	if (setsockopt(fd, SOL_SOCKET, SO_RCVTIMEO, (char*)&timeout, sizeof(timeout)) < 0) {
		throw std::system_error(errno, std::generic_category());
	}

	sockaddr_in self_address;
	self_address.sin_family = type;
	self_address.sin_addr.s_addr = INADDR_ANY;
	self_address.sin_port = htons(0);

	if (bind(fd, (struct sockaddr *)&self_address, sizeof(self_address)) < 0) {
		throw std::system_error(errno, std::generic_category());
	}

	int addrlen = sizeof(self_address);
	fd_set readfds;
	const int max_clients = 30;
	int client_socket[max_clients];
	memset(client_socket, 0, max_clients);

	const int buflen = 1024;
	char buffer[buflen];
	memset(buffer, 0, buflen);

	while(true) {
		// clear the socket set
		FD_ZERO(&readfds);

		// add master socket to set
		FD_SET(fd, &readfds);
		int max_sd = fd;

		// add child sockets to set
		for (int i = 0; i < max_clients; ++i) {
			// socket descriptor
			int sd = client_socket[i];

			// if valid socket descriptor then add to read list
			if(sd > 0)
				FD_SET(sd , &readfds);

			// highest file descriptor number, need it for the select function
			if(sd > max_sd)
				max_sd = sd;
		}

		// wait for an activity on one of the sockets , timeout is NULL ,
		// so wait indefinitely
		int activity = select(max_sd + 1, &readfds, NULL, NULL, NULL);

		if (activity < 0) {
			int err = errno;
			if (err != EINTR) {
				throw std::system_error(err, std::generic_category());
			}
		}

		int new_socket = 0;
		const char * message = "Hui hui hui hui\r\n";
		// If something happened on the master socket ,
		// then its an incoming connection
		if (FD_ISSET(fd, &readfds)) {
			if ((new_socket = accept(fd, (struct sockaddr *)&self_address, (socklen_t*)&addrlen)) < 0) {
				throw std::system_error(errno, std::generic_category());
			}

			// send new connection greeting message
			if (send(new_socket, message, strlen(message), 0) != strlen(message) ) {
				throw std::system_error(errno, std::generic_category());
			}

			// add new socket to array of sockets
			for (int i = 0; i < max_clients; ++i) {
				// if socket is not known yet
				if (client_socket[i] == 0) {
					client_socket[i] = new_socket;
					break;
				}
			}
		}

		// else its some IO operation on some other socket
		for (int i = 0; i < max_clients; ++i) {
			int sd = client_socket[i];

			if (FD_ISSET(sd , &readfds)) {
				// Check if it was for closing, and also read the
				// incoming message
				int valread = 0;
				if ((valread = read(sd, buffer, 1024)) == 0) {
					sockaddr_in address;
					// Somebody disconnected, get his details
					getpeername(sd, (struct sockaddr*)&address, (socklen_t*)&addrlen);
					printf("Host disconnected , ip %s , port %d \n" ,
						  inet_ntoa(address.sin_addr) , ntohs(address.sin_port));

					// Close the socket and mark as 0 in list for reuse
					close(sd);
					client_socket[i] = 0;
				} else { // Echo back the message that came in
					// set the string terminating NULL byte on the end
					// of the data read
					buffer[valread] = '\0';
					send(sd, buffer, strlen(buffer), 0);
				}
			}
		}
	}
}
