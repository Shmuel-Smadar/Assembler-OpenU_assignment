;this file has first stage errors for the assembler
; illegal operands
W: mov illegal_label, r1
add W, 3 
bne W_
sub W, !@
lea W, 3, 4 
bne B.3
add F.4, G.5

;extra text
not W, #3, 4 
clr W, #3, 4 
inc W, #3, 4 
dec W, #3, 4 
jmp W, #3, 4 
bne W, #3, 4 
get W, #3, 4 
jsr W, #3, 4 
.string "this is a string" extra text
.struct 3, "string" extra text

;unfitting operands
mov #1, #4
add #1,  #4
sub #1, #4
not #1
clr #1
inc #1
dec #1
jmp #1
bne #1
get #1
jsr #1
lea r0, #4
lea #4 , r4

; empty label
label:

;illegal numbers
mov #23a, r1
cmp r1, #23a

;number out of range 
.data 1003
cmp r1, #600

;missing numbers
.data ,3
.data
cmp W, #

;illegal / missing comma/s
.struct 3,,
.struct 3 3

;illegal / missing string
.string "
.string 
.string blah


;illegal label name
_!@+: hlt

;declaring an already defined label as external
 hello: hlt
 .extern hello

;defining label that already declared as external
.extern G
G: hlt

;warning that b will be discarded
b: .extern c
g: .entry d

;missing label after ".entry" \ ".extern"
.extern
.entry

;defining label twice
R2: hlt
R2: hlt
