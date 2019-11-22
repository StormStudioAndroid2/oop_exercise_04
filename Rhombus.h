#pragma once
#include "Point.h"

#include <vector>
template <typename T>
class Rhombus {
    public:
        Point<T> points[4];
        Rhombus() = default;
        Rhombus(Point<T> p1, Point<T> p2, Point<T> p3, Point<T> p4);
        double getSquare() const;
        Point<T> getCenter() const;
        void print(std::ostream& os) const;
        void scan(std::istream &is);
};
template <typename T>
Rhombus<T>::Rhombus(Point<T> p1, Point<T> p2, Point<T> p3, Point<T> p4) {
       if (length(p1, p2) == length(p1, p4)
        && length(p3, p4) == length(p2, p3)
        && length(p1, p2) == length(p2, p3)) {

    } else if (length(p1, p4) == length(p1, p3)
           && length(p2, p3) == length(p2, p4)
           && length(p1, p4) == length(p2, p4)) {
        std::swap(p2, p3);
    } else if (length(p1, p3) == length(p1, p2)
              && length(p2, p4) == length(p3, p4)
              && length(p1, p2)== length(p2, p4)) {
        std::swap(p3, p4);
    } else {
        throw std::logic_error("not rhombus");
    }
    this->points[0] = p1;
    this->points[1] = p2;
    this->points[2] = p3;
    this->points[3] = p4; 
}
template <typename T>
double Rhombus<T>::getSquare() const {
	return length(this->points[1],this->points[3])*length(this->points[0],this->points[2])*0.5;
    }


template <typename T>
Point<T> Rhombus<T>::getCenter() const {

    Point<T> p;
    p.x = 0;
    p.y = 0;
    for (int i = 0; i < 4; ++i) {
        p = p+(points[i]/4);
    }
    return p;
}



template <typename T>
void Rhombus<T>::scan(std::istream &is) {
    Point<T> p1,p2,p3,p4;
    is >> p1 >> p2 >> p3 >> p4;
    *this = Rhombus(p1,p2,p3,p4);
}
template <typename T>
      void Rhombus<T>::print(std::ostream& os) const {
    os << "Rhombus: ";
    for (int i = 0; i < 4; ++i) {
        os << this->points[i] << "p" << i+1 <<" ";
    }
        os << std::endl;

    }

