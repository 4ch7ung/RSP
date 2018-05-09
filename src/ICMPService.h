#ifndef ICMPService_h
#define ICMPService_h

#include <netinet/in.h>

class ICMPService {
public:
	void ping(const sockaddr_in * address);
};

#endif /* ICMPService_h */
