#include <bits/stdc++.h>

using namespace std;

#include "PriorityQueue.hpp"
#include "Graph.hpp"

void test()
{
    ofstream file;
    file.open("randomWalkResults.txt");
    file << "size;avgSteps;avgCost" << endl;
    for (int i = 100; i <= 10000; i += 100)
    {
        int steps = 0;
        double cost = 0;
        Graph graph(i, 1);
        graph.traingleFullGraph();
        for (int k = 0; k < 20; k++)
        {
            pair<int, int> score = graph.simpleRandomWalk(0);
            steps += score.first;
            cost += score.second;
        }
        file << i << ";" << steps / 20 << ";" << cost / 20 << endl;
    }
    file.close();
}

int main(int argc, char *argv[])
{
    int n, u, v;
    double w;
    cout << "Number of vertices: " << endl;
    cin >> n;
    while (n <= 0)
    {
        cout << "Number of vertices must be positive!" << endl;
        cin >> n;
    }
    Graph graph(n, 1);
    //graph.randomFullGraph();
    graph.traingleFullGraph();
    graph.print();
    graph.walking();
    //test();
    return 0;
}