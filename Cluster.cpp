//
// Created by Catie Cook on 2/17/16.
//


#include <cassert>
#include <sstream>
#include <iostream>
#include <fstream>
#include "Cluster.h"
#include "Exceptions.h"
#include "Point.h"

using namespace std;
namespace Clustering {


    LNode::LNode(const Point &p, LNodePtr a) : point(p)
    {
       // point = p;
        next = a;
    }
    void Cluster::__del() {

    }

    bool Cluster::__in(const Point &p) const
    {
        return false;
    }

    void Cluster::__cpy(LNodePtr pts)
    {

    }





// ~~~~~~~~~~~~ INNER CLASS: CENTROID ~~~~~~~~~~~~~

    Cluster::Centroid::Centroid(unsigned int d, const Cluster &c) : __dimensions(d),
                                                                    __p(d),
                                                                    __c(c),
                                                                    __valid(false)
    {
       if (__c.__size == 0)
           __valid = false;
        toInfinity();

//        if (c.__size == 0)
//        {
//            throw ZeroClustersEx();
//        }


    }

    const Point Cluster::Centroid::get() const
    {
        return __p;
    }

    void Cluster::Centroid::set(const Point &p)
    {
        __valid = true;
        __p = p;
    }

    bool Cluster::Centroid::isValid() const
    {

        return __valid;
    }

    void Cluster::Centroid::setValid(bool valid)
    {
        __valid = valid;
    }

    void Cluster::Centroid::compute() //error checking for our own code
    {
        if (__c.__points == nullptr) //checking that there are points and then asserting if the other is the case
        {
            assert(__c.__size == 0);
            toInfinity();
            return;
        }

        LNodePtr curr = __c.__points;
        Point p(__c.getDimensionality());
        unsigned int sizeCheck = 0;

        while (curr!=nullptr)
        {
            p += curr->point / __c.getSize();
            curr = curr->next;
            sizeCheck++;
        }
        assert(sizeCheck == __c.getSize());
        set(p); //set will validate the point and set it
    }

    bool Cluster::Centroid::equal(const Point &point) const
    {
        bool equal = true;

        if (__dimensions == 0) //if something goes wrong in this test it might be here
        {
            throw ZeroDimensionsEx();
        }

        for (unsigned int i = 0; i < __dimensions; i++) {
            if (__p[i] != point[i])
            {
                equal = false;
            }
        }

        return equal;
    }

    void Cluster::Centroid::toInfinity() //got help from a classmate for this one, I just couldn't figure it out
    {
        for (unsigned int i =0; i < __dimensions; ++i)
        {
            __p[i] = numeric_limits<double>::max();

        }
    }


// ~~~~~~~~~~~~ PUBLIC CLUSTER DEFINITIONS ~~~~~~~~~~~~~

    unsigned int Cluster::__idGenerator = 0;
    const char POINT_CLUSTER_ID_DELIMINATOR = ':';

    Cluster::Cluster(unsigned int d) : __dimensionality(d),
                                       __size(0),
                                       __points(nullptr),
                                       __id(__idGenerator++),
                                       centroid(d, *this)
    {
//        if (d != __dimensionality)
//        {
//            throw DimensionalityMismatchEx(d, __dimensionality);
//        }

    }

    Cluster::Cluster(const Cluster &cluster)  : Cluster(cluster.__dimensionality)
    {

        for ( int i = 0; i <cluster.getSize(); i ++)
            add(cluster[i]);

        __id = cluster.__id;
        centroid.compute();
//
        if (cluster.__dimensionality != __dimensionality)
        {
            throw DimensionalityMismatchEx(cluster.__dimensionality, __dimensionality);
        }

//        if (__dimensionality = 0)
//        {
//            throw ZeroClustersEx();
//        }
//
    }


    Cluster &Cluster::operator=(const Cluster &c)

//    {
//        if (__size > 0) {
//            LNodePtr destroy;
//            LNodePtr cursor = __points;
//
//            while (cursor != nullptr) {
//                destroy = cursor;
//                cursor = cursor->next;
//
//                delete destroy;
//            }
//            __size = 0;
//        }
//
//        for (int i = 0; i < c.getSize(); ++i)
//        {
//            add(c[i]);
//        }
//
//        __id = c.__id;
//        centroid.compute();
//
//        return c;
//    }


