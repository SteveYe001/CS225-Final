//
// Created by wrong on 11/14/2021.
//

#include <numeric>
#include "graph.h"



// constructor
adj_graph::adj_graph(vector<pair<string, string>>& routes, unordered_map<string, vector<double>>& airports){
    _routes = routes;
    _airports = airports;
    get_number();
    build_graph();
}

// destructor
adj_graph::~adj_graph(){}

// get graph size
unsigned adj_graph::get_size() {
    return _graph.size();
}

// get index of airport
int adj_graph::get_index(string code) {
    return _index[code];
}

// get IATA code of airport
string adj_graph::get_code(int index) {
    return _dict[index];
}

vector<pair<int,int>> adj_graph::get_adjacent(int airport){
    return _graph[airport];
}

// build graph
void adj_graph::build_graph() {
    for(auto & _route : _routes){
        // get start and end airport
        int start = _index[_route.first];
        int end = _index[_route.second];
        // get distance between two airports
        int distance = calculate_distance(_route.first, _route.second);

        // adjacent list
        _graph[start].push_back({end, distance});
    }
}

//initialize the top100 airports and assign a point radomly for each of the airports.
void adj_graph::initializeNode(vector<unsigned> top_airports) {
    for(auto & it : top_airports){
        string key = get_code(it);
        //get a random x coordinate value of in[0,800]
        int x = std::rand()%800;
        //get a random y coordinate value in [0,500]
        int y = std::rand()%500;
        nodes[key].first=x;
        nodes[key].second=y;
        factor_k = sqrt(800*500)/top_airports.size();//calculate the factor of repultion and traction.
    }
}
/*For this function, we use the latitude and longitude to calculate the repulsion 
which should be imposed between each points from the equation displacementX =  distX / dist * k * k / dist * ejectFactor
. The ejectfactor can be redefined after implementing the graphic output
*/
void adj_graph::calculate_repulsion(vector<unsigned> top_airports){
    int factor = 6;//default
    double distX, distY, dist;
    int u,v;
    for (auto& it1 : top_airports){
        string key = get_code(it1);//obtain the code of airports from vector<unsigned>
        v++;
        Dxmap[key] = 0.0;
        Dymap[key] = 0.0;//initialize the map of delta for x and y
        for (auto & it2:top_airports){
            u++;
            if(u!=v){
                string  key2= get_code(it2);

                distX = _airports[key][0]-_airports[key2][0];
                distY = _airports[key][1]-_airports[key2][1];//calculate the displacement of x axis and y axis.
                dist = sqrt(distX*distX+distY*distY);
                  
                Dxmap[key]=Dxmap[key2]+distX/dist*factor_k*factor_k/dist*factor;
                Dymap[key]=Dymap[key2]+distY/dist*factor_k*factor_k/dist*factor;//calculate each repulsion displacement of the point associate with all other points and put on map.
            }
        }

    }
}
/*For this function, we use the _routes as the connection, edges between each nodes and thus we can use the factors to calculate the traction force and displacement.
*/
void adj_graph::calculate_traction(vector<unsigned> top_airports){
    int condenseFactor = 3;
    pair<int, int> startnode,endnode;
    //check all the routes and if the routes exist
    for(auto& it  : _routes){
        string start = it.first;
        string end = it.second;
        int flaga = 0;//flag to check if the start airport exist in the topairports vector
        int flagb = 0;//flag to check if the end airport exisst in tthe topairports vector
        //check if both point of the routes exist in the top_airports list.
        for (auto&it1 : top_airports){
            string a = get_code(it1);
            if (a ==start){
                flaga = 1;
            }
            if (a == end){
                flagb=1;
            }
        }
        //if exist, then calculate traction of the points.
        if (flaga==1 && flagb==1){
        
        startnode = nodes[start];//obtain the pair of x,y coordinates
        endnode = nodes[end];
        double distX, distY,dist;
        distX = startnode.first-endnode.first;//calculate difference in the coordinates one x axis and y axis
        distY = startnode.second-endnode.second;
        dist=sqrt(distX*distX+distY*distY);//calculate the distance between them
        Dxmap[it.first]=Dxmap[it.first]-distX*dist/factor_k*condenseFactor;
        Dymap[it.first]=Dymap[it.first]-distY*dist/factor_k*condenseFactor;//calculate the x and y displacement of start point and put in map
        Dxmap[it.second]=Dxmap[it.second]+distX*dist/factor_k*condenseFactor;
        Dymap[it.second]=Dymap[it.second]+distY*dist/factor_k*condenseFactor;//calculate the x and y displacement of end point and put in map
        }
    }
}
/*after obtain the displacement of x coordinate and y coordinate, we check if the displacements out of bound and if the points reaches bound, it will rebound to another position 
for a dx/dy*/
void adj_graph::update_coordinate(vector<unsigned> top_airports){
    int maxtx=8,maxy=5;//set max displacement value
    for (auto&it : top_airports){
        string code = get_code(it);
        pair<int,int> node = nodes[code];
        int dx = (int)Dxmap[code];//change from double to int
        int dy = (int)Dymap[code];
        //check if displacement excess the range allowed
        if (dx<-maxtx){
            dx = -maxtx;
        }
        if (dx>maxtx){
            dx=maxtx;
        }
        if (dy<-maxy){
            dy=-maxy;
        }
        if (dy>maxy){
            dy=maxy;
        }
        node.first=node.first+dx;
        node.second=node.second+dy;
        //make sure it does not excess the boundry of the graph
        if (node.first>=800){
            node.first=node.first-2*dx;

        }//if exccess the boundry, then bound back
        if (node.second>=500){
            node.second=node.second-2*dy;
        }
    }
}
// get diatance between two airports
int adj_graph::calculate_distance(string start, string end){
    // R.W. Sinnott, 'Virtues of Haversine', Sky and Telescope, vol.68, no.2, 1984, p.159
    vector<double>src, dst;
    double pi = 3.141592653589793238462;
    double r = 6378.137;
    src = _airports[start];
    dst = _airports[end];
    double rlat1, rlat2, dlon, dlat;
    // latitude in radius
    rlat1 = src[0] * (pi / 180.0);
    rlat2 = dst[0]*(pi/180.0);
    // diff of longitude and latitude in radius
    dlon = (dst[1]-src[1])*(pi/180.0);
    dlat = (dst[0] - src[0])*(pi/180.0);

    double a = pow(sin(dlat/2.0), 2.0) + cos(rlat1) * cos(rlat2) * pow(sin(dlon / 2.0), 2.0);
    double c = 2*atan2(sqrt(a), sqrt(1.0-a));
    // return diatance in kilometer, round to int
    return (int)(r*c);

}

