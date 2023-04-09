#include <iostream>
#include "Header/graph.h"

using namespace std;

bool is_validStation(Graph graph, string name) {
    name = graph.find_code(name);
    if(name == "error") return false;
    return true;
}

bool is_validSource(Graph graph, string name){
    if(is_validStation(graph, name)) {
        return graph.is_valid_source(name);
    }
    return false;
}
bool is_validPath(Graph graph, string source, string target){
    if(is_validStation(graph, target)){
        return graph.is_valid_path(source, target);
    }
    return false;
}
bool check_number(string str) {
    for (int i = 0; i < str.length(); i++)
        if (isdigit(str[i]) == false)
            return false;
    return true;
}
bool LoadGraph(Graph *graph){
    string stationsPath,networkPath;
    cout<<"Please indicate the path for the file that contains Stations"<<endl;
    getline(cin,stationsPath);
    if (stationsPath == "back" || stationsPath == "menu") return true;
    if(stationsPath == "quit") return false;
    cout<<"Please indicate the path for the file that contains Networks"<<endl;
    getline(cin,networkPath);
    if (networkPath == "back" || networkPath == "menu")return true;
    if(networkPath == "quit") return false;
    *graph= Graph(stationsPath,networkPath);
    if(graph->StationSet.empty()){
        cout<<"Graph failed to initialize, check the input paths!"<<endl;
        return true;
    }
    else{
        if(!graph->StationSet.empty()){
            if(graph->StationSet.begin()->second.adj.size() <= 0) {
                cout << "Graph failed to initialize, check the input paths!" << endl;
                return true;
            }
        }
        cout<<"Graph initialized successfully!"<<endl;
        cout<<"\n";
        return true;
    }
    return true;

}
bool MetricMenu(Graph *graph) {
    bool open = true;
    string src, target, final;
    vector<pair<string, string>> store;
    int a;
    while (open) {
        int input;
        cout << "1 -> Maximum number of trains between two stations.\n"
                "2 -> What stations require the most amount of trains.\n"
                "3 -> Where there should be assigned larger budgets for the purchasing and maintenance of trains.\n"
                "4 -> Maximum number of trains that can simultaneously arrive at a given station.\n";
        getline(cin, final);
        while(final != "quit" && final != "menu" && final != "back" && (!isdigit(final[0]) && final.length() != 1)) {
            cout << "Invalid input!\n";
            cout << "1 -> Maximum number of trains between two stations.\n"
                    "2 -> What stations require the most amount of trains.\n"
                    "3 -> Where there should be assigned larger budgets for the purchasing and maintenance of trains.\n"
                    "4 -> Maximum number of trains that can simultaneously arrive at a given station.\n";
            getline(cin, final);
        }
        if(final == "back" || final == "menu")break;
        if(final == "quit") return false;
        input = stoi(final);
        switch (input) {
            case 1:
                do {
                    cout << "Please provide the source station.\n";
                    getline(cin, src);
                    while (!is_validStation(*graph, src) && src != "back" && src != "menu" && src != "quit") {
                        cout << "Please enter a valid station name!\n";
                        getline(cin, src);
                    }
                    if (src == "back") break;
                    if (src == "menu")return true;
                    if (src == "quit") return false;
                    cout << "Please provide the destination station.\n";
                    getline(cin, target);
                    while (!is_validStation(*graph, target) && target != "back" && target != "menu" &&
                           target != "quit") {
                        cout << "Please enter a valid station name!\n";
                        getline(cin, target);
                    }
                    if (target == "back") break;
                    if (target == "menu")return true;
                    if (target == "quit") return false;
                    graph->print_edmondsKarp(src, target);
                    cout << "Show paths?(Y/N)\n";
                    getline(cin, final);
                    while (final != "back" && final != "menu" && final != "quit" && final != "Y" && final != "Yes" &&
                           final != "yes" && final != "y" && final != "N" && final != "No" && final != "no" &&
                           final != "n") {
                        cout << "Please enter a valid input!\n";
                        cout << "Show paths?(Y/N)\n";
                        getline(cin, final);
                    }
                    if (final == "back")break;
                    if (final == "menu")return true;
                    if (final == "quit") return false;
                    if (final == "Y" || final == "Yes" || final == "yes" || final == "y") {
                        cout << "The paths that give the maximum number of trains between " << src << " and " << target
                             << " are:\n";
                        graph->print_path(src, src, target, INT_MAX);
                    }
                    cout << "\nContinue?(Y/N)\n";
                    getline(cin, final);
                    while (final != "back" && final != "menu" && final != "quit" && final != "Y" && final != "Yes" &&
                           final != "yes" && final != "y" && final != "N" && final != "No" && final != "no" &&
                           final != "n") {
                        cout << "Please enter a valid input!\n";
                        cout << "Continue?(Y/N)\n";
                        getline(cin, final);
                    }
                    if (final == "menu") return true;
                    if (final == "quit") return false;
                }while(final == "Yes" || final == "yes" || final == "y" || final == "Y");
                break;
            case 2:
                graph->print_all_station_pairs(&store);
                cout << "Show paths?(Y/N)\n";
                getline(cin, final);
                while (final != "back" && final != "menu" && final != "quit" && final != "Y" && final != "Yes" && final != "yes" && final != "y" && final != "N" && final != "No" && final != "no" && final != "n") {
                    cout << "Please enter a valid input!\n";
                    cout << "Show paths?(Y/N)\n";
                    getline(cin, final);
                }
                while(final == "Y" || final == "Yes" || final == "yes" || final == "y"){
                    cout << "Please enter the source station or write all to see all the best paths.\n";
                    getline(cin, src);
                    while (src!="back" && src != "all" && src != "menu" && src != "quit") {
                        bool test = false;
                        for(pair<string, string> p : store){
                            if(p.first == src || p.second == src){
                                test = true;
                                break;
                            }
                        }
                        if(test)break;
                        cout << "Please enter a valid station name!\n";
                        getline(cin, src);
                    }
                    if (src == "back") break;
                    if(src == "menu") return true;
                    if(src == "quit")return false;
                    if(src == "all"){
                        for(pair<string, string> p : store){
                            cout << "The paths that give the maximum number of trains between " << p.first << " and " << p.second << " are:\n";
                            graph->edmondsKarp(p.first, p.second);
                            graph->print_path(p.first, p.first, p.second, INT_MAX);
                            cout << '\n';
                        }
                    }
                    else {
                        cout
                                << "Please provide the destination station or write all to see all the best paths.\n";
                        getline(cin, target);
                        while (target != "back" && target != "all" && target != "menu" && target != "quit") {
                            bool test = false;
                            for(pair<string, string> p : store){
                                if((p.first == target && p.second == src) || (p.second == target && p.first == src)){
                                    test = true;
                                    break;
                                }
                            }
                            if(test)break;
                            cout << "Please enter a valid station name!\n";
                            getline(cin, target);
                        }
                        if (target == "back") break;
                        if(target == "menu")return true;
                        if(target == "quit")return false;
                        if (target == "all") {
                            for (pair<string, string> p: store) {
                                cout << "The paths that give the maximum number of trains between " << p.first
                                     << " and " << p.second << " are:\n";
                                graph->edmondsKarp(p.first, p.second);
                                graph->print_path(p.first, p.first, p.second, INT_MAX);
                                cout << '\n';
                            }
                        } else {
                            cout << "The paths that give the maximum number of trains between " << src << " and "
                                 << target << " are:\n";
                            int max_flow = graph->edmondsKarp(src, target);
                            graph->print_path(src, src, target, INT_MAX);
                            cout << "\nThe maximum number of trains is " << max_flow << '\n';
                        }
                    }
                    cout << "Continue?(Y/N)\n";
                    getline(cin, final);
                    while (final != "back" && final != "menu" && final != "quit" && final != "Y" && final != "Yes" && final != "yes" && final != "y" && final != "N" && final != "No" && final != "no" && final != "n") {
                        cout << "Please enter a valid input!\n";
                        cout << "Show paths?(Y/N)\n";
                        getline(cin, final);
                    }
                }
                if(final == "menu")return true;
                if(final == "quit") return false;
                break;
            case 3:
                while(true) {
                    cout << "Please provide what you wish to analise.\n0 -> Municipalities?\n1 -> Districts?\n";
                    getline(cin, final);
                    while (final != "back" && final != "menu" && final != "quit" &&
                           (!isdigit(final[0]) && final.length() != 1)) {
                        cout << "Please enter a valid format!\n";
                        getline(cin, src);
                    }
                    if (final == "back") break;
                    if (final == "menu")return true;
                    if (final == "quit")return false;
                    input = stoi(final);
                    switch (input) {
                        case 0:
                            cout << "Please provide the top amount to analise.\n";
                            while(true) {
                                getline(cin, target);
                                while (target != "back" && target != "menu" && target != "quit") {
                                    if(check_number(target))break;
                                    cout << "Please provide a valid input\n";
                                    getline(cin, target);
                                }
                                if (target == "back") break;
                                if (target == "menu")return true;
                                if (target == "quit")return false;
                                a = stoi(target);
                                graph->print_topk_budget_municipios(a);
                                cout << "Write back to go back\n";
                                getline(cin, final);
                                if(final != "back" && final != "menu" && final != "quit"){
                                    cout << "Please provide a valid input\n";
                                    getline(cin, final);
                                }
                                if (final == "back") break;
                                if (final == "menu")return true;
                                if (final == "quit")return false;
                            }
                            break;
                        case 1:
                            cout << "Please provide the top amount to analise.\n";
                            while(true) {
                                getline(cin, target);
                                while (target != "back" && target != "menu" && target != "quit") {
                                    if(check_number(target))break;
                                    cout << "Please provide a valid input\n";
                                    getline(cin, target);
                                }
                                if (target == "back") break;
                                if (target == "menu")return true;
                                if (target == "quit")return false;
                                a = stoi(target);
                                if (a < 0) {
                                    cout << "Please provide a valid input\n";
                                }
                                else {
                                    graph->print_topk_budget_districts(a);
                                    cout << "Write back to go back\n";
                                    getline(cin, final);
                                    if(final != "back" && final != "menu" && final != "quit"){
                                        cout << "Please provide a valid input\n";
                                        getline(cin, final);
                                    }
                                    if (final == "back") break;
                                    if (final == "menu")return true;
                                    if (final == "quit")return false;
                                }
                            }
                            break;
                        default:
                            cout << "Invalid input!\n";
                            break;
                    }
                    if(final == "back") break;
                }
                break;
            case 4:
                while(true) {
                    cout << "Please provide the destination station.\n";
                    getline(cin, target);
                    while (!is_validStation(*graph, target) && target != "back" && target != "menu" &&
                           target != "quit") {
                        cout << "Please enter a valid station name!\n";
                        getline(cin, target);
                    }
                    if (target == "back") break;
                    if (target == "menu")return true;
                    if (target == "quit") return false;
                    graph->print_max_flow_foreachline(target);
                    cout << "Show paths?(Y/N)\n";
                    getline(cin, final);
                    while(final != "back" && final != "menu" && final != "quit" && final != "Y" && final != "y" &&
                          final != "yes" && final != "Yes" && final != "N" && final != "n" && final != "no" &&
                          final != "No"){
                        cout << "Please submit a valid input!\n";
                        getline(cin, final);
                    }
                    if(final == "back")break;
                    if(final == "menu")return true;
                    if(final == "quit")return false;
                    if(final == "Y" || final == "Yes" || final == "yes" || final == "y"){
                        cout << "Please enter the source station or write all to see all\n";
                        getline(cin, src);
                        while(src != "back" && src != "menu" && src != "quit" && src != "all" && !is_validSource(*graph, src)){
                            if(is_validSource(*graph, src)){
                                if(is_validPath(*graph, src, target))break;
                            }
                            cout << "Please enter a valid station!\n";
                            getline(cin, src);
                        }
                        if(src == "back") break;
                        if(src == "menu") return true;
                        if(src == "quit")return false;
                        if(src == "all"){
                            graph->print_all_super_source_paths(target);
                        }
                        else{
                            cout << "The paths between " << src << " <-> " << target << " are:\n";
                            graph->print_path(src, src, target, INT_MAX);
                            cout << '\n';
                        }
                    }
                    cout << "Continue?(Y/N)\n";
                    getline(cin, final);
                    if (final != "back" && final != "menu" && final != "quit" && final != "Y" && final != "y" &&
                        final != "yes" && final != "Yes" && final != "N" && final != "n" && final != "no" &&
                        final != "No") {
                        cout << "Please submit a valid input!\n";
                        getline(cin, final);
                    }
                    if (final == "back" || final == "N" || final == "n" || final == "no" || final == "No")break;
                    if (final == "menu")return true;
                    if (final == "quit") return false;
                }
                break;
            default:
                cout << "Invalid input!\n";
                break;
        }
    }
    return true;
}

