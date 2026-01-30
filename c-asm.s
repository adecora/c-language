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
	li	a5,3
	sw	a5,-20(s0)
	li	a5,5
	sw	a5,-24(s0)
	lw	a5,-20(s0)
	beq	a5,zero,.L2
	lw	a5,-24(s0)
	beq	a5,zero,.L2
	li	a5,1
	j	.L3
.L2:
	li	a5,0
.L3:
	sw	a5,-28(s0)
	lw	a5,-20(s0)
	bne	a5,zero,.L4
	lw	a5,-24(s0)
	beq	a5,zero,.L5
.L4:
	li	a5,1
	j	.L6
.L5:
	li	a5,0
.L6:
	sw	a5,-28(s0)
	lw	a5,-20(s0)
	seqz	a5,a5
	andi	a5,a5,0xff
	sw	a5,-28(s0)
	nop
	lw	s0,28(sp)
	addi	sp,sp,32
	jr	ra
	.size	piyush, .-piyush
	.ident	"GCC: (13.2.0-11ubuntu1+12) 13.2.0"
