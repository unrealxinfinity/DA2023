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
#include <stack>
#include <cmath>
#include <fstream>
#include <sstream>
#include <string>
#include "Station.h"
#include <climits>


using namespace std;

typedef unordered_map<string,Station> Stations;
class Graph {
public:
    Graph(const string station_file,const string network_file);
    Graph();
    ~Graph();
    bool addStation(string name);
    bool addNetwork(string src, string dest, int capacity, string service);
    bool addBidirectionalNetwork(string src, string dest, int w,string service);

    string find_code(string name);

    size_t getNumStation() const;
    Stations getStationSet() const;
    void insertStations();
    void insertNetworks();

    void print_edmundsKarp(string source, string target);
    void print_all_station_pairs();

    void duvidaprostor(string target);

    int bfs(string source, string target);
    void augmentFlowAlongPath(string source, string target, int bottleneck);
    bool testandvisit(queue<string> &q, Network * network, Station *source, Station *target, int flow);
    bool testandvisitCurrency(queue<string> &q, Network* network, Station *source, Station *target, int flow);
    int edmondsKarp(string source, string target);
    vector<pair<string, string>> stationPairs();
    Stations StationSet;
private:
    string station_file;
    string network_file;


};
#endif//UNTITLED4_GRAPH_H