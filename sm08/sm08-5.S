.text
.global main

main:
movl	$0,	%esi		# even
movl	$0,	%edi		# odd
read_and_check:
call    readi32                 # reading a number
jc      end                     # if (EOF): end

movl	%eax,	%ebx
testl   $1,	%ebx            # check odd/even
jz      is_even                 # четное (even)
is_odd:
addl    %ebx,	%edi
jmp     read_and_check
is_even:
addl    %ebx,   %esi
jmp     read_and_check
end:
movl	%esi,	%eax
call	writei32
call	nl
movl	%edi,	%eax
call	writei32
call	nl
    call	finish
