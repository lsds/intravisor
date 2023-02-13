#include <uxr/client/profile/transport/ip/tcp/tcp_transport_posix_nopoll.h>
#include "tcp_transport_internal.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netdb.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

//because our host system is freebsd
struct intr_sockaddr_in  {
	unsigned char	sin_len;
	unsigned char	sin_family;
	unsigned short	sin_port;
	struct	in_addr sin_addr;
	char	sin_zero[8];
} __attribute__((packed));


bool uxr_init_tcp_platform(
        uxrTCPPlatform* platform,
        uxrIpProtocol ip_protocol,
        const char* ip,
        const char* port)
{
    bool rv = false;

    switch (ip_protocol)
    {
        case UXR_IPv4:
	    printf("%d\n", __LINE__);
            platform->fd = socket(AF_INET, SOCK_STREAM, 0);
            break;
        case UXR_IPv6:
	    printf("%d\n", __LINE__);
            platform->fd = socket(AF_INET6, SOCK_STREAM, 0);
            break;
    }

    if (-1 != platform->fd)
    {
        struct addrinfo hints;
        struct addrinfo* result;
        struct addrinfo* ptr;

        memset(&hints, 0, sizeof(hints));
        switch (ip_protocol)
        {
            case UXR_IPv4:
                hints.ai_family = AF_INET;
                break;
            case UXR_IPv6:
                hints.ai_family = AF_INET6;
                break;
        }
        hints.ai_socktype = SOCK_DGRAM;
#if 0
        if (0 == getaddrinfo(ip, port, &hints, &result))
        {
            for (ptr = result; ptr != NULL; ptr = ptr->ai_next)
            {
                if (0 == connect(platform->fd, ptr->ai_addr, ptr->ai_addrlen))
                {
                    rv = true;
                    break;
                }
            }
        }
#else
	printf("Forced TCP: %s %s, fd=%d %d\n", ip, port, platform->fd, AF_INET);
	uint16_t iport;
	iport = (uint16_t)atoi(port);
	struct intr_sockaddr_in remote_addr;
	memset(&remote_addr, 0, sizeof(remote_addr));
        remote_addr.sin_family = AF_INET;
        remote_addr.sin_port = htons(iport);
        remote_addr.sin_addr.s_addr = inet_addr(ip);
        remote_addr.sin_len = sizeof(remote_addr);
        int connected = connect(platform->fd,
                        &remote_addr,
                        sizeof(remote_addr));
        rv = (0 == connected);

#endif
        freeaddrinfo(result);
    }
    return rv;
}

int net_close(int fildes);

bool uxr_close_tcp_platform(
        uxrTCPPlatform* platform)
{
    return (-1 == platform->fd) ? true : (0 == net_close(platform->fd));
}

size_t uxr_write_tcp_data_platform(
        uxrTCPPlatform* platform,
        const uint8_t* buf,
        size_t len,
        uint8_t* errcode)
{
    size_t rv = 0;
    ssize_t bytes_sent = send(platform->fd, (void*)buf, len, 0);
    if (-1 != bytes_sent)
    {
        rv = (size_t)bytes_sent;
        *errcode = 0;
    }
    else
    {
        *errcode = 1;
    }
    return rv;
}

size_t uxr_read_tcp_data_platform(
        uxrTCPPlatform* platform,
        uint8_t* buf,
        size_t len,
        int timeout,
        uint8_t* errcode)
{
    size_t rv = 0;

    timeout = (timeout <= 0) ? 1 : timeout;

    struct timeval tv;
    tv.tv_sec = timeout / 1000;
    tv.tv_usec = (timeout % 1000) * 1000;

    if (0 != setsockopt(platform->fd, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv)))
    {
        *errcode = 1;
        return 0;
    }

    ssize_t bytes_received = recv(platform->fd, (void*)buf, len, 0);
    if (-1 != bytes_received)
    {
        rv = (size_t)bytes_received;
        *errcode = 0;
    }
    else
    {
        *errcode = 1;
    }

    return rv;
}

void uxr_disconnect_tcp_platform(
        struct uxrTCPPlatform* platform)
{
    net_close(platform->fd);
    platform->fd = -1;
}
