    .global _vector_table
    .extern do_reset

    .weak   do_undefined_instruction
    .weak   do_software_interrupt
    .weak   do_prefetch_abort
    .weak   do_data_abort
    .weak   do_not_used
    .weak   do_irq
    .weak   do_fiq

    .section .text.arch.vectors, "ax", %progbits
    .arm

_vector_table:    
    ldr	pc, _reset_handle
	ldr	pc, _undefined_instruction_handle
	ldr	pc, _software_interrupt_handle
	ldr	pc, _prefetch_abort_handle
	ldr	pc, _data_abort_handle
	ldr	pc, _not_used_handle
	ldr	pc, _irq_handle
	ldr	pc, _fiq_handle

_reset_handle:	                .word do_reset
_undefined_instruction_handle:	.word do_undefined_instruction
_software_interrupt_handle:	    .word do_software_interrupt
_prefetch_abort_handle:	        .word do_prefetch_abort
_data_abort_handle:		        .word do_data_abort
_not_used_handle:		        .word do_not_used
_irq_handle:			        .word do_irq
_fiq_handle:			        .word do_fiq

    .balignl 16,0xdeadbeef

    .align	5
do_undefined_instruction:
    b do_undefined_instruction

do_software_interrupt:
    b do_software_interrupt

do_prefetch_abort:
    b do_prefetch_abort

do_data_abort:
    b do_data_abort

do_not_used:
    b do_not_used

do_fiq:
    b do_fiq

do_irq:
    b do_irq

    .end