// Dijkstra shortest path algorithm to all other nodes SSSP
void adj_graph::shortest_path_all(int src, vector<int>&dist, vector<int>&parent){
    unsigned n = _graph.size();
    // if a node has been visited
    vector<bool>visited(n,false);
    // resize distance and parent, set dist to INF
    dist.resize(2*n, INT16_MAX);
    parent.resize(2*n,0);
    // use min heap to find cheapest path
    priority_queue< pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>>pq;

    // mark start node as visited
    visited[src] = true;
    dist[src] = 0;
    parent[src] = 0;
    // push {distance, startpoint} to heap
    pq.push({0,src});

    // loop untill heap is empty
    while(!pq.empty()){
        // get node u
        int u = pq.top().second;
        pq.pop();
        // for all nodes adjacent to u
        for(auto &it : _graph[u]){
            int v = it.first;
            int w = it.second;
            // find cheaper path
            if(!visited[v] && dist[v] > dist[u] + w){
                visited[v] = true;
                // update diatance
                dist[v] = dist[u] + w;
                // add to heap
                pq.push({dist[v], v});
                parent[v] = u;
            }
        }
    }
}

// generate an index for each airport
void adj_graph::get_number(){
    vector<string>airports;
    for(auto & _route : _routes){
        airports.push_back(_route.first);
        airports.push_back(_route.second);
    }
    // sort in alphabet order
    sort(airports.begin(), airports.end());
    // hash table to get unique index
    unordered_map<string, int>index;
    int idx = 0;
    for(auto & airport : airports){
        // if the node was not seen
        if(_index.find(airport) == index.end()){
            // get new index
            _index[airport] = idx;
            _dict[idx] = airport;
            // increase index
            idx++;
        }
    }
}

vector<int> adj_graph::landmark_path(int src, int mid, int dst){
    if(src == dst)
        return {};
    vector<int>dist, parent;
    // find all the shortest path from landmark airport
    shortest_path_all(mid, dist, parent);
    vector<int>path1, path2;
    path1.push_back(src);
    int tmp = src;
    // recurse to find parent
    while(parent[tmp] != mid) {
        path1.push_back(parent[tmp]);
        tmp = parent[tmp];
    }
    path1.push_back(mid);

    path2.push_back(dst);
    tmp = dst;
    // recurse to find parent
    while(parent[tmp] != mid) {
        path2.push_back(parent[tmp]);
        tmp = parent[tmp];
    }
    // reverse to get correct order
    reverse(path2.begin(), path2.end());
    
    vector<int>path;
    // add together to get the path
    for(auto&it:path1)
        path.push_back(it);
    for(auto&it:path2)
        path.push_back(it);

    return path;    
}

