#include "../Header/graph.h"

/************************* Graph  **************************/

Graph::Graph():station_file(""), network_file("") {}

Graph::Graph(const string sf, const string nf) {
    station_file=sf;
    network_file=nf;
    this->insertStations();
    this->insertNetworks();
}


string Graph::find_code(string name) {
    if(StationSet.find(name) != StationSet.end()){
        return name;
    }
    return "error";
}

void Graph::addBidirectionalNetwork(string src, string dest, int w,string service) {
    Station& source_it = StationSet[src];
    Station& destination_it = StationSet[dest];

    source_it.addNetwork(&destination_it, w,service);
    destination_it.addNetwork(&source_it, w,service);
}


Graph::~Graph() {}


//AUXILIARY FUNCTIONS
void Graph::print_all_super_source_paths(string target){
    for(Stations::iterator iter = StationSet.begin(); iter != StationSet.end(); iter++){
        int count = 0;
        for (Networks::iterator it = iter->second.adj.begin(); it != iter->second.adj.end(); it++){
            Station *dest = &StationSet[it->second.getDest()];
            if(iter->second.getLine() == dest->getLine() && iter->second.getName() != target)count++;
        }
        if(count == 1){
            if(is_valid_path(iter->second.getName(), target)) {
                cout << "The paths between " << iter->second.getName() << " <-> " << target << " are:\n";
                print_path(iter->second.getName(), iter->second.getName(), target, INT_MAX);
                cout << '\n';
            }

        }
    }
}

bool Graph::is_valid_source(string source){
    Station *station = &StationSet[source];
    int count = 0;
    for(Networks::iterator it = station->adj.begin(); it != station->adj.end(); it++){
        Station *dest = &StationSet[it->second.getDest()];
        if(dest->getLine() == station->getLine())count++;
    }
    if(count != 1)return false;
    return true;
}

bool Graph::is_valid_path(string source, string target) {
    queue<string> q;
    Station *station = &StationSet[source];
    q.push(source);
    if (source == target)return false;
    while (!q.empty()) {
        string v = q.front();
        q.pop();
        station = &StationSet[v];
        for (Networks::iterator it = station->adj.begin(); it != station->adj.end(); it++) {
            Station *dest = &StationSet[it->second.getDest()];
            if (it->second.getFlow() > 0) {
                if (dest->getName() == target)return true;
                q.push(it->second.getDest());
            }
        }
    }
    return false;
}

void Graph::print_path(string orig, string source, string target, int bottleneck){
    Station *destiny = &StationSet[target];
    if(source == target){
        destiny->setBN(bottleneck);
        destiny->setIndegree(0);
        cout << target << " [trains = " << bottleneck << "]";
    }
    else{
        Station *station = &StationSet[source];
        for (Networks::iterator it = station->adj.begin(); it != station->adj.end(); it++) {
            if (it->second.getFlow() > 0) {
                cout << source << " -> ";
                bottleneck = min(bottleneck, it->second.getFlow());
                print_path(orig, it->second.getDest(), target, bottleneck);
                it->second.setFlow(it->second.getFlow()-destiny->getBN());
                int currency;
                if(it->second.getservice() == "STANDARD")currency = 2;
                else currency = 4;
                destiny->setIndegree(destiny->getIndegree()+(destiny->getBN()*currency));
                if(source == orig) {
                    cout << " [cost = " << destiny->getIndegree() << "$]\n";
                    print_path(orig, source, target, INT_MAX);
                }
                break;
            }
        }
    }
}

bool Graph::test_and_visit(queue<string> &queue, Network* network, Station *source, Station *target, int flow){
    if((!target->isVisited() && (flow > 0))){
        target->setVisited(true);
        target->setPath(network);
        target->setBN(min(source->getBN(), flow));
        queue.push(target->getName());
        return true;
    }
    return false;
}

