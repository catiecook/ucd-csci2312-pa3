//
// Created by Catie Cook on 3/16/16.
//

#include <iosfwd>
#include <cassert>
#include "Kmeans.h"

using namespace std;
namespace Clustering {

// ********** FUNCTION DEFINITIONS *********


    KMeans::KMeans(unsigned int dim, unsigned int k, string filename, unsigned int maxIter)
            : __dimensionality(dim),
              __k(k), __clusters(nullptr),
              __iFileName(filename),
              __maxIter(maxIter),
              __numIter(0),
              __numNonempty(0) {


//        if (__iFileName != "") {
//            std::ifstream csv(__iFileName);
//            if (csv.is_open()) {
//                // __clusters = new cluster;
//            }
//        }
//
//        //allocate the controids
//
//        // pick k points as initial centroids
//
//        __clusters[0]->pickCentroids(__k, __initCentroids);
//
//        // initialize k centroids
//
//        for (unsigned int i = 0; i < __k; i++)
//        {
//            __clusters[i] -> centroid;
//        }
    }

    KMeans::~KMeans() {
        for (unsigned int i = 0; i < __k; i++) {
            delete __clusters[i];
            delete __initCentroids[i];
        }

        delete[] __clusters;
        delete[] __initCentroids;
    }


// ACCESSORS
// *********************
    unsigned int KMeans::getMaxIter() {
        return __maxIter;
    }

    unsigned int KMeans::getNumIters() {
        return __numIter;
    }

    unsigned int KMeans::getNumNonemptyClusters() {
        return __numNonempty;
    }

    unsigned int KMeans::getNumMovesLastIter() {
        return __numMovesLastIter;
    }


// ELEMENT ACCESS TESTING
// ***********************

   Cluster &KMeans::operator[](unsigned int u) {


//
//
// assert (__k > 0); //if size is less than 0 program exits
//
//        LNodePtr cursor = nullptr; //the cursor will go through points
//
//        for (unsigned int i = 0; i < u; ++i)
//        {
//            this->__clusters[i];
//            cursor = cursor->next; //the cursor is now points to next node
//        }
//        return __clusters[i];
    }

    const Cluster &KMeans::operator[](unsigned int u) const
    {
        return 0;
    }

// WRITE RESULTS TO FILE
    ostream &operator<<(ostream &os, const KMeans &kmeans)
    {
        os << kmeans << endl;
        return os;
    }

    void KMeans::run() {

    }

} // end of namespace Clustering