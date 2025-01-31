#include "Matrix.h"
#include <iostream>
#include <cmath>
#define MEMORY_ERROR "Error: there is a problem with the memory allocated"
#define POINTER_ERROR "Error: the matrix that is giving is null"
#define COMPARING_ROWS_COLS "Error: are mat we have and the one we got are not even in there rows are cols"
#define SAME_POINTER "Error: its the same pointer"
#define FILE_ERROR "Error: couldn't read the file is"
#define LENGTH_ERROR "Error: the legnth are not the same"
#define CHECK_NUM 0.1


/**
 * this is a default constructor
 */
Matrix::Matrix(){
    items.rows = 1;
    items.cols =1;
    matrix = matrix_aloc(1,1);
}


/**
 * this is the constructor
 * @param rows
 * @param cols
 */
Matrix::Matrix(int rows, int cols=1) {
    this->items.rows = rows;
    this->items.cols = cols;
    this->matrix = matrix_aloc(rows,cols);
    for (int i = 0; i < rows * cols; ++i) {
        this->matrix[i] = 0;
    }
}

/**
 * we allocate memory for the matrix
 * @param rows
 * @param cols
 * @return the allocated matrix
 */
float *Matrix::matrix_aloc(int rows, int cols){
    auto * new_matrix = new float [rows*cols];
    if(!new_matrix){
        std::cerr<< MEMORY_ERROR << std::endl;
        exit(1);
    }
    for (int i = 0; i < rows * cols; ++i) {
        new_matrix[i] = 0;
    }
    return new_matrix;
}

/**
 * this contracts from a different matrix
 * @param other
 */
Matrix::Matrix(const Matrix &other): items(other.items)  {
    if (other.matrix == nullptr){
        std::cerr<< POINTER_ERROR << std::endl;
        exit(1);
    }
    matrix = matrix_aloc(this->get_rows(), this->get_cols());
    for (int i = 0; i < this->get_rows()*this->get_cols(); ++i) {
        matrix[i] = other.matrix[i];
    }
}

/**
 *we delete the memory alc there was
 */
void Matrix ::dealoc() {
    delete[] this->matrix;
    matrix = nullptr;
}

/**
 * we get the rows
 * @return rows
 */
const int &Matrix ::get_rows() const {
    return items.rows;
}

/**
 * we get the cols
 * @return cols
 */
const int &Matrix ::get_cols() const {
    return items.cols;
}

/**
 * we transpose the matrix
 * @return a transpose matrix
 */
Matrix &Matrix::transpose() {
    if (this->matrix == nullptr){
        std::cerr<< POINTER_ERROR << std::endl;
        exit(1);
    }
    int tmp1 = this->get_rows(), tmp2 = this->get_cols();
    Matrix new_matrix(tmp2,tmp1);;
    for (int i = 0; i < tmp2; ++i) {
        for (int j = 0; j < tmp1; ++j) {
            new_matrix.matrix[(this->items.cols)*j+ i]= this->matrix[(this->items.rows)*i+ j];
        }
    }
    delete[] this->matrix;
    this->matrix = nullptr;
    this->items.rows = tmp2;
    this->items.cols = tmp1;
    this->matrix = matrix_aloc(tmp2,tmp1);
    for (int i = 0; i < tmp1*tmp2; ++i) {
        this->matrix[i] = new_matrix[i];
    }
    return *this;
}


/**
 * we vectorize the matrix into 1 arrays
 * @return a vectorize matrix
 */
Matrix Matrix::vectorize() {
    if (this->matrix == nullptr){
        std::cerr<< POINTER_ERROR << std::endl;
        exit(1);
    }
    this->items.rows= this->items.rows* this->items.cols;
    this->items.cols =1;
    return *this;
}


/**
 * we mul each value in the matrix
 * @param other
 * @return the mul value  matrix
 */
