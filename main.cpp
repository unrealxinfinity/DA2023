#include <iostream>
#include "Header/graph.h"
int main() {
    std::string path1="../DataSet/stations.csv";
    std::string path2="../DataSet/network.csv";

    Graph g=Graph(path1,path2);
    auto it=g.StationSet.begin();
    cout<<it->getAdj().size()<<endl;
    return 0;
}
