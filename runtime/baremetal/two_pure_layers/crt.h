#define START	"outer"

#if 1
__asm__(
".option nocapmode\n\t"

"		lui	s6, 0x3\n\t"
"		add	s6, s6, 1600\n\t"
"		lc	ca6, 0(s6)\n\t"
"		cgettag t6, ca6\n\t"

"		lui	t3, 131072\n\t"
"		lla	t2, 111f\n\t"
"		add		t2, t2, t3\n\t"
"		cspecialr ct3, pcc\n\t"
"		csetaddr ct3, ct3, t2\n\t"
"		li	t2, 1\n\t"
"		csetflags ct3, ct3, t2\n\t"
"		cjr	ct3\n\t"
"111:\n\t"
".option capmode\n\t"
"	auipcc	cs5, 2\n\t"
"	clc	ca5, 578(cs5)\n\t"
"	cgettag		t5, ca5\n\t"
"	ebreak\n\t"
"	cjalr	ca3\n\t");

#endif

//    13d0: 17 26 00 00  	auipcc	ca2, 2
//	  13d4: 0f 26 a6 1b  	clc	ca2, 442(ca2)
//    13d8: d1 45        	addi	a1, zero, 20
//    13da: db 00 c6 fe  	cjalr	ca2


//    144a: 0f 26 a6 1b  	clc	ca2, 442(ca2)