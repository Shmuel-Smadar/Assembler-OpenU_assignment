# Assembler-OpenU_assignment
##Prerequisites
C compiler (should be native on most linux systems)
##Building
```
git clone https://github.com/Shmuel-Smadar/Assembler-OpenU_assignment.git
cd Assembler-OpenU_assignment
make
```
If you've made any modifications, you should execute
```
make clean
```
before you compile again to delete all the .o files.
##usage
The assembler converts a predetermined assembly language into a specified machine code, utilizing a unique base-32 system.
The files intended for translation have a file extension of .as
to translate a file write:
```
./assembler some_file.as
```
