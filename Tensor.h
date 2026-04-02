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
    Tensor(); // constuctor default

    Tensor(const vector<size_t>& shape, const vector<double>& values); // constructor normal

    Tensor(const Tensor& otro);                  // copia
    Tensor& operator=(const Tensor& other);       // asignación copia
    Tensor(Tensor&& other);              // movimiento
    Tensor& operator=(Tensor&& other);   // asignación movimiento
    ~Tensor();                                    // destructor

    void print_info() const;

    // Funciones

    static Tensor zeros(const std::vector<size_t>& shape);
    static Tensor ones(const std::vector<size_t>& shape);
    static Tensor random(const std::vector<size_t>& shape, double min, double max);
    static Tensor arange(int start, int end);
};


#endif