// krawedz do sasiada (do kogo, waga)
struct neighbour
{
    int dest;
    double weight;
};

// krawedz
struct edge
{
    int src;
    int dest;
    double weight;
};

// wezel (do Prima)
struct node
{
    int parent;
    int rank;
};

// wierzcholek zawiera liste sasiadow
class Verticle
{
public:
    list<neighbour> neighbours;
};

// graf
class Graph
{
    Verticle *verticles;
    double **matrix;
    int size;
    int type;

public:
    Graph(int n, int type)
    {
        // odpowiednio dobieramy sposob zapisu wierzcholkow
        // dla grafow pelnych macierz
        size = n;
        this->type = type;
        if (type == 0)
        {
            verticles = new Verticle[n];
        }
        else
        {
            matrix = new double *[n];
            for (int i = 0; i < n; i++)
            {
                matrix[i] = new double[n];
            }
        }
    }
    ~Graph()
    {
        if (type == 0)
        {
            delete[] verticles;
        }
        else
        {
            for (int i = 0; i < size; i++)
            {
                delete[] matrix[i];
            }
            delete[] matrix;
        }
    }

private:
    // sprawdzenie kto jest korzeniem drzewa w ktorym jest v
    int findSet(node nodes[], int v)
    {
        // ciagle przeskakujemy na rodzica
        if (nodes[v].parent != v)
        {
            nodes[v].parent = findSet(nodes, nodes[v].parent);
        }
        return nodes[v].parent;
    }

    // laczenie drzew
    void treeUnion(node nodes[], int u, int v)
    {
        int xroot = findSet(nodes, u);
        int yroot = findSet(nodes, v);
        // korzen drzewa o wyzszym rank staje sie nowym korzeniem
        if (nodes[xroot].rank < nodes[yroot].rank)
            nodes[xroot].parent = yroot;
        else if (nodes[xroot].rank > nodes[yroot].rank)
            nodes[yroot].parent = xroot;
        // jesli rank sa takie same, bierzemy dowolny korzen i zwiekszamy rank
        else
        {
            nodes[yroot].parent = xroot;
            nodes[xroot].rank++;
        }
    }

    // wypisywanie minimalnego drzewa rozpinajacego
    void write(list<edge> tree)
    {
        double sum = 0;
        list<edge>::iterator it;
        for (it = tree.begin(); it != tree.end(); it++)
        {
            sum += it->weight;
            if (it->src < it->dest)
            {
                cout << it->src << " " << it->dest << " " << it->weight << endl;
            }
            else
            {
                cout << it->dest << " " << it->src << " " << it->weight << endl;
            }
        }
        cout << "Weight: " << sum << endl;
    }

    // przechodzenie zachlanne
    void greedyWalk(int start)
    {
        clock_t begin = clock();
        bool visited[size];
        double cost = 0;
        int counter = 0;
        for (int i = 0; i < size; i++)
        {
            visited[i] = false;
        }
        cerr << start << " ";
        while (counter != size - 1)
        {
            visited[start] = true;
            double min = DBL_MAX;
            int index = 0;
            for (int i = 0; i < size; i++)
            {
                // wybieramy nieodwiedzony wierzcholek, do ktorego mozemy sie dostac najmniejszym kosztem
                if (i != start && visited[i] == false)
                {
                    if (matrix[start][i] < min)
                    {
                        min = matrix[start][i];
                        index = i;
                    }
                }
            }
            cost += matrix[start][index];
            start = index;
            cerr << start << " ";
            counter++;
        }
        clock_t end = clock();
        cout << endl
             << counter << " " << cost << " " << sizeof(visited) + sizeof(int) + sizeof(double) << " " << (end - begin) * 1000 / (double)CLOCKS_PER_SEC << endl;
    }

