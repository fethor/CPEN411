	file	 "integrate.i"
data

; cc1 (2.7.2.2) arguments: -O -fdefer-pop -fomit-frame-pointer
; -fcse-follow-jumps -fcse-skip-blocks -fexpensive-optimizations
; -fthread-jumps -fstrength-reduce -funroll-loops -fwritable-strings
; -fpeephole -fforce-mem -ffunction-cse -finline-functions -finline
; -freg-struct-return -fdelayed-branch -frerun-cse-after-loop
; -fschedule-insns -fschedule-insns2 -fcommon -fgnu-linker -m88110 -m88100
; -m88000 -mno-ocs-debug-info -mno-ocs-frame-position -mcheck-zero-division

gcc2_compiled.:
	align	 8
@LC0:
	string	 "varargs function cannot be inline\000"
	align	 8
@LC1:
	string	 "function too large to be inline\000"
	align	 8
@LC2:
	string	 "function with large aggregate parameter cannot be"
	string	 " inline\000"
	align	 8
@LC3:
	string	 "no prototype, and parameter address used; cannot "
	string	 "be inline\000"
	align	 8
@LC4:
	string	 "address of an aggregate parameter is used; cannot"
	string	 " be inline\000"
	align	 8
@LC5:
	string	 "function too large to be inline\000"
text
	align	 8
	global	 _function_cannot_inline_p
_function_cannot_inline_p:
	subu	 r31,r31,64
	st	 r1,r31,48
	st.d	 r24,r31,40
	or	 r25,r0,r2
	st	 r23,r31,36
@Ltb0:
	ld	 r13,r25,8
	bsr.n	 _tree_last
	ld	 r2,r13,16
	or	 r24,r0,r2
	bsr.n	 _list_length
	ld	 r2,r25,52
	ld	 r13,r25,12
	extu	 r13,r13,1<9>
	mak	 r13,r13,0<4>
	addu	 r13,r13,8
	addu	 r2,r2,r13
	bcnd.n	 eq0,r24,@L22
	mak	 r23,r2,0<3>
	or.u	 r13,r0,hi16(_void_type_node)
	ld	 r12,r24,20
	ld	 r13,r13,lo16(_void_type_node)
	cmp	 r12,r12,r13
	bb0.n	 ne,r12,@L22
	or.u	 r2,r0,hi16(@LC0)
	br.n	 @L41
	or	 r2,r2,lo16(@LC0)
	align	 4
@L22:
	bsr	 _get_max_uid
	mak	 r13,r23,0<1>
	cmp	 r2,r2,r13
	bb0.n	 gt,r2,@L23
	or.u	 r2,r0,hi16(@LC1)
	br.n	 @L41
	or	 r2,r2,lo16(@LC1)
	align	 4
@L23:
	ld	 r2,r25,52
	bcnd	 eq0,r2,@L25
@L27:
	ld	 r12,r2,8
	ld.bu	 r13,r12,28
	cmp	 r13,r13,26
	bb0	 ne,r13,@L42
	bcnd	 ne0,r24,@L29
	ld	 r13,r2,12
	bb1	 (31-17),r13,@L43
@L29:
	ld.bu	 r13,r12,12
	subu	 r13,r13,19
	mask	 r13,r13,0xff
	cmp	 r13,r13,1
	bb1	 hi,r13,@L26
	ld	 r13,r2,64
	ld.hu	 r13,r0,r13
	cmp	 r13,r13,37
	bb0	 ne,r13,@L44
@L26:
	ld	 r2,r2,4
	bcnd	 ne0,r2,@L27
@L25:
	bsr	 _get_max_uid
	cmp	 r2,r2,r23
	bb0.n	 gt,r2,@L41
	or	 r2,r0,0
	bsr.n	 _get_first_nonparm_insn
	or	 r25,r0,0
	cmp	 r13,r2,0
	br.n	 @L47
	cmp	 r12,r25,r23
	align	 4
@L36:
	ld.hu	 r12,r0,r2
	subu	 r13,r12,13
	mask	 r13,r13,0xffff
	cmp	 r13,r13,1
	bb1.n	 ls,r13,@L38
	mask	 r13,r12,0xffff
	cmp	 r13,r13,15
	bb1	 ne,r13,@L35
