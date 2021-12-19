#pragma once

#include <vector>
#include <queue>
#include <map>

using std::vector;
using std::queue;
using std::pair;
using std::map;

namespace twitchsocial {

namespace core {
    
class TwitchSocialGraph {
  private: // Node and Edge structs for graph
    /** Node struct used for graph **/
    struct Node {
      /** Constructor **/
      Node(int twitch_id, const pair<double, double>& coords) : twitch_id_(twitch_id), coords_(coords) { }

      int twitch_id_;
      pair<double, double> coords_;
      vector<int> edges_;
    };

    /** Edge struct used for graph **/
    struct Edge {
      /** Constructor **/
      Edge(int to, int from, double distance) : to_(to), from_(from), distance_(distance) { }

      /** Returns the adj of the passed in Node **/
      int getAdj(int source) {
        return source == to_ ? from_ : to_;
      }

      int to_;
      int from_;
      double distance_;
    };

  private: // graph private member variables
    /** nodes of the graph **/
    vector<Node*> nodes_;
    /** edges for the graph **/
    vector<Edge*> edges_;
    
    map<int, int> twitch_to_new_id_;

    double _getDistance(const pair<double, double>& to_coord, const pair<double, double>& from_coord_2) const;

  public: // graph
    /**
     * Empty Constructor
    **/
    TwitchSocialGraph();

    /**
     * Constructor for parser
     * @param edge_data_ a vector of edges storing (to, from)
     * @param node_data_ a vector of nodes storing (id conversion (new, twitch), coordniates(long, lat))
    **/
    TwitchSocialGraph(const vector<pair<int, int > >& edge_data, const vector< pair< pair<int, int>, pair<double, double> > >& node_data);

    /**
     * Destructor
    **/
    ~TwitchSocialGraph();

    const vector<Node*>& getNodes() const;

    const vector<Edge*>& getEdges() const;

    bool areAdjacent(int one, int two) const;

    vector<int> findShortestPath(int source_twitch_id, int destination_twitch_id) const;

    vector<int> BFS(int s) const;

    //Returns twitch_id
    int betweennessCentrality() const;
};

} // namespace core

} // namespace twitchsocial