    // przechodzenie w oparciu o cykl hamiltona
    void Hamilton(int start)
    {
        clock_t begin = clock();
        // tworzymy minimalne drzewo rozpinajce
        //list<edge> tree = KruskalMatrix();
        list<edge> tree = PrimMatrix();
        Verticle *tmpVerticles = new Verticle[size];
        list<edge>::iterator it;
        // przepisujemy je aby bylo latwiej korzystac
        for (it = tree.begin(); it != tree.end(); it++)
        {
            neighbour myNeighbour;
            myNeighbour.dest = it->dest;
            myNeighbour.weight = it->weight;
            tmpVerticles[it->src].neighbours.push_front(myNeighbour);
            myNeighbour.dest = it->src;
            myNeighbour.weight = it->weight;
            tmpVerticles[it->dest].neighbours.push_front(myNeighbour);
        }
        bool visited[size];
        for (int i = 0; i < size; i++)
        {
            visited[i] = false;
        }
        double weight = 0;
        int steps = 0;
        explore(tmpVerticles, 0, visited, &steps, &weight);
        clock_t end = clock();
        cout << endl
             << steps << " " << weight << " " << sizeof(list<edge>) * tree.size() + sizeof(visited) << " " << (end - begin) * 1000 / (double)CLOCKS_PER_SEC << endl;
    }

    // eksploracja grafu
    void explore(Verticle tmpVerticles[], int v, bool visited[], int *steps, double *weight)
    {
        // oznaczamy wierzcholek jako odwiedzony
        visited[v] = true;
        cerr << v << " ";
        list<neighbour>::iterator it;
        for (it = tmpVerticles[v].neighbours.begin(); it != tmpVerticles[v].neighbours.end(); it++)
        {
            // rekurencyjnie idziemy do wierzcholka do ktorego da sie dojsc z v i jeszcze w nim nie bylismy
            if (visited[it->dest] == false)
            {
                (*steps)++;
                *weight += it->weight;
                explore(tmpVerticles, it->dest, visited, steps, weight);
            }
        }
    }

public:
    // dodawanie krawedzi
    void addEdge(int src, int dest, double weight)
    {
        neighbour newNeighbour;
        newNeighbour.dest = dest;
        newNeighbour.weight = weight;
        verticles[src].neighbours.push_back(newNeighbour);
    }

    // wypisywanie grafu
    void print()
    {
        cout << "GRAPH:" << endl;
        if (type == 0)
        {
            for (int i = 0; i < size; i++)
            {
                cout << i << "=>";
                list<neighbour>::iterator it;
                for (it = verticles[i].neighbours.begin(); it != verticles[i].neighbours.end(); it++)
                {
                    cout << it->dest << "(" << it->weight << ") ";
                }
                cout << endl;
            }
        }
        else
        {
            for (int i = 0; i < size; i++)
            {
                for (int j = 0; j < size; j++)
                {
                    cout << matrix[i][j] << " ";
                }
                cout << endl;
            }
        }
    }

    // szukanie najkrotszej sciezki od start do reszty
    void Dijkstra(int start)
    {
        PriorityQueue queue;
        element *heap = new element[size];
        double *dist = new double[size];
        int *prev = new int[size];
        double *edge = new double[size];
        for (int i = 0; i < size; i++)
        {
            heap[i].value = i;
            heap[i].priority = INT_MAX;
            dist[i] = DBL_MAX;
            prev[i] = -1;
            edge[i] = -1.0;
        }
        dist[start] = 0;
        heap[start].priority = 0;
        // tworzymy kolejke priorytetowa
        // kluczem jest wierzcholek
        // priorytetem jest kosz dotarcia do niego
        queue.buildHeap(heap, size);
        while (!queue.empty())
        {
            // sciagamy "najblizszy" wierzcholek
            int nearest = queue.pop();
            list<neighbour>::iterator it;
            for (it = verticles[nearest].neighbours.begin(); it != verticles[nearest].neighbours.end(); it++)
            {
                // jesli do sasiada sciagnietego wierzcholka mozemy dojsc szybciej przez sciagniety wierzcholek
                if (dist[it->dest] > dist[nearest] + it->weight)
                {
                    // ustawiamy nowe dystanse i poprzednikow
                    dist[it->dest] = dist[nearest] + it->weight;
                    prev[it->dest] = nearest;
                    edge[it->dest] = it->weight;
                    // zmienil sie tez priorytet(koszt) sasiada
                    queue.priority(it->dest, dist[it->dest]);
                }
            }
        }
        // wypisywanie wynikow
        cout << "Results:" << endl;
        for (int j = 0; j < size; j++)
        {
            cout << j << ": " << dist[j] << endl;
            int vert = j;
            list<int> route;
            list<double> cost;
            while (vert != -1)
            {
                route.push_front(vert);
                cost.push_front(edge[vert]);
                vert = prev[vert];
            }
            list<int>::iterator it;
            for (it = route.begin(); it != route.end(); it++)
            {
                cerr << *it;
                if (cost.front() == -1)
                {
                    cerr << " ";
                }
                else
                {
                    cerr << "(" << cost.front() << ") ";
                }
                cost.pop_front();
            }
            cout << endl;
        }
        delete[] heap;
        delete[] dist;
        delete[] prev;
        delete[] edge;
    }

