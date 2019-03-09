# Semaphores-for-multithreading
The project makes use of semaphores to implement reusable barriers to implement barrier synchronization among the threads. 
The project aims at sorting integers which read in from a file locally and the number of integers are in the power of 2. 
Each thread compare two values and swap them if the condition is true.  

USAGE
  to compile the file execute the make command
  execute the rest of the code as follows:
     ./sort.exe "filename" -o/-r
     
     -o: the mode in which we can see the array cahnges in each stage and phase
     -r: th emode in which only the sorted array is visible
