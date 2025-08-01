## Names
- Nate Webb cssc1467
- Noah Bakayou cssc1409

## Class Information
- CS480-02-Sum202

## Assignment Information
- Assignment #2 - basic shell

## Filename of This File
- README

---

## File Manifest
- xsh.cpp (Main)  
- xsh.h
- xsh.o (Generated on compile)
- xsh executable (Generated on compile)
- parser.cpp
- parser.h
- parser.o (Generated on compile)
- exec.cpp
- exec.h
- exec.o (Generated on compile)
- utils.cpp
- utils.h
- utils.o (Generated on compile)
- Makefile
- README


---

## Compile Instructions
- Run `make` in the project directory to build the program  
- Generates an executable named `xsh`
- Run  `make clean` to reset the compilation

---

## Operating Instructions
- Run `./xsh` on either account.
- No command-line arguments  
- Prompts user for command (Enter an executable with an argument or pipe or both)

---

## Design Decisions
- Seperated logic into 4 files
    - parser -> parses user input into commands, and splits them by pipes
    - utils  -> provides getter for the username and input
    - exec   -> Manages execution of commands
    - xsh    -> main control loop, exits on command "exit"

---

## Extra Features
- Preserve history

---

## Known Deficiencies or Bugs
- Error handling could be more advanced, handles many errors though, would need something really werid/nondeterministic to occur


---

## Lessons Learned
- Advanced string parsing
- execvp is useful for both PATH executables and executables entered by directory
- fork creates child processes