bool OptimizationMenu(Graph* graph) {
    string src, target, final;
    cout << "Please provide the source station.\n";
    getline(cin, src);
    while (!is_validStation(*graph, src) && src!="back" && src != "menu" && src != "quit") {
        cout << "Please enter a valid station name!\n";
        getline(cin, src);
    }
    if (src == "back" || src == "menu") return true;
    if(src == "quit")return false;
    cout << "Please provide the destination station.\n";
    getline(cin, target);
    while (!is_validStation(*graph, target) && target!="back" && target != "menu" && target != "quit") {
        cout << "Please enter a valid station name!\n";
        getline(cin, target);
    }
    if (target == "back" || target == "menu") return true;
    if(target == "quit") return false;
    graph->print_max_flow_min_cost(src, target);
    cout << "Show paths?(Y/N)\n";
    getline(cin, final);
    while (final != "back" && final != "menu" && final != "quit" && final != "Y" && final != "Yes" && final != "yes" && final != "y" && final != "N" && final != "No" && final != "no" && final != "n") {
        cout << "Please enter a valid input!\n";
        cout << "Show paths?(Y/N)\n";
        getline(cin, final);
    }
    if(final == "back" || final == "menu")return true;
    if(final == "quit") return false;
    if(final == "Y" || final == "Yes" || final == "yes" || final == "y"){
        cout << "The paths that give the maximum number of trains between " << src << " and " << target << " with minimum cost are:\n";
        graph->print_path(src, src, target, INT_MAX);
        cout << '\n';
    }
    cout << "Do you wish to compare the maximum number of trains between " << src << " and " << target << " with the maxmimum number of trains with minimum cost?(Y/N)\n";
    getline(cin, final);
    while (final != "back" && final != "menu" && final != "quit" && final != "Y" && final != "Yes" && final != "yes" && final != "y" && final != "N" && final != "No" && final != "no" && final != "n") {
        cout << "Please enter a valid input!\n";
        getline(cin, final);
    }
    if(final == "quit") return false;
    if(final == "back" || final == "menu")return true;
    if(final == "Y" || final == "y" || final == "yes" || final == "Yes"){
        graph->print_edmondsKarp(src, target);
        graph->print_max_flow_min_cost(src, target);
        cout << "Show paths?(Y/N)\n\n";
        getline(cin, final);
        while (final != "back" && final != "menu" && final != "quit" && final != "Y" && final != "Yes" && final != "yes" && final != "y" && final != "N" && final != "No" && final != "no" && final != "n") {
            cout << "Please enter a valid input!\n";
            getline(cin, final);
        }
        if(final == "quit") return false;
        if(final == "back" || final == "menu")return true;
        if(final == "Y" || final == "Yes" || final == "yes" || final == "y"){
            graph->edmondsKarp(src, target);
            cout << "The paths with the maximum number of trains between " << src << " and " << target << " are:\n";
            graph->print_path(src, src, target, INT_MAX);
            cout << "\nNow the minimum cost paths:\n";
            graph->max_flow_min_cost(src, target);
            graph->print_path(src, src, target, INT_MAX);
            cout << "\nWrite back to go back.\n";
            getline(cin, final);
            if(final != "back" && final != "menu" && final != "quit"){
                cout << "Please submit a valid input!\n";
                getline(cin, final);
            }
            if(final == "quit")return false;
        }
    }

    return true;
}
bool FailuresMenu(Graph* graph) {
    bool open = true;
    string src, target, network_src, network_dest, final, k;
    while (open) {
        int input;
        stack<pair<string, string>> store;
        stack<pair<string, string>> temp;
        cout << "1 -> Maximum number of trains between two stations in a network of reduced connectivity.\n"
                "2 -> Report on the stations that are the most affected by each segment failure.\n"
                "3 -> Report on each pair of stations that are the most affected by the segment failures.\n";
        getline(cin, final);
        while(final != "back" && final != "menu" && final != "quit" && (!isdigit(final[0]) && final.length() != 1)) {
            cout << "Invalid input!\n";
            cout << "1 -> Maximum number of trains between two stations in a network of reduced connectivity.\n"
                    "2 -> Report on the stations that are the most affected by each segment failure.\n"
                    "3 -> Report on each pair of stations that are the most affected by the segment failures.\n";
            getline(cin, final);
        }
        if(final == "back" || final == "menu")return true;
        if(final == "quit") return false;
        input = stoi(final);
        switch (input) {
            case 1:
                cout << "Please provide the source station.\n";
                getline(cin, src);
                while (!is_validStation(*graph, src) && src!="back" && src != "menu" && src != "quit") {
                    cout << "Please enter a valid station name!\n";
                    getline(cin, src);
                }
                if (src == "back") break;
                if(src == "menu") return true;
                if(src == "quit") return false;
                cout << "Please provide the destination station.\n";
                getline(cin, target);
                while (!is_validStation(*graph, target) && target!="back" && target != "menu" && target != "quit") {
                    cout << "Please enter a valid station name!\n";
                    getline(cin, target);
                }
                if (target == "back") break;
                if(target == "menu") return true;
                if(target == "quit") return false;
                do {
                    cout << "Please provide the station from which the unavailable network originates from.\n";
                    getline(cin, network_src);
                    while (!is_validStation(*graph, network_src) && network_src != "back" && network_src != "menu" && network_src != "quit") {
                        cout << "Please enter a valid station name!\n";
                        getline(cin, network_src);
                    }
                    if (network_src == "back") break;
                    if(network_src == "menu") {
                        graph->restore_maintenance();
                        return true;
                    }
                    if(network_src == "quit"){
                        graph->restore_maintenance();
                        return false;
                    }
                    cout << "Please provide the station from which the unavailable network arrives to.\n";
                    getline(cin, network_dest);
                    while (!is_validStation(*graph, network_dest) && network_dest != "back" && network_dest != "menu" && network_dest != "quit") {
                        cout << "Please enter a valid station name!\n";
                        getline(cin, network_dest);
                    }
                    if (network_dest == "back") break;
                    if(network_dest == "menu"){
                        graph->restore_maintenance();
                        return true;
                    }
                    if(network_dest == "quit"){
                        graph->restore_maintenance();
                        return false;
                    }
                    if(graph->valid_remove(network_src, network_dest)) {
                        graph->remove_network(network_src, network_dest);
                        cout << "Network has successfully been put on maintenance\n";
                        store.push(pair<string, string>(network_src, network_dest));
                    }
                    else cout << "The selected network does not connect from " << network_src << "to " << network_dest << "therefore it has not been put on maintenance\n";
                    cout << "Do you wish to select more networks for maintenance?\n(Y/N)\n";
                    getline(cin, final);
                    while (final != "back" && final != "menu" && final != "quit" && final != "Y" && final != "Yes" && final != "yes" && final != "y" && final != "N" && final != "No" && final != "no" && final != "n") {
                        cout << "Please enter a valid input!\n";
                        getline(cin, final);
                    }
                    if(final == "back" || final == "N" || final == "No" || final == "no" || final == "n") break;
                    if(final == "menu"){
                        graph->restore_maintenance();
                        return true;
                    }
                    if(final == "quit"){
                        graph->restore_maintenance();
                        return false;
                    }
                }while(true);
                if(final == "back" || network_dest == "back" || network_src == "back") {
                    graph->restore_maintenance();
                    break;
                }
                graph->print_reduced_connectivity(src, target);
                graph->restore_maintenance();
                cout << "\nShow paths?(Y/N)\n";
                getline(cin, final);
                while (final != "back" && final != "menu" && final != "quit" && final != "Y" && final != "Yes" && final != "yes" && final != "y" && final != "N" && final != "No" && final != "no" && final != "n") {
                    cout << "Please enter a valid input!\n";
                    getline(cin, final);
                }
                if(final == "quit") return false;
                if(final == "menu")return true;
                if(final == "back")break;
                if(final == "Y" || final == "Yes" || final == "yes" || final == "y"){
                    cout << "The paths with the maximum number of trains between " << src << " and " << target
                         << " with the reduced connectivity are:\n";
                    temp = store;
                    while(!temp.empty()){
                        graph->valid_remove(temp.top().first, temp.top().second);
                        graph->remove_network(temp.top().first, temp.top().second);
                        temp.pop();
                    }
                    graph->edmondsKarp(src, target);
                    graph->print_path(src, src, target, INT_MAX);
                    graph->restore_maintenance();
                    cout << '\n';
                }
                cout << "Do you wish to compare the maximum number of trains between " << src << " and " << target << " with and without the reduced connectivity?(Y/N)\n";
                getline(cin, final);
                while (final != "back" && final != "menu" && final != "quit" && final != "Y" && final != "Yes" && final != "yes" && final != "y" && final != "N" && final != "No" && final != "no" && final != "n") {
                    cout << "Please enter a valid input!\n";
                    getline(cin, final);
                }
                if(final == "back")break;
                if(final == "quit") return false;
                if(final == "menu")return true;
                if(final == "Y" || final == "y" || final == "yes" || final == "Yes") {
                    graph->print_edmondsKarp(src, target);
                    temp = store;
                    while (!temp.empty()) {
                        graph->valid_remove(temp.top().first, temp.top().second);
                        graph->remove_network(temp.top().first, temp.top().second);
                        temp.pop();
                    }
                    graph->print_reduced_connectivity(src, target);
                    graph->restore_maintenance();
                    cout << "\nShow paths?(Y/N)\n";
                    getline(cin, final);
                    while (final != "back" && final != "menu" && final != "quit" && final != "Y" && final != "Yes" &&
                           final != "yes" && final != "y" && final != "N" && final != "No" && final != "no" &&
                           final != "n") {
                        cout << "Please enter a valid input!\n";
                        getline(cin, final);
                    }
                    if (final == "quit") return false;
                    if (final == "menu")return true;
                    if(final == "back")break;
                    if (final == "Y" || final == "Yes" || final == "yes" || final == "y") {
                        graph->edmondsKarp(src, target);
                        cout << "The paths with the maximum number of trains between " << src << " and " << target
                             << " are:\n";
                        graph->print_path(src, src, target, INT_MAX);
                        cout << "\nNow the reduced connectivity paths:\n";
                        temp = store;
                        while(!temp.empty()){
                            graph->valid_remove(temp.top().first, temp.top().second);
                            graph->remove_network(temp.top().first, temp.top().second);
                            temp.pop();
                        }
                        graph->edmondsKarp(src, target);
                        graph->print_path(src, src, target, INT_MAX);
                        graph->restore_maintenance();
                    }
                }
                cout << "\nWrite back to go back.\n";
                getline(cin, final);
                while(final != "back" && final != "menu" && final != "quit"){
                    cout << "Please enter a valid input!\n";
                    getline(cin, final);
                }
                if(final == "menu")return true;
                if(final == "quit") return false;
                break;
            case 2:
                cout << "Please provide the source station\n";
                getline(cin, src);
                while (!is_validStation(*graph, src) && src!="back" && src != "menu" && src != "quit") {
                    cout << "Please enter a valid station name!\n";
                    getline(cin, src);
                }
                if (src == "back") break;
                if(src == "menu")return true;
                if(src == "quit")return false;
                cout << "Please provide the destination station\n";
                getline(cin, target);
                while (!is_validStation(*graph, target) && target!="back" && target != "menu" && target != "quit") {
                    cout << "Please enter a valid station name!\n";
                    getline(cin, target);
                }
                if (target == "back") break;
                if(target == "menu")return true;
                if(target == "quit")return false;
                cout << "Please provide the number of stations you wish to see\n";
                getline(cin, k);
                while (k!="back" && k != "menu" && k != "quit" && !check_number(k)) {
                    cout << "Please enter a valid number!\n";
                    getline(cin, k);
                }
                if (k == "back") break;
                if(k == "menu") return true;
                if(k == "quit") return false;
                input = stoi(k);
                do {
                    cout << "Please provide the station from which the unavailable network originates from\n";
                    getline(cin, network_src);
                    while (!is_validStation(*graph, network_src) && network_src != "back" && network_src != "menu" && network_src != "quit") {
                        cout << "Please enter a valid station name!\n";
                        getline(cin, network_src);
                    }
                    if (network_src == "back") break;
                    if(network_src == "menu"){
                        graph->restore_maintenance();
                        return true;
                    }
                    if(network_src == "quit"){
                        graph->restore_maintenance();
                        return false;
                    }
                    cout << "Please provide the station from which the unavailable network arrives to\n";
                    getline(cin, network_dest);
                    while (!is_validStation(*graph, network_dest) && network_dest != "back" && network_dest != "menu" && network_dest != "quit") {
                        cout << "Please enter a valid station name!\n";
                        getline(cin, network_dest);
                    }
                    if (network_dest == "back") break;
                    if(network_dest == "menu"){
                        graph->restore_maintenance();
                        return true;
                    }
                    if(network_dest == "quit"){
                        graph->restore_maintenance();
                        return false;
                    }
                    if(graph->valid_remove(network_src, network_dest)) {
                        cout << "Network has successfully been put on maintenance\n";
                        store.push(pair<string, string>(network_src, network_dest));
                    }
                    else cout << "The selected network does not connect from " << network_src << "to " << network_dest << "therefore it has not been put on maintenance\n";
                    cout << "Do you wish to select more networks for maintenance?\n(Y/N)\n";
                    getline(cin, final);
                    while (final != "back" && final != "menu" && final != "quit" && final != "Y" && final != "Yes" && final != "yes" && final != "y" && final != "N" && final != "No" && final != "no" && final != "n") {
                        cout << "Please enter a valid input!\n";
                        getline(cin, final);
                    }
                    if(final == "back" || final == "N" || final == "No" || final == "no" || final == "n") break;
                    if(final == "menu"){
                        graph->restore_maintenance();
                        return true;
                    }
                    if(final == "quit"){
                        graph->restore_maintenance();
                        return false;
                    }
                }while(true);
                if(final == "back" || network_dest == "back" || network_src == "back") {
                    graph->restore_maintenance();
                    break;
                }
                graph->print_topk_reduced_connectivityALTERNATIVE(src, target,stoi(k));
                graph->restore_maintenance();
                cout << "\nShow paths?(Y/N)\n";
                getline(cin, final);
                while (final != "back" && final != "menu" && final != "quit" && final != "Y" && final != "Yes" && final != "yes" && final != "y" && final != "N" && final != "No" && final != "no" && final != "n") {
                    cout << "Please enter a valid input!\n";
                    getline(cin, final);
                }
                while(final == "Y" || final == "Yes" || final == "yes" || final == "y") {
                    cout << "Please provide the station from which the unavailable network originates from or write all to see for all the unavailable segments\n";
                    getline(cin, network_src);
                    while (network_src != "back" && network_src != "all" && network_src != "menu" &&
                           network_src != "quit") {
                        temp = store;
                        while (!temp.empty()) {
                            if (temp.top().first == network_src || temp.top().second == network_src) {
                                break;
                            }
                            temp.pop();
                        }
                        if(temp.size() > 0)break;
                        cout << "Please submit a valid input!\n";
                        getline(cin, network_src);
                    }
                    if (network_src == "back")break;
                    if (network_src == "menu")return true;
                    if (network_src == "quit")return false;
                    if (network_src == "all") {
                        temp = store;
                        while (!temp.empty()) {
                            cout << "The paths with the maximum number of trains between " << src << " and "
                                 << target << " with the reduced connectivity of " << temp.top().first << " <-> "
                                 << temp.top().second << " are:\n";
                            graph->valid_remove(temp.top().first, temp.top().second);
                            graph->remove_network(temp.top().first, temp.top().second);
                            temp.pop();
                            graph->edmondsKarp(src, target);
                            graph->print_path(src, src, target, INT_MAX);
                            cout << '\n';
                        }
                        graph->restore_maintenance();
                    } else {
                        cout << "Please provide the station from which the unavailable network arrives to\n";
                        getline(cin, network_dest);
                        while (network_dest != "back" && network_dest != "all" && network_dest != "menu" &&
                               network_dest != "quit") {
                            temp = store;
                            while (!temp.empty()) {
                                if ((temp.top().first == network_dest && temp.top().second == network_src) ||
                                    (temp.top().second == network_dest && network_src == temp.top().first)) {
                                    break;
                                }
                                temp.pop();
                            }
                            if(temp.size() > 0)break;
                            cout << "Please submit a valid input!\n";
                            getline(cin, network_dest);
                        }
                        if (network_dest == "back")break;
                        if (network_dest == "menu")return true;
                        if (network_dest == "quit")return false;
                        if (network_dest == "all") {
                            temp = store;
                            while (!temp.empty()) {
                                cout << "The paths with the maximum number of trains between " << src << " and "
                                     << target << " with the reduced connectivity of " << temp.top().first
                                     << " <-> " << temp.top().second << "are:\n";
                                graph->valid_remove(temp.top().first, temp.top().second);
                                graph->remove_network(temp.top().first, temp.top().second);
                                temp.pop();
                                graph->edmondsKarp(src, target);
                                graph->print_path(src, src, target, INT_MAX);
                                cout << '\n';
                            }
                            graph->restore_maintenance();
                        } else {
                            temp = store;
                            cout << "The paths with the maximum number of trains between " << src << " and "
                                 << target << " with the reduced connectivity of " << temp.top().first << " <-> "
                                 << temp.top().second << "are:\n";
                            graph->valid_remove(network_src, network_dest);
                            graph->edmondsKarp(src, target);
                            graph->print_path(src, src, target, INT_MAX);
                            cout << '\n';
                        }
                    }
                    cout << "Continue?(Y/N)\n";
                    getline(cin, final);
                    while (final != "back" && final != "menu" && final != "quit" && final != "Y" && final != "Yes" && final != "yes" && final != "y" && final != "N" && final != "No" && final != "no" && final != "n") {
                        cout << "Please enter a valid input!\n";
                        getline(cin, final);
                    }
                }
                if(final == "quit") return false;
                if(final == "menu")return true;
                if(network_src == "back" || network_dest == "back" || final == "back") break;
                cout << "Do you wish to compare the maximum number of trains between " << src << " and " << target << " with and without the reduced connectivity?(Y/N)\n";
                getline(cin, final);
                while (final != "back" && final != "menu" && final != "quit" && final != "Y" && final != "Yes" && final != "yes" && final != "y" && final != "N" && final != "No" && final != "no" && final != "n") {
                    cout << "Please enter a valid input!\n";
                    getline(cin, final);
                }
                if(final == "back")break;
                if(final == "quit") return false;
                if(final == "menu")return true;
                while(final == "Y" || final == "Yes" || final == "yes" || final == "y") {
                    cout << "Please provide the station from which the unavailable network originates from or write all to see for all the unavailable segments\n";
                    getline(cin, network_src);
                    while (network_src != "back" && network_src != "all" && network_src != "menu" &&
                           network_src != "quit") {
                        temp = store;
                        while (!temp.empty()) {
                            if (temp.top().first == network_src || temp.top().second == network_src) {
                                break;
                            }
                            temp.pop();
                        }
                        if(temp.size() > 0) break;
                        cout << "Please submit a valid input!\n";
                        getline(cin, network_src);
                    }
                    if (network_src == "back")break;
                    if (network_src == "menu")return true;
                    if (network_src == "quit")return false;
                    if (network_src == "all") {
                        graph->print_edmondsKarp(src, target);
                        temp = store;
                        while (!temp.empty()) {
                            cout << "With the network " << temp.top().first << " <-> " << temp.top().second << " on maintenance: ";
                            graph->valid_remove(temp.top().first, temp.top().second);
                            graph->remove_network(temp.top().first, temp.top().second);
                            temp.pop();
                            graph->print_edmondsKarp(src, target);
                            graph->restore_maintenance();
                        }
                    } else {
                        cout << "Please provide the station from which the unavailable network arrives to or write all to see for all the unavailable segments\n";
                        getline(cin, network_dest);
                        while (network_dest != "back" && network_dest != "all" && network_dest != "menu" &&
                               network_dest != "quit") {
                            temp = store;
                            while (!temp.empty()) {
                                if ((temp.top().first == network_dest && temp.top().second == network_src) ||
                                    (temp.top().second == network_dest && network_src == temp.top().first)) {
                                    break;
                                }
                                temp.pop();
                            }
                            if(temp.size() > 0)break;
                            cout << "Please submit a valid input!\n";
                            getline(cin, network_dest);
                        }
                        if (network_dest == "back")break;
                        if (network_dest == "menu")return true;
                        if (network_dest == "quit")return false;
                        if (network_dest == "all") {
                            graph->print_edmondsKarp(src, target);
                            temp = store;
                            while (!temp.empty()) {
                                cout << "With the network " << temp.top().first << " <-> " << temp.top().second << " on maintenance: ";
                                graph->valid_remove(temp.top().first, temp.top().second);
                                graph->remove_network(temp.top().first, temp.top().second);
                                temp.pop();
                                graph->print_edmondsKarp(src, target);
                                graph->restore_maintenance();
                            }
                        } else {
                            graph->print_edmondsKarp(src, target);
                            graph->valid_remove(network_src, network_dest);
                            graph->remove_network(network_src, network_dest);
                            cout << "With the network " << network_src << " <-> " << network_dest << " on maintenance: ";
                            graph->print_edmondsKarp(src, target);
                            graph->restore_maintenance();
                        }
                    }
                    cout << "\nShow paths?(Y/N)\n";
                    getline(cin, final);
                    while (final != "back" && final != "menu" && final != "quit" && final != "Y" && final != "Yes" && final != "yes" && final != "y" && final != "N" && final != "No" && final != "no" && final != "n") {
                        cout << "Please enter a valid input!\n";
                        getline(cin, final);
                    }
                    while(final == "Y" || final == "Yes" || final == "yes" || final == "y") {
                        cout << "Please provide the station from which the unavailable network originates from or write all to see for all the unavailable segments\n";
                        getline(cin, network_src);
                        while (network_src != "back" && network_src != "all" && network_src != "menu" &&
                               network_src != "quit") {
                            temp = store;
                            while (!temp.empty()) {
                                if (temp.top().first == network_src || temp.top().second == network_src) {
                                    break;
                                }
                                temp.pop();
                            }
                            if(temp.size() > 0)break;
                            cout << "Please submit a valid input!\n";
                            getline(cin, network_src);
                        }
                        if (network_src == "back")break;
                        if (network_src == "menu")return true;
                        if (network_src == "quit")return false;
                        if (network_src == "all") {
                            graph->edmondsKarp(src, target);
                            cout << "The paths with the maximum number of trains between " << src << " and " << target << " are:\n";
                            graph->print_path(src, src, target, INT_MAX);
                            cout << '\n';
                            temp = store;
                            while (!temp.empty()) {
                                cout << "Now with the reduced connectivity of " << temp.top().first << " <-> "
                                     << temp.top().second << ":\n";
                                graph->valid_remove(temp.top().first, temp.top().second);
                                graph->remove_network(temp.top().first, temp.top().second);
                                temp.pop();
                                graph->edmondsKarp(src, target);
                                graph->print_path(src, src, target, INT_MAX);
                                graph->restore_maintenance();
                                cout << '\n';
                            }
                        } else {
                            cout << "Please provide the station from which the unavailable network arrives to\n";
                            getline(cin, network_dest);
                            while (network_dest != "back" && network_dest != "all" && network_dest != "menu" &&
                                   network_dest != "quit") {
                                temp = store;
                                while (!temp.empty()) {
                                    if ((temp.top().first == network_dest && temp.top().second == network_src) ||
                                        (temp.top().second == network_dest && network_src == temp.top().first)) {
                                        break;
                                    }
                                    temp.pop();
                                }
                                if(temp.size() > 0)break;
                                cout << "Please submit a valid input!\n";
                                getline(cin, network_dest);
                            }
                            if (network_dest == "back")break;
                            if (network_dest == "menu")return true;
                            if (network_dest == "quit")return false;
                            if (network_dest == "all") {
                                graph->edmondsKarp(src, target);
                                cout << "The paths with the maximum number of trains between " << src << " and " << target << " are:\n";
                                graph->print_path(src, src, target, INT_MAX);
                                cout << '\n';
                                temp = store;
                                while (!temp.empty()) {
                                    cout << "Now with the reduced connectivity of " << temp.top().first << " <-> "
                                         << temp.top().second << ":\n";
                                    graph->valid_remove(temp.top().first, temp.top().second);
                                    graph->remove_network(temp.top().first, temp.top().second);
                                    temp.pop();
                                    graph->edmondsKarp(src, target);
                                    graph->print_path(src, src, target, INT_MAX);
                                    cout << '\n';
                                    graph->restore_maintenance();
                                }
                            } else {
                                graph->edmondsKarp(src, target);
                                cout << "The paths with the maximum number of trains between " << src << " and " << target << " are:\n";
                                graph->print_path(src, src, target, INT_MAX);
                                cout << '\n';
                                cout << "Now for the reduced connectivity of " << network_src << " <-> " << network_dest << ":\n";
                                graph->valid_remove(network_src, network_dest);
                                graph->remove_network(network_src, network_dest);
                                graph->edmondsKarp(src, target);
                                graph->print_path(src, src, target, INT_MAX);
                                graph->restore_maintenance();
                                cout << '\n';
                            }
                        }
                        break;
                    }
                    cout << "Continue?(Y/N)\n";
                    getline(cin, final);
                    while (final != "back" && final != "menu" && final != "quit" && final != "Y" && final != "Yes" && final != "yes" && final != "y" && final != "N" && final != "No" && final != "no" && final != "n") {
                        cout << "Please enter a valid input!\n";
                        getline(cin, final);
                    }
                }
                if(final == "menu")return true;
                if(final == "quit") return false;
                if(final == "back" || network_src == "back" || network_dest == "back")break;
                break;
            case 3:
                cout << "Please provide the number of stations you wish to see.\n";
                getline(cin, final);
                while (final != "back" && final != "menu" && final != "quit" && !check_number(final)) {
                    cout << "Please enter a valid number!\n";
                    getline(cin, final);
                }
                if (final == "back") break;
                if(final == "menu")return true;
                if(final == "quit")return false;
                input = stoi(final);
                do {
                    cout << "Please provide the station from which the unavailable network originates from.\n";
                    getline(cin, network_src);
                    while (!is_validStation(*graph, network_src) && network_src != "back" && network_src != "menu" && network_src != "quit") {
                        cout << "Please enter a valid station name!\n";
                        getline(cin, network_src);
                    }
                    if (network_src == "back") break;
                    if(network_src == "menu"){
                        graph->restore_maintenance();
                        return true;
                    }
                    if(network_src == "quit"){
                        graph->restore_maintenance();
                        return false;
                    }
                    cout << "Please provide the station from which the unavailable network arrives to.\n";
                    getline(cin, network_dest);
                    while (!is_validStation(*graph, network_dest) && network_dest != "back" && network_dest != "menu" && network_dest != "quit" && network_src == network_dest) {
                        cout << "Please enter a valid station name!\n";
                        getline(cin, network_dest);
                    }
                    if (network_dest == "back") break;
                    if(network_dest == "menu"){
                        graph->restore_maintenance();
                        return true;
                    }
                    if(network_dest == "quit"){
                        graph->restore_maintenance();
                        return false;
                    }
                    if(graph->valid_remove(network_src, network_dest)) {
                        cout << "Network has successfully been put on maintenance\n";
                    }
                    else cout << "The selected network does not connect from " << network_src << "to " << network_dest << "therefore it has not been put on maintenance\n";
                    cout << "Do you wish to select more networks for maintenance?\n(Y/N)\n";
                    getline(cin, final);
                    while (final != "back" && final != "menu" && final != "quit" && final != "Y" && final != "Yes" && final != "yes" && final != "y" && final != "N" && final != "No" && final != "no" && final != "n") {
                        cout << "Please enter a valid input!\n";
                        getline(cin, final);
                    }
                    if(final == "back" || final == "N" || final == "No" || final == "no" || final == "n") break;
                    if(final == "menu"){
                        graph->restore_maintenance();
                        return true;
                    }
                    if(final == "quit"){
                        graph->restore_maintenance();
                        return false;
                    }
                }while(true);
                if(final == "back" || network_dest == "back" || network_src == "back") {
                    graph->restore_maintenance();
                    break;
                }
                graph->print_topk_reduced_connectivity(input);
                graph->restore_maintenance();
                cout << "Write back to go back\n";
                getline(cin, final);
                while(final != "back" && final != "menu" && final != "quit"){
                    cout << "Please submit a valid input!\n";
                    getline(cin, final);
                }
                if(final == "menu")return true;
                if(final == "quit")return false;
                break;
            default:
                cout << "Invalid input!\n";
                break;
        }
    }
    return true;
}