@L38:
	addu	 r25,r25,1
@L35:
	ld	 r2,r2,12
	cmp	 r12,r25,r23
	cmp	 r13,r2,0
@L47:
	rot	 r11,r13,28
	and.c	 r13,r12,r11
	extu	 r13,r13,1<lt>
	bcnd.n	 ne0,r13,@L36
	cmp	 r13,r25,r23
	bb0.n	 ge,r13,@L32
	or.u	 r2,r0,hi16(@LC5)
	br.n	 @L41
	or	 r2,r2,lo16(@LC5)
	align	 4
@L42:
	or.u	 r2,r0,hi16(@LC2)
	br.n	 @L41
	or	 r2,r2,lo16(@LC2)
	align	 4
@L43:
	or.u	 r2,r0,hi16(@LC3)
	br.n	 @L41
	or	 r2,r2,lo16(@LC3)
	align	 4
@L44:
	or.u	 r2,r0,hi16(@LC4)
	br.n	 @L41
	or	 r2,r2,lo16(@LC4)
	align	 4
@L32:
	or	 r2,r0,0
@L41:
@Lte0:
	ld	 r1,r31,48
	ld	 r23,r31,36
	ld.d	 r24,r31,40
	jmp.n	 r1
	addu	 r31,r31,64

	align	 8
	global	 _save_for_inline
_save_for_inline:
	subu	 r31,r31,128
	st.d	 r24,r31,72
	or.u	 r25,r0,hi16(_return_label)
	ld	 r13,r25,lo16(_return_label)
	st	 r1,r31,84
	st	 r30,r31,80
	st.d	 r22,r31,64
	st.d	 r20,r31,56
	st.d	 r18,r31,48
	st.d	 r16,r31,40
	addu	 r30,r31,80
	st.d	 r14,r31,32
@Ltb1:
	bcnd.n	 ne0,r13,@L49
	st	 r2,r30,12
	bsr	 _gen_label_rtx
	bsr.n	 _emit_label
	st	 r2,r25,lo16(_return_label)
@L49:
	bsr.n	 _max_label_num
	or.u	 r25,r0,hi16(_max_parm_reg)
	bsr.n	 _get_first_label_num
	or	 r15,r0,r2
	bsr.n	 _max_parm_reg_num
	st	 r2,r30,36
	bsr.n	 _max_reg_num
	st	 r2,r25,lo16(_max_parm_reg)
	ld	 r4,r25,lo16(_max_parm_reg)
	mak	 r4,r4,0<2>
	addu	 r13,r4,15
	and	 r13,r13,0xfff0
	or.u	 r25,r0,hi16(_parmdecl_map)
	subu	 r31,r31,r13
	st	 r2,r30,44
	addu	 r2,r31,32
	or	 r3,r0,0
	bsr.n	 _memset
	st	 r2,r25,lo16(_parmdecl_map)
	ld	 r14,r30,12
	ld	 r12,r14,52
	bcnd.n	 eq0,r12,@L51
	or.u	 r8,r0,0x10
	or.u	 r7,r0,0xffef
	or	 r7,r7,0xffff
	ld	 r10,r25,lo16(_parmdecl_map)
	or.u	 r9,r0,0x4
@L53:
	ld	 r11,r12,64
	ld.hu	 r13,r0,r11
	cmp	 r13,r13,34
	bb1	 ne,r13,@L54
	ld	 r13,r11,4
	st	 r12,r10[r13]
	ld	 r13,r12,12
	br.n	 @L123
	and	 r13,r13,r7
	align	 4
@L54:
	ld	 r13,r12,12
	or	 r13,r13,r8
@L123:
	st	 r13,r12,12
	ld	 r13,r12,12
	or	 r13,r13,r9
	st	 r13,r12,12
	ld	 r12,r12,4
	bcnd	 ne0,r12,@L53
