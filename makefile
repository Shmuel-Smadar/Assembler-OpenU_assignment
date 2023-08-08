assembler:  macro.o node.o linked_list.o first_pass.o second_pass.o parser.o base.o print.o compare.o label.o binary_line.o output_files.o store.o assembler.o
	gcc -g -ansi node.o linked_list.o parser.o macro.o first_pass.o second_pass.o base.o print.o compare.o label.o binary_line.o output_files.o store.o assembler.o -lm -o assembler
assembler.o: assembler.c assembler.h
	gcc -c -Wall -ansi -pedantic assembler.c -o assembler.o
base.o: base.c base.h
	gcc -c -Wall -ansi -pedantic base.c -o base.o
macro.o: macro.c macro.h
	gcc -c -Wall -ansi -pedantic macro.c -o macro.o
node.o: node.c node.h
	gcc -c -Wall -ansi -pedantic node.c -o node.o
linked_list.o: linked_list.c linked_list.h
	gcc -c -Wall -ansi -pedantic linked_list.c -o linked_list.o
first_pass.o: first_pass.c first_pass.h
	gcc -c -Wall -ansi -pedantic first_pass.c -o first_pass.o
second_pass.o: second_pass.c second_pass.h
	gcc -c -Wall -ansi -pedantic second_pass.c -o second_pass.o
parser.o: parser.c parser.h
	gcc -c -Wall -ansi -pedantic parser.c -o parser.o
print.o: print.c print.h
	gcc -c -Wall -ansi -pedantic print.c -o print.o
compare.o: compare.c compare.h
	gcc -c -Wall -ansi -pedantic compare.c -o compare.o
label.o: label.c label.h
	gcc -c -Wall -ansi -pedantic label.c -o label.o
binary_line.o: binary_line.c binary_line.h
	gcc -c -Wall -ansi -pedantic binary_line.c -o binary_line.o
output_files.o: output_files.c output_files.h
	gcc -c -Wall -ansi -pedantic output_files.c -o output_files.o
store.o: store.c store.h
	gcc -c -Wall -ansi -pedantic store.c -o store.o
clean:
	rm -f *.o *~ 



