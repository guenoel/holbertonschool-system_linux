BITS 64
    global asm_strcasecmp

    section .text

asm_strcasecmp:
    push rbp        ; save base pointer before mov
    mov rbp, rsp    ; move top of stack to base pointer
    xor rbx, rbx    ;
    xor rax, rax    ; init rax (that contain return value) to 0

.loop:
    mov al, byte [rdi] ; Load the byte at the address pointed to by rdi in al
    cmp al, 'A'        ;
    jl .sec_str_check  ;
    cmp al, 'Z'        ;
    jg .sec_str_check  ;
    add al, 32         ;

.sec_str_check:
	mov bl, byte [rsi] ; Load the byte at the address pointed to by rsi in bl
    cmp bl, 'A'        ;
    jl .compare_chars  ;
    cmp bl, 'Z'        ;
    jg .compare_chars  ;
    add bl, 32         ;

.compare_chars:
    sub bl, al         ;
    cmp bl, 0          ;
    je .equal          ; if result is equal jump equal
    jmp .end

.equal:
    cmp al, 0          ; check if end of first string
    je .end            ; if equal jump to end
    inc rdi            ; increment byte (letter) in rsi
    inc rsi            ; increment byte (letter) in rsi
    jmp .loop          ; back to loop

.end:
    mov al, bl         ;
    mov rsp, rbp       ; move base pointer to top of stack
    pop rbp            ; free rbp pointer
    ret                ; return value of rax