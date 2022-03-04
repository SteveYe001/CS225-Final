# rongw4-yiyanz3-ruoliu2-yongy2
rongw4-yiyanz3-ruoliu2-yongy2  
# please use ews_version branch
## (1)The location of all major Code, data and results
The structure of our project listed below.  
├── APPROVAL  
├── data  
├── development.txt  
├── doc  
├── landmark  
└── README.md
### data  
├── data  
│   ├── airports.csv  
│   ├── airports.dat.txt  
│   ├── routes.csv  
│   └── routes.dat.txt  
We use the airports and routes, stored at `/data`, including "airports" and "routes" in both `.txt` and `.csv` format.  
### major code
├── landmark  
│   ├── catch  
│   ├── CMakeFiles  
│   ├── CMakeLists.txt  
│   ├── cs225  
│   ├── dataIO.cpp  
│   ├── dataIO.h  
│   ├── draw_img.cpp  
│   ├── draw_img.h  
│   ├── frames  
│   ├── graph.cpp  
│   ├── graph.h  
│   ├── images  
│   ├── init.sh  
│   ├── input.txt  
│   ├── landmark  
│   ├── main.cpp  
│   ├── results  
│   └── tests  
`dataIO.h/dataIO.cpp`: read data from "airports.csv" and "routes.csv".  
`graph.h/graph.cpp` create a new class: "adj_graph", including graph algorithms.   
`draw_img.h/draw_img.cpp` draw the outputs of every algorithm.  
our test cases are at `/landmark/tests/`  
### results
landmark  
   ├── results  
   │   ├── airports.png  
   │   ├── between_centrality.txt   
   │   ├── bfs.png  
   │   ├── bfs_wr.png  
   │   ├── bfs_wr.png.gif  
   │   ├── brandes.png  
   │   ├── force.png  
   │   ├── landmark_path.txt  
   │   ├── landmark.png  
   │   ├── landmark.png.gif  
   │   ├── routes.png  
   │   ├── routes.png.gif  
   │   ├── shortest.png  
   │   └── shortest.png.gif  
our results are stored at `/landmark/results`, including `.png` and `.gif` picture of our results.  
the between centralities of every airport are shown in `between_centrality.txt`  
the landmark path is shown in `landmark_path.txt`  
## (2)Full Instructions on how to build and run executable   

1. You are strongly recommended to run the code on the ews mechine of UIUC
   You may refer to this: https://answers.uillinois.edu/illinois.engineering/84207  to learn how to use ews mechine.
2. to get the code, run 
   ```
   git clone -b ews_version https://github-dev.cs.illinois.edu/cs225-fa21/rongw4-yiyanz3-ruoliu2-yongy2.git 
   ```
   please make sure you are in **ews_version** branch!
3. go into `/landmark` folder, run 
   ```
   bash init.sh 
   ```
   to build the project automaticly
4. if you want to input from a file, please edit `input.txt` and run
   ```
   ./landmark 
   ```
   if you want to input with command line, run
   ```
   ./landmark [airport data location] [route data location] [shortest path start airport] [shortest path end airport] [shortest path result location] [bfs start airport] [bfs result location] [landmark start airport] [landmark airport] [landmark end airport] [landmark result location]
   ```
   for example
   ```
   /landmark "..//data/airports.csv" "..//data/routes.csv" "YPH" "CXB" "results/shortest.png" "SEA" "results/bfs_wr.png" "SEA" "YPH" "CXB" "results/landmark.png"
   ```
4. if you want to run test, run `./test`
5. You can check the output in `/landmark/results` folder.

## (3)Full instructions how to build test suite
Test cases are build automaticly when you build the project with `init.sh`
hoever, you can run `make test` in the terminal and `./test` to run the test case.
All the test case is expected to be passed. 
We created test cases for each function:

-read in airport data for dataIO.cpp
-BFS and Dijkstra test case for graph.cpp

Each of the test case is marked with explanation. 
As for the test case, we write the some algorithm individually and use one person's output to 
test another person's code. If pass, merge two algorithms.

### (4)You can find our video here
https://youtu.be/V9CIuLHZF2g
