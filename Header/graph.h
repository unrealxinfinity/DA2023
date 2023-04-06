//
// Created by migue on 10/03/2023.
//

#ifndef UNTITLED4_GRAPH_H
#define UNTITLED4_GRAPH_H

#include <list>
#include <vector>
#include <queue>
#include <iostream>
#include <unordered_map>
#include <stack>
#include <cmath>
#include <fstream>
#include <sstream>
#include <string>
#include "Station.h"
#include <climits>


using namespace std;

typedef unordered_map<string,Station> Stations;
class Graph {
public:
    Graph(const string station_file,const string network_file);
    Graph();
    ~Graph();
    bool addStation(string name);
    bool addNetwork(string src, string dest, int capacity, string service);
    /**
     * Assigns a new network to both the source and sink stations of the aforementioned network.
     * @param string src Network's source station.
     * @param string dest Network's sink station.
     * @param int w Weight of the network.
     * @param string service Type of service provided by the network (Standard or Alpha).
     * @note Time Complexity O(1).
     */
    void addBidirectionalNetwork(string src, string dest, int w,string service);

    /**
     * Checks if a station exists (in the set of stations - #StationSet) given it's name.
     * @param string name
     * @return Parameter \p name if station was found and string 'error' otherwise.
     * @note Time Complexity O(1).
     */
    string find_code(string name);
    /**
     * Extracts all relevant information from file #station_file which is saved to #StationSet.
     * @note Time Complexity O(V).
     */
    void insertStations();
    /**
    * Extracts all relevant information from file #network_file which is saved to the stations of #StationSet.
    * @note Time Complexity O(E).
    */
    void insertNetworks();

    //printers
    /**
     * Prints the maximum flow that a source can pump into a target node
     * @param string source
     * @param string target
     * @note Time complexity O(V*E²)
     */
    void print_edmondsKarp(string source, string target);
    //complexity
    void print_all_station_pairs();

    void print_reduced_connectivity(string source, string target);

    void print_topk_reduced_connectivity(int k);

    void print_topk_budget_municipios(int k);

    void print_topk_budget_districts(int k);

    void print_max_flow_foreachline(string target);

    void print_max_flow_min_cost(string source, string target);
    /**
     * Auxiliary method to edmondsKarp(). <br>
     * Does a breath first search through the railway network #StationSet starting on \p source station.
     * @see testandvisit()
     * @param string source
     * @param string target
     * @return \p target station's bottleneck if the BFS reached it and 0 otherwise.
     * @note Time Complexity O(V+E) (vertixes + edges) <- number of vertexes + edges + (incomings=number of edges)
     */
    int bfs(string source, string target);
    /**
     * Auxiliary method to edmondsKarp_noflowreset_eachline(). <br>
     * Does a breath first search through the railway network #StationSet starting on \p source station and stopping once \p target station is reached, taking in consideration only stations from the given \p line.
     * @see testandvisit()
     * @param string source
     * @param string target
     * @param string line
     * @return \p target station's bottleneck if the BFS reached it and 0 otherwise.
     * @note Time Complexity O(V+E).
     */
    int bfs(string source, string target, string line);
    /**
     * Auxiliary method to edmondsKarp_noflowreset(). <br>
     * Does a breath first search through the railway network #StationSet starting on \p source station, taking in consideration only stations from the given \p line.
     * @see testandvisit()
     * @param string source
     * @param string target is setted with the name of the last station visited by the BFS.
     * @param string line
     * @return \p target station's bottleneck if said station is not the \p source station and 0 otherwise.
     * @note Time Complexity O(V+E).
     */
    int bfs(string source, string *target, string line);
    /**
     * Auxiliary method to edmondsKarp(), edmondsKarp_noflowreset_eachline(), edmondsKarp_noflowreset(). <br>
     * Starting on the \p target station, passes flow through the network backwards path, which is made up of each station's #Station::path, keeping in mind the given \p bottleneck. <br>
     * This method does not assume the responsibility of previously setting the path, as it takes for granted it is already set.
     * TODO (permision to remove argument source)
     * @param string source
     * @param string target
     * @param int bottleneck
     * @param vector of queues of station names-> path
     * @note Time Complexity O(P) being p the number of edges of a certain augmenting path.
     */
    void augmentFlowAlongPath(string source, string target, int bottleneck, vector<queue<string>> *path);
     /**
     * Auxiliary method to bfs(string source, string target), bfs(string source, string target, string line) and bfs(string source, string *target, string line). <br>
     * Sets node as visited, path and bottleneck of \p target and pushes it to the given \p queue, only if it hasn't been visited and the \p flow is higher than zero.
     * @param queue Queue used by the caller method.
     * @param Network network
     * @param Station* source of \p network.
     * @param Station* sink of \p network.
     * @param int flow
     * @return True if \p target is not set as visited and \p flow is higher than zero, false otherwise.
     * @note Time Complexity O(1).
     */
    bool testandvisit(queue<string> &queue, Network * network, Station *source, Station *target, int flow);
    bool test_and_visit_search(Network *network, Station *source, Station *target, int flow, int dist);
    /**
     * Algorithm that uses bfs to calculate shortest augmenting paths, in order to calculate maximum flow by augmenting those paths.
     * @param string source
     * @param string target
     * @param  path
     * @return maximum flow of the graph considering source and target
     * @note Time Complexity O(V*E²)
     */
    int edmondsKarp(string source, string target, vector<queue<string>> *path);
    /**
    * Algorithm that uses bfs to calculate shortest augmenting paths, in order to calculate maximum flow by augmenting those paths. Something to add about no flow reset!!!!
    * @param string source
    * @param string target
    * @param  path
    * @note Time Complexity O(V*E²)
    */
    void edmondsKarp_noflowreset(string source, string line);

