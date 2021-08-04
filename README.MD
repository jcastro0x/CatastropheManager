# Catastrophe Manager
![screenshot](catastrophe.jpg)

## Summary
This if my first attemp to learn how **shared memory** works within O.S, primary focused to Linux systems (and checked in Arch Linux distro)

> The main idea behind this is to aim my progress into _SICE_, a partner company of _CAPITOLE CONSULTING_, since I'm gonna work there the next month.

Composed by two different programs:
- Generator
- Solver

The first, generates differente catastrophes into a shared memory readed by the second program, Solver, that will fix them.

Both programs are CLI programs, so you need to enter the correct commands to handle the catastrophes!

## Layout
### Generator and Solver
Since **shared memory** rely on the concept of have two or more programs interconnected by same memory region, `Catastrophe Manager` have two programs to emulate this concept:
- **Generator :** Write shared memory with castastrophes 
- **Solver    :** Writes/Read shared memort to detect and solve castastrophes created by ___Generator___

### Interpreter
The `interpreter` class uses a vector of `command` instances to check what action will execute. Both `generator` and `solver` uses it.

### Common
The `common` class works as DRY principle to both `generator` and `solver`. 
It's the class that holds all active catastrophes, and the functions to create and delete them.
Also  it's the responsable to create the **shared memory** object through boost library.

#### Type of Catastrophes
- Storm     
- Earthquake
- Volcano
- Flood
- WorldWar
- Godzilla

## Commands
Both programs can handle unix-like program arguments thorugh boot::program_options:

<pre>
v --verbose      : Print all operations to stdout
a --automatic    : Generate and resolve castastrophes automatically
--automatic-rate : (Default = 10 seconds) the amount of time to generate/resolve when --automatic flag are setted
</pre>

## Diagram
Below is the diagram of the program's structure.
`Interpreter` are the mainly class that manages all program stuffs. Stores the current commands that, thought pointer to Interpreter, can access to all other things (like other commands, options or memory manager).

`Interpreter` initalizes the default commands based on `options`. By default, the two modes had the same commands, except for the command `generate` that it's created only if `options` was initialized with --mode=generator, and command `solve` if was initialized with --mode=solver.
![screenshot](diagram.png)

## Credits
Developed by Javier Castro (www.jcastro0x.com | jcastro0x@gmail.com) with ❤️


---

_Powered by_ 
**Boost 1.76 and C++17**