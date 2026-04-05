#ifndef RELU_H
#define RELU_H
#include "TensorTranform.h"
class ReLU : public TensorTranform {
public:
    Tensor apply(const Tensor& t) const override;
};
#endif