#pragma once

#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

class DataParser {
    public:
        vector<pair<int, int>> edge_data(string filename);
        vector<pair<pair<int, int>, pair<double, double>>> user_data(string filename);

    private:
        vector<pair<int,int>> edges;
        vector<pair<pair<int, int>, pair<double, double>>> twitch_user;
};