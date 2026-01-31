	.file	"c-asm.c"
	.option nopic
	.attribute arch, "rv32i2p1_m2p0"
	.attribute unaligned_access, 0
	.attribute stack_align, 16
	.text
	.align	2
	.globl	piyush
	.type	piyush, @function
piyush:
	addi	sp,sp,-32
	sw	s0,28(sp)
	addi	s0,sp,32
	li	a5,1
	sw	a5,-20(s0)
	lw	a5,-20(s0)
	slli	a5,a5,1
	sw	a5,-24(s0)
	lw	a5,-20(s0)
	slli	a5,a5,3
	sw	a5,-24(s0)
	lw	a5,-20(s0)
	slli	a5,a5,31
	sw	a5,-24(s0)
	li	a5,33
	lw	a4,-20(s0)
	sll	a5,a4,a5
	sw	a5,-24(s0)
	li	a5,-2147483648
	sw	a5,-20(s0)
	lw	a5,-20(s0)
	srai	a5,a5,31
	sw	a5,-24(s0)
	li	a5,-2147483648
	sw	a5,-28(s0)
	lw	a5,-28(s0)
	srli	a5,a5,31
	sw	a5,-24(s0)
	nop
	lw	s0,28(sp)
	addi	sp,sp,32
	jr	ra
	.size	piyush, .-piyush
	.ident	"GCC: (13.2.0-11ubuntu1+12) 13.2.0"
