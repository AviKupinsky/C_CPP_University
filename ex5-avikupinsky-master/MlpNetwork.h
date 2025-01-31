//MlpNetwork.h

#ifndef MLPNETWORK_H
#define MLPNETWORK_H

#include "Dense.h"
#define MLP_SIZE 4
#define VET_SIZE 10

/**
 * @struct digit
 * @brief Identified (by Mlp network) digit with
 *        the associated probability.
 * @var value - Identified digit value
 * @var probability - identification probability
 */
typedef struct digit
{
    unsigned int value;
    float probability;
} digit;

const matrix_dims img_dims = {28, 28};
const matrix_dims weights_dims[] = {{128, 784},
                                    {64, 128},
                                    {20, 64},
                                    {10, 20}};
const matrix_dims bias_dims[]    = {{128, 1},
                                    {64, 1},
                                    {20, 1},
                                    {10, 1}};

class MlpNetwork{
    Matrix *array_mat1[4]{};
    Matrix *array_mat2[4]{};
public:
    MlpNetwork(Matrix *arrayMat1, Matrix *arrayMat2);
    digit operator() (const Matrix& img) const;
};

#endif // MLPNETWORK_H
