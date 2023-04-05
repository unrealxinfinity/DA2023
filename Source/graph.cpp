//
// Created by migue on 10/03/2023.
//
#include "../Header/graph.h"

string Graph::find_code(string name) {
    if(StationSet.find(name) != StationSet.end()){
        return name;
    }
    return "error";
}
Graph::Graph() {
    station_file="";
    network_file="";

}
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
    Station res = StationSet.find(name)->second;
    StationSet.insert(pair<string, Station>(name, res));
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

bool Graph::addBidirectionalNetwork(string src, string dest, int w,string service) {
    Station& source_it = StationSet[src];
    Station& destination_it = StationSet[dest];

    source_it.addNetwork(&destination_it, w,service);
    destination_it.addNetwork(&source_it, w,service);
    /*auto targetNet1= source->getAdj().find(e1->getDest());
    auto targetNet2 = target->adj.find(e2->getDest());
    targetNet1->second->setReverse(targetNet2->second);
    targetNet2->second->setReverse(targetNet1->second);*/
    return true;
}


Graph::~Graph() {

}
bool Graph::testandvisit(queue<string> &q, Network* network, Station *source, Station *target, int flow){
    if((!target->isVisited() && (flow > 0))){
        target->setVisited(true);
        target->setPath(network);
        target->setBN(min(source->getBN(), flow));
        q.push(target->getName());
        return true;
    }
    return false;
}

int Graph::bfs(string source, string target){
    for(Stations::iterator iter = StationSet.begin(); iter != StationSet.end(); iter++){
        iter->second.setVisited(false);
        iter->second.setPath(nullptr);
    }
    queue<string> q;
    Station* station = &StationSet[source];
    station->setBN(INT_MAX);
    if(source == target) station->setBN(0);
    station->setVisited(true);
    q.push(source);
    bool a = false;
    while(!q.empty() && !a){
        string v = q.front();
        q.pop();
        station = &StationSet[v];
        Station *dest;
        for(Networks::iterator it = station->adj.begin(); it != station->adj.end(); it++){
            int capacity = it->second.getcapacity();
            string d = it->second.getDest();
            dest = &StationSet[d];
            if(testandvisit(q, &it->second, station, dest, capacity - it->second.getFlow()) && (target == d)) a = true;
        }
        for(PointerNetworks::iterator it = station->incoming.begin(); it != station->incoming.end(); it++){
            string o = it->first;
            dest = &StationSet[o];
            testandvisit(q, it->second, dest, station, it->second->getFlow());
        }
    }
    station = &StationSet[target];
    if(!station->isVisited()) return 0;
    else {
        return station->getBN();
    }
}
void Graph::augmentFlowAlongPath(string source, string target, int bottleneck){
    Station *station = &StationSet[target];
    Network *network = station->getPath();
    while(network != nullptr){
        if(network->getDest() != station->getName()) {
            network->setFlow(network->getFlow() - bottleneck);
            station = &StationSet[network->getDest()];
            network = station->getPath();
        }
        else{
            network->setFlow(network->getFlow()+bottleneck);
            station = &StationSet[network->getOrig()];
            network = station->getPath();
        }
    }
}
int Graph::edmondsKarp(string source, string target) {
    int max_flow = 0;
    int flow = 0;
    for(Stations::iterator iter = StationSet.begin(); iter != StationSet.end(); iter++){
        for(Networks::iterator it = iter->second.adj.begin(); it != iter->second.adj.end(); it++){
            it->second.setFlow(0);
        }
    }
    while((flow = bfs(source, target)) != 0){
        augmentFlowAlongPath(source, target, flow);
        max_flow += flow;
    }
    return max_flow;
}
vector<pair<string, string>> Graph::stationPairs(){
    int max = 0;
    string st = "blah";
    int sub_max = 0;
    string second_st;
    for(Stations::iterator iter = StationSet.begin(); iter != StationSet.end(); iter++){
        Station &station = iter->second;
        if(station.getAdj_cap() > max) {
            sub_max = max;
            max = station.getAdj_cap();
            second_st = st;
            st = station.getName();
        }
        else if(station.getAdj_cap() > sub_max){
            second_st = station.getName();
            sub_max = station.getAdj_cap();
        }
    }
    max = edmondsKarp(st, second_st);
    vector<pair<string, string>> final;
    for(Stations::iterator iter = StationSet.begin(); iter != StationSet.end(); iter++) {
        Station &station = iter->second;
        for(Stations::iterator it = iter; it != StationSet.end(); it++){
            Station &s = it->second;
            if((min(station.getAdj_cap(), s.getAdj_cap()) > max) && (s.getName() != station.getName())){
                int flow = edmondsKarp(station.getName(), s.getName());
                if(flow >= max){
                    if(flow > max) final.clear();
                    max = flow;
                    final.push_back(pair<string, string>(station.getName(), s.getName()));
                }
            }
        }
    }
    return final;
}
bool Graph::search(string source, string target){
    for(Stations::iterator iter = StationSet.begin(); iter != StationSet.end(); iter++){
        iter->second.setVisited(false);
        iter->second.setDist(INT_MAX);
    }
    Station *station = &StationSet[source];
    station->setDist(0);
    while(source != "finish"){
        string best = "finish";
        station->setVisited(true);
        for(Stations::iterator iter = StationSet.begin(); iter != StationSet.end(); iter++){
            if(iter->second.isVisited()) continue;
            for(PointerNetworks::iterator it = station->incoming.begin(); it != station->incoming.end(); it++){
                if(it->second->getFlow() != 0){
                    int value = station->getDist() + station->getIndegree();
                }
            }
            for(Networks::iterator it = station->adj.begin(); it != station->adj.end(); it++){
                Station *dest = &StationSet[it->second.getDest()];
                if(it->second.getFlow() != 0){
                    int currency;
                    if(it->second.getservice() == "STANDARD") currency = 2;
                    else currency = 4;
                    int value = station->getDist() + station->getIndegree() - dest->getIndegree() - currency;
                    if(dest->getDist() > value){
                        dest->setDist(value);
                        dest->setDad(source);
                    }
                }
            }
        }
    }
}
void Graph::max_flow_min_cost(string source, string target){
    for(Stations::iterator iter = StationSet.begin(); iter != StationSet.end(); iter++){
        for(Networks::iterator it = iter->second.adj.begin(); it != iter->second.adj.end(); it++){
            it->second.setFlow(0);
        }
    }
    int total_flow = 0;
    int total_cost = 0;
    while(search(source, target)){

    }

}
void Graph::topk_reduced_connectivity(priority_queue <pair<int, pair<string, string>>> &pq) {
    stack<Network> temp = store;
    for (Stations::iterator iter = StationSet.begin(); iter != StationSet.end(); iter++) {
        Station &station = iter->second;
        for (Stations::iterator it = iter; it != StationSet.end(); it++) {
            Station &s = it->second;
            if (s.getName() != station.getName()) {
                int max_flow_before_remove = edmondsKarp(station.getName(), s.getName());
                while(!temp.empty()){
                    remove_network(temp.top().getOrig(), temp.top().getDest());
                    temp.pop();
                }
                int max_flow_after_remove = edmondsKarp(station.getName(), s.getName());
                int dif = max_flow_before_remove - max_flow_after_remove;
                pq.push(pair<int, pair<string, string>>(dif, pair<string, string>(station.getName(), s.getName())));
                temp = store;
                restore_maintenance();
                store = temp;

            }
        }
    }
}
void Graph::print_reduced_connectivity(string source, string target){
    cout << "With the reduced connectivity:\n";
    print_edmundsKarp(source, target);
}
void Graph::print_topk_reduced_connectivity(int k){
    cout << "The top " << k << " stations who suffered the most out of the maintenance were:\n";
    priority_queue <pair<int, pair<string, string>>> pq;
    topk_reduced_connectivity(pq);
    while(k > 0){
        cout << pq.top().second.first << " <-> " << pq.top().second.second << " (" << pq.top().first << ")\n";
        pq.pop();
        k--;
    }
}
void Graph::restore_maintenance(){
    while(!store.empty()){
        addBidirectionalNetwork(store.top().getOrig(), store.top().getDest(), store.top().getcapacity(), store.top().getservice());
        store.pop();
    }
}
bool Graph::valid_remove(string source, string target){
    Station *station = &StationSet[source];
    auto it = station->adj.find(target);
    if(it == station->adj.end()) return false;
    store.push(it->second);
    return true;
}
void Graph::remove_network(string source, string target){
    Station *station = &StationSet[source];
    Station *dest = &StationSet[target];
    station->removeNetwork(dest);
}

