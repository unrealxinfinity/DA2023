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
    bool operator<(const Station & Station) const; // // required by riorityQueue
    bool operator==(const Station &other ) const;
    string getName() const;
    //Networks getAdj()const;
    bool isVisited() const;
    bool isProcessing() const;
    unsigned int getIndegree() const;
    double getDist() const;
    int getBN() const;
    int getPi() const;
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
    void setPi(int pi);
    void setAdj_cap(int adj_cap);
    void setPath(Network* path);
    Network addNetwork(Station* dest, int w, string service);
    void removeNetwork(Station * destName);

    //friend class riorityQueue<Station>;

protected:
    string Name, District, Municipality, Township, Line;
    // auxiliary fields
    bool visited = false;
    bool processing = false;
    unsigned int indegree;
    double dist = 0;
    int bottleneck = 0;
    int pi = 0;
    int adj_cap = 0;
    Network* path;



    int queueIndex = 0;
public:
    PointerNetworks incoming;
    Networks adj;
};

struct StationHash{
    size_t operator()(const Station &other) const{
        return hash<std::string>()(other.getName());
    }
};

#endif //UNTITLED4_STATION_H
