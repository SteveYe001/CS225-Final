//
// Created by wrong on 11/14/2021.
//
#include "dataIO.h"
//#include <direct.h>

/*
 * read routes data from routes.csv
 * return vector of pair <start, end>
 */
vector<pair<string, string>>read_valid_route(string filename, unordered_map<string, vector<double>>& airports){
    ifstream read_routes(filename);
    // fail to open file
    if(!read_routes.is_open())
        throw runtime_error("Could Not Open File");

    string line, start, end;
    // store all routes
    vector<pair<string, string>>routes_all;

    // read each line, split with ','
    while(getline(read_routes, line)){

        stringstream ss(line);
        // get start airport
        getline(ss, start, ',');
        // get end airport
        getline(ss, end);
        // if start and end airports are vaild
        if(airports.find(start) != airports.end() && airports.find(end) != airports.end())
            routes_all.push_back({start,end});
    }
    return routes_all;

}

unordered_map<string, vector<double>>read_airport(string filename){
    ifstream read_airport(filename);
    // fail to open file
    if(!read_airport.is_open())
        throw runtime_error("Could Not Open File");
    string code;
    string line, la, lo, al;

    // code, [latitude, longitude, altitude]
    unordered_map<string, vector<double>>airport_all;
    while( getline(read_airport,line)){
        stringstream ss(line);
        // get IATA code
        getline(ss, code, ',');
        // get latitude
        getline(ss, la,',');
        // get longitude
        getline(ss, lo,',');
        // get altitude
        getline(ss, al,',');

        // hash code to vector of coordinate
        airport_all[code] = {stod(la),stod(lo),stod(al)};
    }
    return airport_all;
}
