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
    string getDest() const;
    int getcapacity() const;
    string getservice() const;
    bool isSelected() const;
    string getOrig() const;
    Network* getReverse() const;
    int getFlow() const;
    int getCurrencycap() const;
    int getAlfa() const;
    int getStandard() const;
    vector<pair<int, pair<string, int>>> getStore() const;
    bool operator==(const Network &other ) const;
    void setSelected(bool selected);
    void setReverse(Network *reverse) ;
    void setFlow(int flow);
    void setAlfa(int alfa);
    void setCurrencyCap(int currency_cap);
    void setMemory(string memory);
    void setStandard(int standard);
    void reset();
    void add_values(int currency, string dest, int flow);
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
    vector<pair<int, pair<string, int>>> store;
    int Alfa = 0;
    int Standard = 0;
    //int currency = 0;
    int currency_cap = 0;

    int flow = 0; // for flow-related problems
};
/*struct NetworkHash{
    size_t operator()(const string &other) const{
        return hash<std::string>()(other);
    }
};*/

#endif //UNTITLED4_NETWORK_H