void Graph::print_edmundsKarp(string source, string target){
    int flow = edmondsKarp(source, target);
    cout << "The maximum flow between " << source << " and " << target << " is " << flow << '\n';
}
void Graph::print_all_station_pairs(){
    vector<pair<string,string>> final = stationPairs();
    cout << "From all pair of stations, the ones that require the most amount of trains when taking full of the existing network capacity are:\n";
    for(pair<string, string> p : final){
        cout << "From " << p.first << " -> " << p.second << '\n';
    }
    //cout << "The max flow betweeen these stations is " << final.first << '\n';
}


void Graph::duvidaprostor(string target){
    Station *station = &StationSet[target];
    cout << station->getAdj_cap() << '\n';
}


void Graph::find_startofline(Station *dest, string line){
    queue<string> q;
    for(Networks::iterator it = dest->adj.begin(); it != dest->adj.end(); it++){
        Station *station = &StationSet[it->second.getDest()];
        if(station->getLine() == line)
    }
}
void Graph::max_flow_from_lines(string target){
    Station *dest = &StationSet[target];
    stack<string> temp;
    for(Networks::iterator it = dest->adj.begin(); it != dest->adj.end(); it++){
        Station *station = &StationSet[it->second.getDest()];
        temp.push(station->getLine());
    }
    while(!temp.empty()) {
        find_startofline(dest, temp.top());
        temp.pop();
    }
}
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

        if(StationSet.find(Name) != StationSet.end()) continue;
        Station station = Station(Name, District, Municipality, Township, Line);
        StationSet.insert(pair<string, Station>(Name,station));
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