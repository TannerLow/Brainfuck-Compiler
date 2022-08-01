# Brainfuck-Compiler
Compiler that reads Brainfuck source code and compiles it down to an executable on Windows.

---

# How to Use
1. Copy the contents of `x64/Debug` to another directory
2. Open CMD and locate that directory
3. Run this command: `"Brainfuck Compiler.exe" <source code file> [<size of memory array>]` (leaving memory size arg blank uses default of 2048)
4. If successful, run: `main.exe`
5. Optionally, you can check the value of the final memory cell with the command: `echo %errorlevel%`

## Provided Sample Usage
1. Open `x64/Debug` directory in CMD
2. Run the command: `"Brainfuck Compiler.exe" hello_world.bf 20`
3. Run the command: `main.exe`

## Usage in Visual Studio
1. Install Visual Studio
2. Open `.sln` file
3. Open project properties >> `Debugging` >> set `Command Arguments` to desired file and memory size
4. Save settings and run in Visual Studio

---

# How it Works
The program reads in the source code then parses it for instructions. The instructions are then fed to an Interpreter class that converts the source instructions to assembly code. A Compiler class then takes that assembly code and adds some necessary assembly code before and after for things like function prototypes and data commands such as creating the memory array for the source code to operate on. Once the full x86_64 assembly is generated, it is input into the ML64 assembler and linked via LINK (both provided by Microsoft). This then produces an executable for modern computers runnning Windows.
