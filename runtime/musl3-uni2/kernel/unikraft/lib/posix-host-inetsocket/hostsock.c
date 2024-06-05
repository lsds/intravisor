/* SPDX-License-Identifier: BSD-3-Clause */
/* Copyright (c) 2023, Unikraft GmbH and The Unikraft Authors.
 * Licensed under the BSD-3-Clause License (the "License").
 * You may not use this file except in compliance with the License.
 */

#include <string.h>
#include <sys/un.h>

#include <uk/assert.h>
#include <uk/essentials.h>
#include <uk/socket_driver.h>
#include <uk/posix-pipe.h>
#include <uk/file/pollqueue.h>
#include <poll.h>
#include <hostcalls.h>
#include <netinet/in.h>

struct host_sock_data {
	int host_fd; //fd in the host os
	int vfs_fd;
	int skip_first_poll;
};

static
void *unix_socket_create(struct posix_socket_driver *d,
			 int family, int type, int proto)
{
	int fd = host_socket(family, type, proto);

	if (unlikely(fd < 0))
		return ERR2PTR(fd);


	struct host_sock_data *data = uk_malloc(d->allocator, sizeof(*data));
	data->host_fd = fd;
	data->skip_first_poll = 0;

	return data;
}

static
void unix_socket_poll(posix_sock *file)
{
	struct host_sock_data *data = posix_sock_get_data(file);
	if (unlikely(data->skip_first_poll == 0))
		data->skip_first_poll = 1;

	return;
}

static
int unix_socket_socketpair(struct posix_socket_driver *d,
			   int family, int type, int proto,
			   void *sockvec[2])
{
	int ret = 0;
	uk_pr_err("%s, TODO\n", __func__);while(1);

	return ret;
}

static
void unix_socket_socketpair_post(struct posix_socket_driver *d __unused,
				 posix_sock *sv[2])
{
	int ret = 0;
	uk_pr_err("%s, TODO\n", __func__);while(1);

}

static
void *unix_socket_accept4(posix_sock *file,
			  struct sockaddr *restrict addr,
			  socklen_t *restrict addr_len, int flags)
{
	struct host_sock_data *data = posix_sock_get_data(file);
	int new_fd = host_accept(data->host_fd, addr, addr_len); //acept does not use flags

	if (unlikely(new_fd < 0))
		return ERR2PTR(new_fd);

	struct posix_socket_driver *d = posix_sock_get_driver(file);
	struct host_sock_data *data2 = uk_malloc(d->allocator, sizeof(*data2));

	data2->host_fd = new_fd;

	return data2;
}

static
int unix_socket_bind(posix_sock *file,
		     const struct sockaddr *addr, socklen_t addr_len)
{
	struct host_sock_data *data = posix_sock_get_data(file);

	int err = host_bind(data->host_fd, addr, addr_len);
	return err;
}

static
int unix_socket_getpeername(posix_sock *file,
			    struct sockaddr *restrict addr,
			    socklen_t *restrict addr_len)
{
	int ret = 0;
	struct host_sock_data *data = posix_sock_get_data(file);
	ret = host_getpeername(data->host_fd, addr, addr_len);

	return ret;
}

static
int unix_socket_getsockname(posix_sock *file,
			    struct sockaddr *restrict addr,
			    socklen_t *restrict addr_len)
{
	struct host_sock_data *data = posix_sock_get_data(file);

	int ret = 0;
	uk_pr_err("%s, TODO\n", __func__);while(1);


	return 0;
}

static
int unix_socket_getsockopt(posix_sock *file __unused, int level __unused,
			   int optname __unused, void *restrict optval __unused,
			   socklen_t *restrict optlen __unused)
{
	int ret = 0;
	uk_pr_err("%s not implemented\n", __func__);
	return 0;
}

