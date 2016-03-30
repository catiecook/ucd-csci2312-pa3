//
// Created by Catie Cook on 2/17/16.
//
#include "Point.h"
#include "Exceptions.h"

#include <iostream>
#include <cmath>
#include <sstream>
#include <string>
#include <iostream>

using namespace std;
namespace Clustering {


    unsigned int Point::__idGen = 0; // id generator

    //constructors
    Point::Point(unsigned int i)
    {


        __id = __idGen;
        ++__idGen; // increment IDs  as they are created

        __dim = i;
        __values = new double[__dim]; //array of doubles for ids

        for (int j = 0; j < __dim; ++j)
        {
            __values[j] = 0;
        }

        if (i == 0)
        {
            throw ZeroDimensionsEx();
        }
    }


    void Point::rewindIdGen()
    {

    }

    // **** BIG THREE ******
    // CPY CONST
    Point::Point(unsigned int i, double *pDouble)  //not necessary to use this constructor
    {
        __id = __idGen;
        ++__idGen; // increment IDs  as they are created

        __dim = i; //create array with dims
        __values = new double[__dim];
        for (int j = 0; j < __dim; ++j)
        {
            __values[j] = pDouble[j]; //fill the array with the dimensions/data
        }

    }

    Point::Point(const Point &p)
    {
        __dim = p.__dim;
        __values = new double[__dim]; //values is equal to an array of __dim dimensions
        __id = p.__id; //applying the private member functions here

        for (int i = 0; i < __dim; i++)
        {
            __values[i] = p.__values[i]; //copying over values into new array until __dim is run through
        }

    }

    // OVERLOADED =
    Point &Point::operator=(const Point &p)
    {
        if (__dim != p.__dim)
        {
            throw DimensionalityMismatchEx(p.__dim, __dim);
        }

//         (this != &p) {

            __dim = p.__dim;
            __id = p.__id;

            if (__values != nullptr)
                delete[] __values;

            __values = new double[__dim];

            for (int i = 0; i < __dim; ++i)
            {
                __values[i] = p.__values[i];

            }


        return *this;
    }


    // DESTRUCT
    Point::~Point()
    {
        delete [] __values;
    }

    unsigned int Point::getDims() const {
        return __dim;
    }

    int Point::getId() const
    {
        return __id;
    }

    // GET AND SET

    void Point::setValue(unsigned int i, double d)
    {
        if (i >= __dim) {
            throw OutOfBoundsEx(__dim, i);
        }
        __values[i] = d;

    }
    double Point::getValue(unsigned int d) const
    {
        if (d >= __dim)
        {
            throw OutOfBoundsEx(__dim, d);
        }

        return __values[d];

    }

    // **** DISTANCE TO FUNCTION ******

    double Point::distanceTo(const Point &point) const
    {
        if (point.__dim != __dim)
        {
            throw DimensionalityMismatchEx(point.__dim, __dim);
        }

        double sum = 0;
        double distance = 0;

        for (int i = 0; i < point.__dim; i++)
        {
            sum += pow(point.__values[i] - this->__values[i], 2);

        } //The values pointed to in point.

        distance = sqrt(sum);

        return distance;
    }

    // ******** OVERLOADED OPERATORS ******

    Point &Point::operator*=(double d)  // p *= 6; p.operator*=(6); //use for or while loop to multiply every point by the double
    {

        for (int i = 0; i < __dim; i++)
        {
            __values[i] = __values[i] * d;

        }
        return *this;

    }

    Point &Point::operator/=(double d) //use for or while loop to multiply every point by the double
    {
        //Point point(__dim);

        for (int i = 0; i < __dim; i++)
        {
            __values[i] = __values[i] / d;

        }
        return *this; //returns the point

    }

    const Point Point::operator*(double d) const
    {
        Point point(__dim);

        for (int i = 0; i < __dim; i++)
        {
           point.__values[i] = __values[i] * d;

        }
        return point;

    }

    const Point Point::operator/(double d) const
    {
        Point point(__dim);

        for (int i = 0; i < __dim; i++)
        {
            point.__values[i] = __values[i] / d;

        }
        return point;

    }

    double &Point::operator[](unsigned int index)
    {
        if (index >= __dim)
            throw OutOfBoundsEx(__dim, index);

        return __values[index];
    }


    const double &Point::operator[](unsigned int index) const
    {
        if (index >= __dim)
            throw OutOfBoundsEx(__dim, index);

        return __values[index];
    }

    //friends

    Point &operator+=(Point &point, const Point &point1)
    {
        if (point.__dim != point1.__dim)
        {
            throw DimensionalityMismatchEx(point.__dim, point1.__dim);
        }



        for (int i = 0; i < point.__dim; i++)
        {
            point.__values[i] += point1.__values[i];

        }

        return point;
    }

//    {
//        for (int i = 0; i < point; ++i)
//        {
//            point[i] += point1.getValue(i);
//
//        }
//        return point;
//    }

    Point &operator-=(Point &point, const Point &point1)

    {
        if (point.__dim != point1.__dim)
        {
            throw DimensionalityMismatchEx(point.__dim, point1.__dim);
        }



        for (int i = 0; i < point.__dim; i++)
        {
            point.__values[i] -= point1.__values[i];

        }

        return point;
    }

//    {
//        for (int i = 0; i < point; ++i)
//        {
//            point[i] -= point1.getValue(i);
//
//        }
//        return point;
//    }

    const Point operator+(const Point &point, const Point &point1) //defined this in class as an example
    {

        if (point.__dim != point1.__dim)
        {
            throw DimensionalityMismatchEx(point.__dim, point1.__dim);
        }

        Point point2(point.__dim);

            for (int i = 0; i < point2.__dim; i++)
            {
                point2.__values[i] = point.__values[i] + point1.__values[i];

            }
        return point2;

    }

