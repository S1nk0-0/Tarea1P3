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


// Funciones
Tensor Tensor::zeros(const vector<size_t>& shape) {
    size_t total = compute_total_size(shape);
    vector<double> values(total, 0.0);
    return Tensor(shape, values);
}

Tensor Tensor::ones(const vector<size_t>& shape) {
    size_t total = compute_total_size(shape);
    vector<double> values(total, 1.0);
    return Tensor(shape, values);
}

Tensor Tensor::random(const vector<size_t>& shape, double min, double max) {
    if (min >= max) {
        throw invalid_argument("min debe ser menor que max.");
    }

    size_t total = compute_total_size(shape);
    vector<double> values(total);

    if (min >= 0) {
        for (size_t i = 0; i < total; ++i) {
            values[i] = rand() % (max-min) +min ;
        }
    }
    else {
        throw invalid_argument("min debe ser positivo.");
    }


    return Tensor(shape, values);
}

Tensor Tensor::arange(int start, int end) {
    if (start >= end) {
        throw invalid_argument("start debe ser menor que end.");
    }
    vector<double> values;

    for (int i = start; i < end; ++i) {
        values.push_back(i);
    }

    vector<size_t> shape = { values.size() };
    return Tensor(shape, values);
}

// Destructor

Tensor::~Tensor() {
    delete[] data_;
}


