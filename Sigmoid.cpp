#include "Sigmoid.h"
#include <cmath>
#include <vector>
using namespace std;
Tensor Sigmoid::apply(const Tensor& t) const {
    //Se accede a los elementos del tensor
    size_t total = t.get_totaln();
    const double* data = t.get_data();
    const size_t* shape = t.get_shape();
    size_t dims = t.get_dimensiones();
    //Guarda los valores
    vector<double> new_values(total);
    // Aplicar Sigmoid
    for (size_t i = 0; i < total; i++) {
        new_values[i] = 1.0 / (1.0 + exp(-data[i]));//Se aplica la exponencial e ** a la tanto
    }
    // Copiar shape
    vector<size_t> new_shape(shape, shape + dims);
    //Retorna el tensor con la transformacion
    return Tensor(new_shape, new_values);
}