#define SIZE 10000000


// element kolejki, wartosc i priorytet
struct element
{
    int value;
    double priority;
};

class PriorityQueue
{
    element *queue = new element[SIZE];
    int size;

private:
    // zwracanie rodzica, lewego i prawego syna (jesli istnieja)
    int parent(int i)
    {
        return (i - 1) / 2;
    }
    int left(int i)
    {
        int child = 2 * i + 1;
        if (child < size)
        {
            return child;
        }
        else
        {
            return i;
        }
    }
    int right(int i)
    {
        int child = 2 * i + 2;
        if (child < size)
        {
            return child;
        }
        else
        {
            return i;
        }
    }
    int minIndex(int indexes[], int n)
    {
        int index = indexes[0];
        double min = queue[index].priority;
        for (int i = 1; i < n; i++)
        {
            int newIndex = indexes[i];
            if (queue[newIndex].priority < min)
            {
                min = queue[newIndex].priority;
                index = newIndex;
            }
        }
        return index;
    }

    void swap(element *a, element *b)
    {
        element tmp = *a;
        *a = *b;
        *b = tmp;
    }

    // przywracanie wlasnosco kopca
    void heapify(int i)
    {
        int indexes[3] = {i, left(i), right(i)};
        int smallest = minIndex(indexes, 3);
        // jesli najmniejszy z i i synow i nie jest i to zamieniamy i z najmniejszym i wykonujemy to samo na zamienionym
        if (smallest != i)
        {
            swap(&queue[i], &queue[smallest]);
            heapify(smallest);
        }
    }

public:
    PriorityQueue()
    {
        size = 0;
    }

    ~PriorityQueue()
    {
        delete[] queue;
    }

    // wstawianie do kolejki
    void insert(int value, double priority)
    {
        size++;
        int i = size - 1;
        // szukamy miejsca na nasz priorytet
        while (i > 0 && queue[parent(i)].priority > priority)
        {
            queue[i] = queue[parent(i)];
            // przechodzimy na rodzica
            i = parent(i);
        }
        queue[i].value = value;
        queue[i].priority = priority;
    }
    // czy kolejka jest pusta
    bool empty()
    {
        if (size == 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    // pierwsza wartosc w kolejce
    void top()
    {
        if (!empty())
        {
            cout << queue[0].value << endl;
        }
        else
        {
            cout << "" << endl;
        }
    }
    // zrzucenie pierwszej wartosci z kolejki
    int pop()
    {
        if (!empty())
        {
            // zamienamy element z ostatnim i przywracamy wlasnosc kopca
            //int max=queue[0].priority;
            int max = queue[0].value;
            queue[0] = queue[size - 1];
            size--;
            heapify(0);
            //cout << max << endl;
            return max;
        }
        else
        {
            return INT_MAX;
            //cout << "" << endl;
        }
    }
    // zmiana priorytetu elementow o danej wartosci
    void priority(int value, double newPriority)
    {
        for (int i = 0; i < size; i++)
        {
            // jesli znajdziemy taki element
            if (queue[i].value == value)
            {
                if (queue[i].priority > newPriority)
                {
                    // szukamy nowego miejsca dla niego jak w insert
                    int j = i;
                    while (j > 0 && queue[parent(j)].priority > newPriority)
                    {
                        queue[j] = queue[parent(j)];
                        j = parent(j);
                    }
                    // zmieniamy parametry
                    queue[j].value = value;
                    queue[j].priority = newPriority;
                }
            }
        }
    }
    // wypisanie kolejki
    void print()
    {
        for (int i = 0; i < size; i++)
        {
            cout << queue[i].value << ": " << queue[i].priority << endl;
        }
    }
    // budowanie kopca z tablicy
    void buildHeap(element heap[], int n)
    {
        size = n;
        // dodajemy wszystkie elementy
        for (int i = 0; i < size; i++)
        {
            queue[i].value = heap[i].value;
            queue[i].priority = heap[i].priority;
        }
        // naprawiamy wlasnosc kopca na nielisciach
        for (int i = (n / 2) - 1; i >= 0; i--)
        {
            heapify(i);
        }
    }
};