int main() {
    Graph graph;
    string guide;
    bool on = true;
    while (on) {
        int input;
        cout << "1 -> Load Graph (Must initialize for other functions to work)\n"
                "2 -> Basic Service Metrics\n"
                "3 -> Operation Cost Optimization\n"
                "4 -> Reliability and Sensitivity to Line Failures\n"
                "0 -> Guide\n";
        getline(cin, guide);
        while(guide != "quit" && (!isdigit(guide[0]) && guide.length() != 1)) {
            cout << "Invalid input!\n";
            cout << "1- Load Graph(Must initialize for other functions to work)\n"
                    "2 -> Basic Service Metrics\n"
                    "3 -> Operation Cost Optimization\n"
                    "4 -> Reliability and Sensitivity to Line Failures\n"
                    "0 -> Guide\n";
            getline(cin, guide);
        }
        if(guide == "quit")break;
        input = stoi(guide);
        /*cin.clear();
        cin.ignore(INT_MAX, '\n');*/
        switch (input) {
            case 0:
                cout << "To go back at any moment just write back\n"
                        "To terminate the program at any moment just write quit\n"
                        "To go back to main menu just write menu\n";
                getline(cin, guide);
                while(guide != "back" && guide != "quit" && guide != "menu"){
                    cout << "Please submit a valid input!\n";
                    cout << "To go back at any moment just write back\n"
                            "To terminate the program at any moment just write quit\n"
                            "To go back to main menu just write menu\n";
                    getline(cin, guide);
                }
                break;
            case 1:
                if(!LoadGraph(&graph))guide = "quit";
                break;
            case 2:
                if (graph.StationSet.empty()) {cout << "Graph has not been loaded yet!\n"; break;}
                if(!MetricMenu(&graph)) guide = "quit";
                break;
            case 3:
                if (graph.StationSet.empty()) {cout << "Graph has not been loaded yet!\n"; break;}
                if(!OptimizationMenu(&graph)) guide = "quit";
                break;
            case 4:
                if (graph.StationSet.empty()) {cout << "Graph has not been loaded yet!\n"; break;}
                if(!FailuresMenu(&graph)) guide = "quit";
                break;
            default:
                cout << "Invalid input!\n";
                break;
        }
        if(guide == "quit") break;
    }
    return 0;
}
