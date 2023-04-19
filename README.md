# SIC-XE-assembler

# introduction

The aim of our project is to implement a two pass SIC-XE assembler.I designed this assembler which can support all kinds of formats . The assembler I designed also supports Program relocation as well as many machine independent assembler features such as literals, symbol defining statements, expressions,  control section and program linking.

# Execution Flow
# input:
Assembler source program using the SIC-XE instruction set should be written in srcfile.txt
# output:

# Pass 1: 
In Pass-1, assembler generates a intermediate file for Pass-2
# Pass 2:
Pass 2 will generate a listing file containing the input assembly code and address, object code of each instruction and also it will generate an object programincluding following type of record: H, D, R, T, M and E types
# error
An error file is also generated displaying the errors in the assembly program (if any)

# Steps to run and Execute Assembler:
1)First we need to give input in srcfile.txt  
2) we have to compile “pass2.cpp” file by “g++ pass2.cpp -o pass2.exe” command  
3)so by running pass2.cpp file pass1 method will be called which was implemented in pass1.cpp file after running this pass1 function intermediate file will be generated which is given input to pass2 to get object code and object Program.
