#include <iostream>
#include <random>
#include <fstream>

using namespace std;

random_device device;
mt19937 generator(device());
uniform_int_distribution<int> dis(0, 100000);

int comp;

void swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

// szukanie min w tablicy, zwraca wartosc i indeks
// do worst case w partition
int findMin(int t[], int start, int end, int *index)
{
    int min = t[start];
    for (int i = start + 1; i <= end; i++)
    {
        if (t[i] < min)
        {
            min = t[i];
            *index = i;
        }
    }
    return min;
}


// to samo ale dla maxa, do DPQS
int findMax(int t[], int start, int end, int *index)
{
    int max = t[start];
    for (int i = start + 1; i <= end; i++)
    {
        if (t[i] > max)
        {
            max = t[i];
            *index = i;
        }
    }
    return max;
}

int Partition(int t[], int start, int end, int pivot)
{
    int index = end;
    int i = start;

    //opcja gdy nie wybieramy pivota
    if (pivot == -1)
    {
        //pivot = t[index];
        // do WORST CASE
        pivot = findMin(t, start, end, &index);
    }
    // gdy mamy wybranego pivota
    else
    {
        for (int j = start; j <= end; j++)
        {
            comp++;
            if (t[j] == pivot)
            {
                index = j;
                break;
            }
        }
    }
    for (int j = start; j <= end; j++)
    {
        comp++;
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

int Partition2(int t[], int start, int end, int *secondPart, int pivot)
{

    int s = 0;
    int l = 0;
    int i = start + 1;
    int j = i;
    int pivotS;
    int pivotL;
    // opcja WORST CASE
    if (pivot == -1)
    {
        int index1=start;
        int index2=end;
        // pivoty to min i max
        pivotS = findMin(t, start, end, &index1);
        pivotL = findMax(t, start, end, &index2);
        // ustawiamy je na start i end, zeby dostosowac do reszty algorytmu
        swap(&t[index1], &t[start]);
        swap(&t[index2], &t[end]);
    }
    // normalnie pivoty to pierwszy i ostatni
    else
    {
        comp++;
        if (t[start] > t[end])
        {
            swap(&t[start], &t[end]);
        }
        pivotS = t[start];
        pivotL = t[end];
    }
    while (j <= *secondPart)
    {
        if (l <= s)
        {
            comp++;
            if (t[j] < pivotS)
            {
                swap(&t[j], &t[i]);
                i++;
                s++;
                j++;
            }
            else if (t[j] >= pivotL)
            {
                comp++;
                while (*secondPart > j && t[*secondPart] >= pivotL)
                {
                    (*secondPart)--;
                    l++;
                    comp++;
                }
                swap(&t[*secondPart], &t[j]);
                (*secondPart)--;
                l++;
                comp++;
            }
            else
            {
                comp++;
                j++;
            }
        }
        else
        {
            comp++;
            if (t[j] >= pivotL)
            {
                comp++;
                while (*secondPart > j && t[*secondPart] >= pivotL)
                {
                    (*secondPart)--;
                    l++;
                    comp++;
                }
                swap(&t[*secondPart], &t[j]);
                (*secondPart)--;
                l++;
            }
            else if (t[j] < pivotS)
            {
                swap(&t[j], &t[i]);
                i++;
                s++;
                j++;
                comp++;
            }
            else
            {
                j++;
                comp++;
            }
        }
    }

    swap(&t[start], &t[i - 1]);
    swap(&t[end], &t[(*secondPart) + 1]);
    (*secondPart)++;
    return i - 1;
}

void InsertionSort(int t[], int start, int end)
{

    for (int i = start + 1; i <= end; i++)
    {
        int j = i - 1;

        int key = t[i];

        comp++;
        while (j >= start && key < t[j])
        {

            t[j + 1] = t[j];
            j--;
            comp++;
        }

        t[j + 1] = key;
    }
}

int Select(int t[], int p, int q, int k)
{
    if (q - p + 1 <= 5)
    {
        InsertionSort(t, p, q);
        return t[p + k - 1];
    }
    int size = 0;
    int index = -1;
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

// zwykly quick sort
void QuickSort(int t[], int start, int end)
{
    if (end <= start)
    {
        return;
    }
    int part = Partition(t, start, end, -1);
    QuickSort(t, start, part - 1);
    QuickSort(t, part + 1, end);
}

// quick sort z selectem
void QuickSelectSort(int t[], int start, int end)
{
    if (end <= start)
    {
        return;
    }
    // pivot to mediana
    int pivot = Select(t, start, end, (end - start + 1) / 2);
    int part;
    // od razu po selekcie mamy zrobiona partycje
    // szukamy indeksu pivota aby podzielic na dwie tablice
    for (int i = start; i <= end; i++)
    {
        comp++;
        if (t[i] == pivot)
        {
            part = i;
        }
    }
    QuickSelectSort(t, start, part - 1);
    QuickSelectSort(t, part + 1, end);
}


// zwykly dpqs
void DualPivotQuickSort(int t[], int start, int end)
{
    if (end <= start)
    {
        return;
    }
    int secondPart = end - 1;
    int firstPart = Partition2(t, start, end, &secondPart, -1);
    DualPivotQuickSort(t, start, firstPart - 1);
    DualPivotQuickSort(t, firstPart + 1, secondPart - 1);
    DualPivotQuickSort(t, secondPart + 1, end);
}

// dpqs z selectem
void DualPivotQuickSelectSort(int t[], int start, int end)
{
    if (end <= start)
    {
        return;
    }
    int part1, part2;
    // najpierw partycja w stosunku do elementu w 1/3 wielkosci
    int pivotS = Select(t, start, end, 1 + (end - start) / 3);
    for (int i = start; i <= end; i++)
    {
        comp++;
        if (t[i] == pivotS)
        {
            part1 = i;
            break;
        }
    }
    // potem partycja na pozostalej czesci tablicy wobec drugiego pivota, mediany reszty tablicy, czyli 2/3 calej tablicy
    int pivotL = Select(t, part1 + 1, end, (end - part1 + 2) / 2);
    for (int i = part1 + 1; i <= end; i++)
    {
        comp++;
        if (t[i] == pivotL)
        {
            part2 = i;
            break;
        }
    }
    // dzielimy na 3 czesci
    DualPivotQuickSelectSort(t, start, part1 - 1);
    DualPivotQuickSelectSort(t, part1 + 1, part2 - 1);
    DualPivotQuickSelectSort(t, part2 + 1, end);
}

void randomData(int t[], int n)
{
    for (int i = 0; i < n; i++)
    {
        t[i] = dis(generator);
    }
}

void test1()
{
    clock_t begin;
    clock_t end;
    ofstream file;
    file.open("quickStats.txt");
    file << "Alg;n;k;comp;time(ms)\n";
    for (int i = 100; i <= 10000; i += 100)
    {
        for (int s = 0; s < 100; s++)
        {
            int t[i];
            randomData(t, i);
            int cpy[i];
            for (int j = 0; j < i; j++)
            {
                cpy[j] = t[j];
            }
            comp = 0;
            begin = clock();
            QuickSort(cpy, 0, i - 1);
            end = clock();
            file << "QuickSort;" << i << ";" << s << ";" << comp << ";" << (end - begin) * 1000 / (double)CLOCKS_PER_SEC << endl;
            for (int j = 0; j < i; j++)
            {
                cpy[j] = t[j];
            }
            comp = 0;
            begin = clock();
            QuickSelectSort(cpy, 0, i - 1);
            end = clock();
            file << "QuickSelectSort;" << i << ";" << s << ";" << comp << ";" << (end - begin) * 1000 / (double)CLOCKS_PER_SEC << endl;
            for (int j = 0; j < i; j++)
            {
                cpy[j] = t[j];
            }
            comp = 0;
            begin = clock();
            DualPivotQuickSort(cpy, 0, i - 1);
            end = clock();
            file << "DualPivotQuickSort;" << i << ";" << s << ";" << comp << ";" << (end - begin) * 1000 / (double)CLOCKS_PER_SEC << endl;
            for (int j = 0; j < i; j++)
            {
                cpy[j] = t[j];
            }
            comp = 0;
            begin = clock();
            DualPivotQuickSelectSort(cpy, 0, i - 1);
            end = clock();
            file << "DualPivotQuickSelectSort;" << i << ";" << s << ";" << comp << ";" << (end - begin) * 1000 / (double)CLOCKS_PER_SEC << endl;
        }
    }
    file.close();
}

void test2()
{
    clock_t begin;
    clock_t end;
    ofstream file;
    file.open("quickStatsWC.txt");
    file << "Alg;n;k;comp;time(ms)\n";
    for (int i = 100; i <= 10000; i += 100)
    {
        for (int s = 0; s < 10; s++)
        {
            int t[i];
            randomData(t, i);
            int cpy[i];
            for (int j = 0; j < i; j++)
            {
                cpy[j] = t[j];
            }
            comp = 0;
            begin = clock();
            QuickSort(cpy, 0, i - 1);
            end = clock();
            file << "QuickSort;" << i << ";" << s << ";" << comp << ";" << (end - begin) * 1000 / (double)CLOCKS_PER_SEC << endl;
            for (int j = 0; j < i; j++)
            {
                cpy[j] = t[j];
            }
            comp = 0;
            begin = clock();
            QuickSelectSort(cpy, 0, i - 1);
            end = clock();
            file << "QuickSelectSort;" << i << ";" << s << ";" << comp << ";" << (end - begin) * 1000 / (double)CLOCKS_PER_SEC << endl;
            for (int j = 0; j < i; j++)
            {
                cpy[j] = t[j];
            }
            comp = 0;
            begin = clock();
            DualPivotQuickSort(cpy, 0, i - 1);
            end = clock();
            file << "DualPivotQuickSort;" << i << ";" << s << ";" << comp << ";" << (end - begin) * 1000 / (double)CLOCKS_PER_SEC << endl;
            for (int j = 0; j < i; j++)
            {
                cpy[j] = t[j];
            }
            comp = 0;
            begin = clock();
            DualPivotQuickSelectSort(cpy, 0, i - 1);
            end = clock();
            file << "DualPivotQuickSelectSort;" << i << ";" << s << ";" << comp << ";" << (end - begin) * 1000 / (double)CLOCKS_PER_SEC << endl;
        }
    }
    file.close();
}

int main()
{
    int t[10];
    randomData(t,10);
    DualPivotQuickSelectSort(t,0,9);
    for(int i=0;i<10;i++){
        cout<<t[i]<<endl;
    }
    //test1();
    //test2();
 
}
