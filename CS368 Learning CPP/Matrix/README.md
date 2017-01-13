# Matrix
### Desciprtion
A Matrix class capable of storing any type and supports the operators =, +, -, *, +=, -=, *=, ==, !=, and <<.  
The operations supported by this Matrix class:  
1. Addition of 2 matrices using the + operator (e.g. result = m + n)  
2. Subtraction of 2 matrices using the - operator (e.g. result = m - n)  
3. Multiplication of 2 matrices using the * operator (e.g. result = m * n)  
4. Multiplication of a scalar with a matrix (e.g. result = m * 2)  
5. Compound Assignment of 2 matrices (+=, -=, *=)  
6. Multiplication Assignment of a scalar and a matrix (e.g. m *= 2)  
7. Array subscripting operator [], access the elements in the matrix using the following syntax:  
   `m[1][2] = 7;`  
8. Left Shift Operator <<, print a matrix using the following syntax:  
   `std::cout << m << std::endl;`  
### Compile and Run 
Compile using the following command:  
`$ g++ *.cpp -std=c++11`  
where *.cpp means ALL the .cpp files are to be compiled. You need not mention the names of the .hpp files since they are included from within the .cpp files. The option “-std=c++11” informs the compiler that our code may contain C++11 features.
Run with:  
`./a.out`
