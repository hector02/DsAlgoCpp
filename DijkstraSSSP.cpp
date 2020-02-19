#include <bits/stdc++.h>
using namespace std;

template <typename T>
class Graph {
public:
    int V;
    map<T,list<pair<T, int>>> adjList;
    Graph(int v){
        V = v;
    }

    void addEdge(T u, T v, int dist, bool biDir=true){
        adjList[u].push_back(make_pair(v,dist));
        if (biDir){
            adjList[v].push_back(make_pair(u,dist));
        }
    }

    void printGraph(){
        for (auto i: adjList){
            T node = i.first;
            cout << node << " --> ";
            for (auto j: adjList[node]){
                cout << "(" << j.first << ", " << j.second << ")" << " ";
            }
            cout << endl;
        }
    }
    void dijkstraSSSP(T src){
        map<T, int> dist;
        set<pair<int, T>> s;
        //Initialize all the distance to be infinity.
        for (auto i: adjList){
            dist[i.first] = INT_MAX;
        }
        dist[src] = 0;
        // insert this node in the set
        s.insert(make_pair(0,src));
        while(!s.empty()){
            //Now we have to pick the FRONT element as we know that distance 
            //would be minimum because set stores the element in the sorted order. 
            auto p = *(s.begin()); //get the pair which is in front of the set.
            //Get both the values
            //Note: first = node distance, second = node
            T node = p.second;
            int nodeDist = p.first;
            s.erase(s.begin());

            //Explore the neighbours and go to the nearest neighbour.
            for (auto childPair: adjList[node]){
                T neigh = childPair.first;
                if (nodeDist + childPair.second < dist[neigh]){
                    //We have to delete the old pair in the dist array
                    //and insert the new pair because there is no operation in
                    //the set which updates the value directly.
                    auto f = s.find(make_pair(dist[neigh],neigh));
                    //if found, erase it as we have to insert the new value.
                    //f is an iterator returned if found 
                    if (f != s.end()){
                        s.erase(f);
                    }
                    dist[neigh] = nodeDist + childPair.second;

                    s.insert(make_pair(dist[neigh], neigh));
                }
            }
        }

        //Now lets print the distances to all the other nodes
        for (auto d: dist){
            if (d.first != src)
                cout << src << " --> " << d.first << " = " << d.second << endl;
        }
    }
    
};
int main() {
    Graph<string> g(6);
    g.addEdge("Amritsar","Delhi",1);
    g.addEdge("Amritsar","Jaipur",4);
    g.addEdge("Delhi","Jaipur",2);
    g.addEdge("Delhi","Agra",1);
    g.addEdge("Agra","Bhopal",2);
    g.addEdge("Bhopal","Mumbai",3);
    g.addEdge("Mumbai","Jaipur",8);

    //g.printGraph();
    g.dijkstraSSSP("Amritsar");
    return 0;
}
