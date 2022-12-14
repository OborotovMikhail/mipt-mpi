# Definite integral (MIPT MPI Lab Work 2)

## Contents

[Main task](#Main-task)

[Compile and execute](#Compile-and-execute)

[Calculation method](#Calculation-method)

[File description](#File-description)

[Program output](#Program-output)

## Main task

With the help of pthread, it is necessary to make a program that will calculate a definite integral of sin(1/x) function in the limit from a certain positive real number to some larger positive real number. It is necessary to balance the solution - the task execution time on all threads should be the same.

[:arrow_up: Back to contents](#Contents)

## Calculation 

The program calculates the integral using trapezoidal rule. The trapezoidal rule works by approximating the region under the graph of the function f(x) as a trapezoid and calculating its area.
The formula used in this program is:

![alt text](https://github.com/OborotovMikhail/mipt-mpi/blob/master/lab-2-definite-integral/readme-images/formula.png? "The trapezoidal rule formula")

The illustration of trapezoidal rule:

![alt text](https://github.com/OborotovMikhail/mipt-mpi/blob/master/lab-2-definite-integral/readme-images/trapezoid.png? "The illustration of trapezoidal rule")

[:arrow_up: Back to contents](#Contents)

## File description

___definiteIntegral.c___ is the main file. It creates and joins threads, which calculate the integral. Then it prints the result.

___function.h___ and ___function.c___ contain the function to be integrated and its derivative. The function can be changed in the function.c file. By default the function is sin(1/x).

___integrate.h___ and ___integrate.c___ contain methods that do the actual calculation of the integral. There are two methods: single-thread version and multi-thread version.

___argStruct.h___ contains the stucture that is used to pass arguments to a thread when using multi-thread calculation.

___parameters.txt___ is used to set the parameters of the program and the integral. There are 4 parameters: 1) lower integral limit, 2) upped integral limit, 3) number of intervals of calculation, 4) number of threads to be created.

[:arrow_up: Back to contents](#Contents)

## Compile and execute

To compile and execute the code use:
```
gcc -pthread definiteIntegral.c integrate.c function.c -lm
./a.out
```

[:arrow_up: Back to contents](#Contents)

## Program output

An example of program output:

![alt text](https://github.com/OborotovMikhail/mipt-mpi/blob/master/lab-2-definite-integral/readme-images/output.png? "Program output")

[:arrow_up: Back to contents](#Contents)