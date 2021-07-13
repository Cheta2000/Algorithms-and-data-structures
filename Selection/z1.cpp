#include <iostream>
#include <string>
#include <random>
#include <fstream>

using namespace std;

random_device device;
mt19937 generator(device());
uniform_int_distribution<int> dis(0, 1000000);

int switches = 0;
int compares = 0;

// generowanie losowych danych
void randomData(int t[], int n)
{
    for (int i = 0; i < n; i++)
    {
        t[i] = dis(generator);
    }
}

// generowanie danych od 0 do n-1 w losowej kolejnosci
void randomPermutation(int t[], int n)
{
    for (int i = 0; i < n; i++)
    {
        t[i] = i;
    }
    for (int i = 0; i < n; i++)
    {
        int j = 1 + dis(generator) % (n - 1);
        swap(t[i], t[j]);
    }
}

// zamiana dwoch elementow tablicy
void swap(int *a, int *b)
{
    //cerr << "2x switch(swap)" << endl;
    switches += 3;
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

// partycja z wybranym losowo pivotem
int RandPartition(int t[], int start, int end)
{
    // wybieramy losowo indeks z zakresu i ustawiamy go jako pivot
    int index = start + dis(generator) % (end - start + 1);
    int pivot = t[index];
    //cerr<<"Random pivot"<<pivot<<endl;
    int i = start;
    for (int j = start; j <= end; j++)
    {
        //cerr << "Compare" << endl;
        compares++;
        if (t[j] < pivot)
        {
            if (i == index)
            {
                index = j;
            }
            swap(&t[i], &t[j]);
            i++;
        }
    }
    swap(&t[i], &t[index]);
    return i;
}

// partycja z pivotem mediany median
int Partition(int t[], int start, int end, int pivot)
{
    //cerr << "Median pivot: " << pivot << endl;
    int i = start;
    int index;
    // szukamy indeksu pivota
    for (int j = start; j <= end; j++)
    {
        //cerr << "Compare" << endl;
        compares++;
        if (t[j] == pivot)
        {
            index = j;
            break;
        }
    }
    for (int j = start; j <= end; j++)
    {
        //cerr << "Compare" << endl;
        compares++;
        if (t[j] < pivot)
        {
            // jesli zamieniamy cos z pivotem to musimy zmienic tez jego indeks
            if (i == index)
            {
                index = j;
            }
            swap(&t[i], &t[j]);
            i++;
        }
    }
    swap(&t[i], &t[index]);
    return i;
}

// wybor k tej statystyki pozycyjnej na podstawie losowego pivota
int randomizedSelect(int t[], int p, int q, int k)
{
    if (p == q)
    {
        return t[p + k - 1];
    }
    // sprawdzamy statystyke pozycyjna pivota
    int r = RandPartition(t, p, q);
    int s = r - p + 1;
    // jesli to szukana to zwracamy
    if (s == k)
    {
        return t[p + s - 1];
    }
    // jesli jest wieksza niz szukana to szukamy w lewej podtablicy
    if (s > k)
    {
        return randomizedSelect(t, p, r - 1, k);
    }
    // jesli jest mniejsza niz szukana to szukamy statystyki k-s w prawej podtablicy(w lewej mamy juz s)
    else
    {
        return randomizedSelect(t, r + 1, q, k - s);
    }
}

// sortowanie przez wstawianie do sortowanie 5 el tablic w select
void InsertionSort(int t[], int start, int end)
{

    for (int i = start + 1; i <= end; i++)
    {
        int j = i - 1;

        int key = t[i];

        //cerr << "Compare" << endl;
        compares++;
        while (j >= start && key < t[j])
        {
            //cerr << "Switch" << endl;
            switches++;
            t[j + 1] = t[j];
            j--;
            //cerr << "Compare" << endl;
            compares++;
        }

        t[j + 1] = key;
    }
}

// wybor k tej statystyki pozycyjnej na podstawie pivota mediany median
int Select(int t[], int p, int q, int k)
{
    // jesli tablica ma mniej niz 6 elementow sortujemy i zwracamy srodkowy
    if (q - p + 1 <= 5)
    {
        InsertionSort(t, p, q);
        return t[p + k - 1];
    }
    // size mowi nam ile mamy mini tablic
    int size = 0;
    // index mowi gdzie jest mediana w tablicy ktora nie ma 5 elementow
    int index = -1;
    // sortowanie 5 elementowych podtablic i tego co zostanie
    for (int i = p; i <= q; i += 5)
    {
        if (q >= i + 4)
        {
            InsertionSort(t, i, i + 4);
        }
        else
        {
            index = (i + q) / 2;
            InsertionSort(t, i, q);
        }
        size++;
    }

    // tworzymy tablice median
    int med[size];
    for (int i = 0; i < size - 1; i++)
    {
        med[i] = t[p + 5 * i + 2];
    }
    if (index == -1)
    {
        med[size - 1] = t[q - 2];
    }
    else
    {
        med[size - 1] = t[index];
    }
    // pivotem jest mediana z tablicy median
    int pivot = Select(med, 0, size - 1, (size + 1) / 2);
    int r = Partition(t, p, q, pivot);
    int s = r - p + 1;
    if (s == k)
    {
        return t[p + s - 1];
    }
    if (s > k)
    {
        return Select(t, p, r - 1, k);
    }
    else
    {
        return Select(t, r + 1, q, k - s);
    }
}

// select ale ze zmienna iloscia elementow w mini tablicach
// wszystko analogicznie tylko z paremetrem l
int SelectParam(int t[], int p, int q, int k, int l)
{
    if (q - p + 1 <= l)
    {
        InsertionSort(t, p, q);
        return t[p + k - 1];
    }
    int size = 0;
    int index = -1;
    for (int i = p; i <= q; i += l)
    {
        if (q >= i + l - 1)
        {
            InsertionSort(t, i, i + l - 1);
        }
        else
        {
            index = (i + q) / 2;
            InsertionSort(t, i, q);
        }
        size++;
    }

    int med[size];
    for (int i = 0; i < size - 1; i++)
    {
        med[i] = t[p + l * i + l / 2];
    }
    if (index == -1)
    {
        med[size - 1] = t[q - l / 2];
    }
    else
    {
        med[size - 1] = t[index];
    }
    int pivot = SelectParam(med, 0, size - 1, (size + 1) / 2, l);
    int r = Partition(t, p, q, pivot);
    int s = r - p + 1;
    if (s == k)
    {
        return t[p + s - 1];
    }
    if (s > k)
    {
        return SelectParam(t, p, r - 1, k, l);
    }
    else
    {
        return SelectParam(t, r + 1, q, k - s, l);
    }
}

void test1()
{
    ofstream file;
    file.open("selectStats.txt");
    file << "k;Size;Repeat;Data;Algorithm;Compares;Switches" << endl;
    for (int d = 0; d < 2; d++)
    {
        if (d == 0)
        {

            for (int i = 100; i <= 10000; i += 100)
            {
                for (int m = 0; m < 100; m++)
                {

                    int t[i];
                    int cpy[i];

                    randomData(t, i);

                    for (int s = 0; s < 3; s++)
                    {
                        int k;
                        if (s == 0)
                        {
                            file << "small;";
                            k = 50;
                        }
                        if (s == 1)
                        {
                            file << "medium;";
                            k = i / 2;
                        }
                        if (s == 2)
                        {
                            file << "large;";
                            k = i - dis(generator) % (i / 10);
                        }
                        for (int j = 0; j < i; j++)
                        {
                            cpy[j] = t[j];
                        }
                        compares = 0;
                        switches = 0;
                        randomizedSelect(t, 0, i - 1, k);
                        file << i << ";" << m << ";randomNumbers;randomizeSelect;" << compares << ";" << switches << endl;
                        for (int j = 0; j < i; j++)
                        {
                            cpy[j] = t[j];
                        }
                        compares = 0;
                        switches = 0;
                        Select(t, 0, i - 1, k);
                        if (s == 0)
                        {
                            file << "small;";
                        }
                        if (s == 1)
                        {
                            file << "medium;";
                        }
                        if (s == 2)
                        {
                            file << "large;";
                        }
                        file << i << ";" << m << ";randomNumbers;select;" << compares << ";" << switches << endl;
                    }
                }
            }
        }
        else
        {
            {
                for (int i = 100; i <= 10000; i += 100)
                {

                    for (int m = 0; m < 100; m++)
                    {

                        int t[i];
                        int cpy[i];

                        randomPermutation(t, i);

                        for (int s = 0; s < 3; s++)
                        {
                            int k;
                            if (s == 0)
                            {
                                file << "small;";
                                k = 50;
                            }
                            if (s == 1)
                            {
                                file << "medium;";
                                k = i / 2;
                            }
                            if (s == 2)
                            {
                                file << "large;";
                                k = i - dis(generator) % (i / 10);
                            }
                            for (int j = 0; j < i; j++)
                            {
                                cpy[j] = t[j];
                            }
                            compares = 0;
                            switches = 0;
                            randomizedSelect(t, 0, i - 1, k);
                            file << i << ";" << m << ";randomPermutation;randomizeSelect;" << compares << ";" << switches << endl;
                            for (int j = 0; j < i; j++)
                            {
                                cpy[j] = t[j];
                            }
                            compares = 0;
                            switches = 0;
                            Select(t, 0, i - 1, k);
                            if (s == 0)
                            {
                                file << "small;";
                            }
                            if (s == 1)
                            {
                                file << "medium;";
                            }
                            if (s == 2)
                            {
                                file << "large;";
                            }
                            file << i << ";" << m << ";randomPermutation;select;" << compares << ";" << switches << endl;
                        }
                    }
                }
            }
        }
    }
    file.close();
}

void test2()
{
    clock_t begin;
    clock_t end;
    ofstream file;
    file.open("selectStats2.txt");
    file << "k;Size;Repeat;Groups;Data;Compares;Switches;Time" << endl;
    for (int d = 0; d < 2; d++)
    {
        if (d == 0)
        {

            for (int i = 100; i <= 10000; i += 100)
            {
                for (int m = 0; m < 10; m++)
                {

                    int t[i];
                    int cpy[i];
                    randomData(t, i);

                    for (int l = 3; l <= 25; l += 2)
                    {

                        for (int s = 0; s < 3; s++)
                        {
                            int k;
                            if (s == 0)
                            {
                                file << "small;";
                                k = 50;
                            }
                            if (s == 1)
                            {
                                file << "medium;";
                                k = i / 2;
                            }
                            if (s == 2)
                            {
                                file << "large;";
                                k = i - dis(generator) % (i / 10);
                            }
                            int cpy[i];
                            for (int j = 0; j < i; j++)
                            {
                                cpy[j] = t[j];
                            }
                            compares = 0;
                            switches = 0;
                            begin = clock();
                            SelectParam(cpy, 0, i - 1, k, l);
                            end = clock();
                            file << i << ";" << m << ";" << l << ";randomNumbers;" << compares << ";" << switches << ";" << (end - begin) * 1000 / (double)CLOCKS_PER_SEC << endl;
                        }
                    }
                }
            }
        }
        else
        {
            {
                for (int i = 100; i <= 10000; i += 100)
                {

                    for (int m = 0; m < 10; m++)
                    {

                        int t[i];
                        int cpy[i];
                        randomPermutation(t, i);

                        for (int l = 3; l <= 25; l += 2)
                        {

                            for (int s = 0; s < 3; s++)
                            {
                                int k;
                                if (s == 0)
                                {
                                    file << "small;";
                                    k = 50;
                                }
                                if (s == 1)
                                {
                                    file << "medium;";
                                    k = i / 2;
                                }
                                if (s == 2)
                                {
                                    file << "large;";
                                    k = i - dis(generator) % (i / 10);
                                }
                                int cpy[i];
                                for (int j = 0; j < i; j++)
                                {
                                    cpy[j] = t[j];
                                }
                                compares = 0;
                                switches = 0;
                                begin = clock();
                                SelectParam(cpy, 0, i - 1, k, l);
                                end = clock();
                                file << i << ";" << m << ";" << l << ";randomPermutation;" << compares << ";" << switches << ";" << (end - begin) * 1000 / (double)CLOCKS_PER_SEC << endl;
                            }
                        }
                    }
                }
            }
        }
    }
    file.close();
}

// wyniki podstawowego dzialania programu
void score(int t[], int n, int score1, int score2, int k)
{
    cerr << "k: " << k << endl;
    cout << "Array with randomized select: " << endl;
    // wyniki po random selekcie
    for (int i = 0; i < n; i++)
    {
        if (t[i] == score1)
        {
            cout << "[ ";
            cout << t[i];
            cout << " ]" << endl;
        }
        else
        {
            cout << t[i] << endl;
        }
    }
    cout << "Array with median select: " << endl;
    // wyniki po selekcie
    for (int i = 0; i < n; i++)
    {
        if (t[i] == score2)
        {
            cout << "[ ";
            cout << t[i];
            cout << " ]" << endl;
        }
        else
        {
            cout << t[i] << endl;
        }
    }
}

int main(int argc, char *argv[])
{
    int n;
    int k;
    char type;
    int score1, score2;
    if (argc != 2)
    {
        cout << "Incorrect number or arguments\n";
        return 1;
    }
    type = argv[1][1];
    // gdy robimy testy
    if (type == 't')
    {
        //test1();
        test2();
        return 0;
    }
    cout << "Insert size of array: " << endl;
    cin >> n;
    if (n <= 0)
    {
        cout << "Size must be positive";
        return 1;
    }
    cout << "Insert k statistic: " << endl;
    cin >> k;
    int t[n];
    if (k <= 0 || k > n)
    {
        cout << "Invalid k value";
        return 1;
    }
    // gdy chcemy losowe dane
    if (type == 'r')
    {
        randomData(t, n);
        int cpy[n];
        cerr << "Random array: " << endl;
        for (int i = 0; i < n; i++)
        {
            cpy[i] = t[i];
            cerr << t[i] << endl;
        }
        compares=0;
        switches=0;
        score1 = randomizedSelect(t, 0, n - 1, k);
        cerr<<"Compares in RS: "<<compares<<endl;
        cerr<<"Switches in RS: "<<switches<<endl;
        compares=0;
        switches=0;
        score2 = Select(cpy, 0, n - 1, k);
        cerr<<"Compares in S: "<<compares<<endl;
        cerr<<"Switches in S: "<<switches<<endl;
    }
    // gdy chcemy losowa permutacje
    else if (type == 'p')
    {
        randomPermutation(t, n);
        int cpy[n];
        cerr << "Random permutation array: " << endl;
        for (int i = 0; i < n; i++)
        {
            cpy[i] = t[i];
            cerr << t[i] << endl;
        }
        compares=0;
        switches=0;
        score1 = randomizedSelect(t, 0, n - 1, k);
        cerr<<"Compares in RS: "<<compares<<endl;
        cerr<<"Switches in RS: "<<switches<<endl;
        compares=0;
        switches=0;
        score2 = Select(cpy, 0, n - 1, k);
        cerr<<"Compares in S: "<<compares<<endl;
        cerr<<"Switches in S: "<<switches<<endl;
    }
    else
    {
        cout << "Invalid parameter";
        return 1;
    }
    score(t, n, score1, score2, k);

    return 0;
}