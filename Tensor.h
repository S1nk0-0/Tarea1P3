#ifndef TAREA1P3_TENSOR_H
#define TAREA1P3_TENSOR_H

#include "string"
#include "iostream"
#include "vector"
using namespace std;

class Tensor {
    vector<size_t> shape;
    vector<double> values;
    int totaln;
    double* data;


public:
    Tensor();

    Tensor(const vector<size_t>& shape, const vector<double>& values);

    Tensor(const Tensor& other);                  // copia
    Tensor& operator=(const Tensor& other);       // asignación copia
    Tensor(Tensor&& other);              // movimiento
    Tensor& operator=(Tensor&& other);   // asignación movimiento
    ~Tensor();                                    // destructor

    // Getters
    const std::vector<size_t>& shape() const;
    size_t size() const;
    const double* data() const;
    double* data();

    void print_info() const;
};


#endif