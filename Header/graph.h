//
// Created by migue on 10/03/2023.
//

#ifndef UNTITLED4_GRAPH_H
#define UNTITLED4_GRAPH_H

#include <list>
#include <vector>
#include <queue>
#include <iostream>
#include <unordered_set>
#include <stack>
#include <cmath>
#include <fstream>
#include <sstream>
#include <string>
#include "Station.h"
#include <climits>

using namespace std;


typedef std::unordered_set<Station,StationHash> Stations;
class Graph {
public:
    Graph(const string station_file,const string network_file);
    ~Graph();
    bool addStation(string name);
    bool addNetwork(string src, string dest, int capacity, string service);
    bool addBidirectionalNetwork(string src, string dest, double w,string service);

    size_t getNumStation() const;
    Stations getStationSet() const;
    void insertStations();
    void insertNetworks();
    int bfs(string source, string target);
    void edmondsKarp(string source, string target);
    Stations StationSet;
private:
    string station_file;
    string network_file;


};
#endif//UNTITLED4_GRAPH_H