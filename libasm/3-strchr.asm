BITS 64
    global asm_strchr

    section .text

asm_strchr:
    push rbp           ; save base pointer before mov
    mov rbp, rsp       ; move top of stack to base pointer

    xor rax, rax       ; init rax (that will contain return value) to 0
    xor rcx, rcx       ; init rcx (that will contain loop counter) to 0
    xor rdx, rdx       ; init rdx (that will contain a char) to 0

    mov rdx, rsi       ; Load the byte at the address pointed to by rsi in rdx

.loop:
    mov al, byte [rdi + rcx]; Load the byte at the address pointed to by rdi in al

    cmp al, dl         ; compare those 2 values
    je .equal          ; if result is equal jump equal

    cmp al, 0          ; check if end of first string
    je .not_found      ; if equal go to str1_end

    inc rcx            ; increment loop counter
    jmp .loop          ; jump .loop

.equal:
    lea rax, [rdi + rcx]; Store the effective memory address from an operand to a register
    jmp .end           ; jump .end

.not_found:
    xor rax, rax       ; set rax to 0

.end:
    mov rsp, rbp       ; move base pointer to top of stack
    pop rbp            ; free rbp pointer
    ret                ; return value of rax