    const Point operator-(const Point &point, const Point &point1)
    {

        if (point.__dim != point1.__dim)
        {
            throw DimensionalityMismatchEx(point.__dim, point1.__dim);
        }

        Point point2(point.__dim);

        for (int i = 0; i < point2.__dim; i++)
        {
            point2.__values[i] = point.__values[i] - point1.__values[i];

        }
        return point2;

    }

    bool operator==(const Point &point, const Point &point1)
    {
        if (point.__dim != point1.__dim)
        {
            throw DimensionalityMismatchEx(point.__dim, point1.__dim);
        }

        if (point.__dim != point1.__dim)
        {
            return false;
        }

        else
        {
            for ( int i = 0; i < point.__dim; i++)
            {
                if (point.__values[i] != point1.__values[i])
                    return false;
            }

            return true;
        }

        return true; //if values match return true

    }

    bool operator!=(const Point & point, const Point & point1)

    {

        if (point.__dim != point1.__dim)
        {
            return true;
        }

        else
        {
            for ( int i = 0; i < point.__dim; i++)
            {
                if (point.__values[i] != point1.__values[i])
                    return true;
            }

            return false;
        }
    }

    bool operator>(const Point & point, const Point & point1)
    {

        if (point.__dim != point1.__dim)
        {
            throw DimensionalityMismatchEx(point.__dim, point1.__dim);
        }

        else
        {
            for ( int i = 0; i < point.__dim; i++)
            {
                if (point.__values[i] > point1.__values[i])
                    return true;

                else if (point.__values[i] < point1.__values[i])
                {
                    return false;
                }
            }

            return false;
        }
    }

    bool operator<(const Point &point, const Point &point1)
    {
        if (point.__dim != point1.__dim)
        {
            throw DimensionalityMismatchEx(point.__dim, point1.__dim);
        }

        else
        {
            for ( int i = 0; i < point.__dim; i++)
            {
                if (point.__values[i] < point1.__values[i])
                    return true;

                else if (point.__values[i] > point1.__values[i])
                {
                    return false;
                }
            }

            return false;
        }

    }

    bool operator<=(const Point &point, const Point &point1)
    {
        return !(point > point1);
    }

    bool operator>=(const Point &point, const Point &point1)
    {
        return  !(point < point1);

    }
    ostream &operator<<(ostream &out, const Point &point) //module 3 lesson 11
    {

        int i = 0;
        for ( ; i < point.__dim - 1; ++i)
        {
            out << point.__values[i] << ", ";
        }
        out << point.__values[i];

        return out;
    }


    istream &operator>>(istream &is, Point &point) // find code for this in lesson 11.
    {

        string line;

        int count = 0;
        static const char POINT_VALUE_DELIM = ',';

        while (getline(is, line, ','))
        {
           point.__values[count] = stod(line);
            count++;
        }

        if (point.__dim != count)
        {
            throw DimensionalityMismatchEx(point.__dim, count);
        }

        return is;
    }



}//end of point.cpp




/*

 class Point {
    double a, b;
 public:
    Point () : Point (0, 0) {}
    Pint (double a, double b) : a(a), b(b) {} //the a outside the bracket is always going to be a member and inside will be argument so compiler knows which is which AKA no ambiguity

    double getA() const; { return a; }
    double getB() const; { return b; }
    void setA(double a) { this->a = a; } //the this pointer is the pointer to the current object point. When implimenting something you can use 'this' to point to the current value without explicitly setting it
    void setB(double b) { this ->b = b; } //this is equiv to (*this).a the pointer dereferences and points to it at once

     friend ostream @operator<<(ostream @os, const Point &p);
     };

     friend ostream @operator<<(ostream &os, const Point &p)
    {
    os <<  p.a << ", " << p.b << endl;

    return os;
    }



 TEMPLATES


 template <typename T> // the name doens't matter, just has to be something

 class Point {
    T a, b;
 public:
    Point () : Point (0, 0) {}
    Pint (T a, T b) : a(a), b(b) {} //the a outside the bracket is always going to be a member and inside will be argument so compiler knows which is which AKA no ambiguity

    T getA() const; { return a; }
    T getB() const; { return b; }
    void setA(double a) { this->a = a; } //the this pointer is the pointer to the current object point. When implimenting something you can use 'this' to point to the current value without explicitly setting it
    void setB(double b) { this ->b = b; } //this is equiv to (*this).a the pointer dereferences and points to it at once


    template <typename S>
     friend ostream @operator<<(ostream @os, const Point<S> &p);
     };

      template <typename W>
     friend ostream @operator<<(ostream &os, const Point<W> &p)
    {
    os <<  p.a << ", " << p.b << endl;

    return os;
    }

    int main () {
    cout << "Hellow World!" << endl;

    Point <double> p(6.7, 8.3);
    Point <int> point(6, 3);
    Point<std::string> spoint("one", "two")

 cout << p << endl;
 cout << point << endl;
 cout << spoint << endl;  //all types should work if the functionality of the template is correct









  template <typename T> // the name doens't matter, just has to be something

 class Point {
    int __dim;
    T *__values;

 public:
    Point (int dim) :
        __dim(dim),
        __values(new T[__dim])
        {}


    T getValue() const; { return __values[i]; }

    void setValue( int i, T a ) { values[i] = a; } //the this pointer is the pointer to the current object point. When implimenting something you can use 'this' to point to the current value without explicitly setting it
    void setB(double b) { this ->b = b; } //this is equiv to (*this).a the pointer dereferences and points to it at once

    T &operator[] (int i) { return __values[i]}

    template <typename S>
     friend ostream @operator<<(ostream @os, const Point<S> &p);
     };

 */


