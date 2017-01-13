////////////////////////////////////////////////////////////////////////////////
// File Name:      Matrix.hpp
//
// Author:         Alec Yu
// CS email:       ayu@cs.wisc.edu
//
// Description:    The matrix header file for a4.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef MATRIX_HPP
#define MATRIX_HPP  

#include <vector>

using namespace std;

template <typename T>
class Matrix {
    
private:
    int rows;
    int cols;
    vector<vector<T>> mtx;
public:
    Matrix();
    Matrix(int rows, int cols);
    int getRows() const;
    int getCols() const;
    const vector<vector<T>> getMatrix() const;
    vector<T> &operator[](int index);
    const vector<T> &operator[](int index) const;
    template <class U>
    friend ostream &operator<<(ostream &os, Matrix<T> m);
    void checkDim (const Matrix<T> m) const;
    void checkDimIn (const Matrix<T> m) const;
    bool operator==(Matrix<T> m) const;
    bool operator!=(Matrix<T> m) const;
    const Matrix<T> operator+(const Matrix<T> m) const;
    const Matrix<T> operator-(const Matrix<T> m) const;
    const Matrix<T> operator*(const Matrix<T> m) const;
    template <class U>
    friend Matrix<U> operator*(U x, Matrix<U> m); 
    template <class U>
    friend Matrix<U> operator*(Matrix<U> m, U x); 
    Matrix<T> &operator+=(const Matrix<T> &m);
    Matrix<T> &operator-=(const Matrix<T> &m);
    Matrix<T> &operator*=(const Matrix<T> &m);
    Matrix<T> &operator*=(T x);
};

//Blank constructor
template <typename T>
Matrix<T>::Matrix(){ 
    rows = 0;
    cols = 0;
}

/**
 * constructor for a matrix with size row*col
 * @param _rows
 * @param _cols
 */
template <typename T>
Matrix<T>::Matrix(int _rows, int _cols) : rows(_rows) , cols(_cols) {
    //must be a valid matrix
    if (rows >= 0 && cols >= 0)
    {
        mtx = vector<vector<T>> (rows,vector<T>(cols));  
    }
    
}

/**
 * 
 * @return rows
 */
template <typename T>
int Matrix<T>::getRows() const {
    return rows;
}

/**
 * 
 * @return cols
 */
template <typename T>
int Matrix<T>::getCols() const {
    return cols;
}

/**
 * 
 * @return the 2d vector representing the matrix data
 */
template <typename T>
const vector<vector<T>> Matrix<T>::getMatrix() const {
    return mtx;
}

/**
 * the [] operator, accesses the data at a specified index
 * @param index
 * @return data at index
 */
template <typename T>
vector<T> &Matrix<T>::operator[](int index) {
    return mtx[index];
}

/**
 * const method for the [] operator
 * @param index
 * @return data at index
 */
template <typename T>
const vector<T> &Matrix<T>::operator[](int index) const {
    return mtx[index]; 
}

/**
 * the << operator prints out the contents of the matrix
 * @param os
 * @param m
 * @return 
 */
template <typename T>
ostream &operator<<(ostream &os, Matrix<T> m) {
    for (int r = 0; r < m.getRows(); r++) { 
        for (int c = 0; c < m.getCols(); c++) { 
            if (c > 0) { 
                os << " "; 
            }
            os << m.getMatrix()[r][c];
        } 
        os << endl; 
    } 
    return os;
} 

/**
 * checks the dimensions of a matrix to see of they match this one
 * if not, abort
 * @param m
 */
template <typename T>
void Matrix<T>::checkDim (const Matrix<T> m) const {
    if (this->rows!=m.getRows()||this->cols!=m.getCols())
    {
        abort();
    }
}

/**
 * checks if the inside dimensions of this matrix with another one match
 * if not, abort
 * @param m
 */
template <typename T>
void Matrix<T>::checkDimIn (const Matrix<T> m) const {
    if (this->rows!=m.getCols())
    {
        abort();
    }
}