    // tworzenie min drzewa rozpinajacego
    void Kruskal()
    {
        list<edge> tree;
        node *nodes = new node[size];
        element *heap = new element[size * size];
        pair<int, int> *edges = new pair<int, int>[size * size];
        PriorityQueue queue;
        // na pocazatku mamy size pustych drzew
        for (int i = 0; i < size; i++)
        {
            nodes[i].parent = i;
            nodes[i].rank = 0;
        }
        int counter = 0;
        // tworzymy kolejke priorytetowa
        // klucz to index tablicy edges, ktora zawiera pare (u,v)
        // priorytet to waga krawedzi miedzy ta para
        for (int i = 0; i < size; i++)
        {
            list<neighbour>::iterator it;
            for (it = verticles[i].neighbours.begin(); it != verticles[i].neighbours.end(); it++)
            {
                edges[counter] = make_pair(i, it->dest);
                heap[counter].value = counter;
                heap[counter].priority = it->weight;
                counter++;
            }
        }
        queue.buildHeap(heap, counter);
        while (!(queue.empty()))
        {
            // sciagamy "najtansza" krawedz
            int index = queue.pop();
            int u = edges[index].first;
            int v = edges[index].second;
            // jesli wierzcholki ktore laczy nie sa polaczone
            if (findSet(nodes, u) != findSet(nodes, v))
            {
                // dodajemy ta krawedz do drzewa rozpinajacego
                edge treeEdge;
                treeEdge.src = u;
                treeEdge.dest = v;
                treeEdge.weight = heap[index].priority;
                tree.push_back(treeEdge);
                // laczymy dwa drzewa w jedno
                treeUnion(nodes, u, v);
            }
        }
        delete[] heap;
        delete[] edges;
        delete[] nodes;
        write(tree);
    }

