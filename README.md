# Overview
This was my final project for my data strucutres class.

# Twitch User Social Graph
Using the Twitch User Social graph program, you can run a BFS Traversal, Dijkstra's Shortest Path Algorithm, and the Betweenness Centrality to determine the shortest path amongst Twitch users in the United States, as well as the user with the most mutual followings on the Twitch platform.


# Building Files
This project will run most efficiently on the University of Illinois at Urbana Champaign's EWS machine. When working on EWS, you must execute the following commands:
```
module load llvm/6.0.1
make
```
This will compile and build your graph and parsing classes used for the functionality of this program.

# Run
You can run the TwitchSocialGraph in 2 differenct capacities. In order to run created tests to validate the accuracy of our used algorithms, you can run `make test` followed by `./test` In order to run our main function, allowing for other datasets and combinations of algorithms, you can run `./main`.

# Data Format
Samples of datasets are included within the `parsing/data` folder. The `.txt` file carrying the edges of twitch user data must use the following format: 

```
from,to
*twitch_id1*,*twitch_id2*
*twitch_id1*,*twitch_id1*
...
```
The `.txt` file carrying the twitch user data must use the following format:

```
id,days,mature,views,partner,new_id
*twitch_id*,*days*,*mature_bool*,*views*,*partner_bool,*new_id* //
...
```