/**
 * checks if the data in two matrixies are equal
 * @param m
 * @return true if equal
 */
template <typename T>
bool Matrix<T>::operator==(Matrix<T> m) const{
    return mtx==m.mtx;
}

/**
 * checks if two matricies are not equal
 * @param m
 * @return true if not equal
 */
template <typename T>
bool Matrix<T>::operator!=(Matrix<T> m) const{
    return mtx!=m.mtx;
}

/**
 * adds the contents of two matricies
 * @param m
 * @return the result of addition
 */
template <typename T>
const Matrix<T> Matrix<T>::operator+(const Matrix<T> m) const {
    checkDim(m);
    Matrix<T> add(rows,cols);
    for (int r = 0; r < rows; r++)
    {
        for (int c = 0; c < cols; c++)
        {
            add[r][c] = mtx[r][c]+m[r][c];
        }
    }
    return add;
}

/**
 * subtracts the contents of two matricies
 * @param m
 * @return result of subtraction
 */
template <typename T>
const Matrix<T> Matrix<T>::operator-(const Matrix<T> m) const {
    checkDim(m);
    Matrix<T> add(rows,cols);
    for (int r = 0; r < rows; r++)
    {
        for (int c = 0; c < cols; c++)
        {
            add[r][c] = mtx[r][c]-m[r][c];
        }
    }
    return add;
}

/**
 * multiplies two matricies
 * @param m
 * @return result of multiplication
 */
template <typename T>
const Matrix<T> Matrix<T>::operator*(const Matrix<T> m) const {
    checkDimIn(m);
    Matrix<T> mult(rows, m.getCols());
    for (int r = 0; r < rows; r++)
    {
        for (int c = 0; c < m.getCols(); c++)
        {
            T p = 0;
            for (int x = 0; x < rows; x++)
            {
                p += mtx[r][x]*m[x][c];
            }
            mult[r][c] = p;
        }
    }
    return mult;
} 

/**
 * compound addition on two matricies
 * @param m
 * @return result of compound addition
 */
template <typename T>
Matrix<T> &Matrix<T>::operator+=(const Matrix<T> &m) { 
    Matrix<T> cam = *this + m; 
    this->mtx = cam.mtx; 
    return *this; 
} 

/**
 * compound subtraction of 2 matricies
 * @param m
 * @return result of compound subtraction
 */
template <typename T>
Matrix<T> &Matrix<T>::operator-=(const Matrix<T> &m) { 
    Matrix<T> csm = *this - m; 
    this->mtx = csm.mtx; 
    return *this; 
} 

/**
 * multiplies a matrix by a scalar
 * @param x
 * @param m
 * @return result of multplication by scalar
 */
template <class U>
Matrix<U> operator*(U x, Matrix<U> m){
    Matrix<U> mult(m.getRows(), m.getCols());
    for (int r = 0; r < mult.getRows(); r++) {
        for (int c = 0; c < mult.getCols(); c++) {
            mult[r][c] = x * m[r][c];
        }
    }
    return mult;
}

/**
 * multiplies a matrix by a scalar
 * @param m
 * @param x
 * @return result of multiplication by scalar
 */
template <class U>
Matrix<U> operator*(Matrix<U> m, U x) {
    return x * m;
} 

/**
 * compound multiplication on 2 matricies
 * @param m
 * @return result of compound multiplication
 */
template <typename T>
Matrix<T> &Matrix<T>::operator*=(const Matrix<T> &m) { 
    Matrix<T> cmm = *this * m; 
    this->mtx = cmm.mtx; 
    return *this; 
} 

/**
 * compound multiplication of a matrix with a scalar
 * @param x
 * @return result of compound multiplication
 */
template <typename T>
Matrix<T> &Matrix<T>::operator*=(T x) { 
    Matrix<T> cmm = *this * x; 
    this->mtx = cmm.mtx; 
    return *this; 
} 


#endif //MATRIX_HPP