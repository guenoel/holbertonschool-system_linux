BITS 64
    global asm_strlen

    section .text

asm_strlen:
    push rbp      ; save base pointer before mov
    mov rbp, rsp  ; move top of stack to base pointer
    mov rcx, 0    ; init loop counter to 0
    mov rax, 0    ; init rax (that contain return value) to 0


.loop_count:
    cmp byte [rdi + rcx], 0 ; comp char with 0 (null byte)
    je .end_of_string       ; if flag ZF (result of previous comp) is 0 (true) go to end_of_string
    inc rcx                 ; counter for loop or string
    jmp .loop_count         ; go to the same function again

.end_of_string:
    mov rax, rcx ; move result of counter to "return register"
    mov rsp, rbp ; move base pointer to top of stack
    pop rbp      ; free rbp pointer
    ret          ; return value