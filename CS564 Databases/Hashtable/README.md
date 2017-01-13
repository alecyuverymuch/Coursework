# Hashtable
C++ file name: cs564_p1.cpp  
### Description
An implementation of a hashtable in C++. Accepts a csv document and adds its contents into a hashtable. Memory is dynamically allocated. Then the program outputs a datafile containing the keys of the entries along with the average of all the column 2 values and the ma of the column 3 values.  
### Input files
data1.dat  
data2.dat  
data3.dat  
*data1.dat and data2.dat have been modified due to excessivly large file sizes
### Compile and Run
To complile, type into the command line:  
`g++ -std=c++11 -o cs564_p1 -Wall -g cs564_p1.cpp`

or use the makefile by typing in:
`make`

To start the program, type `./cs564_p1` followed by the name of the data file to read from, for example:
`./cs564_p1 data1.dat`
### Analysis
How many buckets used?  
The hash table implemented dynamically resizes the number of buckets used.  
It initially starts off with a table size of 13 (because prime numbers help reduce the number of collisions)
and doubles every time 70% or more of the total buckets are in use.  
For data1.dat, it uses 53,248 buckets.  
data2.dat uses 26 buckets  
data3.dat uses 13 buckets  

