#include <iostream>
#include "Tensor.cpp"
#include "RELU.cpp"
#include "Sigmoid.cpp"
using namespace std;

int main() {
    // 1) tensor de dimnsiones 1000x20x20
    Tensor X = Tensor::random({1000, 20, 20}, 0.0, 1.0);
    //2) transformarlo a 1000x400
    Tensor X1 = X.view({1000, 400});

    // 3) multiplicarlo por una matriz 400x100
    Tensor b1 = Tensor::random({400, 100},0.0, 1.0);
    Tensor X2 = matmul(X1,b1) ;

    // 4) Sumarle una matriz 1x100
    Tensor b2 = Tensor::ones({1, 100});
    Tensor X3 = X2 + b2;

return 0;
}