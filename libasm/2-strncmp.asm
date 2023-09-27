BITS 64
    global asm_strncmp

    section .text

asm_strncmp:
    push rbp           ; save base pointer before mov
    mov rbp, rsp       ; move top of stack to base pointer
    xor rax, rax       ; init rax (that contain return value) to 0
    xor rcx, rcx       ; init loop counter to 0
    cmp rdx, 1         ; check n with 1
    jl .end            ; if less than 1 then n <= 0

.loop:
    mov al, byte [rdi + rcx] ; Load the byte at the address pointed to by rdi in al
	mov bl, byte [rsi + rcx] ; Load the byte at the address pointed to by rsi in bl

    cmp al, 0          ; check if end of first string
    je .str1_end       ; if equal go to str1_end
    cmp bl, 0          ; check if end of second string
    je .str2_end       ; if equal go to str2_end

    cmp al, bl         ; compare those 2 values
    jl .less           ; if result is less jump less
    jg .more           ; if result is more jump more
    je .equal          ; if result is equal jump equal

.equal:
    xor rax, rax       ; set return value to 0
    inc rcx            ; increment loop counter
    cmp rcx, rdx       ; compare loop counter with third argument
    jnz .loop          ; back to loop

.end:
    mov rsp, rbp       ; move base pointer to top of stack
    pop rbp            ; free rbp pointer
    ret                ; return value of rax

.less:
    mov rax, -1        ; return value to -1
    jmp .end           ; jump to end

.more:
    mov rax, 1         ; return value to 1
    jmp .end           ; jump to end

.str1_end:
    cmp bl, 0          ;
    jnz .less          ;
    jmp .end           ;

.str2_end:
    cmp al, 0          ;
    jnz .more          ;
    jmp .end           ;