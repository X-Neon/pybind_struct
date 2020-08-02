# pybind_struct

pybind_struct is a single header include that defines macros for exporting aggregate classes when using pybind11. This reduces the amount of boilerplate necessary when exposing simple structs to Python.

For example, consider the following struct:

```cpp
struct example
{
    int a;
    float b;
    std::vector<double> c;
};
```

The macro `PYBIND_STRUCT_READWRITE(example, a, b, c)` is equivalent to:

```cpp
py::class_<example>(m, "example")
    .def(py::init<>())
    .def(py::init<int, float, std::vector<double>>(), py::arg("a")=int{}, py::arg("b")=float{}, py::arg("c")=std::vector<double>{})
    // + Other Python magic functions, listed below
    .def_readwrite("a", &example::a)
    .def_readwrite("b", &example::b)
    .def_readwrite("c", &example::c);
```

There also exists `PYBIND_STRUCT_READONLY` which defines no constructors and read-only access to its members, and `PYBIND_STRUCT_ENUM` for defining enums in a similar fashion. 

pybind_struct will also define magic methods on your type:

* Pickle serialization and deserialization support
* `__copy__` and `__deepcopy__`
* `__str__` if `std::ostream << Type` is valid
* `__nonzero__ / __bool__` (depending on Python 2/3) if `std::is_convertible<Type, bool>` is true
* `__eq__`, `__ne__`, `__lt__`, `__le__`, `__gt__` and `__ge__` if `Type OPERATOR Type` is valid for the corresponding operator

## Requirements

pybind_struct requires a C++17 compliant compiler.

## Usage

To use pybind_struct, simply include the single header file:

```cpp
#include "pybind_struct.hpp"
```
