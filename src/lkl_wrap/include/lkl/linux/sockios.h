/* SPDX-License-Identifier: GPL-2.0+ WITH Linux-syscall-note */
/*
 * INET		An implementation of the TCP/IP protocol suite for the LINUX
 *		operating system.  INET is implemented using the  BSD Socket
 *		interface as the means of communication with the user level.
 *
 *		Definitions of the socket-level I/O control calls.
 *
 * Version:	@(#)sockios.h	1.0.2	03/09/93
 *
 * Authors:	Ross Biro
 *		Fred N. van Kempen, <waltje@uWalt.NL.Mugnet.ORG>
 *
 *		This program is free software; you can redistribute it and/or
 *		modify it under the terms of the GNU General Public License
 *		as published by the Free Software Foundation; either version
 *		2 of the License, or (at your option) any later version.
 */
#ifndef _LKL_LINUX_SOCKIOS_H
#define _LKL_LINUX_SOCKIOS_H

#include <lkl/asm/sockios.h>

/* Linux-specific socket ioctls */
#define LKL_SIOCINQ		FIONREAD
#define LKL_SIOCOUTQ	TIOCOUTQ        /* output queue size (not sent + not acked) */

#define LKL_SOCK_IOC_TYPE	0x89

/* Routing table calls. */
#define LKL_SIOCADDRT	0x890B		/* add routing table entry	*/
#define LKL_SIOCDELRT	0x890C		/* delete routing table entry	*/
#define LKL_SIOCRTMSG	0x890D		/* unused			*/

/* Socket configuration controls. */
#define LKL_SIOCGIFNAME	0x8910		/* get iface name		*/
#define LKL_SIOCSIFLINK	0x8911		/* set iface channel		*/
#define LKL_SIOCGIFCONF	0x8912		/* get iface list		*/
#define LKL_SIOCGIFFLAGS	0x8913		/* get flags			*/
#define LKL_SIOCSIFFLAGS	0x8914		/* set flags			*/
#define LKL_SIOCGIFADDR	0x8915		/* get PA address		*/
#define LKL_SIOCSIFADDR	0x8916		/* set PA address		*/
#define LKL_SIOCGIFDSTADDR	0x8917		/* get remote PA address	*/
#define LKL_SIOCSIFDSTADDR	0x8918		/* set remote PA address	*/
#define LKL_SIOCGIFBRDADDR	0x8919		/* get broadcast PA address	*/
#define LKL_SIOCSIFBRDADDR	0x891a		/* set broadcast PA address	*/
#define LKL_SIOCGIFNETMASK	0x891b		/* get network PA mask		*/
#define LKL_SIOCSIFNETMASK	0x891c		/* set network PA mask		*/
#define LKL_SIOCGIFMETRIC	0x891d		/* get metric			*/
#define LKL_SIOCSIFMETRIC	0x891e		/* set metric			*/
#define LKL_SIOCGIFMEM	0x891f		/* get memory address (BSD)	*/
#define LKL_SIOCSIFMEM	0x8920		/* set memory address (BSD)	*/
#define LKL_SIOCGIFMTU	0x8921		/* get MTU size			*/
#define LKL_SIOCSIFMTU	0x8922		/* set MTU size			*/
#define LKL_SIOCSIFNAME	0x8923		/* set interface name */
#define	LKL_SIOCSIFHWADDR	0x8924		/* set hardware address 	*/
#define LKL_SIOCGIFENCAP	0x8925		/* get/set encapsulations       */
#define LKL_SIOCSIFENCAP	0x8926		
#define LKL_SIOCGIFHWADDR	0x8927		/* Get hardware address		*/
#define LKL_SIOCGIFSLAVE	0x8929		/* Driver slaving support	*/
#define LKL_SIOCSIFSLAVE	0x8930
#define LKL_SIOCADDMULTI	0x8931		/* Multicast address lists	*/
#define LKL_SIOCDELMULTI	0x8932
#define LKL_SIOCGIFINDEX	0x8933		/* name -> if_index mapping	*/
#define LKL_SIOGIFINDEX	LKL_SIOCGIFINDEX	/* misprint compatibility :-)	*/
#define LKL_SIOCSIFPFLAGS	0x8934		/* set/get extended flags set	*/
#define LKL_SIOCGIFPFLAGS	0x8935
#define LKL_SIOCDIFADDR	0x8936		/* delete PA address		*/
#define	LKL_SIOCSIFHWBROADCAST	0x8937	/* set hardware broadcast addr	*/
#define LKL_SIOCGIFCOUNT	0x8938		/* get number of devices */

