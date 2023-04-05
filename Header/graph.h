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
    void print_reduced_connectivity(string source, string target);
    void print_topk_reduced_connectivity(int k);

    void duvidaprostor(string target);

    int bfs(string source, string target);
    void augmentFlowAlongPath(string source, string target, int bottleneck);
    bool testandvisit(queue<string> &q, Network * network, Station *source, Station *target, int flow);
    int edmondsKarp(string source, string target);
    bool valid_remove(string source, string target);
    vector<pair<string, string>> stationPairs();
    void max_flow_from_lines(string target);
    void max_flow_min_cost(string source, string target);
    bool search(string source, string target);
    void topk_reduced_connectivity(priority_queue <pair<int, pair<string, string>>> &pq);
    void restore_maintenance();
    void remove_network(string source, string target);
    void find_startofline(Station *dest, string line);
    Stations StationSet;
    stack<Network> store;
private:
    string station_file;
    string network_file;


};
#endif//UNTITLED4_GRAPH_H