void Graph::augmentFlowAlongPath(string target, int bottleneck){
    Station*destiny = &StationSet[target];
    Station *station = &StationSet[target];
    Network *network = station->getPath();
    unsigned int currency = 0;
    int value = 0;
    bool is_resid = false;
    while(network != nullptr){
        if(network->getservice() == "STANDARD")value = 2;
        else value = 4;
        if(network->getDest() != station->getName()) {
            network->setFlow(network->getFlow() - bottleneck);
            currency = currency - (value*bottleneck);
            station = &StationSet[network->getDest()];
            is_resid = true;
            network = station->getPath();
        }
        else{
            network->setFlow(network->getFlow()+bottleneck);
            currency = currency + (value*bottleneck);
            if(!is_resid){
                station->setInc_flow(station->getInc_flow() + bottleneck);
            }
            is_resid = false;
            station = &StationSet[network->getOrig()];
            network = station->getPath();
        }
    }
    station = &StationSet[target];
    station->setIndegree(station->getIndegree() + currency);
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


//EXERCISE 2.1 AND AUXILIARY FUNCTION
void Graph::print_edmondsKarp(string source, string target){
    Station *station = &StationSet[target];
    int flow = edmondsKarp(source, target);
    cout << "The maximum number of trains between " << source << " and " << target << " is " << flow << " and it has cost " << station->getIndegree() << "$\n";
}

int Graph::edmondsKarp(string source, string target) {
    int max_flow = 0;
    int flow = 0;
    for(Stations::iterator iter = StationSet.begin(); iter != StationSet.end(); iter++){
        iter->second.setIndegree(0);
        iter->second.setInc_flow(0);
        for(Networks::iterator it = iter->second.adj.begin(); it != iter->second.adj.end(); it++){
            it->second.setFlow(0);
        }
    }
    while((flow = bfs(source, target)) != 0){
        augmentFlowAlongPath(target, flow);
        max_flow += flow;
    }
    return max_flow;
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
            if(test_and_visit(q, &it->second, station, dest, capacity - it->second.getFlow()) && (target == d)) a = true;
        }
        for(PointerNetworks::iterator it = station->incoming.begin(); it != station->incoming.end(); it++){
            string o = it->first;
            dest = &StationSet[o];
            test_and_visit(q, it->second, dest, station, it->second->getFlow());
        }
    }
    station = &StationSet[target];
    if(!station->isVisited()) return 0;
    else {
        return station->getBN();
    }
}

//END OF AUXILIARY FUNCTIONS


//EXERCISE 2.2
void Graph::print_all_station_pairs(vector<pair<string,string>> *final){
    int max_flow = stationPairs(final);
    cout << "From all pair of stations, the ones that require the most amount of trains when taking full of the existing network capacity are:\n";
    for(pair<string, string> p : *final){
        cout << "From " << p.first << " <-> " << p.second << " [Max Flow = " << max_flow << "]\n";
    }
}

int Graph::stationPairs(vector<pair<string, string>> *final){
    int max = 0;
    string st = "";
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
    for(Stations::iterator iter = StationSet.begin(); iter != StationSet.end(); iter++) {
        Station &station = iter->second;
        for(Stations::iterator it = iter; it != StationSet.end(); it++){
            Station &s = it->second;
            if((min(station.getAdj_cap(), s.getAdj_cap()) >= max) && (s.getName() != station.getName())){
                int flow = edmondsKarp(station.getName(), s.getName());
                if(flow >= max){
                    if(flow > max) final->clear();
                    max = flow;
                    final->push_back(pair<string, string>(station.getName(), s.getName()));
                }
            }
        }
    }
    return max;
}


//EXERCISE 2.3
void Graph::print_topk_budget_districts(int k){
    priority_queue <pair<int, string>> pq;
    topk_budget_districts(pq);
    if(k > pq.size())k=pq.size();
    cout << "The top " << k << " districts which require more budget are:\n";
    while(k>0){
        cout << pq.top().second << " " << pq.top().first << "$\n";
        pq.pop();
        k--;
    }
}

