#include <iostream>
#include "Tensor.cpp"
#include "RELU.cpp"
#include "Sigmoid.cpp"
using namespace std;

int main() {

    cout << "============================================================\n";
    cout << "Paso  Operacion                                Dimension\n";
    cout << "============================================================\n";

    // 1) tensor de dimnsiones 1000x20x20
    Tensor X0 = Tensor::random({1000, 20, 20}, 0.0, 1.0);
    cout << "1  Tensor de entrada                         " << X0 << endl;

    //2) transformarlo a 1000x400
    Tensor X1 = X0.view({1000, 400});
    cout << "2  view                                      " << X1 << endl;

    // 3) multiplicarlo por una matriz 400x100
    Tensor b1 = Tensor::random({400, 100},0.0, 1.0);
    Tensor X2 = matmul(X1,b1) ;
    cout << "3  matmul con pesos W1                       " << X2 << endl;

    // 4) Sumarle una matriz 1x100
    Tensor b2 = Tensor::ones({1, 100});
    Tensor X3 = X2 + b2;
    cout << "4  Suma con bias b1 (1x100)                  " << X3 << endl;

    // 5) Aplicar funcion RELU
    Tensor X4 = X3.apply(ReLU());
    cout << "5  Activacion de ReLU                        " << X4 << endl ;


    // 6) Multiplicar por una matriz 100 x 10
    Tensor b3 = Tensor::random({100, 10},0.0, 1.0);
    Tensor X5 = matmul(X4,b3) ;
    cout << "6  matmul con pesos W2                       " << X5 << endl;

    // 7) Sumar una matriz 1 x 10
    Tensor b4 = Tensor::ones({1, 10});
    Tensor X6 = X5 + b4;
    cout << "7  Suma con bias b2 (1x10)                   " << X6 << endl;

    // 8) Aplicar la funcion Sigmoid
    Tensor X7 = X6.apply(Sigmoid());
    cout << "8  Activacion Sigmoid                        " << X7 << endl;

    cout << "============================================================\n";


return 0;
}