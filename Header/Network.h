//
// Created by not_real_fu on 14-03-2023.
//

#ifndef UNTITLED4_NETWORK_H
#define UNTITLED4_NETWORK_H

#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>
#include <unordered_set>
#include <string>
using namespace std;
/********************** Network
 *****************************/

class Network{
public:
    Network(string orig, string dest, int w, string service);

    string getDest() const;
    int getcapacity() const;
    bool isSelected() const;
    string getOrig() const;
    Network* getReverse() const;
    int getFlow() const;
    bool operator==(const Network &other ) const;
    void setSelected(bool selected);
    void setReverse(Network *reverse);
    void setFlow(int flow);
protected:
    string dest; // destination Station
    int capacity; // Network// capacity, can also be used for capacity
    string service;
    // auxiliary fields
    bool selected = false;

    // used for bidirectional Network
    //s
    string orig;
    Network* reverse;

    int flow; // for flow-related problems
};
struct NetworkHash{
    size_t operator()(const Network &other) const{
        return hash<std::string>()(other.getDest());
    }
};

#endif //UNTITLED4_NETWORK_H