static
int unix_socket_setsockopt(posix_sock *file, int level,
			   int optname, const void *optval,
			   socklen_t optlen)
{
	int ret = 0;
	struct host_sock_data *data = posix_sock_get_data(file);

	if(level != SOL_SOCKET && level != IPPROTO_TCP && level !=IPPROTO_IPV6) {
		uk_pr_err("Unknown Level (%x)\n", level);
		return -1;
	}

	if(level == IPPROTO_IPV6) {
		uk_pr_err("IPV6 is not supported in %s\n", __func__);
		return -1;
	}

#define	BSD_SOL_SOCKET	0xffff
#define	BSD_SO_REUSEADDR	0x00000004	/* allow local address reuse */
#define	BSD_SO_KEEPALIVE	0x00000008	/* keep connections alive */

#define	BSD_IPPROTO_IP		0		/* dummy for IP */
#define	BSD_IPPROTO_ICMP	1		/* control message protocol */
#define	BSD_IPPROTO_TCP		6		/* tcp */
#define	BSD_IPPROTO_UDP		17		/* user datagram protocol */
#define	BSD_TCP_NODELAY		1

#define	BSD_O_NONBLOCK	0x0004
#define	BSD_O_CLOEXEC	0x00100000
#define BSD_F_GETFL	3
#define BSD_F_SETFL	4

#define	TCP_NODELAY	1

	if(level == SOL_SOCKET) {
		switch(optname) {
			case -1:
				ret = host_fcntl(data->host_fd, BSD_F_SETFL, 0);
				break;
			case SOCK_NONBLOCK:
				ret = host_fcntl(data->host_fd, BSD_F_GETFL, 0);
				ret = host_fcntl(data->host_fd, BSD_F_SETFL, ret | BSD_O_NONBLOCK);
				break;
			case SOCK_CLOEXEC:
				ret = host_fcntl(data->host_fd, BSD_F_GETFL, 0);
				ret = host_fcntl(data->host_fd, BSD_F_SETFL, ret | BSD_O_CLOEXEC);
				break;
			case SO_REUSEADDR:
				ret = host_setsockopt(data->host_fd, BSD_SOL_SOCKET, BSD_SO_REUSEADDR, optval, optlen);
				break;
			case SO_KEEPALIVE:
				ret = host_setsockopt(data->host_fd, BSD_SOL_SOCKET, BSD_SO_KEEPALIVE, optval, optlen);
				break;
			default:
				uk_pr_err("Unknown optname (%x)\n", optname);
				ret = -1;
				break;
		}
	}

	if(level == IPPROTO_TCP) {
		switch(optname) {
			case TCP_NODELAY:
				ret = host_setsockopt(data->host_fd, BSD_IPPROTO_TCP, BSD_TCP_NODELAY, optval, optlen);
				break;
			default:
				uk_pr_err("Unknown optname (%x)\n", optname);
				ret = -1;
				break;
		}
	}
	return ret;
}


static
int unix_sock_connect_stream(posix_sock *file, posix_sock *target)
{
	int err;
	int ret = 0;
	uk_pr_err("%s, TODO\n", __func__);while(1);

	return err;
}

static
int unix_sock_connect_dgram(posix_sock *file, posix_sock *target)
{
	int ret = 0;
	uk_pr_err("%s, TODO\n", __func__);while(1);

	return 0;
}


static
int unix_socket_connect(posix_sock *file,
			const struct sockaddr *addr, socklen_t addr_len)
{
	int err = 0;
	uk_pr_err("%s, TODO\n", __func__);while(1);

	return err;
}

static
int unix_socket_listen(posix_sock *file, int backlog)
{
	int ret = 0;

	struct host_sock_data *data = posix_sock_get_data(file);
	ret = host_listen(data->host_fd, backlog);

	return ret;
}

static
ssize_t unix_socket_recvmsg(posix_sock *file, struct msghdr *msg, int flags)
{
	int ret = 0;
		uk_pr_err("%s, TODO\n", __func__);while(1);
	return ret;
}

static
ssize_t unix_socket_recvfrom(posix_sock *file, void *restrict buf,
			     size_t len, int flags, struct sockaddr *from,
			     socklen_t *restrict fromlen)
{
#if 0
	struct iovec iov = {
		.iov_base = buf,
		.iov_len = len
	};
	struct msghdr msg = {
		.msg_name = from,
		.msg_namelen = *fromlen,
		.msg_iov = &iov,
		.msg_iovlen = 1,
		.msg_control = NULL,
		.msg_controllen = 0,
		.msg_flags = 0
	};
	ssize_t ret = unix_socket_recvmsg(file, &msg, flags);

	if (ret >= 0)
		*fromlen = msg.msg_namelen;
	return ret;
#else
	struct host_sock_data *data = posix_sock_get_data(file);
	ssize_t ret = host_recv(data->host_fd, buf, len, flags);
	return ret;
#endif
}

static
ssize_t unix_socket_sendmsg(posix_sock *file,
			    const struct msghdr *msg, int flags)
{
	int ret = 0;
	uk_pr_err("%s, TODO\n", __func__);while(1);
	return ret;
}

static
ssize_t unix_socket_sendto(posix_sock *file, const void *buf,
			   size_t len, int flags,
			   const struct sockaddr *dest_addr, socklen_t addrlen)
{
#if 0
	struct iovec iov = {
		.iov_base = (void *)buf,
		.iov_len = len
	};
	struct msghdr msg = {
		.msg_name = (struct sockaddr *)dest_addr,
		.msg_namelen = addrlen,
		.msg_iov = &iov,
		.msg_iovlen = 1,
		.msg_control = NULL,
		.msg_controllen = 0,
		.msg_flags = 0
	};

	return unix_socket_sendmsg(file, &msg, flags);
#else
	struct host_sock_data *data = posix_sock_get_data(file);
	ssize_t ret = host_send(data->host_fd, buf, len, flags);
	return ret;
#endif
}

