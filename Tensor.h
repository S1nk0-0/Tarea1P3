#ifndef TAREA1P3_TENSOR_H
#define TAREA1P3_TENSOR_H
#include "iostream"
#include "string"
#include "vector"
class TensorTranform; //Para que no ocurra una llamada de archivos continua
using namespace std;//n

//size_t utilizado para representar tamaños de objetos y contadores de elementos

class Tensor {

    friend Tensor dot ( const Tensor & a , const Tensor & b ) ;
    friend Tensor matmul ( const Tensor & a , const Tensor & b ) ;

    friend ostream& operator<<(ostream& os, const Tensor& t);    //Atributos

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
    Tensor(Tensor&& other) noexcept;              // Constructor de movimiento
    Tensor& operator=(Tensor&& other) noexcept;   // Operador de asignación de movimiento
    ~Tensor();                                    // Destructor

    //Para hacer una tranformacion al tensor
    Tensor apply(const TensorTranform& tranform) const;
    //Se reciba una referencia a culaquier cosa que herede de TensorTranform

    //   void print_info() const;

    // Funciones
    static Tensor zeros(const vector<size_t>& shape); //Inicializa en ceros
    static Tensor ones(const vector<size_t>& shape); //Inicializa en unos
    static Tensor random(const vector<size_t>& shape, double min, double max); //Nos da valores randoms
    static Tensor arange(int start, int end); //Para definir el rango
    static Tensor concat(const std::vector<Tensor>& tensores, size_t dim); //Para concatenar tensores
    //Getters
    size_t get_totaln() const;
    size_t get_dimensiones() const;
    const size_t* get_shape() const;
    const double* get_data() const;
    //Sobrecarga de Operadores
    //Sobrecarga de operador +
    Tensor operator+(const Tensor& otro) const;
    //Sobrecarga de operador -
    Tensor operator-(const Tensor& other) const;
    //Sobrecarga de operador * con un valor
    Tensor operator*(double valor) const;
    //Sobrecarga de operador * con otro tensor
    Tensor operator*(const Tensor& other) const;

    //Modificacion de dimensiones
    Tensor view(const vector<size_t>& new_shape);
    Tensor unsqueeze(size_t dim);


};




#endif