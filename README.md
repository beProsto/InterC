# InterC Compiler and Interpreter
## InterC is going to be a c-like programming language, with a simple pipeline compiling it into InterCC (InterC Compiled), and then interpreting InterCC.
## For now I'm working on InterCC, and as soon as I'm done with it, I'm going to start working on InterC.

- To compile the InterCC interpreter, simply compile `main.cpp` using C++17
    - `g++ main.cpp -o intercc -std=c++17`
- To interpret the InterCC program, pass a path to it as an argument while running the interpreter
    - `./interc "test.icc"`