#ifndef TENSORTRANFORM_H
#define TENSORTRANFORM_H
#include "Tensor.h"
//Clase abstracta

class TensorTranform {
public :// Permite aplicar una transformación al tensor actual.
// Recibe un objeto de tipo TensorTransform (o una clase derivada)
// y ejecuta su metodo apply usando polimorfismo dinámico.
// *this representa el tensor actual que será transformado.
// Retorna un nuevo tensor con la transformación aplicada.
virtual Tensor apply( const Tensor & t ) const = 0;
    virtual ~ TensorTranform () = default ;
};
//Plantilla para crear transformaciones
//Tensor actual - enviar a transformador - recibir nuevo tensor



#endif