    {
        if (__size > 0)
        {
            LNodePtr temp;
            LNodePtr cursor = __points;

            while (cursor != nullptr) {
                temp = cursor;
                cursor = cursor->next;

                delete temp;
            }
            __size = 0;
        }

        for (int i = 0; i < c.getSize(); i++)
        {
            add(c[i]);
        }

        return *this;
    }

    Cluster::~Cluster()
    {
        LNodePtr curr;
        while (__points != nullptr)
        {
            curr = __points;
            __points = curr->next; //curr ptr points to the next data and deletes it and then moves on to the next

            delete curr;
        }
    }


   unsigned int Cluster::getSize() const
   {

        return __size;
    }


    unsigned int Cluster::getDimensionality() const
    {
       return __dimensionality;
    }

    unsigned int Cluster::getId() const
    {
//
//        if (__id == 0)
//        {
//            throw ZeroDimensionsEx();
//        }
        return __id;
    }

    void Cluster::add(const Point &point)
    {
        if (__dimensionality != point.getDims())
        {
            throw DimensionalityMismatchEx(__dimensionality, point.getDims());
        }

        if (__size == 0)
        {
            ++__size;
            __points = new LNode(point, nullptr);
            centroid.setValid(false);
        }

        else
        {
            //find the right spot
            LNodePtr n = __points, p = nullptr;

           centroid.setValid(false);

            while (n != nullptr)
            {
                if (point < n->point)
                {
                    if (p == nullptr)
                    {
                        __points = new LNode(point, n);

                        ++__size;

                        return;
                    }
                }

                p = n;
                n = n->next;
            }
            ++__size;
            p->next = new LNode(point, nullptr);
//
            }

    } //end Add

    const Point &Cluster::remove(const Point &ptr)  {
        //if no points exist
        //assert(const Point &ptr)
        if (contains(ptr)) {


            LNodePtr c;
            LNodePtr pre = nullptr;

            c = __points; //n = __points->next; //n is = to the pint after __ppoints aka next node

            while (c != nullptr) {

                if (c->point == ptr)  //the point was found
                {
                    if (pre == nullptr) {
                        __points = c->next; //the c (next) local pointer points to the next node

                        delete c;

                        --__size; //decrements size one so we keep track of current size

                        break;
                    }
//
//

                }//end second if

                pre = c;
                c = c->next; //c is a ptf now pointing to the new current node which is the old next node

            } // end while
        } //end first if
        return ptr;

    } //end function


    bool Cluster::contains(const Point &p) const
    {
        if (__dimensionality != p.getDims())
        {
            throw DimensionalityMismatchEx(__dimensionality, p.getDims());
        }

        LNodePtr c = __points; //same as previous declaration

        while (c != nullptr) {
            if (c->point.getId() == p.getId()) {
                return true;
            }
            else
                c = c->next;
        }

        return false; //all of the if statements skipped, return = false
    }

    void Cluster::pickCentroids(unsigned int k, Point **pointArray)
//    {
//        if (k >= __size) {
//            for (unsigned int i = 0; i < __size; ++i) {
//                *(pointArray[i]) = (*this)[i];
//            }
//            if (k > __size) {
//                for (unsigned int i = __size; i < k; ++i) {
//                    //pointArray[i] = new Point(__dimensionality);
//                    for (unsigned int d = 0; d < __dimensionality; ++d) {
//                        pointArray[i]->setValue(d, std::numeric_limits<double>::max());
//                        //(pointArray[i])[d] = std::numeric_limits<double>::max();
//                    }
//                }
//            }
//        }
//        else {
//            if (k > 100) {
//                for (unsigned int i = 0; i < k; ++i) {
//                    *(pointArray[i]) = (*this)[i];
//                }
//            }
//            else {
//                *(pointArray[0]) = __points->point;
//                // a is index of point k
//                // b is index of cluster
//                // c is index of distance between pointArray and next point
//                for (unsigned int a = 1; a < k; ++a) {
//                    double avgD = 0;
//                    unsigned int furIndx = 0;
//                    for (unsigned int b = 0; b < __size; ++b) {
//                        double nextD = 0;
//                        bool used = false;
//
//                        // Average distance between current point and pointArray
//                        for (unsigned int c = 0; c < a; ++c) {
//                            nextD += ((*this)[b]).distanceTo(*(pointArray[c]));
//                            if ((*this)[b] == *(pointArray[c]))
//                                used = true;
//                        }
//                        nextD /= a;
//
//                        // New furthest point
//                        if (nextD > avgD && !used) {
//                            avgD = nextD;
//                            furIndx = b;
//                        }
//                    }
//                    *(pointArray[a]) = (*this)[furIndx];
//                    //pointArray[a] = new Point((*this)[furIndx]);
//                }
//            }
//        }
//    }



