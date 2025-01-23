#include <ifaddrs.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>

int main(void) {
    struct ifaddrs *addresses;

    if (getifaddrs(&addresses) == -1) {
        printf("getifaddrs call failed\n");
        return -1;
    }
    struct ifaddrs *address = addresses;
    while (address) {
        /**
          The family field determines whether the address is IPv4 or IPv6
          AF_INET: IPv4
          AF_INET6: IPv6
        **/

        int family = address->ifa_addr->sa_family;
        if (family == AF_INET || family == AF_INET6) {
            printf("%s\t", address->ifa_name);
            printf("%s\t", family == AF_INET ? "IPv4" : "IPv6");
            int family_size = 0;
            if (family == AF_INET) {
                family_size = sizeof(struct sockaddr_in);
            } else {
                family_size = sizeof(struct sockaddr_in6);
            }
            char ap[100];
            getnameinfo(address->ifa_addr, family_size, ap, sizeof(ap), 0, 0,
                        NI_NUMERICHOST);
            printf("\t%s\n", ap);
        }
        address = address->ifa_next;
    }
    freeifaddrs(addresses);
    return 0;
}
