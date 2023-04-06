#include <iostream>
#include "Header/graph.h"

using namespace std;

bool is_validStation(Graph graph, string name) {
    name = graph.find_code(name);
    if(name == "error") return false;
    return true;
}
Graph LoadGraph(){
    string stationsPath,networkPath;
    cout<<"Please indicate the path for the file that contains Stations or write back to go back"<<endl;
    cin.ignore();
    getline(cin,stationsPath);
    if (stationsPath == "back") return Graph();
    cout<<"Please indicate the path for the file that contains Networks or write back to go back"<<endl;
    cin.ignore();
    getline(cin,networkPath);
    if (stationsPath == "back") return Graph();
    Graph g = Graph(stationsPath,networkPath);
    if(g.StationSet.empty()){
        cout<<"Graph failed to initialize, check the input paths!"<<endl;
    }
    else{
        cout<<"Graph initialized successfully!"<<endl;
        cout<<"\n";
    }
    return g;

}
void MetricMenu(Graph *graph) {
    bool open = true;
    string src, target;
    int a;
    while (open) {
        int input;
        cout << "1 -> Maximum number of trains between two stations.\n"
                "2 -> What stations require the most amount of trains.\n"
                "3 -> Where there should be assigned larger budgets for the purchasing and maintenance of trains.\n"
                "4 -> Maximum number of trains that can simultaneously arrive at a given station.\n"
                "0 -> Go Back\n";
        while(!(cin >> input)) {
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            cout << "Invalid input!\n";
            cout << "1 -> Maximum number of trains between two stations.\n"
                    "2 -> What stations require the most amount of trains.\n"
                    "3 -> Where there should be assigned larger budgets for the purchasing and maintenance of trains.\n"
                    "4 -> Maximum number of trains that can simultaneously arrive at a given station.\n"
                    "0 -> Go Back\n";
        }
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        switch (input) {
            case 0:
                open = false;
                break;
            case 1:
                cout << "Please provide the source station or write back to go back.\n";
                getline(cin, src);
                while (!is_validStation(*graph, src) && src!="back") {
                    cout << "Please enter a valid station name!\n";
                    getline(cin, src);
                }
                if (src == "back") break;
                cout << "Please provide the destination station or write back to go back.\n";
                getline(cin, target);
                while (!is_validStation(*graph, target) && target!="back") {
                    cout << "Please enter a valid station name!\n";
                    getline(cin, target);
                }
                if (target == "back") break;
                graph->print_edmondsKarp(src, target);
                break;
            case 2:
                graph->print_all_station_pairs();
                break;
            case 3:
                cout << "Please provide what you wish to analise.\nMunicipalities?\nDistricts?\n";
                getline(cin, src);
                while (src!="back" && src != "districts" && src != "municipalities" && src != "Municipalities" && src != "Districts") {
                    cout << "Please enter a valid format!\n";
                    getline(cin, src);
                }
                if (src == "back") break;
                cout << "Please provide the top amount to analise.\n";
                getline(cin, target);
                a = stoi(target);
                while(a<0 && target != "back"){
                    cout << "Please provide a valid number\n";
                    getline(cin, target);
                    a = stoi(target);
                }
                if(target == "back") break;
                if(src == "districts" || src == "Districts")graph->print_topk_budget_districts(a);
                else graph->print_topk_budget_municipios(a);
                break;
            case 4:
                cout << "Please provide the station or write back to go back.\n";
                getline(cin, target);
                while (!is_validStation(*graph, target) && target!="back") {
                    cout << "Please enter a valid station name!\n";
                    getline(cin, target);
                }
                if (target == "back") break;
                graph->print_max_flow_foreachline(target);
                break;
            default:
                cout << "Invalid input!\n";
                break;
        }
    }
}

