# README - C Program Compilation and Execution

## Overview
This guide explains how to compile, execute, and test any C program.

## Compilation and Execution

### **1. Compiling a C Program**
To compile a C program, use `gcc` (GNU Compiler Collection) in a terminal:
```sh
gcc -o output_name source_file.c
```
For example, to compile `program.c`:
```sh
gcc -o program program.c
```
This command generates an executable file named `program`.

### **2. Running the Program**
Once compiled, execute the program using:
```sh
./program
```
Replace `program` with the name of your executable file.

## Testing the Program

### **Example Usage**
If your program takes user input, follow the prompts when executing it. Example:
```sh
./program
Enter a number: 5
The result is: 25
```

### **Error Handling**
If you get an error like:
```sh
bash: ./program: Permission denied
```
Try adding execution permissions:
```sh
chmod +x program
```

## Notes
- Ensure `gcc` is installed. You can check with:
  ```sh
  gcc --version
  ```
- Use `-Wall` to enable warnings for better debugging:
  ```sh
  gcc -Wall -o program program.c
  ```
- If using multiple source files:
  ```sh
  gcc -o program file1.c file2.c
  ```
- Run the program in debug mode with `gdb` if necessary:
  ```sh
  gdb ./program
  ```

