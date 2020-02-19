#include <bits/stdc++.h>
using namespace std;

template<typename T>
class Graph{
public:
    int V;
    unordered_map<T,list<T>> adjList;

    Graph(int v){
        V = v;
    }

    void addEdge(T u, T v, bool biDir=true){
        adjList[u].push_back(v);
        if (biDir){
            adjList[v].push_back(u);
        }
    }

    void printGraph(){
        for (auto i : adjList){
            T node = i.first;
            cout << node << "-->";
            for (auto neigh: adjList[node]){
                cout << neigh << " ";
            }
            cout << endl;
        }
    }

    bool dfsHelper(T node,map<T, bool> &visited, map<T, bool> &inStack){
        int res;
        visited[node] = true;
        inStack[node] = true;

        //Explore the neighbours
        for (auto neigh: adjList[node]){
            //Two things can happen.
            // 1. If the neighour node is not visited and its further branch leads to a cycle then return true.
            // 2. if the neighbour node is found in the stack and also marked as visited.
            if (((!visited[neigh]) && (dfsHelper(neigh, visited, inStack))) || 
                 ((inStack[neigh] == true) && (visited[neigh])))
                return true;
        }
        inStack[node] = false;
        return false;
    }
    void detectCycle(T node){
        map<T, bool> visited;
        map<T, bool> inStack;
        bool res;

        for (auto i: adjList){
            T node = i.first;
            inStack[i.first] = false;
            if (!visited[node]){
                res = dfsHelper(node, visited, inStack);
                if (res)
                    cout << "Cycle found in the graph" << endl;
                else
                    cout << "Cycle not found in the graph" << endl;
            }
        }
    }
};

int main() {
    Graph<int> g(6);

    g.addEdge(0,1,false);
    g.addEdge(0,2,false);
    g.addEdge(1,5,false);
    g.addEdge(4,5,false);
    g.addEdge(2,4,false);
    g.addEdge(2,3,false);
    g.addEdge(3,0,false);

    g.printGraph();

    g.detectCycle(0);
    return 0;
}
