#include "../../catch/catch.hpp"
#include "../DataParser.h"
#include <istream> 

//sample user 29
//sample edges 23
DataParser parser;


TEST_CASE("Test edge data") { 
    vector<pair<int,int>> edges;

    edges = parser.edge_data("parsing/data/sample_edges.txt");
    pair<int, int> pair, expected;

    SECTION("Test edge data is correct") {
        pair = edges[0]; expected = {6194, 255};
        REQUIRE(pair == expected);
        pair = edges[3]; expected = {6194, 2507};
        REQUIRE(pair == expected);
        pair = edges[7]; expected = {15, 343};
        REQUIRE(pair == expected);

    }

     SECTION("Test size") {
        REQUIRE(edges.size() == 22);
    }
    
}

TEST_CASE("Test user data") {   
    vector<pair<pair<int, int>, pair<double, double>>> twitch_user;

    twitch_user = parser.user_data("parsing/data/sample_user.txt");
    pair<int, int> conversion, expected_conversion;
    pair<double, double> coords, expected_coords;

    SECTION("Test user data is correct") {

        conversion = twitch_user[0].first; expected_conversion = {2299, 73045350}; 
        coords = twitch_user[0].second; expected_coords = {155, -34};
        cout << "first coord" << coords.first << " " << coords.second;
        REQUIRE(conversion == expected_conversion);
        REQUIRE(coords == expected_coords);
        conversion = twitch_user[3].first; expected_conversion = {5623, 117338954}; 
        coords = twitch_user[3].second; expected_coords = {77, -48};
        cout << "second coord" << coords.first << " " << coords.second;
        REQUIRE(conversion == expected_conversion);
        REQUIRE(coords == expected_coords);
        conversion = twitch_user[7].first; expected_conversion = {6367, 126853728};
        coords = twitch_user[7].second; expected_coords = {154, -42};
        cout << "third coord" << coords.first << " " << coords.second;
        REQUIRE(conversion == expected_conversion);
        REQUIRE(coords == expected_coords);
    }

    SECTION("Test size") {
        REQUIRE(twitch_user.size() == 28);
    }
    
}

TEST_CASE("Test actual") { 
    vector<pair<int,int>> edges;
    vector<pair<pair<int, int>, pair<double, double>>> twitch_user;

    edges = parser.edge_data("parsing/data/engb_edges.txt");
    twitch_user = parser.user_data("parsing/data/engb_user.txt");
    int size = twitch_user.size();
    vector<int> users;

    for (int i = 0; i < size; ++i) {
        users.push_back(twitch_user[i].first.first);
    }

    sort(users.begin(), users.end());
    for (int i = 0; i < size; ++i) {
        REQUIRE(users[i] == i);
    }
}







