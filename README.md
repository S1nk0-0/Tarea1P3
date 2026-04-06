# Tensor++ - Programación III

Implementación en C++ de una librería básica de tensores inspirada en bibliotecas como NumPy y PyTorch.

## Integrantes
- Danilson
- Ferrel Valentino Infante Garcia

## Descripción
Este proyecto desarrolla una clase `Tensor` capaz de trabajar con tensores de hasta 3 dimensiones, utilizando memoria dinámica y aplicando conceptos de Programación Orientada a Objetos.

La implementación incluye:
- creación de tensores con `zeros`, `ones`, `random` y `arange`
- gestión de memoria con constructor de copia, constructor de movimiento, asignación de copia, asignación de movimiento y destructor
- transformaciones polimórficas mediante `TensorTranform`
- funciones de activación `ReLU` y `Sigmoid`
- sobrecarga de operadores
- modificación de dimensiones con `view` y `unsqueeze`
- concatenación con `concat`
- funciones amigas `dot` y `matmul`
- una demostración en `main.cpp` de una red neuronal simple

## Estructura del proyecto

- `Tensor.h` / `Tensor.cpp`  
  Implementación principal de la clase `Tensor`.

- `TensorTranform.h` / `TensorTranform.cpp`  
  Interfaz abstracta para transformaciones aplicables a tensores.

- `RELU.h` / `RELU.cpp`  
  Implementación de la función de activación ReLU.

- `Sigmoid.h` / `Sigmoid.cpp`  
  Implementación de la función de activación Sigmoid.

- `main.cpp`  
  Programa principal de prueba.

- `CMakeLists.txt`  
  Archivo de configuración para compilación con CMake.


## Compilación con CMake

### Opción 1: desde CLion
1. Abrir el proyecto en CLion.
2. Esperar a que CMake cargue el proyecto.
3. Compilar con el botón **Build** o **Run**.

