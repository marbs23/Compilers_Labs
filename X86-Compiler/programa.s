.data
print_fmt: .string "%ld\n" 
.text
.globl main
main:
pushq %rbp
movq %rsp, %rbp
movq $5, %rax
movq %rax, -8(%rbp)
movq $10, %rax
movq %rax, -16(%rbp)
movq $5, %rax
pushq %rax
movq $3, %rax
movq %rax, %rcx
popq %rax
addq %rcx, %rax
pushq %rax
movq $2, %rax
movq %rax, %rcx
popq %rax
addq %rcx, %rax
movq %rax, %rsi
leaq print_fmt(%rip), %rdi
call printf@PLT
movq $0, %rax
leave
ret
.section .note.GNU-stack,"",@progbits  