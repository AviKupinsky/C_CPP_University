// Matrix.h

#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <fstream>

/**
 * @struct MatrixDims
 * @brief Matrix dimensions container. Used in MlpNetwork.h and in main.cpp.
 */
typedef struct matrix_dims
{
    int rows, cols;
} matrix_dims;


class Matrix{
    matrix_dims items{};
    float * matrix;
public:
    //the constructor section
    Matrix (int rows, int cols);
    Matrix();
    static float * matrix_aloc(int rows,int cols);

    // the operator section
    Matrix (Matrix const &other);
    float operator[](unsigned int idx) const;
    float& operator[](unsigned int idx);
    Matrix operator+(const Matrix& rhs);
//    friend Matrix operator+(const Matrix& lhs,Matrix& rhs);
    Matrix operator*(const Matrix& rhs) const;
    Matrix &operator+=(const Matrix& rhs) ;
    Matrix &operator=(const Matrix &other);
    friend Matrix operator*(float scalarToMultiply, const Matrix& mat);
    Matrix operator *(float idx) const;
    float operator() (size_t r,size_t c) const;
    float &operator() (size_t r,size_t c);

    // get and general function
    const int &get_rows() const;
    const int &get_cols() const;
    Matrix& transpose();
    Matrix vectorize();
    Matrix dot(const Matrix& other) const;
    float norm() const;
    void dealoc();

    // the printing section
    void plain_print() const;
    friend std::ostream &operator<<(std::ostream &os, const Matrix &matrix);
    friend std::istream& operator>>(std::istream &is, const Matrix &matrix);


    // the destructor
    ~Matrix();
};


#endif //MATRIX_H
