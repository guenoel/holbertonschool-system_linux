BITS 64
    global asm_putc

    section .text

asm_putc:
    push rbp             ; save base pointer before mov
    mov rbp, rsp         ; move top of stack to base pointer
    xor rax, rax         ; init rax (that will contain return value) to 0
    
    mov rax, 1           ; syscall number for write (in x86-64 on Linux)
    
    ; Arguments for the write syscall - write (int fd, void* buf, size_t cnt) buf -> rsi ?
    mov [rsi], rdi       ; Places the character (passed in RDI) in the memory address pointed to by RSI (buf argument of write)
    mov rdi, 1           ; Standard Output File Descriptor
    mov rdx, 1           ; Input data length (single character)

    syscall              ; Call the write syscall to print the character

.end:
    mov rsp, rbp       ; move base pointer to top of stack
    pop rbp            ; free rbp pointer
    ret                ; return value of rax