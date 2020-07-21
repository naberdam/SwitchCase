.section .text
.global switch2
switch2:
movq $0,%rax
subq $21,%rdx
cmpq $10,%rdx
ja .L7
jmp *.L9(,%rdx,8)
.L0:
movq (%rdi),%rbx
movq %rbx,(%rsi)
movq (%rsi),%rbx
movq %rbx,%rax
jmp .L8
.L1:
movq (%rsi),%rbx
addq %rbx,(%rdi)
movq (%rdi),%rbx
movq %rbx,%rax
jmp .L8
.L2:
.L3:
movq $59,%rbx
subq %rbx,(%rdi)
movq (%rdi),%rbx
subq %rbx,(%rsi)
jmp .L8
.L4:
movq $60,%rbx
addq %rbx,(%rdi)
.L5:
movq (%rsi),%rbx
imulq (%rdi),%rbx
movq %rbx,(%rdi)
movq (%rsi),%rbx
movq %rbx,%rax
movq %rax,%rbx
imulq %rax,%rbx
movq %rbx,%rax
jmp .L8
.L6:
movq (%rsi),%rbx
movq %rbx,%rax
movq (%rdi),%rcx
sarq %cl,%rax
jmp .L8
.L7:
movq $12,%rbx
movq %rbx,%rax
movq $3,%rcx
shlq %cl,%rax
.L8:
ret
.section .rodata
.align 8
.L9:
	.quad .L5
	.quad .L7
	.quad .L4
	.quad .L7
	.quad .L1
	.quad .L7
	.quad .L0
	.quad .L7
	.quad .L2
	.quad .L3
	.quad .L6
