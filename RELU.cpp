#include "RELU.h"
#include <algorithm>
#include <vector>
using namespace std;
Tensor ReLU::apply(const Tensor& t) const {
    //Se accede a los datos del Tensor
    size_t total = t.get_totaln();
    const double* data = t.get_data();
    const size_t* shape = t.get_shape();
    size_t dims = t.get_dimensiones();
    //Guarda los datos
    vector<double> new_values(total);
    //Aplicar ReLU a cada elemento
    for (size_t i = 0; i < total; i++) {
        new_values[i] = max(0.0, data[i]);
    }
    // Copiar shape
    vector<size_t> new_shape(shape, shape + dims);
    //Devuelve el vector ya aplicando ReLU
    return Tensor(new_shape, new_values);
}