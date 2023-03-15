//
// Created by not_real_fu on 14-03-2023.
//
#include "../Header/Network.h"
/********************** Network  ****************************/

Network::Network(string orig, string dest, int capacity, string service): orig(orig), dest(dest), capacity(capacity), service(service) {}

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

Network* Network::getReverse() const {
    return this->reverse;
}

bool Network::isSelected() const {
    return this->selected;
}

int Network::getFlow() const {
    return flow;
}

void Network::setSelected(bool selected) {
    this->selected = selected;
}

void Network::setReverse(Network *reverse) {
    this->reverse = reverse;
}

void Network::setFlow(int flow) {
    this->flow = flow;
}