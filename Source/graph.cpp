//
// Created by migue on 10/03/2023.
//
#include "../Header/graph.h"

string Graph::find_code(string name) {
    if(StationSet.find(name) != StationSet.end()){
        return name;
    }
    for (Stations::iterator iter=StationSet.begin(); iter!=StationSet.end();++iter) {
        if (iter->second.getName()==name) return iter->first;
    }
    return "error";
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
int Graph::bfs(string source, string target){
    queue<string> q;
    Station& station = StationSet.find(source)->second;
    station.setBN(INT_MAX);
    station.setVisited(true);
    q.push(source);
    bool a = false;
    while(!q.empty()){
        string v = q.front();
        q.pop();
        if(a || (source == target)) break;
        Station& st = StationSet.find(v)->second;
        for(Networks::iterator it = st.adj.begin(); it != st.adj.end(); it++){
            int capacity = it->second.getcapacity();
            string d = it->second.getDest();
            Station& dest = StationSet.find(d)->second;
            if((!dest.isVisited() && (capacity-it->second.getFlow()) > 0)){
                dest.setVisited(true);
                dest.setPath(&it->second);
                dest.setBN(min(st.getBN(), capacity-it->second.getFlow()));
                q.push(d);
                if(d == target) a = true;
            }
        }
        for(PointerNetworks::iterator it = st.incoming.begin(); it != st.incoming.end(); it++){
            string o = it->first;
            Station& orig = StationSet.find(o)->second;
            if(!orig.isVisited() && (it->second->getFlow() > 0)){
                orig.setVisited(true);
                orig.setPath(it->second);
                it->second->setSelected(true);
                orig.setBN(min(st.getBN(), it->second->getFlow()));
                q.push(o);
                if(o == target) a = true;
            }
        }
    }
    Station& station2 = StationSet.find(target)->second;
    //station = StationSet[target];
    if(!a)return 0;
    int bottleneck = station2.getBN();
    Network *network = station2.getPath();
    while(true){
        if(network->isSelected()) {
            network->setFlow(network->getFlow() - bottleneck);
            network->setSelected(false);
            Station &station3 = StationSet.find(network->getDest())->second;
            if(station3.getName() == source) break;
            network = station3.getPath();
        }
        else{
            network->setFlow(network->getFlow()+bottleneck);
            Station &station3 = StationSet.find(network->getOrig())->second;
            if(station3.getName() == source) break;
            network = station3.getPath();
        }
    }

    return bottleneck;
}
int Graph::edmondsKarp(string source, string target) {
    int max_flow = 0;
    int flow = 0;
    for(Stations::iterator iter = StationSet.begin(); iter != StationSet.end(); iter++){
        for(Networks::iterator it = iter->second.adj.begin(); it != iter->second.adj.end(); it++){
            it->second.setFlow(0);
        }
    }
    do {
        for(Stations::iterator iter = StationSet.begin(); iter != StationSet.end(); iter++){
            iter->second.setVisited(false);
        }
        if(max_flow == 10) {
            int count = 0;
        }
        flow = bfs(source, target);
        max_flow += flow;
    }while(flow != 0);
    return max_flow;
}
vector<pair<string, string>> Graph::stationpairs(){
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
void Graph::print_edmundsKarp(string source, string target){
    int flow = edmondsKarp(source, target);
    cout << "The maximum flow between " << source << " and " << target << " is " << flow << '\n';
}
void Graph::print_all_station_pairs(){
    vector<pair<string,string>> final = stationpairs();
    cout << "From all pair of stations, the ones that require the most amount of trains when taking full of the existing network capacity are:\n";
    for(pair<string, string> p : final){
        cout << "From " << p.first << " -> " << p.second << '\n';
    }
    //cout << "The max flow betweeen these stations is " << final.first << '\n';
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