#define LKL_SIOCGIFBR	0x8940		/* Bridging support		*/
#define LKL_SIOCSIFBR	0x8941		/* Set bridging options 	*/

#define LKL_SIOCGIFTXQLEN	0x8942		/* Get the tx queue length	*/
#define LKL_SIOCSIFTXQLEN	0x8943		/* Set the tx queue length 	*/

/* SIOCGIFDIVERT was:	0x8944		Frame diversion support */
/* SIOCSIFDIVERT was:	0x8945		Set frame diversion options */

#define LKL_SIOCETHTOOL	0x8946		/* Ethtool interface		*/

#define LKL_SIOCGMIIPHY	0x8947		/* Get address of MII PHY in use. */
#define LKL_SIOCGMIIREG	0x8948		/* Read MII PHY register.	*/
#define LKL_SIOCSMIIREG	0x8949		/* Write MII PHY register.	*/

#define LKL_SIOCWANDEV	0x894A		/* get/set netdev parameters	*/

#define LKL_SIOCOUTQNSD	0x894B		/* output queue size (not sent only) */
#define LKL_SIOCGSKNS	0x894C		/* get socket network namespace */

/* ARP cache control calls. */
		    /*  0x8950 - 0x8952  * obsolete calls, don't re-use */
#define LKL_SIOCDARP	0x8953		/* delete ARP table entry	*/
#define LKL_SIOCGARP	0x8954		/* get ARP table entry		*/
#define LKL_SIOCSARP	0x8955		/* set ARP table entry		*/

/* RARP cache control calls. */
#define LKL_SIOCDRARP	0x8960		/* delete RARP table entry	*/
#define LKL_SIOCGRARP	0x8961		/* get RARP table entry		*/
#define LKL_SIOCSRARP	0x8962		/* set RARP table entry		*/

/* Driver configuration calls */

#define LKL_SIOCGIFMAP	0x8970		/* Get device parameters	*/
#define LKL_SIOCSIFMAP	0x8971		/* Set device parameters	*/

/* DLCI configuration calls */

#define LKL_SIOCADDDLCI	0x8980		/* Create new DLCI device	*/
#define LKL_SIOCDELDLCI	0x8981		/* Delete DLCI device		*/

#define LKL_SIOCGIFVLAN	0x8982		/* 802.1Q VLAN support		*/
#define LKL_SIOCSIFVLAN	0x8983		/* Set 802.1Q VLAN options 	*/

/* bonding calls */

#define LKL_SIOCBONDENSLAVE	0x8990		/* enslave a device to the bond */
#define LKL_SIOCBONDRELEASE 0x8991		/* release a slave from the bond*/
#define LKL_SIOCBONDSETHWADDR      0x8992	/* set the hw addr of the bond  */
#define LKL_SIOCBONDSLAVEINFOQUERY 0x8993   /* rtn info about slave state   */
#define LKL_SIOCBONDINFOQUERY      0x8994	/* rtn info about bond state    */
#define LKL_SIOCBONDCHANGEACTIVE   0x8995   /* update to a new active slave */
			
/* bridge calls */
#define LKL_SIOCBRADDBR     0x89a0		/* create new bridge device     */
#define LKL_SIOCBRDELBR     0x89a1		/* remove bridge device         */
#define LKL_SIOCBRADDIF	0x89a2		/* add interface to bridge      */
#define LKL_SIOCBRDELIF	0x89a3		/* remove interface from bridge */

/* hardware time stamping: parameters in linux/net_tstamp.h */
#define LKL_SIOCSHWTSTAMP	0x89b0		/* set and get config		*/
#define LKL_SIOCGHWTSTAMP	0x89b1		/* get config			*/

/* Device private ioctl calls */

/*
 *	These 16 ioctls are available to devices via the do_ioctl() device
 *	vector. Each device should include this file and redefine these names
 *	as their own. Because these are device dependent it is a good idea
 *	_NOT_ to issue them to random objects and hope.
 *
 *	THESE IOCTLS ARE _DEPRECATED_ AND WILL DISAPPEAR IN 2.5.X -DaveM
 */
 
#define LKL_SIOCDEVPRIVATE	0x89F0	/* to 89FF */

/*
 *	These 16 ioctl calls are protocol private
 */
 
#define LKL_SIOCPROTOPRIVATE 0x89E0 /* to 89EF */
#endif	/* _LKL_LINUX_SOCKIOS_H */
