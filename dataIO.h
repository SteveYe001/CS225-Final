//
// Created by wrong on 11/14/2021.
//

#ifndef LANDMARK_fileIO_H
#define LANDMARK_fileIO_H

#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<sstream>
#include<unordered_map>
#include <algorithm>

using namespace std;

// read airport (IATA_code, [latitude, longitude, altitude])
unordered_map<string, vector<double>>read_airport(string filename);

// read valid route where airport has an IATA_code (start, end)
vector<pair<string, string>>read_valid_route(string filename, unordered_map<string, vector<double>>& airports);

#endif //LANDMARK_fileIO_H
