#include "Tensor.cpp"
#include "RELU.cpp"
#include "Sigmoid.cpp"
#include <ctime>
#include <iostream>
///
/*
Importante:::::
Los .cpp no se deben incluir en el main osea en vez de .cpp debe ser .h
El tensor b1 y b2 estaban como 1, 100 y 1, 10 respectivamente
Se cambio algunas cosas como el view y el matmul por la logica que estaba dentro
en el CMakeList.txt se incluyen archivos .cpp y estos deberian correr automaticamente lo cual no esta pasando ns xq xd
*/
///
using namespace std;
int main() {
        srand(time(0));
        // 1) tensor de dimnsiones 1000x20x20
        Tensor X = Tensor::random({1000, 20, 20}, 0.0, 1.0);
        //2) transformarlo a 1000x40
        Tensor X1 = X.view({1000, 400});

        // 3)
        Tensor W1 = Tensor::random({400, 100}, 0.0, 1.0);
        Tensor b1 = Tensor::random({1000, 100}, 0.0, 1.0);

        Tensor Z1 = matmul(X1, W1);
        Tensor H1 = (Z1 + b1).apply(ReLU());

        Tensor W2 = Tensor::random({100, 10}, 0.0, 1.0);
        Tensor b2 = Tensor::random({1000, 10}, 0.0, 1.0);

        Tensor Z2 = matmul(H1, W2);
        Tensor Y = (Z2 + b2).apply(Sigmoid());

        cout << "Red neuronal ejecutada correctamente." << endl;
        cout << "Dimensiones de salida: ";
        const size_t* shape = Y.get_shape();
        for (size_t i = 0; i < Y.get_dimensiones(); ++i) {
            cout << shape[i];
            if (i + 1 < Y.get_dimensiones()) {
                cout << " x ";
            }
        }
        cout << endl;

    return 0;
}