Matrix Matrix::dot(const Matrix &other) const
{
    if (this->matrix == nullptr || other.matrix == nullptr){
        std::cerr<< POINTER_ERROR << std::endl;
        exit(1);
    }
    if (this->items.rows != other.items.rows || this->items.cols != other.items.cols){
        std::cerr<< COMPARING_ROWS_COLS << std::endl;
        exit(1);
    }
    Matrix new_matrix(other.get_rows(),other.get_cols());
    for (int i = 0; i < other.items.rows*other.items.cols; ++i) {
            new_matrix.matrix[i] = (this->matrix[i]*other.matrix[i]);
    }
    return new_matrix;
}

/**
 * we get the norm of the function
 * @return the norm
 */
float Matrix ::norm() const {
    if (this->matrix == nullptr){
        std::cerr<< POINTER_ERROR << std::endl;
        exit(1);
    }
    float sum = 0;
    for (int i = 0; i < this->items.rows*this->items.cols; ++i) {
        sum +=  matrix[i]*matrix[i];
    }
    float res = sqrt(sum);
    return res;
}


/**
 * we add both matrix
 * @param rhs
 * @return the added matrix
 */
Matrix Matrix ::operator+(const Matrix &rhs)  {
    if (this->matrix == nullptr || rhs.matrix == nullptr){
        std::cerr<< POINTER_ERROR << std::endl;
        exit(1);
    }
    if (this->items.rows != rhs.items.rows || this->items.cols !=rhs.items.cols){
        std::cerr<< COMPARING_ROWS_COLS << std::endl;
        exit(1);
    }
    Matrix tmp(this->get_rows(), this->get_cols());
    for (int i = 0; i < rhs.items.rows*rhs.items.cols; ++i) {
        tmp.matrix[i] = (this->matrix[i] + rhs.matrix[i]);
    }
    return tmp;
}

/**
 * we add to the own matrix
 * @param rhs
 * @return the own matrix
 */
Matrix &Matrix::operator+=(const Matrix &rhs)  {
    if (this->matrix == nullptr || rhs.matrix == nullptr){
        std::cerr<< POINTER_ERROR << std::endl;
        exit(1);
    }
    if (this->items.rows != rhs.items.rows || this->items.cols !=rhs.items.cols){
        std::cerr<< COMPARING_ROWS_COLS << std::endl;
        exit(1);
    }
    for (int i = 0; i < rhs.items.rows*rhs.items.cols; ++i) {
        matrix[i] = (this->matrix[i] + rhs.matrix[i]);
    }
    return *this;
}

/**
 * are mat equal to the mat you bring
 * @param other
 * @return the equal matrix
 */
Matrix& Matrix::operator=(const Matrix &other) {
    if (this->matrix == nullptr || other.matrix == nullptr){
        std::cerr<< POINTER_ERROR << std::endl;
        exit(1);
    }
    if(this == &other){
        std::cerr<< SAME_POINTER << std::endl;
        return *this;
    }
    if (this->items.rows){
        delete[] this->matrix;
        matrix = nullptr;
    }
    this->items = other.items;
    this->matrix = matrix_aloc(other.get_rows(),other.get_cols());
    for (int i = 0; i < this->get_rows()*this->get_cols(); ++i) {
        this->matrix[i] = other.matrix[i];
    }
    return *this;
}

/**
 * we mul between mat
 * @param rhs
 * @return the mul mat
 */
Matrix Matrix ::operator*(const Matrix &rhs) const {
    if (this->matrix == nullptr || rhs.matrix == nullptr){
        std::cerr<< POINTER_ERROR << std::endl;
        exit(1);
    }
    if (this->items.cols != rhs.items.rows){
        std::cerr<< COMPARING_ROWS_COLS << std::endl;
        exit(1);
    }
    Matrix tmp(this->items.rows,rhs.items.cols);
    for (int i = 0; i <tmp.items.rows; ++i) {
        for (int j = 0; j < tmp.items.cols; ++j) {
            for (int k = 0; k < rhs.items.rows; ++k) {
                tmp.matrix[(i * tmp.items.cols) + j] += (this->matrix[(i * this->items.cols) + k] * rhs.matrix[(k * rhs.items.cols) + j]);
            }
        }
    }
    return tmp;
}

/**
 * we mul with a scalar from the left
 * @param idx
 * @return matrix after mul with scalar
 */
