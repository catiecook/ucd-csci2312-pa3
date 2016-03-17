#include "Exceptions.h"
#include <cassert>
#include <sstream>
#include "Cluster.h"



namespace Clustering {

// ~~~~~~~~~~~~ OutOfBoundsEx ~~~~~~~~~~~~~
    OutOfBoundsEx::OutOfBoundsEx(unsigned int c, int r)
    {

        c = __current;
        r = __rhs;

    //example of this from point implimentation
//        Point::Point(unsigned int i)
//          __id = __idGen;
//        ++__idGen; // increment IDs  as they are created
//
//        __dim = i;
//        __values = new double[__dim]; //array of doubles for ids
//
//        for (int j = 0; j < __dim; ++j)
//        {
//            __values[j] = 0;
//        }

    }


    unsigned int OutOfBoundsEx::getCurrent() const
    {

        return __current;
    }


    int OutOfBoundsEx::getRhs() const
    {

        return __rhs;
    }


    std::string OutOfBoundsEx::getName() const
    {
        return __name;
    }


    std::ostream &Clustering::operator<<(std::ostream &os, const OutOfBoundsEx &ex)
    {
        return os;
    }

// ~~~~~~~~~~~ DimensionalityMismatchEx ~~~~~~~~~~~~



    DimensionalityMismatchEx::DimensionalityMismatchEx(unsigned int c, unsigned int r)
    {
        c = getCurrent();
        r = getRhs();
    }

    unsigned int DimensionalityMismatchEx::getCurrent() const
    {
        return __current;
    }

    unsigned int DimensionalityMismatchEx::getRhs() const
    {
        return __rhs;
    }

    std::string DimensionalityMismatchEx::getName() const
    {
        return __name;
    }


    std::ostream &Clustering::operator<<(std::ostream &os, const DimensionalityMismatchEx &ex)
    {

            os << "DimensionalityMismatchEx ("
            << "current = " << ex.__current << ", "
            << "rhs = " << ex.__rhs << ')';
            return os;

    }

// ~~~~~~~~ ZeroClustersEx ~~~~~~~~~~~

    ZeroClustersEx::ZeroClustersEx()
    {

    }

    std::string ZeroClustersEx::getName() const
    {
        return __name;
    }




    std::ostream &Clustering::operator<<(std::ostream &os, const ZeroClustersEx &ex)
    {
        return os;
    }


// ~~~~~~~~~~~~ DataFileOpenEx ~~~~~~~~~~~

    DataFileOpenEx::DataFileOpenEx(std::string filename)
    {
        filename = __filename; //dont know if this is right just made it up
    }


    std::string DataFileOpenEx::getFilename() const
    {
        return __filename;
    }


    std::string DataFileOpenEx::getName() const
    {
        return __name;
    }

    std::ostream &Clustering::operator<<(std::ostream &os, const DataFileOpenEx &ex)
    {
        return os;
    }

// ~~~~~~~~~~ ZeroDimensionsEx ~~~~~~~~~~~

    ZeroDimensionsEx::ZeroDimensionsEx()
    {

    }

    std::string ZeroDimensionsEx::getName() const
    {
        return __name;
    }


    std::ostream &Clustering::operator<<(std::ostream &os, const ZeroDimensionsEx &ex)
    {
        return os;
    }

// ~~~~~~~~ EmptyClusterEx ~~~~~~~~~~~~


    EmptyClusterEx::EmptyClusterEx()
    {

    }


    std::string EmptyClusterEx::getName() const
    {
        return __name;
    }


    std::ostream &Clustering::operator<<(std::ostream &os, const EmptyClusterEx &ex)
    {
        return os;
    }
}