    // to samo dla reprezentacji macierzowej
    list<edge> KruskalMatrix()
    {
        list<edge> tree;
        node *nodes = new node[size];
        element *heap = new element[size * size];
        pair<int, int> *edges = new pair<int, int>[size * size];
        PriorityQueue queue;
        for (int i = 0; i < size; i++)
        {
            nodes[i].parent = i;
            nodes[i].rank = 0;
        }
        int counter = 0;

        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                edges[counter] = make_pair(i, j);
                heap[counter].value = counter;
                heap[counter].priority = matrix[i][j];
                counter++;
            }
        }
        cout << counter << endl;
        queue.buildHeap(heap, counter);
        while (!(queue.empty()))
        {
            int index = queue.pop();
            int u = edges[index].first;
            int v = edges[index].second;
            if (findSet(nodes, u) != findSet(nodes, v))
            {
                edge treeEdge;
                treeEdge.src = u;
                treeEdge.dest = v;
                treeEdge.weight = heap[index].priority;
                tree.push_back(treeEdge);
                treeUnion(nodes, u, v);
            }
        }
        //write(tree);
        delete[] heap;
        delete[] edges;
        delete[] nodes;
        return tree;
    }

    // tworzenie min drzewa rozpinajacego
    // podobne do dijkstry
    void Prim()
    {
        list<edge> tree;
        PriorityQueue queue;
        element heap[size];
        bool visited[size];
        int parents[size];
        // budujemy kolejke priorytetowa
        // kluczem jest wierzcholek
        // priorytetem koszt dotarcia do niego
        for (int i = 0; i < size; i++)
        {
            heap[i].priority = INT_MAX;
            heap[i].value = i;
            visited[i] = false;
            parents[i] = -1;
        }
        heap[0].priority = 0;
        queue.buildHeap(heap, size);
        while (!queue.empty())
        {
            int u = queue.pop();
            // ustawiamy wierzcholek na odwiedzony
            visited[u] = true;
            if (u != 0)
            {
                // jesli dalo sie do niego dotrzec
                if (parents[u] >= 0)
                {
                    // dodajemy do drzewa rozpinajacego "najtansza" krawedz (z wierzcholka parent, przez niego jest najkrotsza trasa)
                    edge treeEdge;
                    treeEdge.src = u;
                    treeEdge.dest = parents[u];
                    treeEdge.weight = heap[u].priority;
                    tree.push_back(treeEdge);
                }
            }
            // przechodzimy po sasiadach
            list<neighbour>::iterator it;
            for (it = verticles[u].neighbours.begin(); it != verticles[u].neighbours.end(); it++)
            {
                // jesli mamy nieodwiedzonego sasiada i droga przez u jest tansza niz do tej pory
                if (visited[it->dest] == false && it->weight < heap[it->dest].priority)
                {
                    heap[it->dest].priority = it->weight;
                    // zmienil sie priorytet i poprzednik
                    queue.priority(it->dest, it->weight);
                    parents[it->dest] = u;
                }
            }
        }
        write(tree);
    }

    // to samo dla reprezentacji macierzowej
    list<edge> PrimMatrix()
    {
        list<edge> tree;
        PriorityQueue queue;
        element heap[size];
        bool visited[size];
        int parents[size];
        for (int i = 0; i < size; i++)
        {
            heap[i].priority = INT_MAX;
            heap[i].value = i;
            visited[i] = false;
            parents[i] = -1;
        }
        heap[0].priority = 0;
        queue.buildHeap(heap, size);
        while (!queue.empty())
        {
            int u = queue.pop();
            visited[u] = true;
            if (u != 0)
            {
                if (parents[u] >= 0)
                {
                    edge treeEdge;
                    treeEdge.src = u;
                    treeEdge.dest = parents[u];
                    treeEdge.weight = heap[u].priority;
                    tree.push_back(treeEdge);
                }
            }
            for (int j = 0; j < size; j++)
            {
                if (visited[j] == false && matrix[u][j] < heap[j].priority)
                {
                    heap[j].priority = matrix[u][j];
                    queue.priority(j, matrix[u][j]);
                    parents[j] = u;
                }
            }
        }
        //write(tree);
        return tree;
    }

    // losowy graf pelny
    void randomFullGraph()
    {
        random_device device;
        mt19937 generator(device());
        uniform_real_distribution<double> dis(0, size);
        for (int i = 0; i < size; i++)
        {
            for (int j = i; j < size; j++)
            {
                double weight = dis(generator);
                matrix[i][j] = weight;
                matrix[j][i] = weight;
            }
        }
    }

    // graf pelny spelniajcy nierownosc trojkata
    void traingleFullGraph()
    {
        random_device device;
        mt19937 generator(device());
        uniform_real_distribution<double> dis(3, 5);
        for (int i = 0; i < size; i++)
        {
            for (int j = i; j < size; j++)
            {
                double weight = dis(generator);
                matrix[i][j] = weight;
                matrix[j][i] = weight;
            }
        }
    }

    // przechodzenie po grafie
    void walking()
    {
        cout << "Results:" << endl;
        random_device device;
        mt19937 generator(device());
        uniform_int_distribution<int> dis(0, size - 1);
        int start = dis(generator);
        cout << "RANDOM" << endl;
        simpleRandomWalk(start);
        cout << "GREEDY" << endl;
        greedyWalk(start);
        cout << "HAMILTON" << endl;
        Hamilton(start);
    }

    // losowe przechodzenie po grafie
    pair<int, int> simpleRandomWalk(int start)
    {
        clock_t begin = clock();
        random_device device;
        mt19937 generator(device());
        uniform_int_distribution<int> dis(0, size - 1);
        bool visited[size];
        int counter = 0;
        int steps = 0;
        double cost = 0;
        for (int i = 0; i < size; i++)
        {
            visited[i] = false;
        }
        visited[start] = true;
        cerr << start << " ";
        // dopoki nie odwiedzimy wszytskich wierzcholkow
        while (counter != size - 1)
        {

            int from = start;
            // losujemy kolejna krawedz
            start = dis(generator);
            steps++;
            // jesli jest nieodwiedzona idziemy
            if (visited[start] == false)
            {
                visited[start] = true;
                counter++;
            }
            cerr << start << " ";
            cost += matrix[from][start];
        }
        clock_t end = clock();
        cout << endl
             << steps << " " << cost << " " << sizeof(visited) + sizeof(int) << " " << (end - begin) * 1000 / (double)CLOCKS_PER_SEC << endl;
        return make_pair(steps, cost);
    }
};