Matrix Matrix::operator*(float idx) const {
    if (this->matrix == nullptr){
        std::cerr<< POINTER_ERROR << std::endl;
        exit(1);
    }
    for (int i = 0; i < this->items.rows * this->items.cols; ++i) {
        this->matrix[i] = this->matrix[i]*idx;
    }
    return *this;
}


/**
 * we mul with a scalar from the right
 * @param scalarToMultiply
 * @param mat
 * @return matrix after mul with scalar
 */
Matrix operator*(float scalarToMultiply, const Matrix &mat) {
    if (mat.matrix == nullptr){
        std::cerr<< POINTER_ERROR << std::endl;
        exit(1);
    }
    Matrix new_mat(mat.get_rows(),mat.get_cols());
    for (int i = 0; i < mat.items.rows*mat.items.cols; ++i) {
        new_mat.matrix[i] = mat.matrix[i] *scalarToMultiply;
    }
    return new_mat;
}

/**
 * we find index with Parenthesis
 * @param r
 * @param c
 * @return the value in the index
 */
float &Matrix::operator()(size_t r, size_t c) {
    if (this->matrix == nullptr){
        std::cerr<< POINTER_ERROR << std::endl;
        exit(1);
    }
    return matrix[(this->items.rows)*r+ c];
}


/**
 * we find index with Brackets cons
 * @param idx
* @return the value in the index
 */
float Matrix ::operator[](unsigned int idx) const {
    if (this->matrix == nullptr){
        std::cerr<< POINTER_ERROR << std::endl;
        exit(1);
    }
    return matrix[idx];
}

/**
 * we print the function all the value in it
 */
void Matrix ::plain_print() const {
    if (this->matrix == nullptr){
        std::cerr<< POINTER_ERROR << std::endl;
        exit(1);
    }
    int check = this->items.cols;
    for (int i = 0; i < this->items.rows * this->items.cols; ++i) {
        std::cout << this->matrix[i] << " \n"[i == check-1];
        if (i == check-1){
            check += this->get_cols();
        }
    }
}


/**
 * we find index with Brackets
 * @param idx
* @return the value in the index
 */
float &Matrix::operator[](unsigned int idx) {
    if (this->matrix == nullptr){
        std::cerr<< POINTER_ERROR << std::endl;
        exit(1);
    }
    return this->matrix[idx];
}


/**
 * we find index with Parenthesis with const
 * @param r
 * @param c
 * @return the value in the index
 */
float Matrix::operator()(size_t r, size_t c) const {
    if (this->matrix == nullptr){
        std::cerr<< POINTER_ERROR << std::endl;
        exit(1);
    }
    return matrix[(this->items.rows)*r+ c];
}


/**
 * we read from the file to put value in the matrix
 * @param is
 * @param matrix
 * @return is
 */
std::istream &operator>>(std::istream &is, const Matrix &matrix) {
    if (matrix.matrix == nullptr){
        std::cerr<< POINTER_ERROR << std::endl;
        exit(1);
    }
    is.seekg (0, std::istream::end);
    unsigned int length = is.tellg();
    is.seekg (0, std::istream::beg);
    unsigned int num = matrix.get_rows()*matrix.get_cols()* sizeof(float );
    if(num != length){
        std::cerr<< LENGTH_ERROR << std::endl;
        exit(1);
    }
    is.read((char *)matrix.matrix, num);
    if (!is){
        std::cerr<< FILE_ERROR << std::endl;
        exit(1);
    }
    return is;
}


/**
 * we print with ** and spaces
 * @param os
 * @param matrix
 * @return os
 */
std::ostream &operator<<(std::ostream &os, const Matrix &matrix) {
    if (matrix.matrix == nullptr){
        std::cerr<< POINTER_ERROR << std::endl;
        exit(1);
    }
    for (int i = 0; i < matrix.get_rows(); ++i) {
        for (int j = 0; j < matrix.get_cols(); ++j) {
            if(matrix(i,j) > CHECK_NUM){
                os << "**";
            } else{
                os <<"  ";
            }
        }
        os << std::endl;
    }
    return os;
}

/**
 * the destructor
 */
Matrix::~Matrix() {
    dealoc();
}
