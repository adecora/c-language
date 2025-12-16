	.file	"c-asm.c"
	.option nopic
	.attribute arch, "rv32i2p1"
	.attribute unaligned_access, 0
	.attribute stack_align, 16
	.text
	.align	2
	.globl	piyush
	.type	piyush, @function
piyush:
	addi	sp,sp,-16
	li	a5,10
	sw	a5,12(sp)
	lw	a5,12(sp)
	addi	a5,a5,1
	sw	a5,12(sp)
	lw	a5,12(sp)
	addi	a5,a5,10
	sw	a5,12(sp)
	lw	a0,12(sp)
	addi	sp,sp,16
	jr	ra
	.size	piyush, .-piyush
	.ident	"GCC: (13.2.0-11ubuntu1+12) 13.2.0"
