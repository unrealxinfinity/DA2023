//
// Created by migue on 10/03/2023.
//

#ifndef UNTITLED4_STATIONNETWORK_H
#define UNTITLED4_STATIONNETWORK_H

#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>

class Network;

#define INF std::numeric_limits<double>::max()

/************************* Station  **************************/

class Station {
public:
    Station(int id);
    bool operator<(Station & Station) const; // // required by MutablePriorityQueue

    int getId() const;
    std::vector<Network*> getAdj() const;
    bool isVisited() const;
    bool isProcessing() const;
    unsigned int getIndegree() const;
    double getDist() const;
    Network*getPath() const;
    std::vector<Network*> getIncoming() const;

    void setId(int info);
    void setVisited(bool visited);
    void setProcesssing(bool processing);
    void setIndegree(unsigned int indegree);
    void setDist(double dist);
    void setPath(Network*path);
    Network* addNetwork(Station *dest, double w);
    bool removeNetwork(int destID);

    friend class MutablePriorityQueue<Station>;
protected:
    int id;                // identifier
    std::vector<Network*> adj;  // outgoing Network// s

    // auxiliary fields
    bool visited = false; // used by DFS, BFS, Prim ...
    bool processing = false; // used by isDAG (in addition to the visited attribute)
    unsigned int indegree; // used by topsort
    double dist = 0;
    Network*path = nullptr;

    std::vector<Network*> incoming; // incoming Network// s

    int queueIndex = 0; 		// required by MutablePriorityQueue and UFDS
};

/********************** Network
 *****************************/

class Network{
public:
    Network(Station *orig, Station *dest, double w);

    Station * getDest() const;
    double getWeight() const;
    bool isSelected() const;
    Station * getOrig() const;
    Network*getReverse() const;
    double getFlow() const;

    void setSelected(bool selected);
    void setReverse(Network*reverse);
    void setFlow(double flow);
protected:
    Station * dest; // destination Station
    double weight; // Network// weight, can also be used for capacity

    // auxiliary fields
    bool selected = false;

    // used for bidirectional Network
    //s
    Station *orig;
    Network*reverse = nullptr;

    double flow; // for flow-related problems
};

#endif //UNTITLED4_STATIONNETWORK_H
