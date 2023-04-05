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
/********************** Network *****************************/

class Network{
public:
    Network();
    Network(string orig, string dest, int w, string service);
    Network(string dest);
    bool operator==(const Network &other ) const;

    string getDest() const;
    int getcapacity() const;
    string getservice() const;
    bool isSelected() const;
    string getOrig() const;
    Network* getReverse() const;
    int getFlow() const;
    int getCurrencycap() const;

    void setSelected(bool selected);
    void setReverse(Network *reverse) ;
    void setFlow(int flow);
    void setCurrencyCap(int currency_cap);
protected:
    string dest; // destination Station
    int capacity; // Network// capacity, can also be used for capacity
    string service;
    string memory;
    // auxiliary fields
    bool selected = false;
    // used for bidirectional Networks
    string orig;
    Network* reverse;
    int Alfa = 0;
    int Standard = 0;
    //int currency = 0;
    int currency_cap = 0;

    int flow = 0; // for flow-related problems
};

#endif //UNTITLED4_NETWORK_H
