#ifndef SIGMOID_H
#define SIGMOID_H
#include "TensorTranform.h"
class Sigmoid : public TensorTranform {
public:
    Tensor apply(const Tensor& t) const override;
};
#endif