.entry LOOP
.entry LENGTH
.extern m1
.extern L3
MAIN:	     mov S1.1 ,W,
	     add r2,STR
LOOP:	     jmp W
LOOP:	     mov S1.4 ,W
	     macro m1
	     	inc K
	     	mov S1.2 r3
	     endmacro
.extern LOOP
	     prn #-5
	     mov r1
	     sub r1,, r4
	     m1
	     bne L3
END:	     hlt #2
STR:	     .string "abcdef"
LENGTH:	     .data 6,-9,15
K:	     .data 22
S1:	     .struct 8, "ab"
