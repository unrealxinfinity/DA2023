//
// Created by migue on 10/03/2023.
//

#ifndef UNTITLED4_GRAPH_H
#define UNTITLED4_GRAPH_H
#include <list>
#include <vector>
#include <queue>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <stack>
#include <cmath>
#include <fstream>
#include <sstream>
#include <string>
#include "StationNetwork.h"
using namespace std;

#endif //UNTITLED4_GRAPH_H
class Graph {
public:
    ~Graph();
    /*
    * Auxiliary function to find a Station with a given ID.
    */
    Station *findStation(const int &id) const;
    /*
     *  Adds a Station with a given content or info (in) to a graph (this).
     *  Returns true if successful, and false if a Station with that content already exists.
     */
    bool addStation(const int &id);

    /*
     * Adds an Network to a graph (this), given the contents of the source and
     * destination vertices and the Network weight (w).
     * Returns true if successful, and false if the source or destination Station does not exist.
     */
    bool addNetwork(const int &sourc, const int &dest, double w);
    bool addBidirectionalNetwork(const int &sourc, const int &dest, double w);

    int getNumStation() const;
    std::vector<Station *> getStationSet() const;
    void insertStations();
protected:
    std::vector<Station *> StationSet;    // Station set

    double ** distMatrix = nullptr;   // dist matrix for Floyd-Warshall
    int **pathMatrix = nullptr;   // path matrix for Floyd-Warshall

    /*
     * Finds the index of the Station with a given content.
     */
    int findStationIdx(const int &id) const;
};

void deleteMatrix(int **m, int n);
void deleteMatrix(double **m, int n);