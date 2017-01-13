# a.cpp
### Description 
This program performs the following:  
1. Reads a file (e.g. students.txt) with details about both graduate and undergraduate students and stores them in 2 separate vectors.  
2. Prints details of each student along with the student’s total score and grade.  
3. Performs some processing on the vectors of student objects / references and prints statistics about each type (grad / undergrad) of students.

### Compile and Run
Compile with Linux g++
`$ g++ *.cpp -std=c++11`  
where *.cpp means ALL the .cpp files are to be compiled. You need not mention the names of the .hpp files since they are included from within the .cpp files. The option “-std=c++11” informs the compiler that our code may contain C++11 features.  
Run using  
`$ ./a.out students.txt`
