#include "../../include/core/graph.h"

#include <vector>
#include <math.h>
#include <algorithm>
#include <numeric>
#include <iterator>
#include <set>

#include <iostream>

using std::vector;
using std::pair;
using std::set;
using std::min;

#define PI 3.14159265358979323846
#define RADIANS_DEGREES_RATIO PI / 180
#define EARTH_RADIUS 3963.19

namespace twitchsocial {

namespace core {

TwitchSocialGraph::TwitchSocialGraph() {
  
}

TwitchSocialGraph::TwitchSocialGraph(const vector<pair<int, int > >& edge_data, 
      const vector< pair< pair<int, int>, pair<double, double> > >& node_data) {

  // creates empty vector with size == input_data.size
  nodes_ = vector<Node*>(node_data.size(), NULL);

  /* Constructs nodes with no edges */
  for (const pair< pair<int, int>, pair<double, double> >& data : node_data) {
    const pair<int, int>& id_conversion = data.first;
    const pair<double, double>& coordinates = data.second;

    Node* node = new Node(id_conversion.second, coordinates);
    nodes_[id_conversion.first] = node;
    twitch_to_new_id_.insert({id_conversion.second, id_conversion.first});
  }

  /* Constructs edges */
  for (unsigned i = 0; i < edge_data.size(); ++i) {
    int to = edge_data[i].first; int from = edge_data[i].second;
    Node* to_node = nodes_[to];   Node* from_node = nodes_[from];

    Edge* edge = new Edge(to, from, _getDistance(to_node->coords_, from_node->coords_));
    edges_.push_back(edge);

    // updating edges in nodes
    to_node->edges_.push_back(i);
    from_node->edges_.push_back(i);
  }
}

TwitchSocialGraph::~TwitchSocialGraph() {
  for (Node* node : nodes_)
    delete node;

  for (Edge* edge : edges_)
    delete edge;
}

const vector<TwitchSocialGraph::Node*>& TwitchSocialGraph::getNodes() const {
  return nodes_;
}

const vector<TwitchSocialGraph::Edge*>& TwitchSocialGraph::getEdges() const {
  return edges_;
}

bool TwitchSocialGraph::areAdjacent(int one, int two) const {
  Node* first = nodes_[one];   Node* second = nodes_[two];
  vector<int>& edges = first->edges_ < second->edges_ ? first->edges_ : second->edges_;
  int source = first->edges_.size() < second->edges_.size() ? one : two;
  int dest = first->edges_.size() < second->edges_.size() ? two : one;

  for (int idx : edges) {
    Edge* edge = edges_[idx];
    if (edge->getAdj(source) == dest) {
      return true;
    }
  }

  return false;
}

double TwitchSocialGraph::_getDistance(const pair<double, double>& to_coord, const pair<double, double>& from_coord_2) const {
  double haversine, temp, distance;

  double to_long = to_coord.first * RADIANS_DEGREES_RATIO;
  double to_lati = to_coord.second  * RADIANS_DEGREES_RATIO;

  double from_long = from_coord_2.first * RADIANS_DEGREES_RATIO;
  double from_lati = from_coord_2.second  * RADIANS_DEGREES_RATIO;

  haversine = (pow(sin((1.0 / 2) * (from_lati - to_lati)), 2)) + ((cos(to_lati)) * (cos(from_lati)) * (pow(sin((1.0 / 2) * (from_long - to_long)), 2)));
  temp = 2 * asin(min(1.0, sqrt(haversine)));
  distance = EARTH_RADIUS * temp;

  return distance;
}

vector<int> TwitchSocialGraph::findShortestPath(int source_twitch_id, int destination_twitch_id) const {
  map<int, double> tentative_dists_;
  set<int> visited_set_;
  queue<int> priority_queue_;
  map<int, int> previous_;

  auto start_node_itr = twitch_to_new_id_.find(source_twitch_id);
  auto end_node_itr = twitch_to_new_id_.find(destination_twitch_id);

  if (start_node_itr == twitch_to_new_id_.end() || end_node_itr == twitch_to_new_id_.end()) {
    return {-1};
  }

  int start_node_id = start_node_itr->second; // new_id
  int end_node_id = end_node_itr->second;

  //No path in or out
  if (nodes_.at(start_node_id)->edges_.empty() || nodes_.at(end_node_id)->edges_.empty()) {
    return {-1};
  }

  tentative_dists_.insert({start_node_id, 0});

  previous_[start_node_id] = -1; // previous map set with new id
  vector<int> path; // return vector

  priority_queue_.push(start_node_id);

  while (priority_queue_.front() != end_node_id) {
    int curr_node_id = priority_queue_.front();
    if (priority_queue_.empty()) {
      return {-1};
    }
    Node* curr_node = nodes_.at(priority_queue_.front());
    visited_set_.insert(curr_node_id);
    priority_queue_.pop();
    auto curr_itr = tentative_dists_.find(curr_node_id);

    for (int edge_id : curr_node->edges_) {
      Edge* edge = edges_[edge_id];
      int neighbor = edge->getAdj(curr_node_id);
      if (visited_set_.find(neighbor) == visited_set_.end()) {
        double dist = edge->distance_;
        auto neigh_itr = tentative_dists_.find(neighbor);

        double potential_dist = curr_itr->second + dist;
        if (neigh_itr == tentative_dists_.end()) {
          tentative_dists_.insert({neighbor, potential_dist});
          if (previous_.find(neighbor) != previous_.end()) {
            previous_.find(neighbor)->second = curr_node_id;
          } else {
            previous_.insert({neighbor, curr_node_id});
          }
          
        } else if (potential_dist < neigh_itr->second) {
          neigh_itr->second = potential_dist;
          previous_.find(neighbor)->second = curr_node_id;
        }

        priority_queue_.push(neighbor);
      } else if (priority_queue_.empty() && (unsigned long)edge_id == curr_node->edges_.size() - 1) {
        return {-1};
      }
    }
  }

  auto end_itr = previous_.find(end_node_id);
  while (end_itr->first != start_node_id) {
    path.push_back(end_itr->first);
    end_itr = previous_.find(end_itr->second);
  }
  path.push_back(start_node_id);

  std::reverse(path.begin(), path.end());

  return path;
}

vector<int> TwitchSocialGraph::BFS(int s) const {
  vector<int> path;

  vector<bool> visited = vector<bool>(nodes_.size(), false);

  queue<int> queue;

  visited[s] = true;
  queue.push(s);

  while(!queue.empty()) {
      s = queue.front();
      path.push_back(s);
      queue.pop();

      for (int idx : nodes_[s]->edges_) {
          int adj = edges_[idx]->getAdj(s);
          if (!visited[adj]) {
              visited[adj] = true;
              queue.push(adj);
          }
      }
  }
  return path;
}

//Needs Testing
int TwitchSocialGraph::betweennessCentrality() const {
  Node* central = NULL;
  std::vector<double> betweenness_factor;
  betweenness_factor.resize(nodes_.size());
  int max_index = 0;
  //determine betweenness factor for each node
  for (unsigned i = 0; i < nodes_.size(); i++) {
    std::vector<double> betweenness;
    std::vector<int> shortest_path;
    //calculate shortest path of each node to each node (not including) through dijkstra's
    for (unsigned node_one = 0; node_one < nodes_.size(); node_one++) {
      for (unsigned node_two = node_one + 1; node_two < nodes_.size(); node_two++) {
        if ((node_one != i) && (node_two != i) && (node_one != node_two)) {
          shortest_path = findShortestPath(nodes_[node_one]->twitch_id_, nodes_[node_two]->twitch_id_);
          //check if node i is in path
          if (std::find(shortest_path.begin(), shortest_path.end(), i) != shortest_path.end()) {
            betweenness.push_back(1.0);
          } else {
            betweenness.push_back(0.0);
          }
        }
      }
    }
    betweenness_factor[i] = std::accumulate(betweenness.begin(), betweenness.end(), 0)/((double)betweenness.size());
    if (betweenness_factor[i] > betweenness_factor[max_index]) {
      max_index = i;
    }
  }
  if (max_index == 0 && betweenness_factor[0] == 0) {
   return -1;
  }
  if (!betweenness_factor.empty()) {
    central = nodes_[max_index];
  }
  return central->twitch_id_;
}
 
} // namespace core

} // namespace twitchsocial

