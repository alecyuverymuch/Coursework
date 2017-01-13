#ifndef MATRIX_HPP
#define MATRIX_HPP  

#include <vector>

using namespace std;

//template <typename T>
class Matrix {
    
private:
    int rows;
    int cols;
    vector<vector<int>> mtx;
public:
    Matrix();
    Matrix(int rows, int cols);
    int getRows() const;
    int getCols() const;
    const vector<vector<int>> getMatrix() const;
    vector<int> &operator[](int index);
    const vector<int> &operator[](int index) const;
    friend ostream &operator<<(ostream &os, Matrix m);
    void checkDim (const Matrix m) const;
    void checkDimIn (const Matrix m) const;
    bool operator==(Matrix m) const;
    bool operator!=(Matrix m) const;
    const Matrix operator+(const Matrix m) const;
    const Matrix operator-(const Matrix m) const;
    const Matrix operator*(const Matrix m) const;
    friend Matrix operator*(int x, Matrix m); 
    friend Matrix operator*(Matrix m, int x); 
    Matrix &operator+=(const Matrix &m);
    Matrix &operator-=(const Matrix &m);
    Matrix &operator*=(const Matrix &m);
    Matrix &operator*=(int x);
};

//template <typename T>
Matrix::Matrix(){ 
    rows = 0;
    cols = 0;
}

//template <typename T>
Matrix::Matrix(int _rows, int _cols) : rows(_rows) , cols(_cols) {
    // TODO: fill this in later
    if (rows >= 0 && cols >= 0)
    {
        mtx = vector<vector<int>> (rows,vector<int>(cols));  
    }
    
}

//template <typename T>
int Matrix::getRows() const {
    return rows;
}

//template <typename T>
int Matrix::getCols() const {
    return cols;
}

//template <typename T>
const vector<vector<int>> Matrix::getMatrix() const {
    return mtx;
}

//template <typename T>
vector<int> &Matrix::operator[](int index) {
    return mtx[index];
}

//template <typename T>
const vector<int> &Matrix::operator[](int index) const {
    return mtx[index]; 
}

//template <typename T>
ostream &operator<<(ostream &os, Matrix m) {
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

//template <typename T>
void Matrix::checkDim (const Matrix m) const {
    if (this->rows!=m.getRows()||this->cols!=m.getCols())
    {
        abort();
    }
}

//template <typename T>
void Matrix::checkDimIn (const Matrix m) const {
    if (this->rows!=m.getCols())
    {
        abort();
    }
}

//template <typename T>
bool Matrix::operator==(Matrix m) const{
    return mtx==m.mtx;
}

//template <typename T>
bool Matrix::operator!=(Matrix m) const{
    return mtx!=m.mtx;
}

//template <typename T>
const Matrix Matrix::operator+(const Matrix m) const {
    checkDim(m);
    Matrix add(rows,cols);
    for (int r = 0; r < rows; r++)
    {
        for (int c = 0; c < cols; c++)
        {
            add[r][c] = mtx[r][c]+m[r][c];
        }
    }
    return add;
}

//template <typename T>
const Matrix Matrix::operator-(const Matrix m) const {
    checkDim(m);
    Matrix add(rows,cols);
    for (int r = 0; r < rows; r++)
    {
        for (int c = 0; c < cols; c++)
        {
            add[r][c] = mtx[r][c]-m[r][c];
        }
    }
    return add;
}

//template <typename T>
const Matrix Matrix::operator*(const Matrix m) const {
    checkDimIn(m);
    Matrix mult(rows, m.getCols());
    
    for (int r = 0; r < rows; r++)
    {
        for (int c = 0; c < m.getCols(); c++)
        {
            int p = 0;
            for (int x = 0; x < rows; x++)
            {
                p += mtx[r][x]*m[x][c];
            }
            mult[r][c] = p;
        }
    }
    return mult;
} 

//template <typename T>
Matrix &Matrix::operator+=(const Matrix &m) { 
    Matrix cam = *this + m; 
    this->mtx = cam.mtx; 
    return *this; 
} 

//template <typename T>
Matrix &Matrix::operator-=(const Matrix &m) { 
    Matrix csm = *this - m; 
    this->mtx = csm.mtx; 
    return *this; 
} 

//template <typename T>
Matrix operator*(int x, Matrix m) {
    Matrix mult(m.getRows(), m.getCols());
    for (int r = 0; r < mult.getRows(); r++) {
        for (int c = 0; c < mult.getCols(); c++) {
            mult[r][c] = x * m[r][c];
        }
    }
    return mult;
}

//template <typename T>
Matrix operator*(Matrix m, int x) {
    return x * m;
} 

//template <typename T>
Matrix &Matrix::operator*=(const Matrix &m) { 
    Matrix cmm = *this * m; 
    this->mtx = cmm.mtx; 
    return *this; 
} 

//template <typename T>
Matrix &Matrix::operator*=(int x) { 
    Matrix cmm = *this * x; 
    this->mtx = cmm.mtx; 
    return *this; 
} 


#endif //MATRIX_HPP
