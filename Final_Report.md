# CS 225 Final Project Final Report

## **Goals** 

1. **Leading Question**
Provided two cities, our goal is to find the shortest route between these cities’ airports via the landmarks we choose.
Then we would like to draw a map of the world and draw the airports over it, and work on a traversal highlight the path from the starting airport to the ending airport.

2. **Dataset Acquistion and Processing** <br>We propose using the OpenFlights Dataset. We will focus on the Airports and Route subset of this data, which consists of airports information (Airport ID, latitude, longtitude, and altitude) in airports.dat and airlines information (source airport,
In this project, we will use databases from OpenFlights. Since our focus is on the Landmark algorithm, we will focus on the Airports and Routes data files. We will take the IATA code corresponding to the airport as the key of the current node, and compare the data of routes between adjacent nodes to find out whether there is a corresponding route, so as to establish the graph. Meanwhile, the approximate distance of routes between nodes is calculated by latitude and longitude. Find the closest routes from one point to another. Meanwhile, we will filter out the data which are invalid by removing data without an IATA number.
The URL of database which we want to use is https://openflights.org/data.html (Mainly on airports.dat and routes.dat). To be specific:
The URL of dataset:
Airports: https://raw.githubusercontent.com/jpatokal/openflights/master/data/airports.dat
Routes:https://raw.githubusercontent.com/jpatokal/openflights/master/data/routes.dat

3. **Graph Algorithms**  <br>For our graph traversal, we decided to implement BFS. Because BFS can be used to find single source shortest path in an unweighted graph and we are able to reach a vertex with minimum number of edges from a source vertex.
Our input would be the starting IATA node, which is a 3-letter IATA code. For example, Aiken Regional Airport is AIK. The running time is $O(m + n)$, with n is the number of Nodes and m is the number of edges.
Dijkstra's algorithm is an algorithm for finding the shortest paths between nodes in a graph. Our input will be the starting IATA node, the landmark IATA node, and the destination IATA node. Our output should be the shortest route from origin to destination via landmarks. The running time is $O(m+nlog n)$, m stands for the number of edges, and n stands for the number of vertices. 
Finally, we use Force-directed graph drawing algorithms to show our results. Force-directed graph drawing algorithm is used to position the nodes in two-dimensional space such that all edges are of more or less equal length and there are as few crossing edges as possible. The input of this algorithm is vertives and edges of the airports, the output is a graph showing the position and link of these airports. In this case, we use Airport database as the node, and use Route database as the link. There are over $10,000$ airports and $67663$ routes. The output is a force-directed graph. The running time is equivalent to $O(n^3)$, where n is the number of nodes of the input graph. 

4. **Timeline**
Nov 8   - submit project proposal, team contract, and initial repo
Nov 11 - learn how to write Makefile
Nov 13 - learn to read from files and convert the input data into readable format
Nov 15 - start to implement BFS traversal
Nov 22 - finish BFS traversal, start to implement Dijikstra’s algorithm, and start to learn about graphic output
Nov 29 - (Mid-Proj checkin)make progress on graphic output and Dijikstra's algorithm, meet with project mentor
Dec 6   - Finalize the project, so that we could have another week to optimize our code and add some extra features. Start to write final report
Dec 10 - record final presentation
Dec 13 - submit presentation


## **Development**

The develpment log was documented with the development.txt in the same directory


## **Result**

## List of Successful Implementations 

* Parse airport and routes data into readable data structure
  * Assign weights as the real distances between two Airports
* Implement a BFS
Implement Dijkstra’s Algorithm to find the shortest path between two airports
Implement landmark function to find shortest path between two airports through one landmark
Graphic Output: 
* 1.Map Projection
  * Map Airport latitude and longitude to pixel coordinates
  * Visualize Airports and Routes on Mercator Map
  * Visualize the process of making BFS and Dijkstra as png and gif

* 2.Force-directed graph
  * ap the airports so that there are as few cross edges as possible
  * Simulate the motion of the routes and airports as physical forces
  * Visualize the output as PNG file
* 3.Betweenness centrality
  * measure centrality in a graph based on shortest paths
  * Output the centrality of airports as txt and png files


In this final project, we managed to accomplish all goals we set in our project proposal. Also, we added some functionality of our own to answer some questions we found while we implement our code, including the animation feature and the betweenness centrality algorithm.

Regarding reading and processing data sets, first, we read airports data as a hash table. We store the IATA code of each airport as keys and the corresponding vector which stores the latitude, longitude and altitude as values. Then read the data by line using the getline function and create a stringstream object to store the line we read. We get the valid data from the string stream object by splitting the object. Then we have a utility function to help calculate the spherical distance between two locations and draw the line between the two airports.

Given all the data processed, we run several algorithms to assist us to achieve our goal. The first one is BFS, it helps get all the airports as vertices that are connected based on the routes we have and it returns a vector of all such routes. Then, with all the routes and their corresponding distance, we can apply Dijkstra’s algorithm to get the shortest path given two airports as starting and ending points. After all such operations, the function will give a vector contains the airports that we go through, show the airports that we go through, and also return the distance between the two airports. Also, we have a function to get all the shortest path to all airports and store predecessors and distances of routes as vectors.

For the graphics output, first we have a function to mark all the points of airports onto the world map while scaling the coordinates correctly. We used a helper function that converts the longitude and latitude of the airports into (x, y) coordinates by scaling and shifting. The next part is to draw lines between two airports. We learn through an YouTube video to get the method of making lines with correct slope. Also, we go through mp_traversals to learn how to make animation of BFS and Dijkstra’s algorithm.

Then, we find some useful paper online on the how to compute the betweenness centrality. Then we write functions that compute the centrality and sort the airports with a max heap. And then we output the result with different color signatures the different importance of the top airports. For force directed graph, we also read one useful paper on how we can achieve our goal. Then we write some function to calculate the compulsion force, traction force, and updated coordinates of each airport onto the force directed graph. For our final force directed graph, we choose the top central 100 airports using the betweenness centrality function so that the graph doesn’t get too crowded. And also, we choose some important important routes to reflect onto graph.

In all, our project is able to take in inputs of source data files for airports and flight routes, departure airport, destination airport, and output graph and animation in “/landmark/results” folder.

## Observations

* The shortest path between two Airports was not expected to be a straight line between the two airports, but rather often involves a connecting flight to major airports
* When traveling from LIT to TRI, the shortest path will be LIT->ATL->TRI, through ATL.


* After visualizing all the routes, we noticed that Europe and the United States were almost entirely covered by routes. The least sparse routes with a small density of airports locate mostly in domestic areas like Northern Canada, the bottom of South America, Australia, Greenland, and the Angola/Congo region.


