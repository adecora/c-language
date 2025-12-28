	.file	"register.c"
	.option nopic
	.attribute arch, "rv64i2p1_m2p0_a2p1_f2p2_d2p2_c2p0_zicsr2p0"
	.attribute unaligned_access, 0
	.attribute stack_align, 16
	.text
	.align	1
	.globl	main
	.type	main, @function
main:
	addi	sp,sp,-16
	sd	s0,8(sp)
	sd	s1,0(sp)
	addi	s0,sp,16
	# Carga 10 en el registro s1
	li	s1,10
	# Suma una word (4 bytes - 32 bits, int) s1  y 1 en el registro a5
	addiw	a5,s1,1
	# sext.w (sign extend word) extiende con signo un valor de 32 bits a 64 bits, copiando el bit de signo a los 32 bits superiores
	# a5 se guarda en s1. El valor de i nunca solo se maneja en registros, no se pasa al stack!
	sext.w	s1,a5
	mv	a5,s1
	# Mueve el valor final de i a a0 que es el registro de retorno
	mv	a0,a5
	ld	s0,8(sp)
	ld	s1,0(sp)
	addi	sp,sp,16
	jr	ra
	.size	main, .-main
	.ident	"GCC: (13.2.0-11ubuntu1+12) 13.2.0"
