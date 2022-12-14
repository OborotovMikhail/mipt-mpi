# Transport equation (MIPT MPI lab 1)


## Contents

- [Main task](#main-task)
- [Compile and execute](#compile-and-execute)


## Main task

Develop a sequential program and a parallel program (using MPI technology) that numerically solve the transfer equation according to the difference scheme in accordance with the individual variant.

[:arrow_up: Back to contents](#contents)


## Compile and execute

Compile and execute **MPI version (parallel)** of transport equation solver
```
mpicc transport-equation.c conditions.c calculate-methods.c
mpirun -np 4 ./a.out
python3 plot-data.py 
```

[:arrow_up: Back to contents](#contents)