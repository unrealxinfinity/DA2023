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

typedef std::unordered_map<string,Network*> Networks;
/************************* Station  **************************/
class Station {
public:
    Station(string name, string District, string Municipality, string Township, string Line);
    Station(string name);
    bool operator<(const Station & Station) const; // // required by MutablePriorityQueue
    bool operator==(const Station &other ) const;
    string getName() const;
    Networks getAdj() const;
    bool isVisited() const;
    bool isProcessing() const;
    unsigned int getIndegree() const;
    double getDist() const;
    Network* getPath() const;
    Networks getIncoming() const;

    void setName(string name);
    void setVisited(bool visited);
    void setProcesssing(bool processing);
    void setIndegree(unsigned int indegree);
    void setDist(double dist);
    void setPath(Network* path);
    Network* addNetwork(Station* dest, int w, string service) const;
    bool removeNetwork(string destName);

    //friend class MutablePriorityQueue<Station>;

protected:
    string Name, District, Municipality, Township, Line;


    // auxiliary fields
    bool visited = false;
    bool processing = false;
    unsigned int indegree;
    double dist = 0;
    Network* path;


    mutable Networks incoming;

    int queueIndex = 0;
public:
    mutable Networks adj;
};
struct StationHash{
    size_t operator()(const Station &other) const{
        return hash<std::string>()(other.getName());
    }
};
#endif //UNTITLED4_STATION_H
