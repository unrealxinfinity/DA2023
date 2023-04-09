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
/************************* Graph  **************************/
class Graph {
public:
    Graph();
    Graph(const string station_file,const string network_file);
    ~Graph();
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
     * Checks if a station exists (in the set of stations - #StationSet) given it's \p name.
     * @param name
     * @return Parameter \p name if station was found, string 'error' otherwise.
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
    /**
     * Outputs the network path from a station \p source to a station \p target, together with the flow and cost at the end of said path.
     * @param orig Keeps the first source station, used for recursion related reasons.
     * @param source
     * @param target
     * @param bottleneck
     * @note Time complexity O(V*E²).
     */
    void print_path(string orig, string source, string target, int bottleneck);
    /**
     * Outputs the network path from all start of line stations to \p target, together with the flow and cost at the end of said path.
     * @param target
     * @note Time complexity O(V*E³).
     */
    void print_all_super_source_paths(string target);
    /**
     * Outputs the maximum flow between a \p source and \p target station.
     * @see edmondsKarp()
     * @param source
     * @param target
     * @note Time Complexity O(V²*E + V*E²).
     */
    void print_edmondsKarp(string source, string target);
    /**
     * Outputs the pairs of stations with the highest flow amongst all pairs of stations.
     * @see stationPairs()
     * @param final Vector of pairs with the maximum flow (there can be multiple pairs).
     * @note Time Complexity O(V⁴*E + V³*E²).
     */
    void print_all_station_pairs(vector<pair<string, string>> *final);
    /**
     * Outputs the current maximum flow from station \p source to \p target given that the railway network suffered a decrease in connectivity (networks in maintenance).
     * @param source
     * @param target
     * @note Time Complexity O(V²*E + V*E²).
     */
    void print_reduced_connectivity(string source, string target);
    /**
     * Outputs the top \p k stations most affected by a decrease in the railway network connectivity (networks in maintenance).
     * @see topk_reduced_connectivity()
     * @param k
     * @note Time Complexity O(V⁴*E + V³*E²).
     */
    void print_topk_reduced_connectivity(int k);
    /**
     * Outputs the top \p k municipalities with higher cost, in descending order.
     * @see topk_budget_municipios()
     * @param k
     * @note Time Complexity O(V³*E + V²*E²).
     */
    void print_topk_budget_municipios(int k);
    /**
     * Outputs the top \p k districts with higher cost, in descending order.
     * @see topk_budget_districts()
     * @param k
     * @note Time Complexity O(V³*E + V²*E²).
     */
    void print_topk_budget_districts(int k);
    /**
     * Outputs the maximum flow arriving at a given station \p target.
     * @see max_flow_foreachline()
     * @param target
     * @note Time Complexity O(V³*E + V²*E²).
     */
    void print_max_flow_foreachline(string target);
    /**
     * Outputs the cost and maximum flow of the path with minimum cost between a \p source and \p target station.
     * @see max_flow_min_cost()
     * @param source
     * @param target
     * @note Time Complexity O(V²*E²).
     */
    void print_max_flow_min_cost(string source, string target);
    /**
     * Outputs the top \p k stations most affected by a network maintenance, in the context of traveling between a \p source and \p target station.
     * @see topk_reduced_connectivityALTERNITIVE()
     * @param source
     * @param target
     * @param k
     * @note Time Complexity O(V²*E + V*E²).
     */
    void print_topk_reduced_connectivityALTERNATIVE(string source, string target, int k);
    /**
     * Auxiliary method to edmondsKarp(). <br>
     * Does a breath first search through the railway network #StationSet starting on \p source station.
     * @see test_and_visit(queue<string> &queue, Network * network, Station *source, Station *target, int flow)
     * @param source
     * @param target
     * @return \p target station's bottleneck if the BFS reached it and 0 otherwise.
     * @note Time Complexity O(V+E)
     */
    int bfs(string source, string target);
    /**
     * Auxiliary method to edmondsKarp_noflowreset_eachline(). <br>
     * Does a breath first search through the railway network #StationSet starting on \p source station and stopping once \p target station is reached, taking in consideration only stations from the given \p line.
     * @see test_and_visit(queue<string> &queue, Network * network, Station *source, Station *target, int flow)
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
     * @see test_and_visit(queue<string> &queue, Network * network, Station *source, Station *target, int flow)
     * @param source
     * @param target Is set with the name of the last station visited by the BFS. Relevant to caller method.
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
     * @note Time Complexity O(E).
     */
    void augmentFlowAlongPath(string target, int bottleneck);
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
     * Auxiliary method to is_negative_cycle(). <br>
     * Sets the path and dist of \p target if the given \p flow is higher than zero and the \p target's dist is bigger than the given \p dist.
     * @param network
     * @param target Sink of \p network.
     * @param flow
     * @param dist
     * @return True if the given \p flow is bigger than zero and the \p target's dist is bigger than the given \p dist, false otherwise.
     * @note Time Complexity O(1).
     */
    bool test_and_visit(Network *network, Station *target, int flow, int dist);
    /**
     * Uses BFS to calculate shortest augmenting paths between a \p source and \p target station, in order to calculate the maximum flow by augmenting those paths.
     * @see bfs(string source, string target) <br> augmentFlowAlongPath()
     * @param source
     * @param target
     * @return Maximum flow reaching \p target station from \p source station.
     * @note Time Complexity O(V²*E + V*E²)
     */
    int edmondsKarp(string source, string target);
    /**
    * Uses BFS to calculate shortest augmenting paths starting on station \p source and taking in consideration only stations from the given \p line, in order to then augment those paths.
    * @see bfs(string source, string *target, string line) <br> augmentFlowAlongPath()
    * @param source
    * @param line
    * @note Time Complexity O(V²*E + V*E²)
    */
    void edmondsKarp_noflowreset(string source, string line);
    /**
    * Uses BFS to calculate shortest augmenting paths between a \p source and \p target station, taking in consideration only stations from the given \p line, in order to calculate the maximum flow by augmenting those paths.
    * @see bfs(string source, string target, string line) <br> augmentFlowAlongPath()
    * @param source
    * @param target
    * @param line
    * @return Maximum flow reaching \p target station from \p source station, taking in consideration only stations from the given \p line.
    * @note Time Complexity O(V²*E + V*E²)
    */
    int edmondsKarp_noflowreset_eachline(string source, string target, string line);
    /**
     * Checks if the given network can be removed. <br>
     * A network can be removed if it's source and sink make for an existing network.
     * @param source network's source station.
     * @param target network's sink station.
     * @return True if it can be removed, false otherwise.
     * @note Time Complexity O(1).
     */
    bool valid_remove(string source, string target);
    /**
     * Checks if the given path from \p source to \p target is reachable. <br>
     * A path is reachable if it is possible to start at the source and navigate through each network with flow until you reach the target.
     * @param source
     * @param target
     * @return True if path can be made from \p source to \p target, false otherwise.
     * @note Time Complexity O(V+E).
     */
    bool is_valid_path(string source, string target);
    /**
     * Checks if the given \p station is the start of a line. <br>
     * A station is the start of a line when it only has one Network originating from it that arrives at a station of the same line.
     * @param source
     * @return True if is the start of a line, false if not.
     * @note Time Complexity O(E).
     */
    bool is_valid_source(string source);
    /**
     * Obtains the maximum flow between all pairs of stations while reducing the number of iteration by tracking the likeliness of a pair to have the maximum flow.
     * @see edmondsKarp()
     * @param final Vector setted with the pairs with the maximum flow (there can be multiple pairs). Relevant to caller method.
     * @return The maximum flow obtained.
     * @note Time Complexity O(V⁴*E + V³*E²).
     */
    int stationPairs(vector<pair<string, string>> *final);
    /**
     * Calculates the overall cost of all networks coming into and within each municipality.
     * @see edmondsKarp_noflowreset()
     * @param pq Priority queue setted with all municipalities and respective costs, with preference to higher costs. Relevant to caller method.
     * @note Time Complexity O(V³*E + V²*E²).
     */
    void topk_budget_municipios(priority_queue<pair<int, string>> &pq);
    /**
     * Calculates the overall cost of all networks coming into and within each district.
     * @see edmondsKarp_noflowreset()
     * @param pq Priority queue setted with all districts and respective costs, with preference to higher costs. Relevant to caller method.
     * @note Time Complexity O(V³*E + V²*E²).
     */
    void topk_budget_districts(priority_queue<pair<int, string>> &pq);
    /**
     * Obtains the maximum flow between all stations and \p target station, while reducing the number of iteration by tracking the likeliness of a selected pair to have the maximum flow.
     * @see edmondsKarp_noflowreset_eachline()
     * @param target
     * @return The max flow calculated.
     * @note Time Complexity O(V³*E + V²*E²).
     */
    int max_flow_foreachline(string target);
    /**
     * Calculates the maximum flow of the path with minimum cost between a \p source and \p target station.
     * @see is_negative_cycle() <br> edmondsKarp()
     * @param source
     * @param target
     * @note Time Complexity O(V²*E²).
     */
    void max_flow_min_cost(string source, string target);
    /**
     * Auxiliary method to max_flow_min_cost(). <br>
     * Checks, going backwards, if the paths to station \p target, which are made up of each station's #Station::path, have a negative cycle.
     * @see find_better_path() <br> test_and_visit(Network *network, Station *target, int flow, int dist)
     * @param target
     * @return True if current paths have a negative cycle and false otherwise.
     * @note Time Complexity O(V*E).
     */
    bool is_negative_cycle(string target);
    /**
     * Auxiliary method to is_negative_cycle(). <br>
     * Given that the currently setted paths, ending in \p station, have a negative cycle, changes the flow of said cycle's edges based on the cycle's bottleneck, effectively eradicating the aforementioned cycle.
     * @param station
     * @return Currently updated best cost.
     * @note Time Complexity O(E).
     */
    int find_better_path(Station *station);
    /**
     * Given a group of networks in maintenance, calculates the stations most affected by the absence of those networks.
     * @param pq Priority queue of networks in maintenance.
     * @note Time Complexity O(V⁴*E + V³*E²).
     */
    void topk_reduced_connectivity(priority_queue <pair<int, pair<string, string>>> &pq);
    /**
     * Auxiliary method to topk_reduced_connectivity(). <br>
     * Restores the railway network to it's original state, before networks were removed due to maintenance. <br>
     * @note Time Complexity O(N) being n the number of networks/edges to restore.
     */
    void restore_maintenance();
    /**
     * Auxiliary method to topk_reduced_connectivity(). <br>
     * Removes a specified network from the railway network #StationSet.
     * @param source network's source station.
     * @param target network's sink station.
     * @note Time Complexity O(1).
     */
    void remove_network(string source, string target);
    /**
     * Given a network in maintenance, calculates the stations most affected by the absence of that network, in the context of traveling between a \p source and \p target station.
     * @param source
     * @param target
     * @param pq Priority queue of stations most affected. Relevant to caller method.
     * @param temp Holds the flow in each station, before the network goes in maintenance.
     * @note Time Complexity O(V²*E + V*E²).
     */
    void topk_reduced_connectivityALTERNITIVE(string source, string target, priority_queue <pair<int, string>> &pq, unordered_map<string, int> temp);

    Stations StationSet; /**< Unordered map of all station names(key) and respective instance of class Station (value), see also #Stations. <br> Represents the railway network.*/
    stack<Network> store; /**< Stacks all networks that where set as in maintenance in valid_remove(). <br> Relevant to topk_reduced_connectivity(). */

private:
    string station_file; /**< Name of file with information on stations, this attribute is obtained through user input. */
    string network_file; /**< Name of file with information on networks, this attribute is obtained through user input. */

};
#endif//UNTITLED4_GRAPH_H