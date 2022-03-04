//
// Created by RONG WANG on 11/27/21.
//
#include "draw_img.h"
#include <utility>

draw_img::draw_img(adj_graph* graph) {
    // read image
    _background_img.readFromFile("images/map.png");
    // initialize params
    _height = 2*_background_img.height();
    _width = _background_img.width();
    _offset = 300;
    _draw_graph = graph;

    init_local_map();
}

// draw all the airports on the map
void draw_img::draw_airports_all(const string& output){
    cs225::PNG airport_map(_background_img);
    // get all airports
    for(auto& mp:_local_map){
        auto coord = mp.second;
        // draw airport
        airport_map.getPixel(coord.first, coord.second) = _point;
        // draw boarder
        draw_border(coord, _border, airport_map);
    }
    airport_map.writeToFile(output);
}
// draw force directed graph
void draw_img::draw_force(const string& output,vector<unsigned> top_airports){
    cs225::PNG png(800,500);//initialize a canvas of 800*500
    _draw_graph->initializeNode(top_airports);
    _draw_graph->calculate_repulsion(top_airports);
    _draw_graph->calculate_traction(top_airports);
    _draw_graph->update_coordinate(top_airports);//procedure of calculating coordinates.
    int count = 0;
    //check all the points in top_airports
    for (auto&it : top_airports){
        string code = _draw_graph->get_code(it);
        auto coord = _draw_graph->nodes[code];
        draw_border(coord, _red, png);
    }
    //check for adjacent airports which are in the list of top_airports.
    unordered_set<unsigned>visited;
    for(auto &it: top_airports){
        if(visited.find(it) == visited.end()){
            visited.insert(it);
            vector<pair<int,int>>adjacent = _draw_graph->get_adjacent(it);//get the vector of the index of airport.
            for(auto & it1: adjacent){
                int airport1 = it1.first;
                //if(airport_set.find(airport1) != airport_set.end() && visited.find(airport1)==visited.end()){
                if(visited.find(airport1)==visited.end()){
                    visited.insert(airport1);
                string src = _draw_graph->get_code(it);//translate into the code
                string dst = _draw_graph->get_code(airport1);
                auto coord1 = _draw_graph->nodes[src];//get the coordinates
                auto coord2 = _draw_graph->nodes[dst];
                cs225::HSLAPixel p;
                p.l=0;
                draw_line(coord1, coord2, p, png);
                }
            }
        }
    }
    png.writeToFile(output);
}

// draw all the routes
void draw_img::draw_routes_all(const string& output){
    cs225::PNG routes_map(_background_img);
    // initialize an Animation object
    Animation routes_gif;
    unsigned frame_cnt = 0;
    // get all routes
    for(auto &route:_draw_graph->_routes){
        int src = _draw_graph->get_index(route.first);
        int dst = _draw_graph->get_index(route.second);
        // draw src on map
        auto coord1 = _local_map[src];
        routes_map.getPixel(coord1.first, coord1.second) = _point;
        draw_border(coord1, _border,routes_map);
        // draw dst on map
        auto coord2 = _local_map[dst];
        routes_map.getPixel(coord2.first, coord2.second) = _point;
        draw_border(coord2, _border,routes_map);
        // draw line between two airports
        draw_line(coord1, coord2, _route, routes_map);

        if(frame_cnt%2000 == 0)
            routes_gif.addFrame(routes_map);
        frame_cnt++;
    }

    routes_map.writeToFile(output);
    routes_gif.write(output+".gif");
}

// draw shortest path from src to dst
void draw_img::draw_shortest_path(string src, string dst, const string& output) {
    cs225::PNG airport_map(_background_img);
    Animation path_gif;
    vector<int>path;
    // get start and end index
    int start = _draw_graph->get_index(std::move(src));
    int end = _draw_graph->get_index(std::move(dst));
    // get path length 
    int length = _draw_graph->shortest_path(start, end, path);
    // draw all the airports
    for(auto &p:path){
        auto coord = _local_map[p];
        airport_map.getPixel(coord.first, coord.second) = _point;
        draw_border(coord, _border,airport_map);
    }
    // draw line 
    for(size_t i = 0; i < path.size() -1; i++){
        int p1 = path[i], p2 = path[i+1];
        draw_line(_local_map[p1], _local_map[p2], _route, airport_map);
        path_gif.addFrame(airport_map);
    }
    cout << "length of shortest path: "<< length <<endl;
    airport_map.writeToFile(output);
    path_gif.write(output+".gif");
}

// draw landmark path
void draw_img::draw_landmark(string src, string landmark, string dst, const string& output){
    cs225::PNG airport_map(_background_img);
    Animation path_gif;
    vector<int>path;
    // get index of src, dst and landmark
    int start = _draw_graph->get_index(std::move(src));
    int mid = _draw_graph->get_index(std::move(landmark));
    int end = _draw_graph->get_index(std::move(dst));
    path = _draw_graph->landmark_path(start, mid, end);
    // draw all the airports
    for(auto &p:path){
        auto coord = _local_map[p];
        airport_map.getPixel(coord.first, coord.second) = _point;
        draw_border(coord, _border,airport_map);
    }
    // draw all the lines
    for(size_t i = 0; i < path.size() -1; i++){
        int p1 = path[i], p2 = path[i+1];
        draw_line(_local_map[p1], _local_map[p2], _route, airport_map);
        path_gif.addFrame(airport_map);
    }
    airport_map.writeToFile(output);
    path_gif.write(output+".gif");
}



