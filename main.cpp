#include <iostream>
#include "dataIO.h"
#include "graph.h"
#include "draw_img.h"
#include "catch/catch.hpp"

#define CATCH_CONFIG_MAIN
int main(int argc, const char* argv[]) {
  
    if(argc == 1){
        cout<<"Read input from input.txt:"<<endl;
        // read input file
        ifstream input("input.txt");
        string line, src, dst, output;
        // get airport file
        getline(input, line);
        unordered_map<string, vector<double>> airports = read_airport(line);
        cout<<"Read airports successfully!"<<endl;
        // get route file
        getline(input, line);
        vector<pair<string, string>> valid_routes = read_valid_route(line, airports);
        cout << "Read routes successfully!"<<endl;
        
        // get shortest path param
        getline(input, line);
        stringstream ss(line);
        getline(ss, src, ',');
        getline(ss, dst, ',');
        getline(ss, output);

        // get bfs param
        string line1, src1, dst1, output1;
        getline(input, line1);
        stringstream ss1(line1);
        getline(ss1, src1, ',');
        getline(ss1, output1);

        // get landmark param
        string line2, src2, mid2, dst2, output2;
        getline(input, line2);
        stringstream ss2(line2);
        getline(ss2, src2, ',');
        getline(ss2, mid2, ',');
        getline(ss2, dst2, ',');
        getline(ss2, output2);

        // create graph
    adj_graph graph(valid_routes, airports);
    cout<<"Build graph successfully!"<<endl;

    // create draw image class
    draw_img draw(&graph);

    // draw all the airports
    cout<<"Drawing airports ..."<<endl;
    draw.draw_airports_all("results/airports.png");
    

    // draw all the routes
    cout << "Drawing routes ..." <<endl;
    draw.draw_routes_all("results/routes.png");

    // draw shortest path
    cout << "Drawing shortest path ..." <<endl;
    draw.draw_shortest_path(src, dst, output);

    // draw landmark path
    cout << "Drawing landmark path ..." <<endl;
    draw.draw_landmark(src2, mid2, dst2, output2);
    
    // draw bfs
    cout << "Drawing bfs ..." << endl;
    draw.draw_bfs_wr(src1, output1);

    
    //draw between centrality
     vector<unsigned>top_airports;
     top_airports = draw.draw_between_centrality();
     cout <<"Calculate between centrality successfully!"<<endl;

    //draw force-dricted graph
     cout <<"Drawing force-dricted graph..."<<endl;
     draw.draw_force("results/force.png",top_airports);

    cout <<"Finished!"<<endl;
    }
    else if(argc == 12){
        cout<<"Using command line input."<<endl;
        cout<<"-------------------------"<<endl;
        cout<<"Param 1: airports file. '..//data/airports.csv'"<<endl;
        cout<<"Param 2: routes file. '..//data/routes.csv'"<<endl;
        cout<<"Param 3: shortest path start 'YPH'"<<endl;
        cout<<"Param 4: shortest path end 'CXB'"<<endl;
        cout<<"Param 5: shortest path output 'results/shortest.png'"<<endl;
        cout<<"Param 6: bfs start 'SEA'"<<endl;
        cout<<"Param 7: bfs output 'results/bfs_wr.png'"<<endl;
        cout<<"Param 8: landmark start 'SEA'"<<endl;
        cout<<"Param 9: landmark 'YPH'"<<endl;
        cout<<"Param 10: landmark end 'CXB'"<<endl;
        cout<<"Param 11: landmark output 'results/landmark.png'"<<endl;

        unordered_map<string, vector<double>> airports = read_airport(argv[1]);
        cout<<"Read airports successfully!"<<endl;
        // get route file
        vector<pair<string, string>> valid_routes = read_valid_route(argv[2], airports);
        cout << "Read routes successfully!"<<endl;

        adj_graph graph(valid_routes, airports);
        cout<<"Build graph successfully!"<<endl;

        // create draw image class
        draw_img draw(&graph);

        // draw all the airports
        cout<<"Drawing airports ..."<<endl;
        draw.draw_airports_all("results/airports.png");
        

        // draw all the routes
        cout << "Drawing routes ..." <<endl;
        draw.draw_routes_all("results/routes.png");

        // draw shortest path
        cout << "Drawing shortest path ..." <<endl;
        draw.draw_shortest_path(argv[3], argv[4], argv[5]);

         // draw bfs
        cout << "Drawing bfs ..." << endl;
        draw.draw_bfs_wr(argv[6], argv[7]);

        // draw landmark path
        cout << "Drawing landmark path ..." <<endl;
        draw.draw_landmark(argv[8], argv[9], argv[10], argv[11]);
        
        //draw between centrality
        vector<unsigned>top_airports;
        top_airports = draw.draw_between_centrality();
        cout <<"Calculate between centrality successfully!"<<endl;

        //draw force-dricted graph
        cout <<"Drawing force-dricted graph..."<<endl;
        draw.draw_force("results/force.png",top_airports);

        cout <<"Finished!"<<endl;

    }
    else{
        cout<<"Invalid command line input."<<endl;
        cout<<"-------------------------"<<endl;
        cout<<"Param 1: airports file. '..//data/airports.csv'"<<endl;
        cout<<"Param 2: routes file. '..//data/routes.csv'"<<endl;
        cout<<"Param 3: shortest path start 'YPH'"<<endl;
        cout<<"Param 4: shortest path end 'CXB'"<<endl;
        cout<<"Param 5: shortest path output 'results/shortest.png'"<<endl;
        cout<<"Param 6: bfs start 'SEA'"<<endl;
        cout<<"Param 7: bfs output 'results/bfs_wr.png'"<<endl;
        cout<<"Param 8: landmark start 'SEA'"<<endl;
        cout<<"Param 9: landmark 'YPH'"<<endl;
        cout<<"Param 10: landmark end 'CXB'"<<endl;
        cout<<"Param 11: landmark output 'results/landmark.png'"<<endl;

    }

    return 0;
}
