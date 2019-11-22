#pragma once

#include <vector>
template <typename T>

class Trapeze {
    public:
    Point<T> points[4];
    Trapeze<T>() = default;
    Trapeze(Point<T> p1, Point<T> p2, Point<T> p3, Point<T> p4);
    double getSquare() const;
    Point<T> getCenter() const ;
    void scan(std::istream &is);
    void print(std::ostream& os) const;
};
template <typename T>
Trapeze<T>::Trapeze(Point<T> p1, Point<T> p2, Point<T> p3, Point<T> p4) {
       if (IsParallel(p1,p2,p3,p4) 
        && !IsParallel(p1,p3,p2,p4)) {
        std::swap(p2, p3);

    } else if (!IsParallel(p1,p2,p3,p4) 
        && IsParallel(p1,p3,p2,p4)) {

    
    } else {
        throw std::logic_error("not Trapeze");
    }
    this->points[0] = p1;
    this->points[1] = p2;
    this->points[2] = p3;
    this->points[3] = p4; 
    }


template <typename T>   
double Trapeze<T>::getSquare() const {

    return (length(this->points[0],this->points[2])+length(this->points[1],this->points[3]))*fabs((this->points[0].y-this->points[1].y))*(0.5);
}
template <typename T>
void Trapeze<T>::print(std::ostream& os) const {
    os << "Trapeze ";
    for (int i = 0; i < 4; ++i) {
        os << this->points[i] << " p" << i+1 <<" ";
    }
        os << std::endl;

}

template <typename T>
void Trapeze<T>::scan(std::istream &is) {
    Point<T> p1,p2,p3,p4;
    is >> p1 >> p2 >> p3 >> p4;
    *this = Trapeze(p1,p2,p3,p4);
}

template <typename T>
Point<T> Trapeze<T>::getCenter() const {

    Point<T> p;
    p.x = 0;
    p.y = 0;
    for (size_t i = 0; i <4; ++i) {
        p = p+(points[i]/4);
    }
    return p;
}



