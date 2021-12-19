#include "../../catch/catch.hpp"
#include "../include/core/graph.h"

//using Parser::Node;
using namespace std;
using twitchsocial::core::TwitchSocialGraph;

vector<pair<int, int > > edge_data = { {0,1}, {0,2} };
vector< pair< pair<int, int>, pair<double, double> > > node_data = { {{0, 0}, {3,3}}, {{1, 10}, {2,2}}, {{2, 20}, {0,0}} };
TwitchSocialGraph small_graph(edge_data, node_data);

vector<pair<int, int > > edge_data_weighted = { {4,0}, {5, 0}, {2, 3}, {3, 4}, {4, 1}, {2, 5}};
vector< pair< pair<int, int>, pair<double, double> > > node_data_weighted = { {{0, 0}, {0,0}}, {{1, 10}, {2,1}}, {{2, 20}, {2,4}},
                                                                            {{3, 30}, {4,0}}, {{4, 40}, {6,10}}, {{5, 50}, {6,0}} };
TwitchSocialGraph weighted_graph(edge_data_weighted, node_data_weighted);

TEST_CASE("Test Small Graph Constructor") {
    vector<pair<int, int > > edge_data = { {0,1}, {0,2} };
    vector< pair< pair<int, int>, pair<double, double> > > node_data = { {{0, 0}, {3,3}}, {{1, 10}, {2,2}}, {{2, 20}, {0,0}} };
    TwitchSocialGraph graph(edge_data, node_data);
    SECTION("Test vector of nodes is the correct", "[graph]") {
        REQUIRE(graph.getNodes().size() == 3);
        for (unsigned i = 0; i < graph.getNodes().size(); ++i) {
            REQUIRE(graph.getNodes()[node_data[i].first.first]->twitch_id_ == node_data[i].first.second);
            REQUIRE(graph.getNodes()[node_data[i].first.first]->coords_ == node_data[i].second);
        }

        REQUIRE(graph.getNodes()[0]->edges_.size() == 2);
        REQUIRE(graph.getNodes()[1]->edges_.size() == 1);
        REQUIRE(graph.getNodes()[2]->edges_.size() == 1);

        REQUIRE(graph.getNodes()[0]->edges_[0] == 0);
        REQUIRE(graph.getNodes()[0]->edges_[1] == 1);
        REQUIRE(graph.getNodes()[1]->edges_[0] == 0);
        REQUIRE(graph.getNodes()[2]->edges_[0] == 1);
        
    }

    SECTION("Test vector of edges is the correct", "[graph]") {
        REQUIRE(graph.getEdges().size() == 2);
        REQUIRE(floor(graph.getEdges()[0]->distance_ + 0.5) == 98);
        REQUIRE(floor(graph.getEdges()[1]->distance_ + 0.5) == 293);
    }
}


TEST_CASE("Test areAdjacent small") {   

    SECTION("Test areAdjacent with adjacent nodes", "[graph]") {
        REQUIRE(small_graph.areAdjacent(0, 1) == true);
        REQUIRE(small_graph.areAdjacent(0, 2) == true);
    }
    
    SECTION("Test areAdjacent with non-adjacent nodes", "[graph]") {
        REQUIRE(small_graph.areAdjacent(2, 1) == false);
        REQUIRE(small_graph.areAdjacent(1, 2) == false);
    }
}

TEST_CASE("Test findShortestPath small") {   
    vector<pair<int, int > > edge_data = { {0,1}, {0,2} };
    vector< pair< pair<int, int>, pair<double, double> > > node_data = { {{0, 0}, {1,1}}, {{1, 10}, {2,2}}, {{2, 20}, {0,0}} };
    TwitchSocialGraph graph(edge_data, node_data);
    
    vector<int> path = { 0 };
    REQUIRE(graph.findShortestPath(0, 0) == path);
    path = { 1 };
    REQUIRE(graph.findShortestPath(10, 10) == path);
    path = { 2 };
    REQUIRE(graph.findShortestPath(20, 20) == path);

    SECTION("Test findShortestPath from adjacent edges", "[graph]") {
        vector<int> path1  = {0, 1};
        vector<int> path2  = {0, 2};
        vector<int> path3  = {1, 0};
        vector<int> path4  = {2, 0};
        REQUIRE(graph.findShortestPath(0, 10) == path1);
        REQUIRE(graph.findShortestPath(0, 20) == path2);
        REQUIRE(graph.findShortestPath(10, 0) == path3);
        REQUIRE(graph.findShortestPath(20, 0) == path4);
    }
    
    SECTION("Test findShortestPath from non-adjacent nodes", "[graph]") {
        vector<int> path1 = {2, 0, 1};
        vector<int> path2 = {1, 0, 2};
        REQUIRE(graph.findShortestPath(20, 10) == path1);
        REQUIRE(graph.findShortestPath(10, 20) == path2);
    }
}