@L51:
	ld	 r4,r30,36
	or.u	 r13,r0,hi16(_max_parm_reg)
	ld	 r7,r30,44
	or	 r2,r0,0
	ld	 r6,r13,lo16(_max_parm_reg)
	or.u	 r13,r0,hi16(_current_function_args_size)
	or	 r3,r0,0
	ld	 r8,r13,lo16(_current_function_args_size)
	bsr.n	 _gen_inline_header_rtx
	or	 r5,r0,r15
	st	 r2,r30,20
	ld	 r16,r2,4
	bsr.n	 _preserve_data
	st	 r16,r30,28
	bsr	 _get_insns
	or	 r22,r0,r2
	ld.hu	 r13,r0,r22
	cmp	 r13,r13,18
	bb0	 ne,r13,@L57
	bsr	 _abort
	align	 4
@L57:
	bsr.n	 _rtx_alloc
	or	 r2,r0,18
	ld	 r13,r22,16
	ld	 r14,r30,44
	or	 r17,r0,r2
	st	 r13,r17,16
	ld	 r13,r22,20
	st	 r13,r17,20
	ld	 r13,r22,4
	or.u	 r12,r0,hi16(_rtx_length+136)
	or	 r18,r0,r17
	st	 r13,r17,4
	mak	 r13,r14,0<2>
	st	 r0,r17,8
	addu	 r13,r13,19
	st	 r0,r17,12
	and	 r13,r13,0xfff0
	subu	 r24,r14,1
	subu	 r31,r31,r13
	ld	 r13,r12,lo16(_rtx_length+136)
	or.u	 r12,r0,hi16(_reg_map)
	addu	 r21,r31,32
	st	 r21,r12,lo16(_reg_map)
	mak	 r13,r13,0<2>
	cmp	 r12,r24,55
	bb0.n	 gt,r12,@L59
	addu	 r3,r13,4
	or.u	 r12,r0,hi16(_maybepermanent_obstack)
	or	 r13,r0,55
	or	 r23,r0,r3
	subu	 r13,r13,r24
	bb0.n	 (31-31),r13,@L61
	or	 r25,r12,lo16(_maybepermanent_obstack)
	ld	 r13,r25,12
	ld	 r12,r25,16
	addu	 r13,r13,r23
	cmp	 r13,r13,r12
	bb1.n	 ls,r13,@L125
	or.u	 r13,r0,hi16(_regno_reg_rtx)
	bsr.n	 __obstack_newchunk
	or	 r2,r0,r25
	or.u	 r13,r0,hi16(_regno_reg_rtx)
@L125:
	ld	 r13,r13,lo16(_regno_reg_rtx)
	ld	 r2,r25,12
	ld	 r3,r13[r24]
	bsr.n	 _memcpy
	or	 r4,r0,r23
	ld	 r13,r25,12
	ld	 r12,r25,24
	ld	 r11,r25,4
	addu	 r13,r13,r23
	ld	 r9,r25,16
	addu	 r10,r13,r12
	and.c	 r12,r10,r12
	st	 r13,r25,12
	subu	 r13,r12,r11
	subu	 r11,r9,r11
	st	 r12,r25,12
	cmp	 r13,r13,r11
	ld	 r12,r25,8
	bb0	 gt,r13,@L112
	st	 r9,r25,12
@L112:
	ld	 r13,r25,12
	ld	 r16,r30,44
	st	 r13,r25,8
	st	 r12,r21[r24]
	subu	 r24,r16,2
	cmp	 r13,r24,55
	bb0	 gt,r13,@L59
@L61:
	ld	 r13,r25,12
	ld	 r12,r25,16
	addu	 r13,r13,r23
	or.u	 r20,r0,hi16(_reg_map)
	cmp	 r13,r13,r12
	ld	 r21,r20,lo16(_reg_map)
	bb1.n	 ls,r13,@L115
	or	 r2,r0,r25
	bsr.n	 __obstack_newchunk
	or	 r3,r0,r23
@L115:
	or.u	 r19,r0,hi16(_regno_reg_rtx)
	ld	 r13,r19,lo16(_regno_reg_rtx)
	ld	 r2,r25,12
	ld	 r3,r13[r24]
	bsr.n	 _memcpy
	or	 r4,r0,r23
	ld	 r13,r25,12
	ld	 r12,r25,24
	ld	 r10,r25,4
	addu	 r13,r13,r23
	ld	 r9,r25,16
	addu	 r11,r13,r12
	and.c	 r12,r11,r12
	st	 r13,r25,12
	subu	 r13,r12,r10
	subu	 r10,r9,r10
	st	 r12,r25,12
	cmp	 r13,r13,r10
	ld	 r12,r25,8
	bb0	 gt,r13,@L116
	st	 r9,r25,12