void Graph::topk_budget_districts(priority_queue<pair<int, string>> &pq){
    for(Stations::iterator iter = StationSet.begin(); iter != StationSet.end(); iter++){
        for(Networks::iterator it = iter->second.adj.begin(); it != iter->second.adj.end(); it++){
            it->second.setFlow(0);
        }
    }
    for(Stations::iterator iter = StationSet.begin(); iter != StationSet.end(); iter++){
        int count = 0;
        for(Networks::iterator it = iter->second.adj.begin(); it != iter->second.adj.end(); it++){
            Station *dest = &StationSet[it->second.getDest()];
            if(dest->getLine() == iter->second.getLine())count++;
        }
        if(count == 1) edmondsKarp_noflowreset(iter->second.getName(), iter->second.getLine());
    }
    unordered_map<string, int> temp;
    for(Stations::iterator iter = StationSet.begin(); iter != StationSet.end(); iter++){
        for(Networks::iterator it = iter->second.adj.begin(); it != iter->second.adj.end(); it++){
            Station *dest = &StationSet[it->second.getDest()];
            int currency;
            if(it->second.getservice() == "STANDARD") currency = 2;
            else currency = 4;
            if(temp.find(dest->getDistrict()) != temp.end()){
                auto &a = temp[dest->getDistrict()];
                a += it->second.getFlow() * currency;
            }
            else temp.insert(pair<string, int>(dest->getDistrict(), it->second.getFlow() * currency));
        }
    }
    for(unordered_map<string, int>::iterator it = temp.begin(); it!=temp.end(); it++){
        pq.push(pair<int, string>(it->second, it->first));
    }
}

void Graph::print_topk_budget_municipios(int k){
    priority_queue <pair<int, string>> pq;
    topk_budget_municipios(pq);
    if(k > pq.size())k=pq.size();
    cout << "The top " << k << " municipalities which require more budget are:\n";
    while(k>0){
        cout << pq.top().second << " " << pq.top().first << "$\n";
        pq.pop();
        k--;
    }
}

void Graph::topk_budget_municipios(priority_queue<pair<int, string>> &pq){
    for(Stations::iterator iter = StationSet.begin(); iter != StationSet.end(); iter++){
        for(Networks::iterator it = iter->second.adj.begin(); it != iter->second.adj.end(); it++){
            it->second.setFlow(0);
        }
    }
    for(Stations::iterator iter = StationSet.begin(); iter != StationSet.end(); iter++){
        int count = 0;
        for(Networks::iterator it = iter->second.adj.begin(); it != iter->second.adj.end(); it++){
            Station *dest = &StationSet[it->second.getDest()];
            if(dest->getLine() == iter->second.getLine())count++;
        }
        if(count == 1) {
            edmondsKarp_noflowreset(iter->second.getName(), iter->second.getLine());
        }
    }
    unordered_map<string, int> temp;
    for(Stations::iterator iter = StationSet.begin(); iter != StationSet.end(); iter++){
        for(Networks::iterator it = iter->second.adj.begin(); it != iter->second.adj.end(); it++){
            Station *dest = &StationSet[it->second.getDest()];
            int currency;
            if(it->second.getservice() == "STANDARD") currency = 2;
            else currency = 4;
            if(dest->getMuni() == ""){
                string v = it->second.getOrig();
                string w = it->second.getDest();
                int z = 0;
            }
            if(temp.find(dest->getMuni()) != temp.end()){
                auto &a = temp[dest->getMuni()];
                a += it->second.getFlow() * currency;
            }
            else temp.insert(pair<string, int>(dest->getMuni(), it->second.getFlow() * currency));
        }
    }
    for(unordered_map<string, int>::iterator it = temp.begin(); it!=temp.end(); it++){
        pq.push(pair<int, string>(it->second, it->first));
    }
}

void Graph::edmondsKarp_noflowreset(string source, string line){
    int flow = 0;
    string target = "";
    while((flow = bfs(source, &target, line)) != 0){
        augmentFlowAlongPath(target, flow);
    }
}

