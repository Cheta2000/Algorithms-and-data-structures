#include <bits/stdc++.h>

using namespace std;

#include "PriorityQueue.hpp"
#include "Graph.hpp"

int main()
{
    int n, m, u, v, start;
    double w;
    cout << "Number of vertices: " << endl;
    cin >> n;
    while (n <= 0)
    {
        cout << "Number of vertices must be positive!" << endl;
        cin >> n;
    }
    Graph graph(n,0);
    cout << "Number of edges: " << endl;
    cin >> m;
    while (m < 0)
    {
        cout << "Number of edges cannot be negative!" << endl;
        cin >> m;
    }
    cout << "Edges: " << endl;
    int i = 0;
    while (i < m)
    {
        cin >> u >> v >> w;
        if (w < 0)
        {
            cout << "Weight cannot be negative!" << endl;
        }
        else if (u < 0 || u >= n || v < 0 || v >= n)
        {
            cout << "Invalid range!" << endl;
        }
        else
        {
            graph.addEdge(u,v,w);
            i++;
        }
    }
    graph.print();
    cout << "Start: " << endl;
    cin >> start;
    while (start < 0 || start >= n)
    {
        cout << "Invalid range!" << endl;
        cin >> start;
    }
    clock_t begin = clock();
    graph.Dijkstra(start);
    clock_t end=clock();
    cerr<<"Time: "<<(end - begin) * 1000 / (double)CLOCKS_PER_SEC<<endl;
    return 0;
}