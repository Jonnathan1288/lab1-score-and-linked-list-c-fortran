# Lab 1: Score and Linked List

This project contains two small programs for learning data structures and numerical I/O:

- `linked_list/` - C code for a linked list implementation.
- `score/` - Score programs in C and Fortran.

The `linked_list` program demonstrates basic linked list operations in C. The `score` programs show how to read, process, and print a score value in both C and Fortran.

## Run the linked list C program

1. Open a terminal in the project root.
2. Compile the C program:

```powershell
cd linked_list
gcc linked_list.c -o linked_list.exe
```

3. Run the executable:

```powershell
./linked_list.exe
```

## Run the score C program

1. Open a terminal in the project root.
2. Compile the C program:

```powershell
cd score\c
gcc score.c -o score_c.exe
```

3. Run it:

```powershell
./score_c.exe
```

## Run the score Fortran program

1. Open a terminal in the project root.
2. Compile the Fortran program:

```powershell
cd score\fortran
gfortran score.f90 -o score_fortran.exe
```

3. Run it:

```powershell
./score_fortran.exe
```

## Notes

- Make sure you have `gcc` installed to compile C code.
- Make sure you have `gfortran` installed to compile Fortran code.
- If you are using a different environment, adapt the compile and run commands accordingly.
