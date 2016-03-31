// File: main.cpp
//
// Created by Ivo Georgiev on 11/22/15.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include "ErrorContext.h"
#include "ClusteringTests.h"

using std::cout;
using std::endl;

using namespace Testing;

int main() {

    const int NumIters = 3;

    cout << endl << "Testing PA2!!" << endl << endl;

    cout << "NOTE:  If you see any memory errors, you MUST fix them!" << endl;
    cout << "       Tests intentionally invoke destructors after they complete," << endl;
    cout << "       so if you see a seg-fault after a passed test, it is" << endl;
    cout << "       probably a bug in your destructor." << endl;

    cout << endl;

    ErrorContext ec(cout);

  //  point tests DONE
    test_point_smoketest(ec);
    test_point_id(ec, NumIters);
    test_point_getsetelem(ec, NumIters);
    test_point_copying(ec, NumIters);
    test_point_assignment(ec, NumIters);
    test_point_equality(ec, NumIters);
    test_point_comparison(ec, NumIters);
    test_point_CAO(ec, NumIters);
    test_point_SAO(ec, NumIters);
    test_point_distance(ec, NumIters);
    test_point_IO(ec, NumIters);
////
////    //cluster tests
    test_cluster_smoketest(ec); // DONE
    test_cluster_subscript(ec, NumIters); // DONE
    test_cluster_equality(ec, NumIters); // DONE
   test_cluster_order(ec, NumIters); //ALL ERRORS
   test_cluster_addremove(ec, NumIters); //DONE
   test_cluster_contain(ec, NumIters); // DONE
    test_cluster_move(ec, NumIters); // DONE
    test_cluster_copying(ec, NumIters); //DONE
    test_cluster_assignment(ec, NumIters); //DONE
    test_cluster_CAO(ec, NumIters); // 36/42 Plus Equal is messed up
    test_cluster_SAO(ec, NumIters); //DONE
    test_cluster_centroid(ec, NumIters); //Something wrong with the zerodimensions catch
    test_cluster_id(ec, NumIters); //3/6
    test_cluster_initselection(ec, NumIters); //ALL ERRORS
    test_cluster_IO(ec, NumIters); //ALL ERRORS

    // kmeans tests
    test_kmeans_smoketest(ec);
    test_kmeans_run(ec, NumIters);
    test_kmeans_IO(ec, NumIters);
    test_kmeans_toofewpoints(ec, NumIters);
    test_kmeans_largepoints(ec, NumIters);
    test_kmeans_toomanyclusters(ec, NumIters);


    return 0;
}
