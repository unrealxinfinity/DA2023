//
// Created by migue on 10/03/2023.
//
#include "../Header/graph.h"
#


Graph::Graph(const string sf, const string nf) {
    station_file=sf;
    network_file=nf;
    this->insertStations();
    this->insertNetworks();
}

size_t Graph::getNumStation() const {
    return StationSet.size();
}

Stations Graph::getStationSet() const {
    return StationSet;
}

/*
 *  Adds a Station with a given content or info (in) to a graph (this).
 *  Returns true if successful, and false if a Station with that content already exists.
 */
bool Graph::addStation(string name) {
    Station station = Station(name);
    auto res = StationSet.find(station);
    if (res != StationSet.end())
        return false;
    StationSet.insert(*res);
    return true;
}
/*bool Graph::addNetwork(string src, string dest, int capacity, string service) {
    auto v1 = StationSet.find(src);
    auto v2 = StationSet.find(dest);
    if (v1 == StationSet.end() || v2 == StationSet.end())
        return false;
    v1->addNetwork(v2, capacity, service);
    return true;
}*/

bool Graph::addBidirectionalNetwork(string src, string dest, double w,string service) {
    auto source_it= StationSet.find(Station(src));
    auto destination_it = StationSet.find(Station(dest));

    // The reference of the content of the interators
    Station *source= const_cast<Station *>(&(*source_it));
    Station *target= const_cast<Station *>(&(*destination_it));

    if (source_it == StationSet.end() || destination_it == StationSet.end()) return false;
    auto e1 = source_it->addNetwork(target, w,service);
    auto e2 = destination_it->addNetwork(source, w,service);
    auto targetNet=source->adj.find(e1->getDest());


    return true;
}


Graph::~Graph() {
}
/*
int Graph::bfs(string source, string target){
    queue<string> q;
    Station station = *StationSet.find(source);
    station.setVisited(true);
    q.push(source);
    bool a = false;
    while(!q.empty()){
        string v = q.front();
        q.pop();
        if(a) break;
        station = *StationSet.find(v);
        for(Network network : station.getAdj()){
            int capacity = network.getcapacity();
            string d = network.getDest();
            Station dest = *StationSet.find(d);
            if(((!dest.isVisited() && (capacity-network.getFlow()) > 0))){
                dest.setVisited(true);
                dest.setPath(network);
                q.push(d);
                if(d == target) a = true;
            }
        }
        for(Network network : station.getIncoming()){
            string o = network.getOrig();
            Station orig = *StationSet.find(o);
            if(!orig.isVisited() && (network.getFlow() > 0)){
                orig.setVisited(true);
                orig.setPath(network);
                network.setSelected(true);
                q.push(o);
                if(o == target) a = true;
            }
        }
    }
    station = *StationSet.find(target);
    Network network = station.getPath();
    if(network == nullptr)return 0;
    int bottleneck = INT_MAX;
    while(network != nullptr){
        if(network->isSelected()) {
            if(network->getFlow() < bottleneck) bottleneck = network->getFlow();
            Station dest = *StationSet.find(network->getDest());
            network = dest.getPath();
        }
        else {
            if ((network->getcapacity() - network->getFlow()) < bottleneck) bottleneck = network->getcapacity() - network->getFlow();
            Station orig = *StationSet.find(network->getOrig());
            network = orig.getPath();
        }
    }
    station = *StationSet.find(target);
    network = station.getPath();
    while(network != nullptr){
        if(network->isSelected()) {
            network->setFlow(network->getFlow() - bottleneck);
            network->setSelected(false);
            network = network->getOrig()->getPath();
        }
        else{
            network->setFlow(network->getFlow()+bottleneck);
            network = network->getDest()->getPath();
        }

    }
    return bottleneck;
}
void Graph::edmondsKarp(string source, string target) {
    int flow = 0;
    for(Station station : StationSet){
        for(Network network : station.getAdj()){
            network.setFlow(0);
        }
    }
    do {
        for(Station station : StationSet){
            station.setVisited(false);
        }
        flow = bfs(source, target);
    }while(flow != 0);
}
*/
void Graph::insertStations() {
    ifstream fout(station_file);

    string temp, Name, District, Municipality, Township, Line;
    getline(fout, temp);
    while(getline(fout, temp)){
        stringstream itStream(temp);
        getline(itStream, Name, ',');
        getline(itStream, District, ',');
        getline(itStream, Municipality, ',');
        getline(itStream, Township, ',');
        getline(itStream, Line, '\r');

        Station station = Station(Name, District, Municipality, Township, Line);
        StationSet.insert(station);
    }

}

void Graph::insertNetworks() {
    ifstream fout(network_file);
    string temp, source, target, capacity, service;
    getline(fout, temp);
    while (getline(fout, temp)) {
        stringstream itStream(temp);
        getline(itStream, source, ',');
        getline(itStream, target, ',');
        getline(itStream, capacity, ',');
        getline(itStream, service, '\r');

        int cap = stoi(capacity);
        addBidirectionalNetwork(source, target, cap, service);
    }
}