# Hashtable
cpp file name: cs564_p1.cpp  
### Compile and Run
To complile, type into the command line:  
g++ -std=c++11 -o cs564_p1 -Wall -g cs564_p1.cpp

or use the makefile by typing in:
make

To start the program, type (./cs564_p1) followed by the name of the data file to read from, for example:
./cs564_p1 data1.dat

How many buckets used?
The hash table implemented dynamically resizes the number of buckets used. 
It initially starts off with a table size of 13 (because prime numbers help reduce the number of collisions)
and doubles every time 70% or more of the total buckets are in use. 
For data1.dat, it uses 53,248 buckets.
data2.dat uses 26 buckets
data3.dat uses 13 buckets

