//Activation.h


#ifndef ACTIVATION_H
#define ACTIVATION_H

#include "Matrix.h"

/**
 * @enum ActivationType
 * @brief Indicator of activation function.
 */
enum ActivationType
{
    RELU,
    SOFTMAX
};

class Activation{
    ActivationType activation_type;
public:
    Activation(ActivationType activationType);

    ActivationType get_activation_type() const;

    Matrix operator() (const Matrix& mat) const;
};


#endif //ACTIVATION_H
