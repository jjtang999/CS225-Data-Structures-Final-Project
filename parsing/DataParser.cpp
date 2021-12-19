#include "DataParser.h"

#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <stdexcept>

using namespace std;
//user -> id,days,mature,views,partner,new_id
//edges -> from,to

vector<pair<int, int>> DataParser::edge_data(string filename){
    string line;
    vector<pair<int,int>> result;

    ifstream myfile(filename);

    if (myfile.is_open()){
        getline (myfile,line); // skips first line
        while (getline (myfile,line)){
            vector<string> temp;
            stringstream s_stream(line);
            while(s_stream.good()) {
                string substr;
                getline(s_stream, substr, ','); //seperate string into vector elements
                temp.push_back(substr);
            }
            result.push_back( { stoi(temp.at(0)), stoi(temp.at(1)) } );
        }
        myfile.close();
    } else {
        throw invalid_argument("Wrong file name");
    }

    return result;
}

vector<pair<pair<int, int>, pair<double, double>>> DataParser::user_data(string filename){
    string line;
    vector<pair<pair<int, int>, pair<double, double>>> result;
    int i = 1;

    ifstream myfile(filename);

    if (myfile.is_open()){
        getline (myfile,line); // skips first line
        while (getline (myfile,line)){
            vector<string> temp;
            stringstream s_stream(line);
            while(s_stream.good()) {
                string substr;
                getline(s_stream, substr, ','); //seperate string into vector elements
                temp.push_back(substr);
            }
            srand(i);
            double x = rand() % 181;
            double y = rand() % 91 - 90;  //rng -90 to 90 y, 0 to 180 x
            result.push_back(make_pair(make_pair(stoi(temp.at(5)), stoi(temp.at(0))),make_pair(x,y))); 
            i++;
        }
        myfile.close();
    } else {
        throw invalid_argument("Wrong file name");
    }

    return result;
}
