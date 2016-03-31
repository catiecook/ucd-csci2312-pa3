#include "Exceptions.h"
#include <cassert>
#include <sstream>
#include "Cluster.h"


using namespace std;

namespace Clustering {

// ~~~~~~~~~~~~ OutOfBoundsEx ~~~~~~~~~~~~~
    OutOfBoundsEx::OutOfBoundsEx(unsigned int c, int r)
    {
        this->__name = "OutOfBoundsEx";
        this->__current = c;
        this->__rhs = r;

    }


    unsigned int OutOfBoundsEx::getCurrent() const
    {

        return this->__current;
    }


    int OutOfBoundsEx::getRhs() const
    {

        return this->__rhs;
    }


    string OutOfBoundsEx::getName() const
    {

        return this->__name;
    }


    ostream &operator<<(ostream &os, const OutOfBoundsEx &ex)
    {
        os << "DimensionalityMismatchEx ("
        << "current = " << ex.__current << ", "
        << "rhs = " << ex.__rhs << ')';
        return os;
    }

// ~~~~~~~~~~~ DimensionalityMismatchEx ~~~~~~~~~~~~

    DimensionalityMismatchEx::DimensionalityMismatchEx(unsigned int c, unsigned int r)
    {
        this->__name = "DimensionalityMismatchEx";
        this->__current = c;
        this->__rhs = r;
    }

    unsigned int DimensionalityMismatchEx::getCurrent() const
    {

        return this->__current;
    }

    unsigned int DimensionalityMismatchEx::getRhs() const
    {

        return this->__rhs;
    }

    string DimensionalityMismatchEx::getName() const
    {

        return this->__name;
    }


    ostream &operator<<(ostream &os, const DimensionalityMismatchEx &ex)
    {

            os << "DimensionalityMismatchEx ("
            << "current = " << ex.__current << ", "
            << "rhs = " << ex.__rhs << ')';
            return os;

    }

// ~~~~~~~~ ZeroClustersEx ~~~~~~~~~~~

    ZeroClustersEx::ZeroClustersEx()
    {
        __name = "";
    }

    string ZeroClustersEx::getName() const
    {

        return this->__name;
    }


    ostream &operator<<(ostream &os, const ZeroClustersEx &ex)
    {
        os << ex << endl;
        return os;
    }


// ~~~~~~~~~~~~ DataFileOpenEx ~~~~~~~~~~~

    DataFileOpenEx::DataFileOpenEx(string filename)
    {
        __filename = filename;
        __name = "DataFileOpenEx";

        this->__filename = filename; //dont know if this is right just made it up
    }


   string DataFileOpenEx::getFilename() const
    {

        return this->__filename;
    }


    string DataFileOpenEx::getName() const
    {

        return this->__name;
    }

    ostream &operator<<(ostream &os, const DataFileOpenEx &ex)
    {
        os << ex.__name << ": " << ex.__filename << endl;
    }

// ~~~~~~~~~~ ZeroDimensionsEx ~~~~~~~~~~~

    ZeroDimensionsEx::ZeroDimensionsEx()
    {
        __name = "ZeroDimensionsEx";
    }

    string ZeroDimensionsEx::getName() const
    {

        return this->__name;
    }


    ostream &operator<<(ostream &os, const ZeroDimensionsEx &ex)
    {
        os << ex.getName() << endl;
        return os;
    }

// ~~~~~~~~ EmptyClusterEx ~~~~~~~~~~~~


    EmptyClusterEx::EmptyClusterEx()
    {
        __name = "EmptyClusterEx";
    }


    string EmptyClusterEx::getName() const
    {

        return this->__name;
    }

    ostream &operator<<(ostream &os, const EmptyClusterEx &ex)
    {


        os << ex.__name << endl; 
        return os;
    }


}