TEST_CASE("Test findShortestPath weighted") {  

    // vector<pair<int, int > > edge_data_weighted = { {4,0}, {5, 0}, {2, 3}, {3, 4}, {4, 1}, {2, 5}};
    // vector< pair< pair<int, int>, pair<double, double> > > node_data_weighted = { {{0, 0}, {0,0}}, {{1, 10}, {2,1}}, {{2, 20}, {2,4}},
    //                                                                         {{3, 30}, {4,0}}, {{4, 40}, {6,10}}, {{5, 50}, {6,0}} };
    // //Dist: 6

    // //Dist: 11.66

    // //Dist: 4.2

    // //Dist: 2

    // //Dist: 4.12

    // //Dist: 7.211

    // TwitchSocialGraph graph(edge_data_weighted, node_data_weighted);
    // TwitchSocialGraph graph = weighted_graph;
    vector<int> actual;
    actual = {0};
    REQUIRE(weighted_graph.findShortestPath(0, 0) == actual);
 
    actual = {1};
    REQUIRE(weighted_graph.findShortestPath(10, 10) == actual);
 
    actual = {2};
    REQUIRE(weighted_graph.findShortestPath(20, 20) == actual);
 
    SECTION("Test adjacent nodes") {
        actual = {0, 4};
        REQUIRE(weighted_graph.findShortestPath(0, 40) == actual);
 
        actual = {4, 0};
        REQUIRE(weighted_graph.findShortestPath(40, 0) == actual);
 
        actual = {0, 5};
        REQUIRE(weighted_graph.findShortestPath(0, 50) == actual);
 
        actual = {5, 2};
        REQUIRE(weighted_graph.findShortestPath(50, 20) == actual);
    }
    SECTION("Test non-adjacent nodes") {
        actual = {0, 5, 2}; // true path = { 0, 4, 3, 2 }, but greedy, so actual = { 0, 5, 2 }
        REQUIRE(weighted_graph.findShortestPath(0, 20) == actual);
 
        actual = {5, 2, 3};
        REQUIRE(weighted_graph.findShortestPath(50, 30) == actual);
 
        actual = {1, 4, 3, 2};
        REQUIRE(weighted_graph.findShortestPath(10, 20) == actual);
 
        actual = {1, 4, 3};
        REQUIRE(weighted_graph.findShortestPath(10, 30) == actual);
 
        actual = {1, 4, 0, 5};
        REQUIRE(weighted_graph.findShortestPath(10, 50) == actual);
 
        actual = {1, 4, 0};
        REQUIRE(weighted_graph.findShortestPath(10, 0) == actual);
    }

    SECTION("Test shortest path with nodes without path") {
        vector<pair<int, int > > edge_data = { {0,1}, {3,2} };
        vector< pair< pair<int, int>, pair<double, double> > > node_data = { {{0, 0}, {3,3}}, {{1, 10}, {2,2}}, {{2, 20}, {0,0}}, {{3, 30}, {0,1}} };
        TwitchSocialGraph graph(edge_data, node_data);
        actual = {-1};
        REQUIRE(graph.findShortestPath(0, 30) == actual);
    }
}


TEST_CASE("Test Small Connected BFS") {
    // vector<pair<int, int > > edge_data = { {0,1}, {0,2} };
    // vector< pair< pair<int, int>, pair<double, double> > > node_data = { {{0, 0}, {3,3}}, {{1, 10}, {2,2}}, {{2, 20}, {0,0}} };
    // TwitchSocialGraph graph(edge_data, node_data);

    vector<int> traversal;  vector<int> expected;

    traversal = small_graph.BFS(2);   expected = {2, 0 ,1};
    REQUIRE(traversal == expected);

    traversal = small_graph.BFS(1);   expected = {1, 0 ,2};
    REQUIRE(traversal == expected);

    traversal = small_graph.BFS(0);   expected = {0, 1, 2};
    REQUIRE(traversal == expected);
}

TEST_CASE("Test Large Connected BFS") {
    vector<pair<int, int > > edge_data = { 
        {0,1}, {0,2}, {3,9}, {3,7}, {3,4}, {3,6}, {3,5}, 
        {7,4}, {7,6}, {7,5}, {6,8}, {8,0}
        };
    vector< pair< pair<int, int>, pair<double, double> > > node_data = {
        {{0, 0}, {3,3}}, {{1, 10}, {2,2}}, {{2, 20}, {0,0}},
        {{3, 1}, {7,3}}, {{4, 4}, {2,1}}, {{5, 5}, {3,9}}, {{6, 6}, {3,90}}, {{7, 7}, {30,9}}, {{8, 8}, {9,4}},
        {{9, 9}, {12,34}} 
    };

    TwitchSocialGraph graph(edge_data, node_data);
    vector<int> traversal;  vector<int> expected;

    SECTION("Check Edge Nodes") {
        traversal = graph.BFS(9);   expected = {9, 3, 7, 4, 6, 5, 8, 0, 1, 2};
        REQUIRE(traversal == expected);
    
        traversal = graph.BFS(2);   expected = {2, 0, 1, 8, 6, 3, 7, 9, 4, 5};
        REQUIRE(traversal == expected);
    }

    SECTION("Check Middle Nodes") {
        traversal = graph.BFS(3);   expected = {3, 9, 7, 4, 6, 5, 8, 0, 1, 2};
        REQUIRE(traversal == expected);

        traversal = graph.BFS(6);   expected = {6, 3, 7, 8, 9, 4, 5, 0, 1, 2};
        REQUIRE(traversal == expected);

        traversal = graph.BFS(8);   expected = {8, 6, 0, 3, 7, 1, 2, 9, 4, 5};
        REQUIRE(traversal == expected);
    }
}

