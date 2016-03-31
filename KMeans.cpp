//
// Created by Catie Cook on 3/16/16.
//

#include <iosfwd>
#include <cassert>
#include "Kmeans.h"
#include "Exceptions.h"

using namespace std;
namespace Clustering {

// ********** FUNCTION DEFINITIONS *********


    KMeans::KMeans(unsigned int dim, unsigned int k, string filename, unsigned int maxIter)
            : __dimensionality(dim),
              __k(k), __clusters(nullptr),
              __iFileName(filename),
              __maxIter(maxIter),
              __numIter(0),
              __numNonempty(0)

    {
        if (k == 0)
        {
            throw ZeroClustersEx();
        }
        std::ifstream file(filename);

        if (!file) // if there is no file ot open
        {
            throw DataFileOpenEx(filename);
        }

//        __maxIter = maxIter;
//        __numNonempty = 1;
//        __dimensionality = dim;
//        __k = k;

        __clusters = new Cluster *[k];
        for (unsigned int i = 0; i < k; ++i) __clusters[i] = new Cluster(dim);

        file >> *(__clusters[0]);

        file.close();

        __initCentroids = new Point *[k];
        for (unsigned int i = 0; i < k; ++i) __initCentroids[i] = new Point(dim);

        __clusters[0]->pickCentroids(k, __initCentroids);
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

   Cluster &KMeans::operator[](unsigned int u)
   {

       return *(__clusters[u]);
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
        return *(__clusters[u]);
    }

// WRITE RESULTS TO FILE
    ostream &operator<<(ostream &os, const KMeans &kmeans)
    {
        for (unsigned int i = 0; i < kmeans.__k; ++i) {

            os << kmeans[i];
        }
    }
    void KMeans::run()
    {

        assert(__clusters[0]->getSize() > 0);

        unsigned int moves = 100;
        unsigned int iter = 0;

        unsigned int totalpoints = __clusters[0]->getSize();

        for (unsigned int i = 1; i < __k; ++i) {
            Cluster::Move move(*(__initCentroids[i]), *(__clusters[0]), *(__clusters[i]));
            move.perform();
        }

        if (__k < totalpoints) {
            while (moves > 0 && iter < __maxIter) {
                moves = 0;

                for (unsigned int c = 0; c < __k; ++c) {
                    for (unsigned int p = 0; p < __clusters[c]->getSize(); ++p) {
                        double distance = (*(__clusters[c]))[p].distanceTo(__clusters[c]->centroid.get());
                        unsigned int closestIndex = c;
                        for (unsigned int i = 0; i < __k; ++i) {
                            double d = (*(__clusters[c]))[p].distanceTo(__clusters[i]->centroid.get());
                            if (i != c && d < distance) {
                                distance = d;
                                closestIndex = i;
                            }
                        }

                        if (closestIndex != c && __clusters[c]->getSize() > 1) {
                            Cluster::Move move((*(__clusters[c]))[p], *(__clusters[c]), *(__clusters[closestIndex]));
                            move.perform();
                            --p;

                            moves++;
                        }
                    }
                }

                for (unsigned int c = 0; c < __k; ++c) {
                    if (!__clusters[c]->centroid.isValid())
                        __clusters[c]->centroid.compute();
                }

                iter++;
            }
        }
        else {
            iter = 1;
            moves = 0;
        }

        __numIter = iter;
        __numMovesLastIter = moves;
        __numNonempty = 0;
        for (unsigned int c = 0; c < __k; ++c) {
            if (__clusters[c]->getSize() > 0)
                __numNonempty++;
        }
    }


} // end of namespace Clustering