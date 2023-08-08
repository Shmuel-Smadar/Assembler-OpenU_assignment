;this file has second stage errors for the assembler:

;declaring label as entry without definition
.entry blah

;using non defined or declared as external labels 
mov P, Q