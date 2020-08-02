#pragma once

#include <functional>
#include <sstream>
#include <type_traits>

#include <pybind11/pybind11.h>
#include <pybind11/operators.h>

namespace pybind_struct {

template <typename _Tp, typename dummy = void>
struct is_printable : std::false_type {};

template <typename _Tp>
struct is_printable<_Tp, typename std::void_t<decltype(std::declval<std::ostringstream>() << std::declval<_Tp>())>> : std::true_type {};

template <typename C, typename T>
void add_print_method(C& cls)
{
    if constexpr (is_printable<T>::value) {
        cls.def("__str__", [](const T& t) {
            std::ostringstream s;
            s << t;
            return s.str();
        });
    }
}

template <typename _Tp, typename Cmp, typename dummy = void>
struct has_cmp_op : std::false_type {};

template <typename _Tp, typename Cmp>
struct has_cmp_op<_Tp, Cmp, 
    typename std::enable_if_t<std::is_same_v<decltype(Cmp()(std::declval<_Tp>(), std::declval<_Tp>())), bool>>> : std::true_type {};

template <typename C, typename T, typename Cmp>
void add_cmp_method(C& cls, Cmp cmp = Cmp())
{
    if constexpr (has_cmp_op<T, Cmp>::value) {
        cls.def(cmp(pybind11::self, pybind11::self));
    }
}

template <typename C, typename T>
void add_bool_method(C& cls)
{
    if constexpr (std::is_convertible<T, bool>::value) {
        cls.def(PYBIND11_BOOL_ATTR, [](const T& t) {
            return bool(t);
        });
    }
}

template <typename C, typename T>
void add_copy_methods(C& cls)
{
    cls.def("__copy__", [](const T& t) {
        return t;
    });
    cls.def("__deepcopy__", [](const T& t, pybind11::dict) {
        return t;
    });
}

}

#define PYBIND_STRUCT_CONCATENATE(arg1, arg2)  arg1##arg2
#define PYBIND_STRUCT_FOR_ARG_N(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, N, ...) N 
#define PYBIND_STRUCT_FOR_RSEQ_N() 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0
#define PYBIND_STRUCT_FOR_NARG(...) PYBIND_STRUCT_FOR_NARG_(__VA_ARGS__, PYBIND_STRUCT_FOR_RSEQ_N())
#define PYBIND_STRUCT_FOR_NARG_(...) PYBIND_STRUCT_FOR_ARG_N(__VA_ARGS__) 

#define PYBIND_STRUCT_FOR_T_1(what, x, ...) what(x)
#define PYBIND_STRUCT_FOR_T_2(what, x, ...) what(x), PYBIND_STRUCT_FOR_T_1(what, __VA_ARGS__)
#define PYBIND_STRUCT_FOR_T_3(what, x, ...) what(x), PYBIND_STRUCT_FOR_T_2(what, __VA_ARGS__)
#define PYBIND_STRUCT_FOR_T_4(what, x, ...) what(x), PYBIND_STRUCT_FOR_T_3(what, __VA_ARGS__)
#define PYBIND_STRUCT_FOR_T_5(what, x, ...) what(x), PYBIND_STRUCT_FOR_T_4(what, __VA_ARGS__)
#define PYBIND_STRUCT_FOR_T_6(what, x, ...) what(x), PYBIND_STRUCT_FOR_T_5(what, __VA_ARGS__)
#define PYBIND_STRUCT_FOR_T_7(what, x, ...) what(x), PYBIND_STRUCT_FOR_T_6(what, __VA_ARGS__)
#define PYBIND_STRUCT_FOR_T_8(what, x, ...) what(x), PYBIND_STRUCT_FOR_T_7(what, __VA_ARGS__)
#define PYBIND_STRUCT_FOR_T_9(what, x, ...) what(x), PYBIND_STRUCT_FOR_T_8(what, __VA_ARGS__)
#define PYBIND_STRUCT_FOR_T_10(what, x, ...) what(x), PYBIND_STRUCT_FOR_T_9(what, __VA_ARGS__)
#define PYBIND_STRUCT_FOR_T_11(what, x, ...) what(x), PYBIND_STRUCT_FOR_T_10(what, __VA_ARGS__)
#define PYBIND_STRUCT_FOR_T_12(what, x, ...) what(x), PYBIND_STRUCT_FOR_T_11(what, __VA_ARGS__)
#define PYBIND_STRUCT_FOR_T_13(what, x, ...) what(x), PYBIND_STRUCT_FOR_T_12(what, __VA_ARGS__)
#define PYBIND_STRUCT_FOR_T_14(what, x, ...) what(x), PYBIND_STRUCT_FOR_T_13(what, __VA_ARGS__)
#define PYBIND_STRUCT_FOR_T_15(what, x, ...) what(x), PYBIND_STRUCT_FOR_T_14(what, __VA_ARGS__)
#define PYBIND_STRUCT_FOR_T_16(what, x, ...) what(x), PYBIND_STRUCT_FOR_T_15(what, __VA_ARGS__)

