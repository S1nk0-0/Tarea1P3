#include "Tensor.h"
using namespace std;

size_t Tensor::compute_total_size(const vector<size_t>& shape) {
    if (shape.empty()) {
        cout << "El shape no puede estar vacío." << endl;
    }
    if (shape.size() > 3) {
        cout <<"El tensor no puede tener más de 3 dimensiones." << endl;
    }

    size_t total = 1;

    for (size_t dim : shape) {
        if (dim == 0) {
            cout << "Las dimensiones deben ser mayores que 0." << endl;
        }
        total *= dim;
    }
    return total;
}

Tensor::Tensor() : shape_{0}, total_size_(0), data_(nullptr) {}

