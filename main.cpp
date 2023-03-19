#include <iostream>
#include "Header/graph.h"

using namespace std;

bool is_validStation(Graph graph, string name) {
    name = graph.find_code(name);
    if(name == "error") return false;
    if (graph.getStationSet().find(name)!=graph.getStationSet().end()) return true;
    return false;
}

void MetricMenu(Graph *graph) {
    bool open = true;
    string src, target;
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
                graph->print_edmundsKarp(src, target);
                break;
            case 2:
                graph->print_all_station_pairs();
                break;
            case 3:
                //graph->print_..;
                break;
            case 4:
                cout << "Please provide the station or write back to go back.\n";
                getline(cin, target);
                while (!is_validStation(*graph, target) && target!="back") {
                    cout << "Please enter a valid station name!\n";
                    getline(cin, target);
                }
                if (target == "back") break;
                //graph->print_..;
                break;
            default:
                cout << "Invalid input!\n";
                break;
        }
    }
}
void OptimizationMenu(Graph* graph) {
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
    //graph->print_..;
}
void FailuresMenu(Graph* graph) {
    bool open = true;
    string src, target;
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
                //graph->print_..;
                break;
            case 2:
                //graph->print_..;
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
    Graph graph=Graph(path1,path2);
    graph.print_edmundsKarp("Santarém", "Lisboa Oriente");
    //graph.print_all_station_pairs();

    bool on = true;
    while (on) {
        int input;
        cout << "1 -> Basic Service Metrics\n"
                "2 -> Operation Cost Optimization\n"
                "3 -> Reliability and Sensitivity to Line Failures\n"
                "0 - Quit\n";
        while(!(cin >> input)) {
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            cout << "Invalid input!\n";
            cout << "1 -> Basic Service Metrics\n"
                    "2 -> Operation Cost Optimization\n"
                    "3 -> Reliability and Sensitivity to Line Failures\n"
                    "0 - Quit\n";
        }
        switch (input) {
            case 0:
                on=false;
                break;
            case 1:
                MetricMenu(&graph);
                break;
            case 2:
                OptimizationMenu(&graph);
                break;
            case 3:
                FailuresMenu(&graph);
                break;
            default:
                cout << "Invalid input!\n";
                break;
        }
    }
    return 0;
}
