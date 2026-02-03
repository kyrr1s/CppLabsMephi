# CppLabsMephi
My c++ projects (labs) from Mephi course

## Description to projects
All descriptions are in corresponding dirs.

### Lab1
Process a sparse integer matrix from input. For each row, extract the sub-sequence between the first positive and first negative element (order preserved). If one condition is missing, take elements to the end of the row. Skip rows containing only zeros. Print both original and resulting matrices.

### Lab2
A C++ class implementing the Bernoulli Lemniscate curve, defined by focal distance parameter c. The class provides methods to calculate polar radius, curvature radius (as functions of angle and radius), polar sector area, and total area, along with constructors and accessors. Includes an interactive test program.

### Lab3
A C++ class representing a digital logic element, defined by an array of terminal descriptors (structs). Each descriptor stores terminal type (input/output), connection count (max 1 for input, max 3 for output), and signal state (0, 1, or X). The class provides constructors (default inverter, configurable I/O counts, array initialization), methods to get/set terminal states and connection counts, add terminals, and I/O operations.

### Lab4
A Tower Defence game on SFML engine.

### ExternalCode
A C++ class for representing large decimal integers (up to ~47 digits) stored as a static array of char digits in signed magnitude format, using two's complement for arithmetic operations. The class provides constructors (default, from long, from string), I/O stream operators, methods to get two's complement, perform addition and subtraction with sign handling, and operations for multiplying and dividing the number by 10.