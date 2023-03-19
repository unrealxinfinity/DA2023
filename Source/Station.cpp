//
// Created by not_real_fu on 13-03-2023.
//
#include "../Header/Station.h"

/************************* Station  **************************/

Station::Station() {}

Station::Station(string Name, string District, string Municipality, string Township, string Line):Name(Name),District(District),Municipality(Municipality),Township(Township),Line(Line){
}

 Station::Station(string Name): Name(Name) {
    this->District="";
    this->Municipality="";
    this->Township="";
    this->Line="";
}


/*
 * Auxiliary function to add an outgoing Network to a Station (this),
 * with a given destination Station (d) and Network capacity (w).
 */


Network Station::addNetwork(Station* dest, int capacity,string service) {
    Network newNetwork = Network(this->getName() , dest->getName(), capacity , service);
    adj.insert(pair<string,Network>(newNetwork.getDest(),newNetwork));
    adj_cap += capacity;
    dest->incoming.insert({newNetwork.getOrig(),&newNetwork});
    return newNetwork;
}

/*
 * Auxiliary function to remove an outgoing Network (with a given destination (d))
 * from a Station (this).
 * Returns true if successful, and false if such Network does not exist.
 */

bool Station::removeNetwork(string destName) {
    bool removedNetwork = false;
    auto it = adj.find(destName);
    while (it != adj.end()) {
        Network network = it->first;
        string dest = network.getDest();

        /* if (dest== destName) {
            it = adj.erase(it);
            // Also remove the corresponding Network from the incoming list
            auto targetDest= Networks.
            auto it2 = targetDest.incoming.begin();
            while (it2 != targetDest.incoming.end()) {
                if ((*it2)->getOrig() == Name) {
                    it2 = targetDest.incoming.erase(it2);
                }
                else {
                    it2++;
                }
            }
            delete *it;
            removedNetwork = true; // allows for multiple Networks to connect the same pair of vertices (multigraph)
        }
        else {
            it++;
        }
    }
    return removedNetwork;*/
    }
    return 1;
}
bool Station::operator<(const Station & Station) const {
    return this->dist < Station.dist;
}
bool Station::operator==(const Station &other) const{
    return this->Name == other.getName();
}

string Station::getName() const {
    return this->Name;
}
/*
Networks Station::getAdj() const {
    return this->adj;
}
*/
bool Station::isVisited() const {
    return this->visited;
}

bool Station::isProcessing() const {
    return this->processing;
}

unsigned int Station::getIndegree() const {
    return this->indegree;
}

double Station::getDist() const {
    return this->dist;
}
int Station::getBN() const {
    return this->bottleneck;
}
int Station::getCurrency() const {
    return this->currency;
}
int Station::getInc_cap() const {
    return this->incoming_cap;
}
int Station::getAdj_cap() const {
    return this->adj_cap;
}

Network* Station::getPath() const {
    return this->path;
}

PointerNetworks Station::getIncoming() const {
    return this->incoming;
}

void Station::setName(string Name) {
    this->Name = Name;
}

void Station::setVisited(bool visited) {
    this->visited = visited;
}

void Station::setProcesssing(bool processing) {
    this->processing = processing;
}

void Station::setIndegree(unsigned int indegree) {
    this->indegree = indegree;
}

void Station::setDist(double dist) {
    this->dist = dist;
}
void Station::setBN(int bn) {
    this->bottleneck = bn;
}
void Station::setCurrency(int currency) {
    this->currency = currency;
}
void Station::setInc_cap(int inc_cap) {
    this->incoming_cap = inc_cap;
}
void Station::setAdj_cap(int adj_cap) {
    this->adj_cap = adj_cap;
}

void Station::setPath(Network* path) {
    this->path = path;
}

