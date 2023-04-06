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
#include <unordered_set>
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
     * @param src network's source station.
     * @param dest network's sink station.
     * @param w Weight of the network.
     * @param service Type of service provided by the network (Standard or Alpha).
     * @note Time Complexity O(1).
     */
    void addBidirectionalNetwork(string src, string dest, int w, string service);

    /**
     * Checks if a station exists (in the set of stations - #StationSet) given it's name.
     * @param name
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
     * @param source
     * @param target
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
     * @param source
     * @param target
     * @return \p target station's bottleneck if the BFS reached it and 0 otherwise.
     * @note Time Complexity O(V+E) (vertixes + edges) <- number of vertexes + edges + (incomings=number of edges)
     */
    int bfs(string source, string target);
    /**
     * Auxiliary method to edmondsKarp_noflowreset_eachline(). <br>
     * Does a breath first search through the railway network #StationSet starting on \p source station and stopping once \p target station is reached, taking in consideration only stations from the given \p line.
     * @see testandvisit()
     * @param source
     * @param target
     * @param line
     * @return \p target station's bottleneck if the BFS reached it and 0 otherwise.
     * @note Time Complexity O(V+E).
     */
    int bfs(string source, string target, string line);
    /**
     * Auxiliary method to edmondsKarp_noflowreset(). <br>
     * Does a breath first search through the railway network #StationSet starting on \p source station, taking in consideration only stations from the given \p line.
     * @see testandvisit()
     * @param source
     * @param target Is setted with the name of the last station visited by the BFS.
     * @param line
     * @return \p target station's bottleneck if said station is not the \p source station and 0 otherwise.
     * @note Time Complexity O(V+E).
     */
    int bfs(string source, string *target, string line);
    /**
     * Auxiliary method to edmondsKarp(), edmondsKarp_noflowreset_eachline(), edmondsKarp_noflowreset(). <br>
     * Starting on the \p target station, passes flow through the network backwards path, which is made up of each station's #Station::path, keeping in mind the given \p bottleneck. <br>
     * This method does not assume the responsibility of previously setting the path, as it takes for granted it is already set.
     * @param target
     * @param bottleneck
     * @note Time Complexity O(P) being p the number of edges of a certain augmenting path.
     */
    void augmentFlowAlongPath(string target, int bottleneck, vector<queue<string>> *path);
     /**
     * Auxiliary method to bfs(string source, string target), bfs(string source, string target, string line) and bfs(string source, string *target, string line). <br>
     * Sets the visited, path and bottleneck of \p target and pushes it to the given \p queue, only if it hasn't been visited and the \p flow is bigger than zero.
     * @param queue Queue used by the caller method.
     * @param network
     * @param source Source of \p network.
     * @param target Sink of \p network.
     * @param flow
     * @return True if \p target is not set as visited and \p flow is bigger than zero, false otherwise.
     * @note Time Complexity O(1).
     */
    bool test_and_visit(queue<string> &queue, Network * network, Station *source, Station *target, int flow);

    /**
     * Auxiliary method to is_negative_cycle()
     * Sets the path and dist of \p target if the given \p flow is higher than zero and the \p target's dist is bigger than the given \p dist.
     * @param network
     * @param target Sink of \p network.
     * @param flow
     * @param dist
     * @return True if the given \p flow is bigger than zero and the \p target's dist is bigger than the given \p dist, false otherwise.
     * @note Time Complexity O(TODO).
     */
    bool test_and_visit(Network *network, Station *target, int flow, int dist);
    /**
     * Uses bfs(string source, string target) to calculate shortest augmenting paths, in order to calculate maximum flow by augmenting those paths.
     * @param source
     * @param target
     * @param path
     * @return Maximum flow of the graph considering \p source and \p target
     * @note Time Complexity O(V*E²)
     */
    int edmondsKarp(string source, string target, vector<queue<string>> *path);
    /**
    * Uses bfs to calculate shortest augmenting paths, in order to calculate maximum flow by augmenting those paths. Something to add about no flow reset!!!!
    * @param source
    * @param target
    * @param path
    * @note Time Complexity O(V*E²)
    */
    void edmondsKarp_noflowreset(string source, string line);
    /**
    * Uses bfs to calculate shortest augmenting paths, in order to calculate maximum flow by augmenting those paths. Something to add about noflowreset eachline !!!!
    * @param source
    * @param target
    * @param path
    * @return
    * @note Time Complexity O(V*E²)
    */
    int edmondsKarp_noflowreset_eachline(string source, string target, string line);
    /**
     * Checks if the given network can be removed. <br>
     * A network can be removed if it's source and sink make for an existing network.
     * @param source network's source station.
     * @param target network's sink station.
     * @return True if it can be removed and false otherwise.
     * @note Time Complexity O(1).
     */
    bool valid_remove(string source, string target);
    /**
     * Calculates the maximum flow between each pair of Stations, stating by calculating the max flow between the two most likely to have the max flow and then iterating through each pair of stations and  only calculating the max flow on those who have a posibility to be better than the current best pair
     * @see
     * @return
     */
    vector<pair<string, string>> stationPairs();
    /**
     * TODO
     * @see edmondsKarp_noflowreset()
     * @param pq
     */
    void topk_budget_municipios(priority_queue<pair<int, string>> &pq);
    /**
     * TODO
     * @see
     * @param pq
     */
    void topk_budget_districts(priority_queue<pair<int, string>> &pq);
    /**
     * TODO
     * only runs if it is evident that there will be a path
     * @see edmondsKarp_noflowreset_eachline()
     * @param target
     * @return
     */
    int max_flow_foreachline(string target);
    /**
     * Calculates the max flow of the path with min cost between a \p source and \p target station
     * @see search(), edmondsKarp().
     * @param source
     * @param target
     * @param path
     */
    void max_flow_min_cost(string source, string target, vector<queue<string>> *path);
    /**
     * Auxiliary method to max_flow_min_cost().
     * Checks if the backwards path from station \p target, which is made up of each station's #Station::path, is a negative cycle.
     * @see find_better_path(), test_and_visit(Network *network, Station *target, int flow, int dist).
     * @param target
     * @return True if current path is a negative cycle and false otherwise.
     * @note Time Complexity O().
     */
    bool is_negative_cycle(string target);
    /**
     * Auxiliary method to is_negative_cycle().
     * TODO
     * @param station
     * @return Cost of the newly created path.
     * @note Time Complexity O().
     */
    int find_better_path(Station *station);
    /**
     * TODO (method in progress)
     * Given a group of networks in maintenance, calculates the stations most afected by the absence of those networks.
     * @param pq Priority queue of networks in maintenance.
     * @param path
     * @note Time Complexity O().
     */
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
     * @param source network's source station.
     * @param target network's sink station.
     * @note Time Complexity O(1).
     */
    void remove_network(string source, string target);

    Stations StationSet; /**< Unordered map of all station names(key) and respective instance of class Station (value), see also #Stations. <br> Represents the railway network.*/

    stack<Network> store; /**< Stacks all networks that where set as in maintenace in valid_remove(). Relevant to topk_reduced_connectivity()*/
private:
    string station_file; /**< Name of file with information on stations, this attribute is obtained through user input. */
    string network_file; /**< Name of file with information on networks, this attribute is obtained through user input. */


};
#endif//UNTITLED4_GRAPH_H