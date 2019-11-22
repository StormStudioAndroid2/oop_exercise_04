#pragma once

#include <utility>
#include "Point.h"

template <typename T>
struct is_point : std::false_type {};

template <typename T>
struct is_point<Point<T>> : std::true_type {};

template <typename T, typename = void>
struct is_figure : std::false_type {};

template <typename T>
struct is_figure<T, std::void_t<decltype(std::declval<const T&>().getSquare()),
                    decltype(std::declval<const T&>().getCenter()),
                    decltype(std::declval<const T&>().print(std::cout)),
                    decltype(std::declval<T&>().scan(std::cin))>> : std::true_type {};

template <typename T> //площадь для всего, что имеет площадь
decltype(std::declval<const T&>().getSquare()) square(const T& figure) {
    return figure.getSquare();
}

template <typename T> //центр для всего, что имеет центр
decltype(std::declval<const T&>().getCenter()) center(const T& figure) {
    return figure.getCenter();
}

template <typename T, typename PrintReturnType = decltype(std::declval<const T&>().print(std::cout))> //вывод для классов с функцией Print
std::ostream& operator << (std::ostream& os, const T& figure) {
    figure.print(os);
    return os;
}

template <typename T, typename PrintReturnType = decltype(std::declval<T&>().scan(std::cin))> //вывод для классов с функцией Print
std::istream& operator >> (std::istream& is, T& figure) {
    figure.scan(is);
    return is;
}

template<class T>
struct is_figurelike_tuple : std::false_type {};

template<class Head, class... Tail>
struct is_figurelike_tuple<std::tuple<Head, Tail...>> : //проверяет, является ли T кортежом, из которых можно составить фигуру
        std::conjunction<is_point<Head>, std::is_same<Head, Tail>...> {};

template<size_t Id, class T>
double computeSquare(const T& tuple) {
    if constexpr (Id >= std::tuple_size_v<T>){
        return 0;
    }else{
        const auto dx1 = std::get<Id - 0>(tuple).x - std::get<0>(tuple).x;
        const auto dy1 = std::get<Id - 0>(tuple).y - std::get<0>(tuple).y;
        const auto dx2 = std::get<Id - 1>(tuple).x - std::get<0>(tuple).x;
        const auto dy2 = std::get<Id - 1>(tuple).y - std::get<0>(tuple).y;
        const double localSquare = std::abs(dx1 * dy2 - dy1 * dx2) * 0.5;
        return localSquare + computeSquare<Id + 1>(tuple);
    }
}

template<typename T>
std::enable_if_t<is_figurelike_tuple<T>::value, double> square(const T& object) {
    if constexpr (std::tuple_size_v<T> < 3){
        return 0;
    }else{
        return computeSquare<2>(object);
    }
}


template<size_t Id, typename T>
std::tuple_element_t<0,T> computeCenter(const T& tuple) {
    if constexpr (Id == std::tuple_size_v<T> - 1){
        return std::get<Id>(tuple);
    } else {
        return std::get<Id>(tuple) + computeCenter<Id + 1>(tuple);
    }
}


template<typename T>
std::enable_if_t<is_figurelike_tuple<T>::value, std::tuple_element_t<0,T>> center(const T& object) {
    return computeCenter<0>(object) / std::tuple_size_v<T>;
}

template<size_t Id, typename T>
void printTuple(std::ostream& os, const T& tuple) {
    if constexpr (Id == std::tuple_size_v<T> - 1) {
        os << "(" << std::get<Id>(tuple) << ")";
    } else {
        os << "(" << std::get<Id>(tuple) << ") ";
        printTuple<Id + 1>(os, tuple);
    }
}

template <typename T>
typename std::enable_if<is_figurelike_tuple<T>::value, std::ostream&>::type operator << (std::ostream& os, const T& tuple) {
    os << "Figurelike tuple of " << std::tuple_size_v<T> << " elements: ";
    printTuple<0>(os, tuple);
    return os;
}

template<size_t Id, typename T>
void scanTuple(std::istream& is, T& tuple) {
    if constexpr (Id == std::tuple_size_v<T> - 1) {
        is >> std::get<Id>(tuple);
    } else {
        is >> std::get<Id>(tuple);
        scanTuple<Id + 1>(is, tuple);
    }
}

template <typename T>
typename std::enable_if<is_figurelike_tuple<T>::value, std::istream&>::type operator >> (std::istream& is, T& tuple) {
    scanTuple<0>(is, tuple);
    return is;
}

template <typename T>
typename std::enable_if<is_figurelike_tuple<T>::value, void>::type process(T& tup) {
    std::cin >> tup;
    std::cout << tup << "\n";
    std::cout << "Area of figurelike tuple: " << square(tup) << "\n";
    std::cout << "Center of figurelike tuple: " << center(tup) << "\n";

}

template <typename T>
typename std::enable_if<is_figure<T>::value, void>::type process(T& fig) {
    std::cin >> fig;
    std::cout << fig << "\n";
    std::cout << "Area of figure: " << square(fig) << "\n";
    std::cout << "Center of figure: " << center(fig) << "\n";

}