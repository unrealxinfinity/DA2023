#ifndef UNTITLED4_NETWORK_H
#define UNTITLED4_NETWORK_H

#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>
#include <unordered_set>
#include <string>
#include <unordered_map>
using namespace std;
/********************** Network *****************************/

class Network{
public:
    Network();
    Network(string orig, string dest, int w, string service);
    bool operator==(const Network &other ) const;

    string getDest() const;
    int getcapacity() const;
    string getservice() const;
    string getOrig() const;
    int getFlow() const;
    void setFlow(int flow);
protected:
    string orig; // origin Station
    string dest; // destination Station
    int capacity;
    string service;

    int flow = 0; // for flow-related problems
};

#endif //UNTITLED4_NETWORK_H
