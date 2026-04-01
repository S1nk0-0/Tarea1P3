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


// Constructor de copia
Tensor::Tensor(const Tensor& otro)
    : shape_(otro.shape_), total_size_(otro.total_size_), data_(nullptr) {

    if (otro.data_ != nullptr) {
        data_ = new double[total_size_];
        for (size_t i = 0; i < total_size_; ++i) {
            data_[i] = otro.data_[i];
        }
    }
}

// Constructor de movimiento
Tensor::Tensor(Tensor&& other)
    : shape_(std::move(other.shape_)),
      total_size_(other.total_size_),
      data_(other.data_) {

    other.total_size_ = 0;
    other.data_ = nullptr;
}


// Destructor

Tensor::~Tensor() {
    delete[] data_;
}


