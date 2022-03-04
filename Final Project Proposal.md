# **CS 225 Data Structures**
## **Project Proposal (rongw4-yiyanz3-ruoliu2-yongy2)** 
1. **Leading Question**
Provided two cities, our goal is to find the shortest route between these cities’ airports via the landmarks we choose.
Then we would like to draw a map of the world and draw the airports over it, and work on a traversal highlight the path from the starting airport to the ending airport.
2. **Dataset Acquistion and Processing** <br>We propose using the OpenFlights Dataset. We will focus on the Airports and Route subset of this data, which consists of airports information (Airport ID, latitude, longtitude, and altitude) in airports.dat and airlines information (source airport,
In this project, we will use databases from OpenFlights. Since our focus is on the Landmark algorithm, we will focus on the Airports and Routes data files. We will take the IATA code corresponding to the airport as the key of the current node, and compare the data of routes between adjacent nodes to find out whether there is a corresponding route, so as to establish the graph. Meanwhile, the approximate distance of routes between nodes is calculated by latitude and longitude. Find the closest routes from one point to another. Meanwhile, we will filter out the data which are invalid by removing data without an IATA number.
The URL of database which we want to use is https://openflights.org/data.html (Mainly on airports.dat and routes.dat). To be specific:
The URL of dataset:
Airports: https://raw.githubusercontent.com/jpatokal/openflights/master/data/airports.dat
Routes:https://raw.githubusercontent.com/jpatokal/openflights/master/data/routes.dat
3. **Graph Algorithms**  <br>For our graph traversal, we decided to implement BFS using an iterator. Because BFS can be used to find single source shortest path in an unweighted graph and we are able to reach a vertex with minimum number of edges from a source vertex. 
Our input to the iterator constructor would be the starting IATA node, which is a 3-letter IATA code. For example, Aiken Regional Airport is AIK. When we call operator++ to implement, the iterator will update its internal position to a new airport's IATA node until no nodes being left to traverse.The running time is $O(m + n)$, with n is the number of Nodes and m is the number of edges.
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
