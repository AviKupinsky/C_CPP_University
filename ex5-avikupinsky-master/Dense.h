#ifndef DENSE_H
#define DENSE_H

#include "Activation.h"
class Dense{
    Matrix weights, bias;
    Activation act;
public:



    Dense(const Matrix &weights, const Matrix &bias, const Activation &act);

    const Matrix &get_weights() const;

    const Matrix &get_bias() const;

    const Activation &get_activation() const;

    Matrix operator() (const Matrix& mat) const;

};


#endif //DENSE_H
