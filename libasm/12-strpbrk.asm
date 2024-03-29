BITS 64
    global asm_strpbrk

    section .text

asm_strpbrk:
    push rbp           ; save base pointer before mov
    mov rbp, rsp       ; move top of stack to base pointer

    xor rax, rax       ; (al) init rax (that contain letter of 1st string or return value) to 0
    xor rbx, rbx       ; (bl) init rbx (that contain letter of 2nd string) to 0
    xor rcx, rcx       ; init main_loop counter to 0
    xor rdx, rdx       ; init sec_loop counter to 0

.main_loop:
    mov al, byte [rdi + rcx] ; Load the byte at the address pointed to by rdi in al
    cmp al, 0          ; check if end of first string
    je .not_found      ; if NULL character go to not_found

.sec_loop:
	mov bl, byte [rsi + rdx] ; Load the byte at the address pointed to by rsi in bl
    inc rdx            ; increment sec_loop counter
    cmp bl, 0          ; check if end of second string
    je .next_letter    ; if NULL character go to next_letter of first string
    cmp al, bl         ; compare values of char of first str and char of sec str
    je .found          ; if result is equal jump .found
    jmp .sec_loop      ; else jump back to sec_loop

.next_letter:
    xor rdx, rdx       ; reset counter of second string to 0
    inc rcx            ; increment counter of first string
    jmp .main_loop     ; jump to .main_loop

.not_found:
    xor rax, rax       ; set return value to 0
    jmp .end           ; go to end

.found:
    lea rax, [rdi + rcx]; set memory address of the found letter in first string

.end:
    mov rsp, rbp       ; move base pointer to top of stack
    pop rbp            ; free rbp pointer
    ret                ; return value of rax
