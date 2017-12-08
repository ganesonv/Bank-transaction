# Bank-transaction
Bank transaction using Doubly Circular Linked List in C

The job is to read in a tfile one line at a time. 
For each line, you need to check if it has the correct format. If the line is malformed, you should print an error message and quit your program. Otherwise, you should convert the line into an internal object/data structure, and insert the object/data structure into a list, sorted by the timestamp. If there is another object/data structure with identical timestamp, you should print an error message and quit your program.


After all the input lines are processed, you should output all the transcations in ascending order, according to their timestamps.



BUILD:

To build, a Makefile is used.
Please type "make" in the command line.
To delete the previously created .o files and executables, use "make clean".
Then use "make"
