#pragma once

#include <map>
#include "templatevector.h"
#include "graph.h"
#include <vector>

using namespace std;

struct DijkstraData {
	std::map<Node*,float> dist;
	std::map<Node*,Node*> previous;
};

Node * vertexInQwithMinDist(TemplateVector<Node*> & Q, DijkstraData * r) {
	Node * minNode = Q[0], * n;
	float minDist = r->dist[minNode], dist;
	for(int i = 1; i < (signed)Q.size(); ++i) {
		n = Q[i];
		dist = r->dist[n];
		if(dist < minDist) {
			minNode = n;
			r->dist[minNode];
		}
	}
	return minNode;
}

// algorithm from http://en.wikipedia.org/wiki/Dijkstra's_algorithm
DijkstraData * Dijkstra(vector<Node> & Graph, Node * source) {	// 1  function Dijkstra(Graph, source):
	DijkstraData * r = new DijkstraData;
	TemplateVector<Node*> Q;
	r->dist[source] = 0;					// 2      dist[source]  := 0                     // Distance from source to source
	for(int i = 0; i < (signed)Graph.size(); ++i) {	// 3      for each vertex v in Graph:            // Initializations
		Node * v = &Graph[i];
		if(v != source) {			// 4          if v != source
			r->dist[v] = FLT_MAX;	// 5              dist[v]  := infinity           // Unknown distance function from source to v
			r->previous[v] = 0;		// 6              previous[v]  := undefined      // Previous node in optimal path from source
		}							// 7          end if 
		Q.add(v);					// 8          add v to Q                         // All nodes initially in Q
	}								// 9      end for
	while(Q.size() > 0) {			//11      while Q is not empty:                  // The main loop
		Node * u = vertexInQwithMinDist(Q, r);		//12          u := vertex in Q with min dist[u]  // Source node in first case
		Q.removeData(u);							//13          remove u from Q 		
		for(int i = 0; i < (signed)u->edges.size(); ++i) {	//15          for each neighbor v of u:           // where v has not yet been removed from Q.
			Node * v = u->edges[i].to;
			float alt =r->dist[u]+u->edges[i].cost;	//16              alt := dist[u] + length(u, v)
			if(alt < r->dist[v]) {					//17              if alt < dist[v]:               // A shorter path to v has been found
				r->dist[v] = alt;					//18                  dist[v]  := alt 
				r->previous[v] = u;					//19                  previous[v]  := u 
			}										//20              end if
		}											//21          end for
	}								//22      end while
	return r;						//23      return dist[], previous[]
}									//24  end function