TEST_CASE("Test Disconnected BFS") {
    vector<pair<int, int > > edge_data = { 
        {0,1}, {0,2}, // subgraph 1
        {3,7}, {3,4}, {3,6}, {3,5}, {7,4}, {7,6}, {7,5}, {6,8} // subgraph 2
        // no edges for subgraph 3
        };
    vector< pair< pair<int, int>, pair<double, double> > > node_data = {
        {{0, 0}, {3,3}}, {{1, 10}, {2,2}}, {{2, 20}, {0,0}}, // subgraph 1
        {{3, 1}, {7,3}}, {{4, 4}, {2,1}}, {{5, 5}, {3,9}}, {{6, 6}, {3,90}}, {{7, 7}, {30,9}}, {{8, 8}, {9,4}},   // subgraph 2
        {{9, 9}, {12,34}}    // subgraph 3
    };

    TwitchSocialGraph graph(edge_data, node_data);
    vector<int> traversal;  vector<int> expected;

    SECTION("Check subgraph 1") {
        traversal = graph.BFS(2);   expected = {2, 0 ,1};
        REQUIRE(traversal == expected);

        traversal = graph.BFS(1);   expected = {1, 0 ,2};
        REQUIRE(traversal == expected);

        traversal = graph.BFS(0);   expected = {0, 1, 2};
        REQUIRE(traversal == expected);
    }

    SECTION("Check subgraph 2") {
        traversal = graph.BFS(3);   expected = {3, 7, 4, 6, 5, 8};
        REQUIRE(traversal == expected);

        traversal = graph.BFS(4);   expected = {4, 3, 7, 6, 5, 8};
        REQUIRE(traversal == expected);

        traversal = graph.BFS(5);   expected = {5, 3, 7, 4, 6, 8};
        REQUIRE(traversal == expected);

        traversal = graph.BFS(6);   expected = {6, 3, 7, 8, 4, 5};
        REQUIRE(traversal == expected);

        traversal = graph.BFS(7);   expected = {7, 3, 4, 6, 5, 8};
        REQUIRE(traversal == expected);

        traversal = graph.BFS(8);   expected = {8, 6, 3, 7, 4, 5};
        REQUIRE(traversal == expected);
    }

    SECTION("Check subgraph 3") {
        traversal = graph.BFS(9);   expected = {9};
        REQUIRE(traversal == expected);
    }
}

TEST_CASE("Test Betweenness Centrality") {
    SECTION("Test betweenness on small graph") {
        int central = small_graph.betweennessCentrality();
        REQUIRE(central == 0);
    }
    SECTION("Test betweenness on weighted graph") {
        int central = weighted_graph.betweennessCentrality();
        REQUIRE(central == 40);
    }
    SECTION("Test betweenness on graph with two nodes of same centrality.") {
        vector<pair<int, int > > edge_data = { {2,1}, {0,2}, {1,3} };
        vector< pair< pair<int, int>, pair<double, double> > > node_data = { {{0, 0}, {3,3}}, {{1, 10}, {2,2}}, {{2, 20}, {0,0}}, {{3, 30}, {1, 1}} };
        TwitchSocialGraph graph(edge_data, node_data);
        REQUIRE(graph.betweennessCentrality() == 10);
    }
    SECTION("Test betweeness on disconnected graph with no central node") {
        vector<pair<int, int > > edge_data = { {0,1}};
        vector< pair< pair<int, int>, pair<double, double> > > node_data = { {{0, 0}, {3,3}}, {{1, 10}, {2,2}}, {{2, 20}, {0,0}}, {{3, 30}, {1, 1}} };
        TwitchSocialGraph graph(edge_data, node_data);
        vector<int> path = {-1};
        REQUIRE(graph.findShortestPath(20, 30) == path);
        REQUIRE(graph.betweennessCentrality() == -1);
    }
    SECTION("Test betweeness on disconnected graph with with central node") {
        vector<pair<int, int > > edge_data = { {0,1}, {1,2}, {3, 4}};
        vector< pair< pair<int, int>, pair<double, double> > > node_data = { {{0, 0}, {3,3}}, {{1, 10}, {2,2}}, {{2, 20}, {0,0}}, {{3, 30}, {1, 1}}, {{4, 40}, {1, 1}}};
        TwitchSocialGraph graph(edge_data, node_data);
        vector<int> path = {-1};
        REQUIRE(graph.findShortestPath(10, 30) == path);
        REQUIRE(graph.betweennessCentrality() == 10);
    }


}