    /**
    * Algorithm that uses bfs to calculate shortest augmenting paths, in order to calculate maximum flow by augmenting those paths. Something to add about noflowreset eachline !!!!
    * @param string source
    * @param string target
    * @param  path
    * @return
    * @note Time Complexity O(V*E^2)
    */
    int edmondsKarp_noflowreset_eachline(string source, string target, string line);
    /**
     * Checks if the given network can be removed. <br>
     * A network can be removed if it's source and sink make for an existing network.
     * @param source Network's source station.
     * @param target Network's sink station.
     * @return true if it can be removed and false otherwise.
     * @note Time Complexity O(1).
     */
    bool valid_remove(string source, string target);
    vector<pair<string, string>> stationPairs();

    void topk_budget_municipios(priority_queue<pair<int, string>> &pq);
    void topk_budget_districts(priority_queue<pair<int, string>> &pq);
    int max_flow_foreachline(string target);
    void max_flow_min_cost(string source, string target, vector<queue<string>> *path);
    bool search(string source, string target);
    int find_better_path(Station *station);
    void topk_reduced_connectivity(priority_queue <pair<int, pair<string, string>>> &pq, vector<queue<string>>* path);
    /**
     * Auxiliary method to topk_reduced_connectivity(). <br>
     * Restores the railway network to it's original state, before networks were removed due to maintenance. <br>
     * @note Time Complexity O(N) being n the number of networks/edges to restore.
     */
    void restore_maintenance();
    /**
     * Auxiliary method to topk_reduced_connectivity(). <br>
     * Removes a specifyed network from the railway network #StationSet.
     * @param source Network's source station.
     * @param target Network's sink station.
     * @note Time Complexity O(1).
     */
    void remove_network(string source, string target);

    Stations StationSet; /**< Unordered map of all station names(key) and respective instance of class Station (value), see also #Stations. <br> Represents the railway network.*/

    stack<Network> store; /**< Something to add!!!!*/
private:
    string station_file; /**< Name of file with information on stations, this attribute is obtained through user input. */
    string network_file; /**< Name of file with information on networks, this attribute is obtained through user input. */


};
#endif//UNTITLED4_GRAPH_H