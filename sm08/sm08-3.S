.text
.global main

main:
call    readi32                 # reading a number
cmpl    $0,     %eax
jl      end                     # if (number < 0): end
print_and_decrease:
push    %eax
call    writei32                # print number
call    nl                      # print \n
pop     %eax
decl    %eax                    # number -= 1
cmpl    $0,     %eax
jge     print_and_decrease      # if (number >= 0): continue
end:
call    finish