int Graph::bfs(string source, string *target, string line){
    for(Stations::iterator iter = StationSet.begin(); iter != StationSet.end(); iter++){
        iter->second.setVisited(false);
        iter->second.setPath(nullptr);
    }
    queue<string> q;
    Station* station = &StationSet[source];
    station->setBN(INT_MAX);
    station->setVisited(true);
    q.push(source);
    *target = source;
    while(!q.empty()){
        string v = q.front();
        *target = v;
        q.pop();
        station = &StationSet[v];
        Station *dest;
        for(Networks::iterator it = station->adj.begin(); it != station->adj.end(); it++){
            int capacity = it->second.getcapacity();
            string d = it->second.getDest();
            dest = &StationSet[d];
            if(dest->getLine()!=line) continue;
            test_and_visit(q, &it->second, station, dest, capacity - it->second.getFlow());
        }
        for(PointerNetworks::iterator it = station->incoming.begin(); it != station->incoming.end(); it++){
            string o = it->first;
            dest = &StationSet[o];
            if(dest->getLine() != line) continue;
            test_and_visit(q, it->second, dest, station, it->second->getFlow());
        }
    }
    station = &StationSet[*target];
    if(station->getName() == source) return 0;
    else {
        return station->getBN();
    }
}


//EXERCISE 2.4
void Graph::print_max_flow_foreachline(string target){
    cout << "The Maximum number of trains that can simultaneously arrive at " << target << " are: ";
    Station *station = &StationSet[target];
    int max_flow = max_flow_foreachline(target);
    cout << max_flow << " and with cost " << station->getIndegree() << "$\n";
}

int Graph::max_flow_foreachline(string target){
    Station *station = &StationSet[target];
    unordered_set<string> lines;
    int max_flow = 0;
    for(Stations::iterator iter = StationSet.begin(); iter != StationSet.end(); iter++){
        iter->second.setIndegree(0);
        iter->second.setInc_flow(0);
        for(Networks::iterator it = iter->second.adj.begin(); it != iter->second.adj.end(); it++){
            it->second.setFlow(0);
        }
    }
    for(Networks::iterator it = station->adj.begin(); it != station->adj.end(); it++){
        Station *dest = &StationSet[it->second.getDest()];
        if(lines.find(dest->getLine()) == lines.end())lines.insert(dest->getLine());
    }
    for(Stations::iterator iter = StationSet.begin(); iter != StationSet.end(); iter++){
        int count = 0;
        if(iter->second.getName() == target)continue;
        for(Networks::iterator it = iter->second.adj.begin(); it != iter->second.adj.end(); it++){
            Station *dest = &StationSet[it->second.getDest()];
            if((dest->getLine() == iter->second.getLine()) && (lines.find(iter->second.getLine()) != lines.end()))count++;
        }
        if(count == 1) max_flow += edmondsKarp_noflowreset_eachline(iter->second.getName(), target, iter->second.getLine());
    }
    return max_flow;
}

int Graph::edmondsKarp_noflowreset_eachline(string source, string target, string line){
    int flow = 0;
    int max_flow = 0;
    while((flow = bfs(source, target, line)) != 0){
        augmentFlowAlongPath(target, flow);
        max_flow += flow;
    }
    return max_flow;
}

int Graph::bfs(string source, string target, string line){
    for(Stations::iterator iter = StationSet.begin(); iter != StationSet.end(); iter++){
        iter->second.setVisited(false);
        iter->second.setPath(nullptr);
    }
    queue<string> q;
    Station* station = &StationSet[source];
    station->setBN(INT_MAX);
    station->setVisited(true);
    if(source == target)return 0;
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
            if(dest->getLine()!=line && dest->getName() != target) continue;
            if(test_and_visit(q, &it->second, station, dest, capacity - it->second.getFlow()) && (d== target)) a = true;
        }
        for(PointerNetworks::iterator it = station->incoming.begin(); it != station->incoming.end(); it++){
            string o = it->first;
            dest = &StationSet[o];
            if(dest->getLine() != line && dest->getName() != target) continue;
            test_and_visit(q, it->second, dest, station, it->second->getFlow());
        }
    }
    station = &StationSet[target];
    if(!station->isVisited()) return 0;
    else {
        return station->getBN();
    }
}


