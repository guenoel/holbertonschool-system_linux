BITS 64
global asm_puts
    extern asm_strlen

    section .text

asm_puts:
    push rbp           ; save base pointer before mov
    mov rbp, rsp       ; move top of stack to base pointer

    push rdi           ; save rdi to stack

    call asm_strlen    ; call extern function
    mov rdx, rax       ; save len (stored in rax by strlen) in rdx

    mov rax, 1         ; syscall number for write (in x86-64 on Linux)
    mov rdi, 1         ; Standard Output File Descriptor
    mov rsi, [rsp]     ; put string from rsp (stack) to rsi (buffer)
    ; rdx set at line 12

    syscall            ; Call the write syscall to print the character

    mov rax, rdx       ; Value of rdx (original length) back to rax (return value of puts)
    pop rdi            ; remove rdi from stack
    mov rsp, rbp       ; move base pointer to top of stack
    pop rbp            ; free rbp pointer
    ret                ; return value of rax