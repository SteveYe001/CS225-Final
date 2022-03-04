//
// Created by RONG WANG on 11/27/21.
//

#ifndef LANDMARK_DRAW_IMG_H
#define LANDMARK_DRAW_IMG_H

#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include "graph.h"
#include <string>
#include <vector>
#include <unordered_map>
#include <cmath>
#include <unordered_set>
#include "cs225/Animation.h"

class draw_img{
public:
    // constructor
    explicit draw_img(adj_graph *graph);

    // draw the shortest path from start to end
    void draw_shortest_path(string src, string dst, const string& out_put);

    // draw all the airports
    void draw_airports_all(const string& output);

    // draw all the routes
    void draw_routes_all(const string& output);

    // draw bfs traversal from start to end
    //void draw_bfs_wr(string src, string dst, const string& output);
    void draw_bfs_wr(string src, const string& output);

    void draw_landmark(string src, string landmark, string dst, const string& output);

    // draw between centrality, return top 50 airports
    vector<unsigned> draw_between_centrality();

    void draw_force(const string& output,vector<unsigned> top_airports);

private:
    // color point
    const cs225::HSLAPixel _point = cs225::HSLAPixel(30,1,0.5,1);
    const cs225::HSLAPixel _border = cs225::HSLAPixel(30,1,0.7,1);
    const cs225::HSLAPixel _route = cs225::HSLAPixel(120,1,0.7,1);
    const cs225::HSLAPixel _red = cs225::HSLAPixel(360,1,0.5,1);
    const cs225::HSLAPixel _pink = cs225::HSLAPixel(332,1,0.5,1);
    const cs225::HSLAPixel _purple = cs225::HSLAPixel(290,1,0.7,1);

    // world map
    cs225::PNG _background_img;
    unsigned _height;
    unsigned _width;
    unsigned _offset;
    // pointer to a graph object
    adj_graph* _draw_graph;
    //coordinate airport mapped on map, first int is airport, pair is coordinate
    unordered_map<int, pair<int,int>> _local_map;
    
    // draw border around a point
    static void draw_border(pair<int,int> coord, cs225::HSLAPixel color, cs225::PNG& png);
    // draw a line
    static void draw_line(pair<int,int>src, pair<int,int>dst, cs225::HSLAPixel color, cs225::PNG& png);
    // initialize graph
    void init_local_map();
    // convert latitude and longitude to pixel x, y
    pair<int,int> local2graph(pair<double,double>local) const;

};

#endif //LANDMARK_DRAW_IMG_H
