#include <bits/stdc++.h>

using namespace std;

#include "PriorityQueue.hpp"
#include "Graph.hpp"

int main(int argc, char *argv[])
{
    int n, m, u, v;
    double w;
    string type;
    if (argc != 2)
    {
        cout << "Invalid number of arguments!" << endl;
        return 1;
    }
    else
    {
        type = argv[1];
    }
    cout << "Number of vertices: " << endl;
    cin >> n;
    while (n <= 0)
    {
        cout << "Number of vertices must be positive!" << endl;
        cin >> n;
    }
    Graph graph(n, 0);
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
            graph.addEdge(u, v, w);
            graph.addEdge(v, u, w);
            i++;
        }
    }
    graph.print();
    if (type == "-p")
    {
        graph.Prim();
    }
    else
    {
        graph.Kruskal();
    }
    return 0;
}