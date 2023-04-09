#include "../Header/Station.h"

/************************* Station  **************************/

Station::Station() {}

Station::Station(string Name, string District, string Municipality, string Township, string Line):Name(Name),District(District),Municipality(Municipality),Township(Township),Line(Line){
}


Network Station::addNetwork(Station* dest, int capacity,string service) {
    Network newNetwork = Network(this->getName() , dest->getName(), capacity , service);
    adj.insert(pair<string,Network>(newNetwork.getDest(),newNetwork));
    adj_cap += capacity;
    dest->incoming.insert({newNetwork.getOrig(),&newNetwork});
    return newNetwork;
}

void Station::removeNetwork(Station *destName) {
    auto it = adj.find(destName->Name);
    auto iter = incoming.find(destName->Name);
    adj_cap -= it->second.getcapacity();
    adj.erase(it);
    incoming.erase(iter);
    it = destName->adj.find(Name);
    destName->setAdj_cap(destName->getAdj_cap()-it->second.getcapacity());
    iter = destName->incoming.find(Name);
    destName->adj.erase(it);
    destName->incoming.erase(iter);
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

int Station::getAdj_cap() const {
    return this->adj_cap;
}

int Station::getInc_flow() const {
    return this->inc_flow;
}

string Station::getLine() const{
    return this->Line;
}

string Station::getMuni() const{
    return this->Municipality;
}

string Station::getDistrict() const{
    return this->District;
}

Network* Station::getPath() const{
    return this->path;
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

void Station::setAdj_cap(int adj_cap) {
    this->adj_cap = adj_cap;
}

void Station::setInc_flow(int inc_flow) {
    this->inc_flow = inc_flow;
}

void Station::setPath(Network* network) {
    this->path = network;
}