void draw_img::draw_bfs_wr(string src, const string& output){
    cs225::PNG bfs_map(_background_img);
    Animation bfs_gif;
    // get index
    int start = _draw_graph->get_index(std::move(src));
    vector<vector<int>>traversal;
    vector<int>parent;
    // get traversal result
    traversal = _draw_graph->bfs(start, parent);
    // draw level order tranversal
    for(auto &path:traversal) {
        for (auto &p: path) {
            auto coord = _local_map[p];
            bfs_map.getPixel(coord.first, coord.second) = _point;
            draw_border(coord, _border, bfs_map);
            int par = parent[p];
            if(par != p){
                auto coord1 = _local_map[par];
                draw_line(coord1, coord, _route, bfs_map);
            }
        }
        bfs_gif.addFrame(bfs_map);
    }
    bfs_map.writeToFile(output);
    bfs_gif.write(output+".gif");
}

vector<unsigned> draw_img::draw_between_centrality(){
    cs225::PNG brandes(_background_img);
    vector<pair<double,unsigned>>result = _draw_graph->brandes();
    vector<unsigned>top_airports;
    // top 10 airports
    for(unsigned i = 0; i < 10; i++){
        unsigned p = result[i].second;
        top_airports.push_back(p);
        auto coord = _local_map[p];
        brandes.getPixel(coord.first, coord.second) = _point;
        draw_border(coord, _red, brandes);
    }
    // top 20 
    for(unsigned i = 10; i < 20; i++){
        unsigned p = result[i].second;
        auto coord = _local_map[p];
        top_airports.push_back(p);
        brandes.getPixel(coord.first, coord.second) = _point;
        draw_border(coord, _pink,brandes);
    }
    // top 30
    for(unsigned i = 20; i < 30; i++){
        unsigned p = result[i].second;
        auto coord = _local_map[p];
        top_airports.push_back(p);
        brandes.getPixel(coord.first, coord.second) = _point;
        draw_border(coord, _purple, brandes);
    }
    // top 100
    for(unsigned i = 30; i < 100; i++){
        unsigned p = result[i].second;
        auto coord = _local_map[p];
        top_airports.push_back(p);
        brandes.getPixel(coord.first, coord.second) = _point;
        draw_border(coord, _border, brandes);
    }
    

    brandes.writeToFile("results/brandes.png");
    return top_airports;
}


void draw_img::draw_border(pair<int,int> coord, const cs225::HSLAPixel color, cs225::PNG& png) {
    if (coord.first > 0) {
        png.getPixel(coord.first - 1, coord.second) = color;
    }
    if (coord.second > 0) {
        png.getPixel(coord.first, coord.second - 1) = color;
    }

    /* check upper bounds */
    if (coord.first < (int) png.width() - 1) {
        png.getPixel(coord.first + 1, coord.second) = color;
    }
    if (coord.second < (int) png.height() - 1) {
        png.getPixel(coord.first, coord.second + 1) = color;
    }
}

void draw_img::draw_line(pair<int,int>src, pair<int,int>dst, const cs225::HSLAPixel color, cs225::PNG& png) {
/* Implementation of the DDA algorithm with help from https://www.youtube.com/watch?v=W5P8GlaEOSI */
    double x1,x2, y1,y2, delta_x, delta_y, s, xinc, yinc;
    x1 = src.first;
    y1 = src.second;
    x2 = dst.first;
    y2 = dst.second;
    delta_x = x2-x1;
    delta_y = y2-y1;

    /* This segment checks if it is closer for the line to wrap around the image */
    double stdDistance = sqrt(delta_x * delta_x + delta_y * delta_y);
    double wx1 = x1, wx2 = x2, wdelta_x;
    x1 <= x2 ? (wx2 = wx2 - png.width()) : (wx1 = wx1 - png.width());
    wdelta_x = wx2 - wx1;
    double wDistance = sqrt(wdelta_x * wdelta_x + delta_y * delta_y);

    if (wDistance <= stdDistance){
        delta_x = wdelta_x;
        x1 = wx1;
    }

    /* Essentailly checking if slope is greater than or less than one to determine step size */
    if (abs(delta_x) > abs(delta_y)){
        s = abs(delta_x);
    } else {
        s = abs(delta_y);
    }

    /*Compute the respective dimension increments */
    xinc = delta_x/s;
    yinc = delta_y/s;

    /* Replace pixel with color to mark path */
    for (unsigned i = 0; i < s; i++) {
        unsigned width = png.width();
        unsigned x = ((((int) round(x1)) % width) + width) % width;
        cs225::HSLAPixel &pixel = png.getPixel((unsigned) x, (unsigned) (round(y1)));

        pixel = color;
        x1 = x1 + xinc;
        y1 = y1 + yinc;
    }
}

void draw_img::init_local_map() {
    for(auto& airport : _draw_graph->_airports){
        // get index
        int idx = _draw_graph->get_index(airport.first);
        // get latitude and longitude
        double lat = airport.second[0];
        double lon = airport.second[1];
        // convert to image cordinate
        auto coord = local2graph({lat, lon});
        if(_local_map.find(idx) == _local_map.end()){
            _local_map[idx] = coord;
        }
    }
}

// convert world coordinate to image coordinate
pair<int,int> draw_img::local2graph(pair<double,double>local) const{
    int w = floor(_width/2.0*(1+local.second/180.0)+0.5);
    int h = floor(_height/2.0*(1+local.first/180.0)+0.5);
    return {w, _height-h-_offset};
}


