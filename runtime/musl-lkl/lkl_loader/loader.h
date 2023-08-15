#include <lkl.h>
#include <lkl_host.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>		/* superset of previous */
#include <arch.h>

#define GD

__intcap_t c_out_7(int, __intcap_t, __intcap_t, __intcap_t, __intcap_t, __intcap_t, __intcap_t, __intcap_t);
__intcap_t c_out_6(int, __intcap_t, __intcap_t, __intcap_t, __intcap_t, __intcap_t, __intcap_t);
__intcap_t c_out_5(int, __intcap_t, __intcap_t, __intcap_t, __intcap_t, __intcap_t);
__intcap_t c_out_4(int, __intcap_t, __intcap_t, __intcap_t, __intcap_t);
__intcap_t c_out_3(int, __intcap_t, __intcap_t, __intcap_t);
__intcap_t c_out_2(int, __intcap_t, __intcap_t);
__intcap_t c_out_1(int, __intcap_t);
__intcap_t c_out_0(int);

struct lkl_netdev_fd {
	struct lkl_netdev dev;
	/* file-descriptor based device */
	int fd_rx;
	int fd_tx;
	/*
	 * Controlls the poll mask for fd. Can be acccessed concurrently from
	 * poll, tx, or rx routines but there is no need for syncronization
	 * because:
	 *
	 * (a) TX and RX routines set different variables so even if they update
	 * at the same time there is no race condition
	 *
	 * (b) Even if poll and TX / RX update at the same time poll cannot
	 * stall: when poll resets the poll variable we know that TX / RX will
	 * run which means that eventually the poll variable will be set.
	 */
	int poll_tx, poll_rx;
	/* controle pipe */
	int pipe[2];

	unsigned long cmp_to_mon;
};

///
void *mount_thread(void *arg);

struct s_mount {
	unsigned long *disk_io;
};
////
