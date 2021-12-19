##### CS 225 Data Structures
### **Final Project Proposal (awachat2-jjtang2-venyaj2-tomsui2)**

### Leading Question:  
Our target goal is to map the degrees of separation between one Twitch user to another Twitch user. Being able to determine the shortest path/least degrees of separation in combination with the distance between users’ locations (users) would allow us to view different Twitch niches and circles. This would allow us to view similarities in games played and streaming habits between users. The algorithms could be used to recommend users to follow and understand streaming habits of larger Twitch streamers, ultimately enabling community and intrapersonal tie detections.
		
### Dataset Acquisition and Processing: 
The dataset we have chosen to use for our final project is the Social Circles: Twitch Social Networks data set found on the Stanford Large Network Dataset Collection. We will be storing, and processing through the data into a CSV file, and parsing it into our data structure. Our dataset includes User IDs, streaming habits, and games played, which will be stored within vertices.  Each vertex represents a twitch user, with a unique identifier. Our edges will represent mutual followings amongst Twitch users and are undirected. The edges will be weighted by distance between users’ locations. A potential error could be that a user has no mutual friends passed into from the CSV file. This will cause issues with our Dijkstra’s algorithm as there will be no possible path to another user. In the event that we pass in a vertex with no mutual friends (existing edges), we output that vertex itself.

### Graph Algorithms: 
* We will use a Breadth-First search algorithm to traverse our graph of Twitch users and their following, which will take in edge E and vertices V, taking a time of O(V + E), and traverse all of the vertices.
* In order to find the shortest number of degrees of separation, represented by the shortest path, between two users, we will use Dijkstra’s algorithm which will take in the edges E and vertices V and output the shortest path of V’s and E’s from one user to another, taking O(V^2) time. 
* We will determine the most influential and connected vertex through the Betweenness Centrality algorithm, which will take in a list of vertices V and output the most central vertex U which represents the center of that list of vertices V’s community twitch community. Because it requires the ability to find the shortest path between all the input vertices, the runtime will take O((v + 1) * V^2), where v is number of vertices in the input list and V is the total number of vertices in a graph.

### Timeline: 
* Nov. 10th - Nov. 29th
    * Parsing Data and loading data
    * Build graph DS
    * Implement Dijkstra’s on graph
    * Write Test cases for everything
* Nov. 29th - Dec 7th
    * Implement Betweenness on Graph
    * Write Test cases (Betweenness)
* Dec 8th - Dec 13th
    * Clean Up + Presentation
