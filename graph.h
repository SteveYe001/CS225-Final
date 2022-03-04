//
// Created by wrong on 11/14/2021.
//

#ifndef LANDMARK_GRAPH_H
#define LANDMARK_GRAPH_H
#include <unordered_map>
#include <vector>
#include <string>
#include <queue>
#include<cmath>
#include<stack>
#include<list>
#include "dataIO.h"
#include "cs225/HSLAPixel.h"
#include "cs225/PNG.h"


using namespace std;

class adj_graph{
public:
    // constructor
    adj_graph(vector<pair<string, string>>& routes, unordered_map<string, vector<double>>& airports);

    // destructor
    ~adj_graph();

    // get size of graph
    unsigned get_size();

    // give an IATA_code, get index
    int get_index(string code);

    // give an index, get IATA_code
    string get_code(int index);

    vector<pair<int,int>>get_adjacent(int airport);

    // shortest path from start to all airports, return distance and parent of each airport
    void shortest_path_all(int src, vector<int>&dist, vector<int>&parent);

    // shortest path from start to end, return length and path
    int shortest_path(int src, int dst, vector<int>&path);

    // shortest path from start to end through a landmark, return length and path
    vector<int> landmark_path(int src, int mid, int dst);

    // bfs traversal from start to end
    vector<vector<int>> bfs(int src, vector<int>&parent);
    
    // calculate between centrality using brands algorithm
    vector<pair<double, unsigned>> brandes();
    
    // store airports, key: IATA code, value: [latitude, longitude, altitude]
    unordered_map<string, vector<double>> _airports;
    // store routes, first: start airport, second: end airport
    vector<pair<string, string>> _routes;

    // used for test case
    int Testdistance(string start,string end);

    // force directed graph
    unordered_map<string,pair<int, int>> nodes;  
    // calculate repulsion of points
    void calculate_repulsion(vector<unsigned> top_airports);
    //calculate tracktion of points
    void calculate_traction(vector<unsigned> top_airports);
    // update the coordinates from points
    void update_coordinate(vector<unsigned> top_airports);
    //initiallize node
    void initializeNode(vector<unsigned> top_airports) ;

private:
    

    // displacement of the point of x and y
    unordered_map<string,double> Dxmap;
    unordered_map<string,double> Dymap;
    cs225::PNG png;
    //struct of Node for FDG
    struct Node{
        int xcoordinate;
        int ycoordinate;
        string key;

    };
    double factor_k;

    // hash table, key: airport index, value: adjacent airport, diatance
    unordered_map<int, vector<pair<int,int>>>_graph;

    // hash table, key: IATA_code, value: index;
    unordered_map<string, int>_index;

    // hash table, key: index, value: IATA_code
    unordered_map<int, string>_dict;

    // helper functions
    // build graph from routes
    void build_graph();

    // assign an index for every airport
    void get_number();

    // calculate distance between two airports
    int calculate_distance(string start, string end);

    // between centrality
    void calculate_between(unsigned src, vector<double>&between);

};
#endif //LANDMARK_GRAPH_H
