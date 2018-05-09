#ifndef SRC_ICMPSTRUCTS_H_
#define SRC_ICMPSTRUCTS_H_

#include <netinet/in.h>

typedef struct ip_header {
    uint8_t versionAndHeaderLength;
    uint8_t differentiatedServices;
    uint16_t totalLength;
    uint16_t identification;
    uint16_t flagsAndFragmentOffset;
    uint8_t timeToLive;
    uint8_t protocol;
    uint16_t headerChecksum;
    uint32_t sourceAddress;
    uint32_t destinationAddress;
} IPHeader;

typedef struct icmp_header {
    uint8_t type;      /* type of message*/
    uint8_t code;      /* type sub code */
    uint8_t checkSum; /* ones complement cksum of struct */
    uint16_t identifier;
    uint16_t sequenceNumber;
} ICMPHeader;

typedef struct icmp_v4_type {
    static uint8_t echoReply = 0;    // code is always 0
    static uint8_t echoRequest = 8;    // code is always 0
} ICMPv4Type;

typedef struct icmp_v6_type {
    static uint8_t echoReply = 129;  // code is always 0
    static uint8_t echoRequest = 128;  // code is always 0
} ICMPv6Type;

#endif /* SRC_ICMPSTRUCTS_H_ */