@L116:
	ld	 r13,r25,12
	st	 r13,r25,8
	st	 r12,r21[r24]
	ld	 r13,r25,12
	ld	 r12,r25,16
	addu	 r13,r13,r23
	cmp	 r13,r13,r12
	ld	 r20,r20,lo16(_reg_map)
	bb1.n	 ls,r13,@L119
	subu	 r21,r24,1
	or	 r2,r0,r25
	bsr.n	 __obstack_newchunk
	or	 r3,r0,r23
@L119:
	ld	 r13,r19,lo16(_regno_reg_rtx)
	ld	 r2,r25,12
	ld	 r3,r13[r21]
	bsr.n	 _memcpy
	or	 r4,r0,r23
	ld	 r13,r25,12
	or	 r10,r0,r25
	addu	 r13,r13,r23
	st	 r13,r25,12
	ld	 r12,r10,24
	ld	 r11,r10,4
	addu	 r13,r13,r12
	ld	 r9,r10,16
	and.c	 r12,r13,r12
	subu	 r13,r12,r11
	subu	 r11,r9,r11
	st	 r12,r10,12
	cmp	 r13,r13,r11
	ld	 r12,r10,8
	bb0	 gt,r13,@L120
	st	 r9,r10,12
@L120:
	ld	 r13,r25,12
	subu	 r24,r24,2
	st	 r13,r25,8
	cmp	 r13,r24,55
	bb1.n	 gt,r13,@L61
	st	 r12,r20[r21]
@L59:
	ld	 r14,r30,44
	or.u	 r13,r0,hi16(_regno_reg_rtx)
	ld	 r2,r13,lo16(_regno_reg_rtx)
	or.u	 r13,r0,hi16(_reg_map)
	subu	 r4,r14,56
	ld	 r3,r13,lo16(_reg_map)
	mak	 r4,r4,0<2>
	addu	 r2,r2,224
	bsr.n	 _memcpy
	addu	 r3,r3,224
	ld	 r16,r30,36
	subu	 r10,r15,r16
	mak	 r13,r10,0<2>
	addu	 r13,r13,15
	ld	 r24,r30,36
	and	 r13,r13,0xfff0
	subu	 r31,r31,r13
	mak	 r12,r24,0<2>
	addu	 r13,r31,32
	or.u	 r11,r0,hi16(_label_map)
	subu	 r13,r13,r12
	cmp	 r12,r24,r15
	bb0.n	 lt,r12,@L68
	st	 r13,r11,lo16(_label_map)
	mask	 r12,r10,3
	bcnd.n	 eq0,r12,@L70
	or	 r23,r0,r11
	cmp	 r13,r12,1
	bb0.n	 gt,r13,@L90
	cmp	 r13,r12,2
	bb0	 gt,r13,@L91
	bsr	 _gen_label_rtx
	ld	 r13,r23,lo16(_label_map)
	st	 r2,r13[r24]
	addu	 r24,r24,1
@L91:
	bsr	 _gen_label_rtx
	ld	 r13,r23,lo16(_label_map)
	st	 r2,r13[r24]
	addu	 r24,r24,1
@L90:
	bsr	 _gen_label_rtx
	ld	 r13,r23,lo16(_label_map)
	st	 r2,r13[r24]
	addu	 r24,r24,1
	cmp	 r12,r24,r15
	bb0	 lt,r12,@L68
@L70:
	bsr.n	 _gen_label_rtx
	addu	 r25,r24,3
	ld	 r13,r23,lo16(_label_map)
	bsr.n	 _gen_label_rtx
	st	 r2,r13[r24]
	ld	 r12,r23,lo16(_label_map)
	addu	 r13,r24,1
	bsr.n	 _gen_label_rtx
	st	 r2,r12[r13]
	addu	 r12,r24,2
	ld	 r13,r23,lo16(_label_map)
	addu	 r24,r24,4
	bsr.n	 _gen_label_rtx
	st	 r2,r13[r12]
	ld	 r13,r23,lo16(_label_map)
	cmp	 r12,r24,r15
	bb1.n	 lt,r12,@L70
	st	 r2,r13[r25]