//EXERCISE 3.1
void Graph::print_max_flow_min_cost(string source, string target){
    Station *station = &StationSet[target];
    max_flow_min_cost(source, target);
    cout << "The maximum number of trains with minimum cost between " << source << " and " << target << " is " << station->getInc_flow() << " and it has cost " << station->getIndegree() << "$\n";
}

void Graph::max_flow_min_cost(string source, string target) {
    edmondsKarp(source, target);
    while (is_negative_cycle(target)) {
    }
}

bool Graph::is_negative_cycle(string target) {
    for (Stations::iterator iter = StationSet.begin(); iter != StationSet.end(); iter++) {
        iter->second.setVisited(false);
        iter->second.setDist(INT_MAX);
        iter->second.setPath(nullptr);
        iter->second.setProcesssing(false);
    }
    Station *destiny = &StationSet[target];
    Station *station = &StationSet[target];
    station->setDist(0);
    for (int i = 0; i <= StationSet.size(); i++) {
        for (Stations::iterator iter = StationSet.begin(); iter != StationSet.end(); iter++) {
            Station *dest;
            station = &iter->second;
            int currency = 0;
            for (PointerNetworks::iterator it = station->incoming.begin(); it != station->incoming.end(); it++) {
                dest = &StationSet[it->first];
                Network *network = &dest->adj[station->getName()];
                if (network->getservice() == "STANDARD") currency = 2;
                else currency = 4;
                int flow;
                if (network->getFlow() != 0)flow = currency;
                else flow = 0;
                int dist = station->getDist() - flow;
                if (station->getDist() == INT_MAX) dist = INT_MAX;
                if (test_and_visit(network, dest, flow, dist) && (i == StationSet.size())) {
                    destiny->setIndegree(destiny->getIndegree() + find_better_path(dest));
                    return true;
                }
            }
            for (Networks::iterator it = station->adj.begin(); it != station->adj.end(); it++) {
                dest = &StationSet[it->second.getDest()];
                if (it->second.getservice() == "STANDARD") currency = 2;
                else currency = 4;
                int flow;
                if (it->second.getcapacity() - it->second.getFlow() > 0) flow = currency;
                else flow = 0;
                int dist = station->getDist() + flow;
                if (station->getDist() == INT_MAX) dist = INT_MAX;
                if (test_and_visit(&it->second, dest, flow, dist) && (i == StationSet.size())) {
                    destiny->setIndegree(destiny->getIndegree() + find_better_path(dest));
                    return true;
                }
            }
        }
    }
    return false;
}

bool Graph::test_and_visit(Network *network, Station *target, int flow, int dist){
    if(flow > 0){
        if(target->getDist() > dist){
            target->setDist(dist);
            target->setPath(network);
            return true;
        }
    }
    return false;
}

int Graph::find_better_path(Station *station){
    Network *network = station->getPath();
    int bottleneck = INT_MAX;
    int currency = 0;
    while(!station->isProcessing()){
        if(network->getDest() != station->getName()) {
            bottleneck = min(bottleneck, network->getFlow());
            station->setProcesssing(true);
            station = &StationSet[network->getDest()];
            network = station->getPath();
        }
        else{
            bottleneck = min(bottleneck, network->getcapacity()-network->getFlow());
            station->setProcesssing(true);
            station = &StationSet[network->getOrig()];
            network = station->getPath();
        }
    }
    Station *final = station;
    network = station->getPath();
    int value = 0;
    if(network->getservice() == "STANDARD")value = 2;
    else value = 4;
    if(network->getDest() != station->getName()){
        network->setFlow(network->getFlow()-bottleneck);
        currency -= (value * bottleneck);
        station = &StationSet[network->getDest()];
        network = station->getPath();
    }
    else{
        network->setFlow(network->getFlow() + bottleneck);
        currency += (value * bottleneck);
        station = &StationSet[network->getOrig()];
        network = station->getPath();
    }
    while(station->getName() != final->getName()){
        if(network->getservice() == "STANDARD")value = 2;
        else value = 4;
        if(network->getDest() != station->getName()) {
            network->setFlow(network->getFlow() - bottleneck);
            currency -= (value * bottleneck);
            station = &StationSet[network->getDest()];
            network = station->getPath();
        }
        else{
            network->setFlow(network->getFlow()+bottleneck);
            currency += (value * bottleneck);
            station = &StationSet[network->getOrig()];
            network = station->getPath();
        }
    }
    return currency;
}