#define PYBIND_STRUCT_FOR_T_(N, what, ...) PYBIND_STRUCT_CONCATENATE(PYBIND_STRUCT_FOR_T_, N)(what, __VA_ARGS__)
#define PYBIND_STRUCT_FOR_T(what, ...) PYBIND_STRUCT_FOR_T_(PYBIND_STRUCT_FOR_NARG(__VA_ARGS__), what, __VA_ARGS__)

#define PYBIND_STRUCT_FOR_S_1(what, x, ...) what(x)
#define PYBIND_STRUCT_FOR_S_2(what, x, ...) what(x) PYBIND_STRUCT_FOR_S_1(what, __VA_ARGS__)
#define PYBIND_STRUCT_FOR_S_3(what, x, ...) what(x) PYBIND_STRUCT_FOR_S_2(what, __VA_ARGS__)
#define PYBIND_STRUCT_FOR_S_4(what, x, ...) what(x) PYBIND_STRUCT_FOR_S_3(what, __VA_ARGS__)
#define PYBIND_STRUCT_FOR_S_5(what, x, ...) what(x) PYBIND_STRUCT_FOR_S_4(what, __VA_ARGS__)
#define PYBIND_STRUCT_FOR_S_6(what, x, ...) what(x) PYBIND_STRUCT_FOR_S_5(what, __VA_ARGS__)
#define PYBIND_STRUCT_FOR_S_7(what, x, ...) what(x) PYBIND_STRUCT_FOR_S_6(what, __VA_ARGS__)
#define PYBIND_STRUCT_FOR_S_8(what, x, ...) what(x) PYBIND_STRUCT_FOR_S_7(what, __VA_ARGS__)
#define PYBIND_STRUCT_FOR_S_9(what, x, ...) what(x) PYBIND_STRUCT_FOR_S_8(what, __VA_ARGS__)
#define PYBIND_STRUCT_FOR_S_10(what, x, ...) what(x) PYBIND_STRUCT_FOR_S_9(what, __VA_ARGS__)
#define PYBIND_STRUCT_FOR_S_11(what, x, ...) what(x) PYBIND_STRUCT_FOR_S_10(what, __VA_ARGS__)
#define PYBIND_STRUCT_FOR_S_12(what, x, ...) what(x) PYBIND_STRUCT_FOR_S_11(what, __VA_ARGS__)
#define PYBIND_STRUCT_FOR_S_13(what, x, ...) what(x) PYBIND_STRUCT_FOR_S_12(what, __VA_ARGS__)
#define PYBIND_STRUCT_FOR_S_14(what, x, ...) what(x) PYBIND_STRUCT_FOR_S_13(what, __VA_ARGS__)
#define PYBIND_STRUCT_FOR_S_15(what, x, ...) what(x) PYBIND_STRUCT_FOR_S_14(what, __VA_ARGS__)
#define PYBIND_STRUCT_FOR_S_16(what, x, ...) what(x) PYBIND_STRUCT_FOR_S_15(what, __VA_ARGS__)

#define PYBIND_STRUCT_FOR_S_(N, what, ...) PYBIND_STRUCT_CONCATENATE(PYBIND_STRUCT_FOR_S_, N)(what, __VA_ARGS__)
#define PYBIND_STRUCT_FOR_S(what, ...) PYBIND_STRUCT_FOR_S_(PYBIND_STRUCT_FOR_NARG(__VA_ARGS__), what, __VA_ARGS__)

