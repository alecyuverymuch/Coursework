# Modified Matrix
A Modified version of the Matrix class (see `https://github.com/alecyuverymuch/Coursework/tree/master/CS368%20Learning%20CPP/Matrix`)  
Modified to handle the following 3 types of exceptions: 
- InvalidDimension  
- IndexOutOfBounds  
- IncompatibleMatrices  
  
### InvalidDimension
When a Matrix with non-positive number of rows or non-positive number of columns (i.e. rows <= 0 or cols <= 0) is created.  

### IndexOutOfBounds
When someone tries to access the a row that is out of bounds.  
*Matrix class cannot detect if the number of columns is out of range when the array subscripting notation is used.  

### IncompatibleMatricies
When arithmetic operations (addition, subtraction, multiplication) are performed between incompatible matrices.

