BITS 64
    global asm_strcmp

    section .text

asm_strcmp:
    push rbp      ; save base pointer before mov
    mov rbp, rsp  ; move top of stack to base pointer
    mov rax, 0    ; init rax (that contain return value) to 0

.loop:
    mov al, byte [rdi] ; Load the byte at the address pointed to by rdi in al
	mov bl, byte [rsi] ; Load the byte at the address pointed to by rsi in bl
    cmp al, bl         ; compare those 2 values
    jl .less           ; if result is less jump less
    jg .more           ; if result is more jump more
    je .equal          ; if result is equal jump equal

.equal:
    cmp al, 0          ; check if end of first string
    je .set_rax_to_0   ; if equal jump to end
    inc rdi            ; increment byte (letter) in rsi
    inc rsi            ; increment byte (letter) in rsi
    jmp .loop          ; back to loop

.less:
    mov rax, -1        ; return value to -1
    jmp .end           ; jump to end

.more:
    mov rax, 1         ; return value to -1
    jmp .end           ; jump to end

.set_rax_to_0:
    mov rax, 0         ; return value to 0
                       ; no need to jump to end

.end:
    mov rsp, rbp       ; move base pointer to top of stack
    pop rbp            ; free rbp pointer
    ret                ; return value of rax