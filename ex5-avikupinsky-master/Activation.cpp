#define POINTER_ERROR "Error: the matrix that is giving is null"
#include "Activation.h"
#include <cmath>

/**
 * this is the constructor
 * @param activationType
 */
Activation::Activation(ActivationType activationType) : activation_type(activationType) {}

/**
 * getting the boj
 * @return activation_type
 */
ActivationType Activation::get_activation_type() const {
    return activation_type;
}


/**
 *we get a mat in the Parenthesis and we use the function that we need
 * @param mat
 * @return matrix
 */
Matrix Activation::operator()(const Matrix &mat) const{
    Matrix new_mat = mat;
    if (get_activation_type() == RELU){
        for (int i = 0; i < new_mat.get_cols()*new_mat.get_rows(); ++i) {
            if (new_mat[i] < 0){
                new_mat[i] = 0;
            }
        }
    } else{
        float sum = 0;
        for (int i = 0; i < new_mat.get_rows()*new_mat.get_cols(); ++i) {
            sum += exp(new_mat[i]);
            new_mat[i] = exp(new_mat[i]);
        }
        sum = 1/sum;
        new_mat*sum;
    }
    return new_mat;
}
