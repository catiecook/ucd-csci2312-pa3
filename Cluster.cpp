//
// Created by Catie Cook on 2/17/16.
//


#include <cassert>
#include <sstream>
#include "Cluster.h"



namespace Clustering {


    LNode::LNode(const Point &p, LNodePtr a) : point(p)
    {
        point = p;
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

//default constructor

//    Cluster::Cluster()
//    {
//        __dimensionality = 0;
//        __size = 0;
//        __id = 0;
//        __points = nullptr;
//    }

//    Cluster::Cluster(const Cluster &c) : Cluster ()
//    {
//        for (int i = 0; i < c.getSize(); ++i)
//        {
//            add(c[i]);
//        }
//    }



// ~~~~~~~~~~~~ INNER CLASS: CENTROID ~~~~~~~~~~~~~

    Cluster::Centroid::Centroid(unsigned int d, const Cluster &c)
    {
        d = ___dimensions;
        c = __c;
    }

    const Point Cluster::Centroid::get() const
    {
        return Clustering::Point(0);
    }

    void Cluster::Centroid::set(const Point &p)
    {

    }

    bool Cluster::Centroid::isValid() const
    {
        if(__p == __valid)
        {
            return true;
        }

        else
            return false;
    }

    void Cluster::Centroid::setValid(bool valid)
    {

    }

    void Cluster::Centroid::compute()
    {

    }

    bool Cluster::Centroid::equal(const Point &p) const
    {
        //return true if p is equal to new point?
    }

    void Cluster::Centroid::toInfinity()
    {

    }


// ~~~~~~~~~~~~ PUBLIC CLUSTER DEFINITIONS ~~~~~~~~~~~~~

    Cluster::Cluster(unsigned int d)
    {

    }

    Cluster::Cluster(const Cluster &cluster)
    {

    }

    Cluster &Cluster::operator=(const Cluster &c)
    {
        if (__size > 0)
        {
            LNodePtr dump;
            LNodePtr cursor = __points;

            while (cursor != nullptr) {
                dump = cursor;
                cursor = cursor->next;

                delete dump;
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


   unsigned int Cluster::getSize() const {

        return __size;
    }


    unsigned int Cluster::getDimensionality() const
    {
        return 0;
    }

    unsigned int Cluster::getId() const
    {
        return 0;
    }

    void Cluster::add(const Point &point)
    {

        LNodePtr a = new LNode(Point(point), nullptr);  //create a new node and point to the head

        if (__points == nullptr)
        {
            __points = a;
        }

        else if (__points->point >
                 point)  //attach a new value into the front, disconnect the ptr and reassign it to point to the new front
        {
            a->next = __points; //always point the new node first, and then disconnect the corresponding pointer to the new node so the linked list works
            __points = a;
        }
        else {
            //find the right spot
            LNodePtr c = __points, n = __points->next;
            while (true) {
                if (n == nullptr || n->point > point) {
                    c->next = a->next = n;
                    break;
                }
                else {
                    c = n;
                    n = n->next;
                }
            }
        }
        __size++;  //keep up with number of points
    }

    const Point &Cluster::remove(const Point &ptr) {
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
//                   else {
//                       pre->next = c->next;
//                       delete c;
//
//                       --__size;
//                       break;
//                   }

                }//end seconif

                pre = c;
                c = c->next; //c is a ptf now pointing to the new current node which is the old next node

            } // end while
        } //end first if
        return ptr;

    } //end function


    bool Cluster::contains(const Point &p) const
    {
        LNodePtr c = __points; //same as previous declaration

        if (c != nullptr) {
            if (c->point.getId() == p.getId()) {
                return true;
            }
            else
                c = c->next;
        }

        return false; //all of the if statements skipped, return = false
    }

    void Cluster::pickCentroids(unsigned int k, Point **pointArray)
    {
        //not sure how to impliment this yet

    }

// ~~~~~~~~~~~~ OVERLOADED OPERATORS ~~~~~~~~~~~~~~

    //COMPARING

    bool operator!=(const Cluster &lhclus, const Cluster &rhclus) //test for non-equality
    {
        return (rhclus != lhclus);
    }

    bool operator==(const Cluster &lhclus, const Cluster &rhclus) //test for equality
    {
        if (rhclus.getSize() != lhclus.getSize())
            return false; //not equal

        for (int i = 0; i < lhclus.getSize(); ++i)
        {
            if (lhclus[i] != rhclus[i])
                return false; //tests for equality through cluster nodes and returns false if it finds nonequality
        }

        return true; //if all are equal it returns true
    }

    //SUBSRIPT

    const Point &Cluster::operator[](unsigned int u) const
    {
        assert (__size > 0); //if size is less than 0 program exits
        LNodePtr cursor = __points; //the cursor will go through points

        for (unsigned int i = 0; i < u; ++i) {
            cursor = cursor->next; //the cursor is now points to next node
        }
        return cursor->point; //point to and dereference to return the current point cursor points to

    }

    // ~~~~~~~~~ IO ~~~~~~~~
    // ~~~~~ - Friends ~~~~~

    std::ostream &operator<<(std::ostream &out, const Cluster &c)
    {
        for (int i = 0; i < c.getSize(); ++i)
        {
            out << c[i];
        }
        return out;
    }


    std::istream &operator>>(std::istream &in, Cluster &c)
    {
        while (!in.eof()) {
            Point p(1);

            std::string line;
            std::getline(in, line);

            if (line.length() > 0) {
                std::stringstream ss(line);
                ss >> p;
                c.add(p);
            }
        }
        return in;

    }


    // ~~~~~~ OPERATORS WITH POINTS ~~~~~~~~
    Cluster &Cluster::operator+=(const Point &point) //need to use the add function instead
    {
        add(point);

        return *this; //returns object from add
    }

    Cluster &Cluster::operator-=(const Point &point) //I need to use the remove function instead
    {
        remove(point);

        return *this;
    }

    // ~~~~~~ OPERATORS WITH CLUSTERS ~~~~~~~~

    Cluster &Cluster::operator+=(const Cluster &rclus) {
        for (int i = 0; i < rclus.getSize(); ++i) {
            add(rclus[i]);  //add clusters together to make one
        }

        return *this;
    }

    Cluster &Cluster::operator-=(const Cluster &rclus)  //literally the same but with remove instead of add
    {
        for (int i = 0; i < rclus.getSize(); ++i)
        {
            remove(rclus[i]);
        }

        return *this;
    }

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

    Cluster::Move::Move(const Point &p, Cluster &from, Cluster &to)
    {
        p = __p; //UGH
        from = __from;
        to = __to;

    }

    void Cluster::Move::perform()
    {

    }
}