void OptimizationMenu(Graph* graph) {
    cin.clear();
    cin.ignore(INT_MAX, '\n');
    string src, target;
    cout << "Please provide the source station or write back to go back.\n";
    getline(cin, src);
    while (!is_validStation(*graph, src) && src!="back") {
        cout << "Please enter a valid station name!\n";
        getline(cin, src);
    }
    if (src == "back") return;
    cout << "Please provide the destination station or write back to go back.\n";
    getline(cin, target);
    while (!is_validStation(*graph, target) && target!="back") {
        cout << "Please enter a valid station name!\n";
        getline(cin, target);
    }
    if (target == "back") return;
    graph->print_max_flow_min_cost(src, target);
}
void FailuresMenu(Graph* graph) {
    bool open = true;
    string src, target, network_src, network_dest, final, k;
    while (open) {
        int input;
        cout << "1 -> Maximum number of trains between two stations in a network of reduced connectivity.\n"
                "2 -> Report on the stations that are the most affected by each segment failure.\n"
                "0 -> Go Back\n";
        while(!(cin >> input)) {
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            cout << "Invalid input!\n";
            cout << "1 -> Maximum number of trains between two stations in a network of reduced connectivity.\n"
                    "2 -> Report on the stations that are the most affected by each segment failure.\n"
                    "0 -> Go Back\n";
        }
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        switch (input) {
            case 0:
                open = false;
                break;
            case 1:
                cout << "Please provide the source station or write back to go back\n";
                getline(cin, src);
                while (!is_validStation(*graph, src) && src!="back") {
                    cout << "Please enter a valid station name!\n";
                    getline(cin, src);
                }
                if (src == "back") break;
                cout << "Please provide the destination station or write back to go back\n";
                getline(cin, target);
                while (!is_validStation(*graph, target) && target!="back") {
                    cout << "Please enter a valid station name!\n";
                    getline(cin, target);
                }
                if (target == "back") break;
                do {
                    cout << "Please provide the station from which the unavailable network originates from or write back to go back\n";
                    getline(cin, network_src);
                    while (!is_validStation(*graph, network_src) && network_src != "back") {
                        cout << "Please enter a valid station name!\n";
                        getline(cin, network_src);
                    }
                    if (network_src == "back") break;
                    cout << "Please provide the station from which the unavailable network arrives to or write back to go back\n";
                    getline(cin, network_dest);
                    while (!is_validStation(*graph, network_dest) && network_dest != "back") {
                        cout << "Please enter a valid station name!\n";
                        getline(cin, network_dest);
                    }
                    if (network_dest == "back") break;
                    if(graph->valid_remove(network_src, network_dest)) {
                        graph->remove_network(network_src, network_dest);
                        cout << "Network has successfully been put on maintenance\n";
                    }
                    else cout << "The selected network does not connect from " << network_src << "to " << network_dest << "therefore it has not been put on maintenance\n";
                    cout << "Do you wish to select more networks for maintenance?\n(Y/N)\n";
                    getline(cin, final);
                    while (final != "back" && final != "Y" && final != "Yes" && final != "yes" && final != "y" && final != "N" && final != "No" && final != "no" && final != "n") {
                        cout << "Please enter a valid input!\n";
                        getline(cin, final);
                    }
                    if(final == "back" || final == "N" || final == "No" || final == "no" || final == "n") break;
                }while(true);
                if(final == "back" || network_dest == "back" || network_src == "back") break;
                graph->print_reduced_connectivity(src, target);
                graph->restore_maintenance();
                break;
            case 2:
                cout << "Please provide the number of stations you wish to see or write back to go back\n";
                getline(cin, k);
                while (k!="back") {
                    cout << "Please enter a valid number!\n";
                    getline(cin, k);
                }
                if (k == "back") break;
                graph->print_topk_reduced_connectivity(stoi(k));
                break;
            default:
                cout << "Invalid input!\n";
                break;
        }
    }
}


int main() {
    std::string path1="../DataSet/stations.csv";
    std::string path2="../DataSet/network.csv";
    Graph graph;
    graph= Graph(path1,path2);

    //graph.print_all_station_pairs();
    /*int a = graph.max_flow_foreachline("Lisboa Oriente");
    cout << a << '\n';*/
    //graph.print_topk_budget_municipios(250);
    //graph.print_topk_budget_districts(50);
    /*int currency = graph.max_flow_min_cost("Casa Branca", "Viana do Castelo");
    cout << currency << '\n';*/
    /*int a = graph.max_flow_foreachline("Linha do Norte");
    cout << a << '\n';*/
    /*graph.valid_remove("Entroncamento", "Lisboa Oriente");*/
    //graph.print_topk_reduced_connectivity(5);
    //graph.print_edmondsKarp("Santarém", "Lisboa Oriente");
    //graph.print_all_station_pairs();

    bool on = true;
    while (on) {
        int input;
        cout << "1 -> Load Graph (Must initialize for other functions to work)\n"
                "2 -> Basic Service Metrics\n"
                "3 -> Operation Cost Optimization\n"
                "4 -> Reliability and Sensitivity to Line Failures\n"
                "0 - Quit\n";
        while(!(cin >> input)) {
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            cout << "Invalid input!\n";
            cout << "1- Load Graph(Must initialize for other functions to work)"
                    "2 -> Basic Service Metrics\n"
                    "3 -> Operation Cost Optimization\n"
                    "4 -> Reliability and Sensitivity to Line Failures\n"
                    "0 - Quit\n";
        }
        switch (input) {
            case 0:
                on=false;
                break;
            case 1:
                graph=LoadGraph();
                break;
            case 2:
                if (graph.StationSet.empty()) {cout << "Graph has not been loaded yet!\n"; break;}
                MetricMenu(&graph);
                break;
            case 3:
                if (graph.StationSet.empty()) {cout << "Graph has not been loaded yet!\n"; break;}
                OptimizationMenu(&graph);
                break;
            case 4:
                if (graph.StationSet.empty()) {cout << "Graph has not been loaded yet!\n"; break;}
                FailuresMenu(&graph);
                break;
            default:
                cout << "Invalid input!\n";
                break;
        }
    }
    return 0;
}