// get shortest path from start to end, based on Dijkstra
int adj_graph::shortest_path(int src, int dst, vector<int>&path){
    if(src == dst)
        return 0;
    unsigned n = _graph.size();
    // memory visited node
    vector<bool>visited(n,false);
    // store distance
    vector<int>dist(n, INT16_MAX);
    vector<int>parent(2*n,0);
    // use min heap
    priority_queue< pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>>pq;
    visited[src] = false;
    dist[src] = 0;
    parent[src] = 0;
    // first is distance, second is index
    pq.push({0,src});
    bool flag = false;

    while(!pq.empty()){
        // get an airport from heap
        int u = pq.top().second;
        pq.pop();
        // stop if reach the end node
        if(u == dst){
            flag = true;
            break;
        }
        for(auto &it : _graph[u]){
            int v = it.first;
            int w = it.second;
            // find a cheaper path
            if(!visited[v] && dist[v] > dist[u] + w){
                visited[v] = true;
                // update cost
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
                parent[v] = u;
            }
        }
    }
    int tmp = dst;
    if(flag){
        // get path from dst to src
        path.push_back(dst);
        // recurse to find parent
        while(parent[tmp] != src) {
            path.push_back(parent[tmp]);
            tmp = parent[tmp];
        }
        path.push_back(src);
        // reverse to get the normal order
        reverse(path.begin(), path.end());

        // output the path
        for(size_t i = 0; i < path.size()-1 ;i++){
            cout << get_code(path[i]) <<"->";
        }
        cout<<get_code(path.back())<<endl;

        // output to a file
        ofstream myfile;
        myfile.open("results/shortest_path.txt");
        // write to file
        for(size_t i = 0; i < path.size()-1 ;i++){
            myfile << get_code(path[i]) <<"->";
        }
        myfile<<get_code(path.back())<<endl;
        myfile.close();


        return dist[dst];
    }
    return -1;
}


vector<vector<int>> adj_graph::bfs(int src, vector<int>&parent){
    unsigned n = _graph.size();
    // visit every node once
    vector<bool>visit(n, false);
    parent.resize(2*n,0);
    // store the level order of bfs traversal
    vector<vector<int>>traversal;
    // bfs queue
    queue<int>q;
    q.push(src);
    // loop untill queue is empty
    while(!q.empty()){
        size_t size = q.size();
        vector<int>tmp;
        // nodes on same level 
        for(size_t i = 0; i < size; i++){
            int airport = q.front();
            q.pop();
            // find all adjacent nodes
            for(auto &it:_graph[airport]){
                int link_airport = it.first;
                // if the node was not visited
                if(!visit[link_airport]){
                    visit[link_airport] = true;
                    parent[link_airport] = airport;
                    // add to queue
                    q.push(link_airport);
                }
            }
            // add the node to vector
            tmp.push_back(airport);
            // reach the end point
        }
        // push all the nodes on the same level to result
        traversal.push_back(tmp);
    }

    return traversal;
}


// calculate between_centrality of every airports
vector<pair<double, unsigned>> adj_graph::brandes() {
    unsigned n = _graph.size();
    vector<double>between(2*n, 0.0);
    // calculate between centrality for every node
    for(unsigned src = 0; src < n; src++){
        calculate_between(src, between);
    }

    vector<pair<double, unsigned>>result;
    // store the normalized between centrality and index
    for(unsigned src = 0; src < n; src++){
        // normalize
        result.emplace_back(between[src]/n, src);
    }
    // sort in decrease order, find important nodes
    sort(result.rbegin(), result.rend());
    // write to file
    ofstream myfile;
    myfile.open("results/between_centrality.txt");
    for(auto &it:result){
        myfile << get_code(it.second) << "  between_centrality: " << it.first << endl; 
    }
    myfile.close();

    return result;
}
void adj_graph::calculate_between(unsigned src, vector<double>&between) {
    // Ulrik Brands, A Faster Algothm for Betweeness Centrality, 2001
    unsigned n = _graph.size();
    stack<unsigned>st;
    vector<int>sigma(n,0);
    vector<int>dist(n,-1);
    vector<double>delta(n,0.0);
    vector<vector<unsigned>>pre(n);
    // set sigma to 1
    sigma[src] = 1;
    dist[src] = 0;
    // bfs queue
    queue<unsigned>q;
    q.push(src);

    while(!q.empty()){
        // get from queue
        unsigned v = q.front();
        q.pop();
        st.push(v);
        // get adjacent airports
        for(auto &it: _graph[v]){
            unsigned w = it.first;
            if(dist[w] < 0){
                q.push(w);
                dist[w] = dist[v] + 1;
            }
            // update sigma
            if(dist[w] == dist[v] + 1){
                sigma[w] += sigma[v];
                pre[w].push_back(v);
            }
        }
    }
    // deal with all airports on the path
    while(!st.empty()){
        unsigned w = st.top();
        st.pop();
        // update delta
        for(auto &v: pre[w]){
            delta[v] += ((double) sigma[v]/sigma[w])*(1 + delta[w]);
        }
        // update betweeness
        if(w != src){
            between[w] += delta[w];
        }
    }
}

// used for test cases
int adj_graph::Testdistance(string start,string end){
    int Distance=calculate_distance(start,end);
    return Distance;
}



