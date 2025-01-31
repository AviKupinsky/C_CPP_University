#include "Matrix.h"
#include "MlpNetwork.h"
#define POINTER_ERROR "Error: the matrix that is giving is null"


/**
 * this is the constructor
 * @param arrayMat1
 * @param arrayMat2
 */
MlpNetwork::MlpNetwork(Matrix *arrayMat1,Matrix *arrayMat2){
    matrix_dims items;
    matrix_dims another;
    for (int i = 0; i < MLP_SIZE; ++i) {
        items.rows = weights_dims[i].rows;
        items.cols  = weights_dims[i].cols;
        arrayMat1[i](items.rows,items.cols);
        this->array_mat1[i] = &arrayMat1[i];
        another.rows = bias_dims[i].rows;
        another.cols = bias_dims[i].cols;
        arrayMat2[i](another.rows,another.cols);
        this->array_mat2[i] = &arrayMat2[i];
    }
}

/**
 *in this operator we get a number and find out what it is
 * @param img
 * @return a digit with the number and its value
 */
digit MlpNetwork::operator()(const Matrix &img) const {
    Matrix *use1 = this->array_mat1[0], *use2 = this->array_mat2[0];
    Dense first(*use1,*use2, RELU);
    Matrix r1 = first(img);
    Matrix *use3 = this->array_mat1[1], *use4 = this->array_mat2[1];
    Dense second(*use3,*use4, RELU);
    Matrix r2 = second(r1);
    Matrix* use5 = this->array_mat1[2], *use6 = this->array_mat2[2];
    Dense third(*use5,*use6, RELU);
    Matrix r3 = third(r2);
    Matrix *use7 = this->array_mat1[3], *use8 = this->array_mat2[3];
    Dense forth(*use7,*use8, SOFTMAX);
    Matrix r4 = forth(r3);
    digit final;
    final.value = 0;
    final.probability = r4[0];
    for (int i = 0; i < VET_SIZE; ++i) {
        if (r4[i] > final.probability){
            final.value = i;
            final.probability = r4[i];
        }
    }
    return final;
}
