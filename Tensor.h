#ifndef TAREA1P3_TENSOR_H
#define TAREA1P3_TENSOR_H
#include "iostream"
#include "string"
#include "vector"
class TensorTransform; //Para que no ocurra una llamada de archivos continua
using namespace std;

//size_t utilizado para representar tamaños de objetos y contadores de elementos

class Tensor {
    //Atributos
    size_t* shape; //Guarda dimensiones del tensor -- Array dinamico
    size_t dimensiones; //Numero de dimensiones que tiene el tensor
    size_t totaln; //numero total de elemntos
    double* data; //Los valores del tensor // se guarda de manera lineal : [1 2 3 4 5 6]

    //Para el control de errores
    static size_t compute_total_size(const vector<size_t>& shape);

public:
    Tensor(); // Constuctor default
    Tensor(const vector <size_t>& shape, const vector<double>& values); // Constructor principal
    Tensor(const Tensor& otro);                  // Constructor de copia
    Tensor& operator=(const Tensor& other);       // Operador de asignación de copia
    Tensor(Tensor&& other);              // Constructor de movimiento
    Tensor& operator=(Tensor&& other);   // Operador de asignación de movimiento
    ~Tensor();                                    // Destructor

    //Para hacer una tranformacion al tensor
    Tensor apply(const TensorTransform& transform) const;
    //Se reciba una referencia a culaquier cosa que herede de TensorTranform

    //   void print_info() const;

    // Funciones
    static Tensor zeros(const std::vector<size_t>& shape); //Inicializa en ceros
    static Tensor ones(const std::vector<size_t>& shape); //Inicializa en unos
    static Tensor random(const std::vector<size_t>& shape, double min, double max); //Nos da valores randoms
    static Tensor arange(int start, int end); //Para definir el rango
    //Getters
    size_t get_totaln() const;
    size_t get_dimensiones() const;
    const size_t* get_shape() const;
    const double* get_data() const;
};


#endif