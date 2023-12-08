MAIN:	     mov S1.1 ,LENGTH
	     add r2,LENGTH
LOOP:	     jmp END
	     macro m1
 		mov S1.2 ,r3
	     endmacro

 	     prn #-8

	     m1
	     bne LOOP
END:	     hlt
STR:	     .string "hello"
LENGTH:	     .data 9,-9,1
K:	     .data 23
S1:	     .struct 5, "HD" 
