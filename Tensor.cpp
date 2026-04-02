#include "Tensor.h"
using namespace std;
//Funcion para manejo de errores
size_t Tensor::compute_total_size(const vector<size_t>& shape) { //Para evitar errores
    if (shape.empty()) {
        throw invalid_argument("El shape no puede estar vacío." );
    }
    if (shape.size() > 3) {
        throw invalid_argument("El constructor solo hasta 3 dimensiones.");
    }
    size_t total = 1;
    for (size_t dim : shape) {
        if (dim == 0) {
            throw invalid_argument("La dimension no puede ser 0.");
        }
        total *= dim;
    }
    return total;
}
//Constructor por defecto
Tensor::Tensor() : shape(nullptr), dimensiones(0), totaln(0), data(nullptr) {}

//Constructor principal
Tensor::Tensor(const vector<size_t>& shape, const vector<double>& values) {
    // Guardar número de dimensiones
    dimensiones = shape.size();
    // Calcular tamaño total
    totaln = compute_total_size(shape);
    // Verificar que values coincida
    if (values.size() != totaln) {
        throw invalid_argument("El tamaño de values no coincide con el shape.");
    }
    // Reservar memoria para shape
    this->shape = new size_t[dimensiones];
    for (size_t i = 0; i < dimensiones; i++) {
        this->shape[i] = shape[i];
    }
    // Reservar memoria para data
    data = new double[totaln];
    for (size_t i = 0; i < totaln; i++) {
        data[i] = values[i];
    }
}

// Constructor de copia
Tensor::Tensor(const Tensor& otro){
    dimensiones = otro.dimensiones;
    totaln = otro.totaln;
    if (otro.shape!=nullptr) { //Si esque el shape no es nulo copia lo que estaba en el otro shape
        shape = new size_t[dimensiones];
        for (size_t i = 0; i < dimensiones; i++) {
            shape[i] = otro.shape[i];
        }
    }
    else {
        shape = nullptr;
    }
    if(otro.data != nullptr) {
        data = new double[totaln];
        for (size_t i = 0; i < totaln; ++i) {
            data[i] = otro.data[i];
        }
    }
    else {
        data = nullptr; //Por si es nullptr
    }
}

//Operador de asignacion de copia
Tensor& Tensor::operator=(const Tensor& other) {
    if (this == &other) {
        return *this; // evitar autoasignación como A=A
    }
    // Liberar memoria actual
    delete[] shape;
    delete[] data;
    //Copiar dimensiones
    dimensiones = other.dimensiones;
    totaln = other.totaln;
    // Copiar shape
    if (other.shape != nullptr) {
        shape = new size_t[dimensiones];
        for (size_t i = 0; i < dimensiones; i++) {
            shape[i] = other.shape[i];
        }
    }
    else {
        shape = nullptr;
    }
    // Copiar data
    if (other.data != nullptr) {
        data = new double[totaln];
        for (size_t i = 0; i < totaln; i++) {
            data[i] = other.data[i];
        }
    }
    else {
        data = nullptr;
    }
}

// Constructor de movimiento
Tensor::Tensor(Tensor&& other) {
    dimensiones = other.dimensiones; //copiar el puntero
    totaln = other.totaln;
    shape = other.shape;
    data = other.data;
    other.shape = nullptr; //para evitar el doble delete
    other.data = nullptr;
    other.dimensiones = 0;
    other.totaln = 0;
}

//Operador de asignacion de movimiento
//Misma memoria pero se cambia el tensor a uno nuevo que recibiremos
Tensor& Tensor::operator=(Tensor&& other) {
    if (this == &other) { //que no sean iguales ambos tensores
        return *this;
    }
    // Liberar memoria actual
    delete[] shape;
    delete[] data;
    // "Copia" por asi decirlo datos
    dimensiones = other.dimensiones;
    totaln = other.totaln;
    shape = other.shape;
    data = other.data;
    // Vacia el otro
    other.shape = nullptr;
    other.data = nullptr;
    other.dimensiones = 0;
    other.totaln = 0;
    return *this; //nos retorna el que queremos
}

// Destructor
Tensor::~Tensor()   {
    delete[] shape; //libera memoria
    delete[] data;
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
        throw invalid_argument("min debe ser menor que max."); //min entero y tambien considerar negativos
    }

    size_t total = compute_total_size(shape);
    vector<double> values(total);

    if (min >= 0) {
        for (size_t i = 0; i < total; ++i) {
            values[i] = rand() % (max-min) +min ; //Codigo mal porque % solo sirve para enteros
            //Formula que se debe implementar random = min + (rand()/RAND_MAX)*(max-min)
        }
    }
    else {
        throw invalid_argument("min debe ser positivo.");
    }


    return Tensor(shape, values);
}

Tensor Tensor::arange(int start, int end){
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


