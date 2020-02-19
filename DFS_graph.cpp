#include <iostream>
#include <list>
#include <map>
#include <queue>

using namespace std;
template<typename T>	

class Graph{
public:
	int V;
	map<T, list<T>> adjList;
	
	Graph(int v){
		V = v;
	}
	void addEdge(T u, T v, bool biDir=true)
	{
	    adjList[u].push_back(v);
	    if (biDir == true){
		    adjList[v].push_back(u);
        }
    }
    void printGraph(){
        for (auto li : adjList){
		    cout << li.first << "-->";
		    for (auto node: li.second){
			    cout << node << " ";
            }
            cout << endl;
        }
    }

    void bfs(T src)
    {
	    queue<T> q;
	    map<T, bool> visited;
	    map<T,T> parent;
	    // Mark the src vertex as visited...
	    q.push(src);
	    visited[src] = true;
	    parent[src] = src;
	    // Check all the vertices in the queue
	    while(!q.empty())
        {
		    // Get the current vertex and traverse all its neighbors
		    T node  =  q.front();
            q.pop();
		    cout << node << " ";
		    for (auto neighbor: adjList[node])
            {
	        //Now we have to visit the neighbor if it not visited before...[IMP]
		        if (!visited[neighbor])
                {
	                q.push(neighbor);
	                parent[neighbor] = node;
				    visited[neighbor] = true;
                }
		    }
        }
    }

    void dfsHelper(T node, map<T, bool> &visited){
        visited[node] = true;
        cout << node << " " << endl;

        for (auto n_vertex: adjList[node]){
            if (!visited[n_vertex]){
                dfsHelper(n_vertex, visited);
            }
        }
    }

    void dfs(T src){
        map<T, bool> visited;
        dfsHelper(src, visited);
    }
};

int main ()
{
	Graph<string> g(9);
	g.addEdge("English","HTML",false);
    g.addEdge("English","Programming Logic",false);
    g.addEdge("Maths","Programming Logic",false);
    g.addEdge("Programming Logic","HTML",false);
    g.addEdge("Programming Logic","Python",false);
    g.addEdge("Programming Logic","JS",false);
    g.addEdge("Programming Logic","Java",false);
    g.addEdge("Python", "Web Development",false);
    g.addEdge("Java", "Web Development",false);
    g.addEdge("JS", "Web Development",false);
    g.addEdge("HTML", "Css",false);
    g.addEdge("Css", "JS",false);

    g.printGraph();
    //g.bfs(0);
    cout << "*****DFS*****" << endl;
    g.dfs("English");
    return 0;
}
