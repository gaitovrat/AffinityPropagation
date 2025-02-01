# AffinityPropagation
Affinity Propagation

## Requirements
### Compiler Support
This project **requires the Clang compiler** due to its robust support for OpenMP. Other compilers, such as MSVC, may not be fully compatible with the current implementation.

### Prerequisites
Ensure you have the following installed:
1. **Clang Compiler**
2. **CMake**

### Command
```sh
cmake -S . -B build -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_C_COMPILER=clang
cmake --build build
```
