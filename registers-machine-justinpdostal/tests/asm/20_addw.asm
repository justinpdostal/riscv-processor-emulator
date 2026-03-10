0:	addiw x10,x0,1
4:	slli x10,x10,0x20
8:	addiw x11,x0,1
c:	slli x11,x11,0x20
10:	addi x11,x11,-1
14:	addi x12,x0,1
18:	addi x13,x0,-1
1c:	addw x14,x10,x12
20:	addw x15,x10,x13
24:	addw x16,x11,x12
28:	addi x17,x0,2
2c:	ecall
