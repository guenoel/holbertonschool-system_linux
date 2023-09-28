BITS 64
    global asm_strspn

    section .text

asm_strspn:
    push rbp           ; save base pointer before mov
    mov rbp, rsp       ; move top of stack to base pointer
    xor rax, rax       ; init rax (that contain return value) to 0
    xor rcx, rcx       ; init main_loop counter to 0
    xor rdx, rdx       ; init sec_loop counter to 0

.main_loop:
    mov al, byte [rdi + rcx] ; Load the byte at the address pointed to by rdi in al
    cmp al, 0          ; check if end of first string
    je .end            ; if NULL character go to end

.sec_loop:
	mov bl, byte [rsi + rdx] ; Load the byte at the address pointed to by rsi in bl
    inc rdx            ; increment sec_loop counter
    cmp bl, 0          ; check if end of second string
    je .end            ; if NULL character go to end
    cmp al, bl         ; compare values of char of first str and char of sec str
    je .equal          ; if result is equal jump equal
    jmp .sec_loop      ; else jump back to sec_loop

.equal:
    inc rcx            ; increment main_loop counter that will be returned at the end
    xor rdx, rdx       ; reset sec_loop counter to 0
    jmp .main_loop     ; back to main_loop

.end:
    mov rax, rcx       ; copy main_loop counter in return register
    mov rsp, rbp       ; move base pointer to top of stack
    pop rbp            ; free rbp pointer
    ret                ; return value of rax
