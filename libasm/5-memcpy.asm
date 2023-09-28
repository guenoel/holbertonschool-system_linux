BITS 64
    global asm_memcpy

    section .text

asm_memcpy:
    push rbp             ; save base pointer before mov
    mov rbp, rsp         ; move top of stack to base pointer

    xor rax, rax         ; init rax (that will contain return value) to 0
    xor rcx, rcx         ; init rcx == cl (that will contain loop counter) to 0
    xor r8, r8           ;
    cmp rdx, 0           ;
    je .end              ;

.loop:
    cmp rdx, rcx                 ;
    je .end                      ;
    mov r8b, byte [rsi + rcx]    ;
    mov byte [rdi + rcx], r8b    ;
    inc rcx                      ;
    jmp .loop                    ;

.end:
    mov rax, rdi       ;
    mov rsp, rbp       ; move base pointer to top of stack
    pop rbp            ; free rbp pointer
    ret                ; return value of rax