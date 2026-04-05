#include "Tensor.h"
#include "TensorTranform.h"
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
    // Guardar las dimensiones
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
    return *this;
}

// Constructor de movimiento
Tensor::Tensor(Tensor&& other) noexcept {
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
Tensor& Tensor::operator=(Tensor&& other) noexcept{
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
Tensor::~Tensor()   {
    delete[] shape; //libera memoria
    delete[] data;
}


//Funcion para valores aleatorios
Tensor Tensor::random(const vector<size_t>& shape,double min,double max) { //Puede tomar decimales
    if (min >= max) {
        throw invalid_argument("min debe ser menor que max.");
    }
    size_t total = compute_total_size(shape);
    vector<double> values(total);
    for (size_t i = 0; i < total; ++i) {
        double r = double(rand()) / (RAND_MAX+1.0); //Formamos un numero aleatorio decimal que va desde [0, 1)
        //RAND_MAX garantiza que sea un valor al menos de 32767
        values[i] = min + r* (max - min); //Convierte esto en un intervalo que va desde min a maximo
    }//Sumamos el min para desplazar el intervalo
    //Se mide la distancia entre max y min esta distancia lo multiplicamos por un valor aleatorio entre 0-1
    //Le añadimos lo faltante osea desplazamos min (cantidad) y asi formamos numeros aleatorios que tambien pueden ser negativos
    return Tensor(shape, values);//Retorna el tensor
}

//Getters
size_t Tensor::get_totaln() const {
    return totaln;
}
size_t Tensor::get_dimensiones() const {
    return dimensiones;
}
const size_t* Tensor::get_shape() const {
    return shape;
}
const double* Tensor::get_data() const {
    return data;
}

//Permite el polimorfismo dinamico
Tensor Tensor::apply(const TensorTranform& tranform) const {
    return tranform.apply(*this); //Nos devuelve un nuevo tensor tranformado

}
//Sobrecarga de Operadores
//Sobrecarga de +
Tensor Tensor::operator+(const Tensor& other) const {
    // Verificar shapes que tengan las mismas dimensiones
    if (dimensiones != other.dimensiones) {
        throw invalid_argument("Dimensiones incompatibles.");
    }
    //Verificar que tenga las mismas filas columnas y en caso 3D alto
    for (size_t i = 0; i < dimensiones; i++) {
        if (shape[i] != other.shape[i]) {
            throw invalid_argument("Shapes diferentes.");
        }
    }
    // Crear el resultado
    vector<double> result(totaln);
    // Sumar elemento a elemento
    for (size_t i = 0; i < totaln; i++) {
        result[i] = data[i] + other.data[i];
    }
    vector<size_t> new_shape(shape, shape + dimensiones);
    //Retornar el nuevo tensor
    return Tensor(new_shape, result);
}
Tensor Tensor::operator-(const Tensor& other) const {
    // Verificar shapes que tengan las mismas dimensiones
    if (dimensiones != other.dimensiones) {
        throw invalid_argument("Dimensiones incompatibles.");
    }
    //Verificar que tenga las mismas filas columnas y en caso 3D alto
    for (size_t i = 0; i < dimensiones; i++) {
        if (shape[i] != other.shape[i]) {
            throw invalid_argument("Shapes diferentes.");
        }
    }
    // Crear el resultado
    vector<double> result(totaln);
    // Restar elemento a elemento
    for (size_t i = 0; i < totaln; i++) {
        result[i] = data[i] - other.data[i];
    }
    vector<size_t> new_shape(shape, shape + dimensiones);
    //Retornar el nuevo tensor
    return Tensor(new_shape, result);
}
Tensor Tensor::operator*(const double valor) const {
    // Crear el resultado
    vector<double> result(totaln);
    // Multiplicar valor por valor
    for (size_t i = 0; i < totaln; i++) {
        result[i] = data[i] * valor; //Se multiplica por el valor que se hace
    }
    vector<size_t> new_shape(shape, shape + dimensiones);
    //Retornar el nuevo tensor
    return Tensor(new_shape, result);
}

Tensor Tensor::operator*(const Tensor& other) const {
    // Verificar shapes que tengan las mismas dimensiones
    if (dimensiones != other.dimensiones) {
        throw invalid_argument("Dimensiones incompatibles.");
    }
    //Verificar que tenga las mismas filas columnas y en caso 3D alto
    for (size_t i = 0; i < dimensiones; i++) {
        if (shape[i] != other.shape[i]) {
            throw invalid_argument("Shapes diferentes.");
        }
    }
    // Crear el resultado
    vector<double> result(totaln);
    // Restar elemento a elemento
    for (size_t i = 0; i < totaln; i++) {
        result[i] = data[i] * other.data[i];
    }
    vector<size_t> new_shape(shape, shape + dimensiones);
    //Retornar el nuevo tensor
    return Tensor(new_shape, result);
}

Tensor Tensor::view(const vector<size_t>& new_shape)  {
    // Validamos que no sea mas de 3 dimensiones
    if (new_shape.empty() || new_shape.size() > 3) {
        throw invalid_argument("El shape debe tener entre 1 y 3 dimensiones.");
    }
    //Calcumaos el tamaño de el tensor que queremos
    size_t nuevo_totaln = 1;
    for (size_t dim : new_shape) {
        if (dim == 0) throw invalid_argument("La dimension no puede ser 0.");
        nuevo_totaln *= dim;
    }
    //Verificamos que el total de elementos sea constante
    if (nuevo_totaln != this->totaln) {
        throw invalid_argument("El numero total de elementos no coincide.");
    }
    //Creamos un tensor que luego retornaremos
    Tensor result;
    result.dimensiones = new_shape.size();
    result.totaln = this->totaln;
    //Asignamos valores a nuestro nuevo tensor que queremos
    result.shape = new size_t[result.dimensiones];
    for (size_t i = 0; i < result.dimensiones; ++i) {
        result.shape[i] = new_shape[i];
    }
    // Accedemos al puntero : "no lo copiamos"
    result.data = this->data;
    // Dejamos el tensor original en un estado vacio
    delete[] this->shape; // Liberamos memoria
    this->shape = nullptr;
    this->dimensiones = 0;
    this->totaln = 0;
    // Retorna el nuevo tensor
    return result;
}

Tensor Tensor::unsqueeze(size_t dim) {
    //Verficamos dimensiones
    if (dimensiones >= 3) {
        throw invalid_argument("No se puede hacer unsqueeze, excede el maximo de 3 dimensiones.");
    }
    //Validamos que la dimension sea la correcta
    if (dim > dimensiones) {
        throw out_of_range("La dimension especificada esta fuera de rango.");
    }
    //Construimos nuestro nuevo shape a base del anterior
    vector<size_t> new_shape(shape, shape + dimensiones);
    //Insertamos un 1 en la posicion que queremos
    new_shape.insert(new_shape.begin() + dim, 1);
    //Utilizamos view para hacer la tranferencia de memoria sin copiar
    return this->view(new_shape);
}

Tensor Tensor::concat(const std::vector<Tensor>& tensores, size_t dim) {
    //Validacion de tener al menos un tensor en la lista
    if (tensores.empty()) {
        throw invalid_argument("La lista de tensores esta vacia. Se requiere al menos un tensor.");
    }
    //Accedemos a la dimension
    size_t dims = tensores[0].get_dimensiones();

    // Verificamos que todos los tensores en la lista tengan la misma cantidad de dimensiones (1D, 2D o 3D)
    for (const Tensor& t : tensores) {
        if (t.get_dimensiones() != dims) {
            throw invalid_argument("Todos los tensores deben tener el mismo numero de dimensiones para concatenarse.");
        }
    }
    // Validación
    if (dim >= dims) {
        throw invalid_argument("La dimension especificada no es valida para estos tensores (ejemplo: dim=1 en un vector 1D).");
    }
    // Creamos el nuevo shape que luego retornaremos y validamos matematicamente
    // Tomamos el shape del primer tensor como base para comparar
    vector<size_t> base_shape(tensores[0].get_shape(), tensores[0].get_shape() + dims);
    vector<size_t> new_shape = base_shape;

    // Iteramos desde el segundo tensor en adelante para validar con el primero
    for (size_t i = 1; i < tensores.size(); ++i) {
        const size_t* curr_shape = tensores[i].get_shape();
        if (dims == 1) {
            //Caso de 1D
        }
        else if (dims == 2) {
            // CASO de 2D:
            if (dim == 0) {
                // Tensor A <a,b> y Tensor B <c,b> -> Resultado <a+c, b> se requiere esta condicion
                if (curr_shape[1] != base_shape[1]) {
                    throw invalid_argument("2D (dim=0): Las columnas <b> deben coincidir para apilar verticalmente.");
                }
            } else if (dim == 1) {
                // Tensor A <a,b> y Tensor B <a,c> -> Resultado <a, b+c> se requiere esta condicion
                if (curr_shape[0] != base_shape[0]) {
                    throw invalid_argument("2D (dim=1): Las filas <a> deben coincidir para apilar horizontalmente.");
                }
            }
        }
        else if (dims == 3) {
            // CASO 3D:
            if (dim == 0) {
                // Concatenar por Altura
                // Tensor A <a,b,c> y Tensor B <d,b,c> -> Resultado <a+d, b, c> se requiere esta condicion
                if (curr_shape[1] != base_shape[1] || curr_shape[2] != base_shape[2]) {
                    throw invalid_argument("3D (dim=0, altura): La profundidad <b> y longitud <c> deben coincidir.");
                }
            } else if (dim == 1) {
                // Concatenar por Profundidad
                // Tensor A <a,b,c> y Tensor B <a,d,c> -> Resultado <a, b+d, c> se requiere esta condicion
                if (curr_shape[0] != base_shape[0] || curr_shape[2] != base_shape[2]) {
                    throw invalid_argument("3D (dim=1, profundidad): La altura <a> y longitud <c> deben coincidir.");
                }
            } else if (dim == 2) {
                // Concatenar por Longitud se requiere esta condicion
                // Tensor A <a,b,c> y Tensor B <a,b,d> -> Resultado <a, b, c+d>
                if (curr_shape[0] != base_shape[0] || curr_shape[1] != base_shape[1]) {
                    throw invalid_argument("3D (dim=2, longitud): La altura <a> y profundidad <b> deben coincidir.");
                }
            }
        }
        // Si esq pasó las validaciones, sumamos el tamaño en la dimensión objetivo
        new_shape[dim] += curr_shape[dim];
    }
    // Creamos la nueva memoria
    // Calculamos el total de elementos de la matriz concatenada
    size_t nuevo_totaln = 1;
    for (size_t s : new_shape) {
        nuevo_totaln *= s;
    }
    // Creamos el vector que almacenará los nuevos datos
    vector<double> result_data(nuevo_totaln, 0.0);
    //Saltos de data
    //Repeticiones = Producto de todas las dimensiones antes de 'dim'
    //Ciclo completo de saltos = a repeticiones
    size_t repeticiones = 1;
    for (size_t i = 0; i < dim; ++i) {
        repeticiones *= new_shape[i];
    }
    size_t offset_escritura = 0; // Puntero virtual para saber dónde escribir en result_data osea le dice al programa el numero que esta aqui
    //ponlo en la posicion 0 luego el otro en posicion 1 ...
    //Veces que hacemos el intercambio
    for (size_t r = 0; r < repeticiones; ++r) {
        //Pasamos por cada uno de los tensores de la lista y hacemos esto repetidamente
        for (const Tensor& t : tensores) {
            // Tamaño del bloque (cuantos elementos seguidos tomamos de este tensor en especifico)
            // Total de elementos del tensor actual dividido entre las repeticiones
            //bloque = a los numeros que copiamos de un tensor antes de seguir copiando cuando saltamos al otro tensor
            size_t bloque_t = t.get_totaln() / repeticiones;
            // Puntero virtual para saber desde dónde leer en el tensor actual
            size_t offset_lectura = r * bloque_t; //Nos sirve para considerar los saltos y no copiar un valor de mas o
            //no saltarnos algun valor
            const double* t_data = t.get_data();
            // Copiamos el bloque de datos a la nueva memoria donde vamos a almacenar todo
            for (size_t i = 0; i < bloque_t; ++i) {
                result_data[offset_escritura] = t_data[offset_lectura + i];
                offset_escritura++;
            }
        }
    }
    // Finalmente, construimos y retornamos el nuevo Tensor
    return Tensor(new_shape, result_data);
}

Tensor dot(const Tensor& a, const Tensor& b) {
    //Verficamos dimensiones
    if (a.dimensiones !=  b.dimensiones) {
        throw invalid_argument("No se puede hacer dot, dimensiones diferentes.");
    }
    //Verficamos shape
    for (size_t i = 0; i < a.dimensiones; ++i) {
        if (a.shape[i] != b.shape[i]) {
            throw invalid_argument("No se puede hacer dot, shape incompatibles.");
        }
    }

    double suma = 0.0;
    for (size_t i = 0; i < a.totaln; ++i) { // multiplicamos los valores
        suma += a.data[i] * b.data[i];
    }
    return move(Tensor({1}, {suma}));
}

Tensor matmul(const Tensor& a, const Tensor& b) {
    // validar que ambos sean 2D

    //Verficamos dimensiones
    if (a.dimensiones != 2  || b.dimensiones != 2) {
        throw invalid_argument("No se puede hacer matmul, dimensiones diferentes a 2D.");
    }
    // validar que a.shape[1] == b.shape[0]
    if (a.shape[1] != b.shape[0]) {
        throw invalid_argument("No se puede hacer matmul, tamanios incompatibles.");
    }

        size_t m = a.shape[0];
        size_t n = a.shape[1]; // == b.shape[0]
        size_t p = b.shape[1];

        vector<double> result(m * p, 0.0);


        //Formula: Resultado[i][j] = sum desde 0 a n-1 (A[i][k] * B[k][j]
        for (size_t i = 0; i < m; ++i) { // que fila calculamos
            for (size_t j = 0; j < p; ++j) { // que columna calculamos
                for (size_t k = 0; k < n; ++k) { // avanzamos por la fila i y columna j, multiplicando y acomulando
                    result[i * p + j] += a.data[i * n + k] * b.data[k * p + j];
                }
            }
        }

    return move(Tensor({m, p}, result));
}
