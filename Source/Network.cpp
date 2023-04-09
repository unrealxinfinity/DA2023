#include "../Header/Network.h"

/********************** Network  ****************************/

Network::Network() {}
Network::Network(string orig, string dest, int capacity, string service): orig(orig), dest(dest), capacity(capacity), service(service),flow(0) {}

bool Network::operator==(const Network &other ) const{
    return other.getDest() == this->getDest();
}

string Network::getDest() const {
    return this->dest;
}

int Network::getcapacity() const {
    return this->capacity;
}

string Network::getOrig() const {
    return this->orig;
}
string Network::getservice() const{
    return this->service;
}

int Network::getFlow() const {
    return flow;
}

void Network::setFlow(int flow) {
    this->flow = flow;
}