    {
        if (k >= __size)
        {
            for (unsigned int i = 0; i < __size; i++)
            {
                *(pointArray[i]) = (*this)[i];
            }
            if (k > __size)
            {
                for (unsigned int i = __size; i < k; i++)
                {
                    for (unsigned int d = 0; d < __dimensionality; d++)
                    {
                        pointArray[i]->setValue(d, numeric_limits<double>::max());

                    }
                }
            }
        }
        else
        {
            if (k > 100)
            {
                for (unsigned int i = 0; i < k; ++i)
                {
                    *(pointArray[i]) = (*this)[i];
                }
            }

            else
            {
                *(pointArray[0]) = __points->point;
                for (unsigned int a = 1; a < k; ++a)
                {
                    double avgD = 0; 
                    unsigned int furIndx = 0; 
                    for (unsigned int b = 0; b < __size; ++b)
                    { 
                        double nextD = 0; 
                        bool used = false;

                        for (unsigned int c = 0; c < a; ++c)
                        {
                            nextD += ((*this)[b]).distanceTo(*(pointArray[c]));
                            if ((*this)[b] == *(pointArray[c]))
                                used = true;
                        }
                        nextD /= a;
                        if (nextD > avgD && !used)
                        {
                            avgD = nextD;
                            furIndx = b;
                        }
                    }
                    *(pointArray[a]) = (*this)[furIndx];

                }
            }
        }
}

// ~~~~~~~~~~~~ OVERLOADED OPERATORS ~~~~~~~~~~~~~~

    //COMPARING

    bool operator!=(const Cluster &lhclus, const Cluster &rhclus) //test for non-equality
    {
        return !(lhclus == rhclus); //can do this because I have already declared the operator == with the bool, so it sees this declaraion as a bool.
//        if (lhclus == 0)
//        {
//            throw EmptyClusterEx();
//        }
//        if (rhclus == 0)
//        {
//            throw EmptyClusterEx();
//        }
//
//        if (lhclus.__points != rhclus.__points)
//        {
//            return true;
//        }
//
//        else
//        {
//            for ( int i = 0; i < lhclus.__size; i++)
//            {
//                if (lhclus[i] != rhclus[i])
//                    return true;
//            }
//
//            return false;
//        }
//      else
//            return !(lhclus == rhclus); //can do this because I have already declared the operator == with the bool, so it sees this declaraion as a bool.

   }

    bool operator==(const Cluster &lhclus, const Cluster &rhclus) //test for equality
    {
        if (lhclus.__dimensionality != rhclus.__dimensionality)
        {
            throw DimensionalityMismatchEx(lhclus.__dimensionality, rhclus.__dimensionality);
        }

        if (lhclus.getSize() != rhclus.getSize())
            return false;

        for (int i = 0; i < lhclus.getSize(); ++i) {
            if (lhclus[i] != rhclus[i])
                return false;
        }

        return true;
    }
//        if (lhclus.__dimensionality != rhclus.__dimensionality) {
//            throw DimensionalityMismatchEx(lhclus.__dimensionality, rhclus.__dimensionality);
//        }
//
//        if (rhclus.__dimensionality != lhclus.__dimensionality)
//            return false; //not equal
//
//        else
//        {
//            //for (int i = 0; i < lhclus.__dimensionality; i++)
//            //{
////                if (lhclus[i] != rhclus[i])
////                    return false;
//
//                for (int i = 0; i < lhclus.getSize(); ++i)
//                {
//                    if (lhclus[i] != rhclus[i])
//                        return false; //tests for equality through cluster nodes and returns false if it finds nonequality
//                }
//
//                return true; //if all are equal it returns true
//            //}
//        }
//    } //end function operator==

    //~~~~~~~~~~ SUBSRIPT ~~~~~~~~~~~~~~

    const Point &Cluster::operator[](unsigned int u) const
    {
        if (__size == 0)
        {
            throw EmptyClusterEx();
        }

        if(u >= __size) //if there isn't room
        {
            throw OutOfBoundsEx(u, __size);
        }

      LNodePtr cursor = __points; // cursor that points to __points

        for (int i = 0; i < u; i++)
        {
            //this->__points[u];
            cursor = cursor->next;

        }

        return cursor->point;

    }

    // ~~~~~~~~~ IO ~~~~~~~~
    // ~~~~~~ Friends ~~~~~~

