BITS 64
    global asm_strstr

    section .text

asm_strstr:
    push rbp           ; save base pointer before mov
    mov rbp, rsp       ; move top of stack to base pointer

    xor rax, rax       ; init rax (that will contain return value) to 0
    xor rdx, rdx       ; init rdx == dl (that will contain a letter of needle) to 0
    xor rbx, rbx       ; init rdx == dl (that will contain a letter of haystack) to 0
    cmp rsi, 0         ;
    je .empty_needle   ;
    cmp rdi, 0         ;
    je .not_found      ;

.init_needle:
    xor rcx, rcx       ; init rcx (that will contain loop counter) to 0
    mov dl, byte [rsi + rcx]; Load the byte at the address pointed to by rsi in rdx

.loop:
    mov bl, byte [rdi] ; Load the byte at the address pointed to by rdi in al

    cmp bl, dl         ; compare those 2 values
    je .store_ptr      ; if result is equal jump store_ptr

    cmp bl, 0          ; check if end of first string
    je .not_found      ; if equal go to str1_end

    inc rdi            ; increment loop counter
    jmp .loop          ; jump .loop

.store_ptr:
    lea rax, [rdi]     ; Store the effective memory address from an operand to a register
                       ; no need to jump to loop_equal

.loop_equal:
    inc rcx            ;
    mov dl, byte [rsi + rcx];
    inc rdi            ;
    mov bl, byte [rdi] ;
    cmp dl, 0          ;
    je .end            ;
    cmp bl, dl         ; compare those 2 values
    je .loop_equal     ; if result is equal jump equal
    jmp .init_needle   ;

.empty_needle:
    lea rax, [rdi]     ;
    jmp .end           ;

.not_found:
    xor rax, rax       ; set rax to 0

.end:
    mov rsp, rbp       ; move base pointer to top of stack
    pop rbp            ; free rbp pointer
    ret                ; return value of rax