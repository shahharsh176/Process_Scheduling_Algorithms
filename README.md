There are three .c file and one process directory which we made.
.c Files: simulator.c , creatingreadyqueue.c,insoutput.c .
directory : processes(process1.txt,process2.txt,process3.txt,process4.txt)

Creatingreadyqueue.c : This file will create ready queue of the any algorithm which user will select. In every algorithm we need ready queue which will create this file.For each process this file create one process control block which will contains following variables ( ). This file will fetch the processes information from the “process” directory and will create ready queue for that processes.
Insoutput.c : This file will give output of process instruction which is stored in any file in the “processes” directory. This file takes instruction as an input parameter and decode that instruction and return the output of that instruction. 

Simulator.c : This file is main file of the project which contain all the algorithms which we implemented so user have to select the algorithm from the menu and execute that algorithm.This file contain c program for First Come First Serve (FCFS), Round Robin (RR),shortest job first (SJF) and Priority scheduling algorithm using threads.Threads will execute as user selected algorithm. In our case four threads will be created and each thread will fetch the instruction from respective file and send that instruction to “insoutput.c” and that instruction will be executed. We have assumed that one instruction will take one second to execute. 

Processes Directory : There are four files in this directory which contains different types of instructions like Add, Sub, Mul, Div and Modulo.

Assumptions :
Each instruction will take one second for execution.
Time slice for round robin algorithm is 1 second.

Platform:
Linux Operating System.

How to Run this program:

cc -pthread simulator.c
./a.out

After run the program:
Select one of algorithm which you want to run your processes.



