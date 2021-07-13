#include <iostream>
#include <random>
#include <fstream>

using namespace std;

int compares = 0;

random_device device;
mt19937 generator(device());
uniform_int_distribution<int> dis(0, 100000);

// przeszukiwanie binarne
int BinarySearch(int t[], int p, int q, int v)
{
    // gdy poczatek tablicy jest wiekszy niz koniec, to znaczy ze nie znalezlismy i konczymy
    if (p > q)
    {
        return 0;
    }
    // srodek tablicy
    int middle = (p + q) / 2;
    compares++;
    // gdy nasz element jest rowny elemntowi ze srodka to go zwracamy
    if (v == t[middle])
    {
        return 1;
    }
    compares++;
    // gdy nasz element jest wiekszy niz element ze srodka to dzialamy na prawej czesci tablicy
    if (v > t[middle])
    {
        return BinarySearch(t, middle + 1, q, v);
    }
    // else na lewej czesci tablicy
    else
    {
        return BinarySearch(t, p, middle - 1, v);
    }
}

void test1()
{
    clock_t begin;
    clock_t end;
    ofstream file;
    file.open("binaryAAA.txt");
    file << "v;Size;Repeat;compares;time" << endl;
    for (int i = 1000; i <= 100000; i += 1000)
    {
        for (int m = 0; m < 100; m++)
        {
            int t[i];
            for (int j = 0; j < i; j++)
            {
                t[j] = j;
            }
            for (int s = 0; s < 4; s++)
            {
                int v;
                if (s == 0)
                {
                    file << "small;";
                    v = dis(generator) % (i / 10);
                    if (v % 2 == 1)
                    {
                        v++;
                    }
                }
                if (s == 1)
                {
                    file << "medium;";
                    v = i / 4 + dis(generator) % (i / 2);
                    if (v % 2 == 1)
                    {
                        v++;
                    }
                }
                if (s == 2)
                {
                    file << "large;";
                    v = i - dis(generator) % (i / 10);
                    if (v % 2 == 1)
                    {
                        v--;
                    }
                }
                if (s == 3)
                {
                    file << "none;";
                    v = dis(generator) % i;
                    if (v % 2 == 0)
                    {
                        if (v < i - 1)
                        {
                            v++;
                        }
                        else
                        {
                            v--;
                        }
                    }
                }
                compares = 0;
                begin = clock();
                BinarySearch(t, 0, i - 1, v);
                end = clock();
                file << i << ";" << m << ";" << compares << ";" << (end - begin) * 1000.0 / (double)CLOCKS_PER_SEC << endl;
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
    file.open("binaryRandom.txt");
    file << "Size;Repeat;compares;time" << endl;
    for (int i = 1000; i <= 100000; i += 1000)
    {
        for (int m = 0; m < 100; m++)
        {
            int t[i];
            for (int j = 0; j < i; j++)
            {
                t[j] = 2 * j;
            }
            int v = t[dis(generator) % i];
            compares = 0;
            begin = clock();
            BinarySearch(t, 0, i - 1, v);
            end = clock();
            file << i << ";" << m << ";" << compares << ";" << (end - begin) * 1000.0 / (double)CLOCKS_PER_SEC << endl;
        }
    }

    file.close();
}

int main()
{
    //test1();
    test2();
    return 0;
}
