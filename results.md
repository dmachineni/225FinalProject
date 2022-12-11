# Results

### Algorithms:  

BFS: Breadth-first search is used to traverse the graph, and it does so by visiting each node. This algorithm tells us if there are nodes that are not connected to any other nodes, and if there are multiple connected components. To test BFS, we outputted the number of connected components and airports that were not connected to confirm that the numbers lined up.

Floyd-Warshall: Floyd-Warshall is used to find the shortest path between two given airports. It does so by creating an adjacency matrix that stores the distance between each airport, and then iterating through it to find the minimum possible distance between two airports. To test Floyd-Warshall, we calculated the distance between two airports with the shortest path, and checked that the output matched that number. We also tested that the program calculated distance using longitude and latitude coordinates correctly. 

A* Search: A* Search is used to find the shortest path between two airports. It does so by traveling to the neighboring node that is the shortest distance from the current node, therefore creating a path of shortest immediate distance.  


### Answer to the leading question:  
Our leading question was "what is the shortest route between two given airports?". Our program answers this question by taking in any two airports, and using Floyd-Warshall and A* Search to find the path between the two airports that minimizes the distance traveled. Through this project, we discovered that even though there may be a route between two given airports, it may not always be the most efficient option to fly that route as a mode of travel. For example, there exists a route between O'Hare airport and Midway airport, as these nodes are part of the same connected component on the graph, however it would be much faster to drive from O'Hare to Midway rather than fly the available route. 