//EXERCISE 4.1
void Graph::print_reduced_connectivity(string source, string target){
    cout << "With the reduced connectivity -> ";
    print_edmondsKarp(source, target);
}


//EXERCISE 4.2
void Graph::print_topk_reduced_connectivity(int k){
    cout << "The top " << k << " stations who were most affected out of the maintenance were:\n";
    priority_queue <pair<int, pair<string, string>>> pq;
    topk_reduced_connectivity(pq);
    if(k > (pq.size()-1)) k = pq.size()-1;
    while(k > 0){
        cout << pq.top().second.first << " <-> " << pq.top().second.second << " (-" << pq.top().first << ")\n";
        pq.pop();
        k--;
    }
}

void Graph::topk_reduced_connectivity(priority_queue <pair<int, pair<string, string>>> &pq) {
    stack<Network> temp = store;

    Station *check = &StationSet[temp.top().getDest()];
    Network *network = &check->adj[temp.top().getOrig()];
    check = &StationSet[temp.top().getOrig()];
    Network *second_network = &check->adj[temp.top().getDest()];
    for (Stations::iterator iter = StationSet.begin(); iter != StationSet.end(); iter++) {
        Station &station = iter->second;
        for (Stations::iterator it = iter; it != StationSet.end(); it++) {
            Station &s = it->second;

            if (s.getName() != station.getName()) {
                int max_flow_before_remove = edmondsKarp(station.getName(), s.getName());
                if((second_network->getFlow() <= 0) && network->getFlow() <= 0) {
                    pq.push(pair<int, pair<string, string>>(0, pair<string, string>(station.getName(), s.getName())));
                    continue;
                }
                while (!temp.empty()) {
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


//EXERCISE 4.2 ALTERNATIVE
void Graph::print_topk_reduced_connectivityALTERNATIVE(string source, string target, int k){
    edmondsKarp(source, target);
    unordered_map<string, int> temp;
    for (Stations::iterator iter = StationSet.begin(); iter != StationSet.end(); iter++) {
        Station &station = iter->second;
        temp.insert(pair<string, int>(station.getName(), station.getInc_flow()));
    }
    int res = k;
    while(!store.empty()) {
        priority_queue <pair<int, string>> pq;
        topk_reduced_connectivityALTERNITIVE(source, target, pq, temp);
        if(k > (pq.size()-1)) k = pq.size()-1;
        cout << "The top " << k << " stations who suffered the most out of the maintenance of network " << store.top().getOrig() << " <-> " << store.top().getDest() << ":\n";
        while(k > 0){
            Station *station = &StationSet[pq.top().second];
            int flow = station->getInc_flow() - temp[station->getName()];
            if(flow <= 0)cout << pq.top().second << " -> " << flow << '\n';
            else cout << pq.top().second << " -> +" << flow << '\n';
            pq.pop();
            k--;
        }
        cout << '\n';
        k = res;
        addBidirectionalNetwork(store.top().getOrig(), store.top().getDest(), store.top().getcapacity(),store.top().getservice());
        store.pop();
    }
}

void Graph::topk_reduced_connectivityALTERNITIVE(string source, string target, priority_queue <pair<int, string>> &pq, unordered_map<string, int> temp) {
    remove_network(store.top().getOrig(), store.top().getDest());
    edmondsKarp(source, target);
    for (Stations::iterator iter = StationSet.begin(); iter != StationSet.end(); iter++) {
        Station &station = iter->second;
        int flow_before = temp[station.getName()];
        pq.push(pair<int, string>(abs(station.getInc_flow() - flow_before), station.getName()));
    }
}


//GRAPH CREATION
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
        if(StationSet.find(Name) != StationSet.end() || Line == "Rede Espanhola") continue;
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
