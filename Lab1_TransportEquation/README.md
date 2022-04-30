# Transport equation (MIPT MPI Lab Work 1)

Main task:

Develop a sequential program and a parallel program (using MPI technology) that numerically solve the transfer equation according to the difference scheme in accordance with the individual variant.

____

## Contents

[Compile and execute](## Compile and execute)
____


## Compile and execute
Compile and execute **MPI version (parallel)** of transport equation solver
```
mpicc TransportEquation.c conditions.c calculateMethods.c
mpirun -np 4 ./a.out
python3 plotData.py 
```