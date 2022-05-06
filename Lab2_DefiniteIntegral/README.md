# Definite integral (MIPT MPI Lab Work 2)

## Contents

[Main task](#Main-task)

[Compile and execute](#Compile-and-execute)

[Calculation method](#Calculation-method)

[File description](#File-description)

## Main task

With the help of pthread, it is necessary to make a program that will calculate a definite integral of sin(1/x) function in the limit from a certain positive real number to some larger positive real number. It is necessary to balance the solution - the task execution time on all threads should be the same. So, the integration steps must be dynamic.

[:arrow_up: Back to contents](#Contents)

## Calculation method

![alt text](https://github.com/OborotovMikhail/MIPT_MPI/blob/main/Lab2_DefiniteIntegral/imageFormula.png?raw=true)

![alt text](https://github.com/OborotovMikhail/MIPT_MPI/blob/main/Lab2_DefiniteIntegral/imageTrapezoid.png?raw=true)

[:arrow_up: Back to contents](#Contents)

## File description



[:arrow_up: Back to contents](#Contents)

## Compile and execute

Compile and execute the code
```
gcc -pthread definiteIntegral.c integrate.c function.c -lm
./a.out
```

[:arrow_up: Back to contents](#Contents)