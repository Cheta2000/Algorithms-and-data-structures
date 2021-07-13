#include <bits/stdc++.h>

using namespace std;

#include "PriorityQueue.hpp"

random_device device;
mt19937 generator(device());
uniform_int_distribution<int> dis(0, 1000);

void commands()
{
    PriorityQueue queue;
    map<string, int>
        operationMap;
    operationMap["insert"] = 1;
    operationMap["empty"] = 2;
    operationMap["top"] = 3;
    operationMap["pop"] = 4;
    operationMap["priority"] = 5;
    operationMap["print"] = 6;
    int n;
    string operation;
    int arg1, arg2;
    int elem;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> operation;
        switch (operationMap[operation])
        {
        case 1:
            cin >> arg1;
            cin >> arg2;
            queue.insert(arg1, arg2);
            break;
        case 2:
            queue.empty();
            break;
        case 3:
            queue.top();
            break;
        case 4:
            elem = queue.pop();
            if (elem != INT_MAX)
            {
                cout << elem << endl;
            }
            else
            {
                cout << "" << endl;
            }
            break;
        case 5:
            cin >> arg1;
            cin >> arg2;
            queue.priority(arg1, arg2);
            break;
        case 6:
            queue.print();
            break;
        default:
            cout << "UNKNOWN OPERATION" << endl;
        }
    }
}

void test()
{
    PriorityQueue queue;
    for (int i = 0; i < 1000; i++)
    {
        queue.insert(dis(generator) % 200, dis(generator) % 100);
        if (i % 20 == 0)
        {
            queue.priority(i, 20);
        }
    }
    //queue.print();
    for (int i = 0; i < 1000; i++)
    {
        //queue.top();
        queue.pop();
    }
}

int main()
{
    commands();
    //test();
    return 0;
}