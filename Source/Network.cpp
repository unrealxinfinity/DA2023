//
// Created by not_real_fu on 14-03-2023.
//
#include "../Header/Network.h"
/********************** Network  ****************************/
Network::Network() {}
Network::Network(string orig, string dest, int capacity, string service): orig(orig), dest(dest), capacity(capacity), service(service),flow(0) {}
Network::Network(string d){
    orig="";
    dest=d;
    capacity=0;
    service="";
    flow=0;

}
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

Network* Network::getReverse() const {
    return this->reverse;
}

bool Network::isSelected() const {
    return this->selected;
}

int Network::getFlow() const {
    return flow;
}
int Network::getCurrencycap() const {
    return currency_cap;
}
void Network::setSelected(bool selected) {
    this->selected = selected;
}

void Network::setReverse(Network *reverse)  {
    this->reverse = reverse;
}

void Network::setFlow(int flow) {
    this->flow = flow;
}
void Network::setCurrencyCap(int currency_cap){
    this->currency_cap = currency_cap;
}