#define PYBIND_STRUCT_INIT_TYPE(Field) decltype(PyBindMacroType::Field)
#define PYBIND_STRUCT_ARG(Field) pybind11::arg(#Field)=decltype(PyBindMacroType::Field){}
#define PYBIND_STRUCT_FIELD_RW(Field) .def_readwrite(#Field, &PyBindMacroType::Field)
#define PYBIND_STRUCT_FIELD_RO(Field) .def_readonly(#Field, &PyBindMacroType::Field)
#define PYBIND_STRUCT_FIELD_ENUM(Field) .value(#Field, &PyBindMacroType::Field)
#define PYBIND_STRUCT_INST_FIELD(Field) t.Field
#define PYBIND_STRUCT_TUPLE_ITER(Field) p.Field = (*b++).cast<decltype(PyBindMacroType::Field)>();

#define PYBIND_STRUCT_PICKLE(...) \
    .def(pybind11::pickle( \
        [](const PyBindMacroType& t){ \
            return pybind11::make_tuple(PYBIND_STRUCT_FOR_T(PYBIND_STRUCT_INST_FIELD, __VA_ARGS__)); \
        }, \
        [](py::tuple t){ \
            PyBindMacroType p; \
            auto b = t.begin(); \
            PYBIND_STRUCT_FOR_S(PYBIND_STRUCT_TUPLE_ITER, __VA_ARGS__) \
            return p; \
        } \
    ))

#define PYBIND_STRUCT_AUX_METHODS(cls) \
    pybind_struct::add_copy_methods<decltype(cls), PyBindMacroType>(cls); \
    pybind_struct::add_print_method<decltype(cls), PyBindMacroType>(cls); \
    pybind_struct::add_bool_method<decltype(cls), PyBindMacroType>(cls); \
    pybind_struct::add_cmp_method<decltype(cls), PyBindMacroType, std::equal_to<>>(cls); \
    pybind_struct::add_cmp_method<decltype(cls), PyBindMacroType, std::not_equal_to<>>(cls); \
    pybind_struct::add_cmp_method<decltype(cls), PyBindMacroType, std::greater<>>(cls); \
    pybind_struct::add_cmp_method<decltype(cls), PyBindMacroType, std::greater_equal<>>(cls); \
    pybind_struct::add_cmp_method<decltype(cls), PyBindMacroType, std::less<>>(cls); \
    pybind_struct::add_cmp_method<decltype(cls), PyBindMacroType, std::less_equal<>>(cls);

#define PYBIND_STRUCT_READWRITE(Module, Type, ...) \
    { \
        using PyBindMacroType = Type; \
        auto cls = pybind11::class_<Type>(Module, #Type) \
            .def(pybind11::init<>()) \
            .def(pybind11::init<PYBIND_STRUCT_FOR_T(PYBIND_STRUCT_INIT_TYPE, __VA_ARGS__)>(), PYBIND_STRUCT_FOR_T(PYBIND_STRUCT_ARG, __VA_ARGS__)) \
            PYBIND_STRUCT_PICKLE(__VA_ARGS__) \
            PYBIND_STRUCT_FOR_S(PYBIND_STRUCT_FIELD_RW, __VA_ARGS__); \
        PYBIND_STRUCT_AUX_METHODS(cls) \
    }

#define PYBIND_STRUCT_READONLY(Module, Type, ...) \
    { \
        using PyBindMacroType = Type; \
        auto cls = pybind11::class_<Type>(Module, #Type) \
            PYBIND_STRUCT_PICKLE(__VA_ARGS__) \
            PYBIND_STRUCT_FOR_S(PYBIND_STRUCT_FIELD_RO, __VA_ARGS__); \
        PYBIND_STRUCT_AUX_METHODS(cls) \
    }

#define PYBIND_STRUCT_ENUM(Module, Type, ...) \
    { \
        using PyBindMacroType = Type; \
        pybind11::enum_<Type>(Module, #Type) \
            PYBIND_STRUCT_FOR_S(PYBIND_STRUCT_FIELD_ENUM, __VA_ARGS__); \
    }
