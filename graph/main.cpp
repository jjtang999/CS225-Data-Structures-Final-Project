#include <iostream>

#include "include/core/graph.h"
#include "../parsing/DataParser.h"

using twitchsocial::core::TwitchSocialGraph;

int main()
{
    // Write your own main here
    TwitchSocialGraph graph;
    DataParser parser;
    vector<pair<int, int> > edges;
    vector< pair < pair < int, int> , pair < double, double > > > nodes;
    edges = parser.edge_data("parsing/data/engb_edges.txt");
    nodes = parser.user_data("parsing/data/engb_user.txt");

    graph = TwitchSocialGraph(edges, nodes);
    vector<int> path = graph.findShortestPath(64700169, 190364784);
    // for (int i : path) {
    //     std::cout << i << ", ";
    // }
    // std::cout << std::endl;
    
    return 0;
}
