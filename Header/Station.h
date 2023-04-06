//
// Created by migue on 10/03/2023.
//

#ifndef UNTITLED4_STATION_H
#define UNTITLED4_STATION_H

#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>
#include "Network.h"
#include "unordered_map"

using namespace std;

typedef std::unordered_map<string,Network> Networks;
typedef std::unordered_map<string,Network*> PointerNetworks;
/************************* Station  **************************/
class Station {
public:
    Station();
    Station(string name, string District, string Municipality, string Township, string Line);
    Station(string name);
    bool operator<(const Station & Station) const; // required by priorityQueue
    bool operator==(const Station &other ) const;

    string getName() const;
    //Networks getAdj()const;
    bool isVisited() const;
    bool isProcessing() const;
    unsigned int getIndegree() const;
    double getDist() const;
    int getBN() const;

    string getLine() const;
    string getMuni() const;
    string getDistrict() const;
    int getAdj_cap() const;
    Network* getPath() const;
    PointerNetworks getIncoming() const;

    void setName(string name);
    void setVisited(bool visited);
    void setProcesssing(bool processing);
    void setIndegree(unsigned int indegree);
    void setDist(double dist);
    void setBN(int bn);
    void setAdj_cap(int adj_cap);
    void setPath(Network *network);
    /**
     * Auxiliary method to Graph::addBidirectionalNetwork(). <br>
     * Adds a new network to the Station's #adj and to the #incoming of the aforementioned network's sink.
     * @param dest network's sink.
     * @param w Weight of the network.
     * @param service Type of service provided by the network (Standard or Alpha).
     * @return Newly created network.
     * @note Time Complexity O(1).
     */
    Network addNetwork(Station* dest, int w, string service);
    /**
     * Auxiliary method to Graph::remove_network(). <br>
     * Removes the network connecting this Station to the Station \p destName from the #adj and #incloming of both Stations.
     * @param destName Destination(sink) of the network to be removed.
     * @note Time Complexity O(1).
     */
    void removeNetwork(Station *destName);

protected:
    string Name, District, Municipality, Township, Line;
    // auxiliary fields
    bool visited = false;
    bool processing = false;
    unsigned int indegree;
    double dist = 0;
    int bottleneck = 0;
    int adj_cap = 0;
    Network* path;

public:
    PointerNetworks incoming; /**< Unordered map of all Networks comming into this Station (value), indexed by the networks's source name(key). See also #PointerNetworks. */
    Networks adj; /**< Unordered map of all Networks comming out of this Station (value), indexed by the networks's sink name(key). See also #Networks. */
};

#endif //UNTITLED4_STATION_H