static
ssize_t unix_socket_read(posix_sock *file,
			 const struct iovec *iov, int iovcnt)
{
#if 0
	struct msghdr msg = {
		.msg_name = NULL,
		.msg_namelen = 0,
		.msg_iov = (struct iovec *)iov,
		.msg_iovlen = iovcnt,
		.msg_control = NULL,
		.msg_controllen = 0,
		.msg_flags = 0
	};
	return unix_socket_recvmsg(file, &msg, 0);
#else
	ssize_t ret = 0;
	int tmp = 0;
	struct host_sock_data *data = posix_sock_get_data(file);
	for(int i = 0; i < iovcnt; i++) {
		tmp = host_recv(data->host_fd, iov[i].iov_base, iov[i].iov_len, 0);
		if(tmp < 0)
			return tmp;
		ret += tmp;
	}
	return ret;
#endif
}

static
ssize_t unix_socket_write(posix_sock *file,
			  const struct iovec *iov, int iovcnt)
{
#if 0
	struct msghdr msg = {
		.msg_name = NULL,
		.msg_namelen = 0,
		.msg_iov = (struct iovec *)iov,
		.msg_iovlen = iovcnt,
		.msg_control = NULL,
		.msg_controllen = 0,
		.msg_flags = 0
	};
	return unix_socket_sendmsg(file, &msg, 0);
#else
	ssize_t ret = 0;
	int tmp = 0;
	struct host_sock_data *data = posix_sock_get_data(file);
	for(int i = 0; i < iovcnt; i++) {
		tmp = host_send(data->host_fd, iov[i].iov_base, iov[i].iov_len, 0);
		if(tmp < 0)
			return tmp;

		ret += tmp;
	}
	return ret;
#endif
}

static
int unix_sock_shutdown(posix_sock *file, int how, int notify)
{
	uk_pr_err("%s, TODO\n", __func__);while(1);
	return 0;
}

static
int unix_socket_shutdown(posix_sock *file, int how)
{
	uk_pr_err("%s, TODO\n", __func__);while(1);
	return unix_sock_shutdown(file, how, 1);
}

static
int unix_socket_close(posix_sock *file)
{
	int r = 0;

	struct host_sock_data *data = posix_sock_get_data(file);

	r = host_close(data->host_fd);

	return r;
}

static
int unix_socket_ioctl(posix_sock *file, int request,
		      void *argp)
{
	struct host_sock_data *data = posix_sock_get_data(file);

	struct pollfd *fds_in = (struct pollfd *) argp;

	struct pollfd fds[1];
	int nfds = 1;
	int ret;

	switch(request) {
		case 0xcaca:
			ret = data->host_fd;
			data->vfs_fd = (int) argp;
			break;
		default:
			uk_pr_err("Unsupported ioctl %x\n", request);
			ret = -1;
			break;
	}

	return ret;
}
#include <stdio.h>
#include <stdlib.h>

static struct posix_socket_ops unix_posix_socket_ops = {
	/* POSIX interfaces */
	.create      = unix_socket_create,
	.accept4     = unix_socket_accept4,
	.bind        = unix_socket_bind,
	.shutdown    = unix_socket_shutdown,
	.getpeername = unix_socket_getpeername,
	.getsockname = unix_socket_getsockname,
	.getsockopt  = unix_socket_getsockopt,
	.setsockopt  = unix_socket_setsockopt,
	.connect     = unix_socket_connect,
	.listen      = unix_socket_listen,
	.recvfrom    = unix_socket_recvfrom,
	.recvmsg     = unix_socket_recvmsg,
	.sendmsg     = unix_socket_sendmsg,
	.sendto      = unix_socket_sendto,
	.socketpair  = unix_socket_socketpair,
	.socketpair_post = unix_socket_socketpair_post,
	/* vfscore ops */
	.read		= unix_socket_read,
	.write		= unix_socket_write,
	.close		= unix_socket_close,
	.ioctl		= unix_socket_ioctl,
	.poll		= unix_socket_poll,
};

#ifndef INTRAVISOR
POSIX_SOCKET_FAMILY_REGISTER(AF_UNIX, &unix_posix_socket_ops);
#else
struct posix_socket_driver host_inet_socket_reg = {		\
		.family = AF_INET,				\
		.libname = "host_inet_socket",		\
		.ops = &unix_posix_socket_ops,			\
	};
#endif