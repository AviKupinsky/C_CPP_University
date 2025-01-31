#include "Matrix.h"
#include "Activation.h"
#include "Dense.h"
#define POINTER_ERROR "Error: the matrix that is giving is null"
#define COMPARING_ROWS_COLS "Error: are mat we have and the one ew got are not even in there rows are cols"


/**
 * this is the constructor
 * @param mat1
 * @param mat2
 * @param act
 */
Dense::Dense(const Matrix &weights, const Matrix &bias, const Activation &act) : weights(weights), bias(bias),
                                                                                 act(act) {}


/**
 * getting first matrix
 * @return matrix
 */
const Matrix &Dense::get_weights() const {
    return weights;
}
/**
 * getting second matrix
 * @return mat2
 */
const Matrix &Dense::get_bias() const {
    return bias;
}

/**
 * getting the function we should to
 * @return obj
 */
const Activation &Dense::get_activation() const {
    return act;
}


/**
 *we get a gun and we do all the tasks for the net phse
 * @param mat
 * @return mat
 */
Matrix Dense::operator()(const Matrix &mat) const {
    if (this->get_weights().get_cols() != mat.get_rows() || this->get_weights().get_cols() != mat.get_rows()){
        std::cerr<< COMPARING_ROWS_COLS << std::endl;
        exit(1);
    }
    Matrix check_mat = (this->weights*mat);
    if (check_mat.get_rows() != this->get_bias().get_rows() || check_mat.get_cols() != this->get_bias().get_cols()){
        std::cerr<< COMPARING_ROWS_COLS << std::endl;
        exit(1);
    }
    check_mat += get_bias();
    Activation check = this->get_activation().get_activation_type();
    Matrix last_mat = check(check_mat);
    return last_mat;
}

