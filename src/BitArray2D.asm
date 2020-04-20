
        global  _set_bit_elem
        global  _get_bit_elem
        section .text

_set_bit_elem:
        push rbp            ; save the base pointer on the stack (at rsp+8)
        mov rbp, rsp        ; set up the rbp for the bottom of this frame

        ; rdi contains array pointer
        ; rsi contains row width
        ; rdx contains row
        ; rcx contains col

        mov r8, [rdi] ;create mask

        mov rax, rdx ;get i (A[i][j])
        imul rax, rsi ;compute i*row width
        add rax, rcx ;add column offset
        add rax, rdi ;add initial spot of array
        mov rax, [rax]
        mov rax, 1
        or rax, r8
        mov rdi, rax

        mov rsp, rbp        ; restore stack pointer to before we pushed parameters onto the stack
        pop rbp             ; remove rbp from the stack to restore rsp to initial value
        ret                 ; return value in rax




_get_bit_elem:
        push rbp            ; save the base pointer on the stack (at rsp+8)
        mov rbp, rsp        ; set up the rbp for the bottom of this frame

        ; rdi contains array pointer
        ; rsi contains row width
        ; rdx contains row
        ; rcx contains col


        mov rax, rdx ;get i (A[i][j])
        imul rax, rsi ;compute i*row width
        add rax, rcx ;add column offset
        add rax, rdi ;add initial spot of array

        mov rsp, rbp        ; restore stack pointer to before we pushed parameters onto the stack
        pop rbp             ; remove rbp from the stack to restore rsp to initial value
        ret                 ; return value in rax