@L68:
	ld	 r14,r30,28
	mak	 r4,r14,0<2>
	addu	 r13,r4,15
	and	 r13,r13,0xfff0
	subu	 r31,r31,r13
	or.u	 r13,r0,hi16(_insn_map)
	addu	 r2,r31,32
	or	 r3,r0,0
	bsr.n	 _memset
	st	 r2,r13,lo16(_insn_map)
@L124:
	ld	 r22,r22,12
	bcnd	 eq0,r22,@L73
	ld.hu	 r2,r0,r22
	or.u	 r13,r0,hi16(_orig_asm_operands_vector)
	st	 r0,r13,lo16(_orig_asm_operands_vector)
	or.u	 r13,r0,hi16(_copy_asm_operands_vector)
	cmp	 r12,r2,16
	bb0.n	 ne,r12,@L83
	st	 r0,r13,lo16(_copy_asm_operands_vector)
	bb1.n	 ls,r12,@L86
	cmp	 r13,r2,17
	bb0.n	 ne,r13,@L82
	cmp	 r13,r2,18
	bb1	 ne,r13,@L84
	ld	 r13,r22,20
	addu	 r13,r13,6
	bcnd	 eq0,r13,@L124
	bsr.n	 _rtx_alloc
	or	 r2,r0,18
	ld	 r13,r22,16
	or	 r25,r0,r2
	st	 r13,r25,16
	ld	 r13,r22,20
	br.n	 @L76
	st	 r13,r25,20
	align	 4
@L86:
	cmp	 r13,r2,13
	bb1	 lo,r13,@L84
	bsr	 _rtx_alloc
	or	 r25,r0,r2
	bsr.n	 _copy_for_inline
	ld	 r2,r22,16
	st	 r2,r25,16
	subu	 r13,r0,1
	st	 r13,r25,20
	st	 r0,r25,24
	bsr.n	 _copy_for_inline
	ld	 r2,r22,28
	br.n	 @L76
	st	 r2,r25,28
	align	 4
@L82:
	or.u	 r13,r0,hi16(_label_map)
	ld	 r12,r22,16
	ld	 r13,r13,lo16(_label_map)
	ld	 r25,r13[r12]
	br	 @L76
	align	 4
@L83:
	bsr.n	 _rtx_alloc
	or	 r2,r0,16
	br.n	 @L76
	or	 r25,r0,r2
	align	 4
@L84:
	bsr	 _abort
	align	 4
@L76:
	ld	 r13,r22,4
	st	 r13,r25,4
	or.u	 r13,r0,hi16(_insn_map)
	ld	 r12,r22,4
	ld	 r13,r13,lo16(_insn_map)
	st	 r25,r13[r12]
	st	 r25,r18,12
	st	 r18,r25,8
	br.n	 @L124
	or	 r18,r0,r25
	align	 4
@L73:
	bsr.n	 _get_first_nonparm_insn
	st	 r0,r18,12
	ld	 r16,r30,20
	bsr.n	 _get_insns
	st	 r2,r16,12
	ld	 r14,r30,12
	st	 r2,r16,16
	bsr.n	 _get_frame_size
	st	 r16,r14,72
	or.u	 r13,r0,hi16(_parmdecl_map)
	st	 r2,r14,68
	st	 r0,r13,lo16(_parmdecl_map)
	or.u	 r13,r0,hi16(_label_map)
	st	 r0,r13,lo16(_label_map)
	or.u	 r13,r0,hi16(_reg_map)
	st	 r0,r13,lo16(_reg_map)
	or	 r2,r0,r17
	ld	 r13,r14,12
	or.u	 r12,r0,hi16(_return_label)
	or	 r3,r0,r18
	st	 r0,r12,lo16(_return_label)
	or	 r13,r13,512
	bsr.n	 _set_new_first_and_last_insn
	st	 r13,r14,12
@Lte1:
	subu	 r31,r30,80
	ld	 r1,r31,84
	ld	 r30,r31,80
	ld.d	 r24,r31,72
	ld.d	 r22,r31,64
	ld.d	 r20,r31,56
	ld.d	 r18,r31,48
	ld.d	 r16,r31,40
	ld.d	 r14,r31,32
	jmp.n	 r1
	addu	 r31,r31,128

