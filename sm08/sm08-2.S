.data
A:      .int    0
B:      .int    0
C:      .int    0
D:      .int    0
R:      .int    0

.text
.global process, A, B, C, D, R

process:
push    %ebx

movl    A,      %eax
imull   B
movl    %eax,   %ebx
movl    C,      %eax
imull   D
subl    %eax,   %ebx
movl    %ebx,   R

pop     %ebx
ret