    ostream &operator<<(ostream &out, const Cluster &c)
    {

//        for ( int i = 0; i < c.getSize(); i++)
//        {
//            out << c[i]  << " " << out << c.__id;
//        }
//// out << cluster[i] << " " << POINT_CLUSTER_ID_DELIM << " " << cluster.__id;
//
//        return out;

        for (int i = 0; i < c.getSize(); ++i)
        {
            out << c[i];
        }
        return out;
    }


    istream &operator>>(istream &in, Cluster &c)
    {

        string line;

        int count = 0;

        static const char POINT_CLUSTER_ID_DELIM = ',';

//        while (getline(in, line, ','))
//        {
//            c[count] =stod(line);
//            count++;
//        }

        if (c.__dimensionality != count)
        {
            throw DimensionalityMismatchEx(c.__dimensionality, count);
        }

        return in;

    }

//        std::string line;
//        while (getline(in,line))
//        {
//           // int d = (int) std::count(line.begin(), line.end(), Point::POINT_VALUE_DELIM);
//
//          // LNodePtr ptr = new Point(d + 1);
//            std::string lineStream;
//            std::getline(in, lineStream);
//
//            Point p(c.__dimensionality);
//
//            std::stringstream ls(lineStream);
//
//            // call to Point::operator>>
//            //lineStream >> *ptr;
//
//            ls >> p;
//            c.add(p);
//        }
//
//
//        return in;




    // ~~~~~~ OPERATORS WITH POINTS ~~~~~~~~


    Cluster &Cluster::operator+=(const Point &point) //need to use the add function instead
    {
        add(point);

        return *this; //returns object from add
    }

    Cluster &Cluster::operator-=(const Point &point) //I need to use the remove function instead
    {
//        if (point.__dim != __dim)
//        {
//            throw DimensionalityMismatchEx(point.__dim, point1.__dim);
//        }
//
//        for (int i = 0; i < point.__dim; i++)
//        {
//            point.__values[i] -= point1.__values[i];
//
//        }
//
//        return point;


        remove(point);

        return *this;
    }

    // ~~~~~~ OPERATORS WITH CLUSTERS ~~~~~~~~

    Cluster &Cluster::operator+=(const Cluster &rclus) {

        if (rclus.__dimensionality != __dimensionality)
        {
            throw DimensionalityMismatchEx(rclus.__dimensionality, __dimensionality);
        }

        for (int i = 0; i < rclus.getSize(); ++i)
        {
            add(rclus[i]);
        }

        return *this;

    }

    Cluster &Cluster::operator-=(const Cluster &rclus)  //literally the same but with remove instead of add
    {
        if (__dimensionality != rclus.__dimensionality)
            throw DimensionalityMismatchEx(__dimensionality, rclus.__dimensionality);

        for (int i = 0; i < rclus.getSize(); ++i) {
            remove(rclus[i]);
        }

        return *this;
    }
//        for (int i = 0; i < rclus.getSize(); ++i)
//        {
//            remove(rclus[i]);
//        }
//
//        return *this;


    // ~~~~~~~~~~ TWO CLUSTERS ~~~~~~~~~~

    const Cluster operator-(const Cluster &lhs, const Cluster &rhs) // (asymmetric) difference //
    {
        Cluster difference(lhs);
        difference -= rhs;

        return difference;
    }

    const Cluster operator+(const Cluster &lhs, const Cluster &rhs) // union
    {
        Cluster added(lhs); //new cluster with constructor copied from lhclus
        added += rhs;

        return added;
    }


    // ~~~~~~~~~ CLUSTER AND POINT ~~~~~~~~~~

    const Cluster operator+(const Cluster &lhs, const Point &rhs)
    {
        Cluster added(lhs);
        added += rhs;

        return added;
    }

    const Cluster operator-(const Cluster &lhs, const Point &rhs)
    {
        Cluster difference(lhs);
        difference -= rhs;

        return difference;
    }

    // ~~~~~~ MOVE CLASS ~~~~~~~~

    Cluster::Move::Move(const Point &p, Cluster &from, Cluster &to) : __from(from), __to(to), __p(p)
        { }

    void Cluster::Move::perform()
    {
        __to.add(__from.remove(__p));

        __to.centroid.setValid(false);
        __from.centroid.setValid(false);

        if(__to.__size == 0)
            __to.centroid.toInfinity();
        if(__from.__size == 0)
            __from.centroid.toInfinity();
    }
}