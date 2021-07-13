#include "trees.hpp"
#include "tree.hpp"
#include "bst.hpp"
#include "rbt.hpp"
#include "splay.hpp"

random_device device;
mt19937 generator(device());
uniform_int_distribution<int> dis(0, 1000000);

const string CHARACTERS = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
const int SIZE = 52;

vector<string> randomString(int n, int s)
{
    vector<string> randomWords;
    for (int i = 0; i < n; i++)
    {
        string word = "";
        for (int j = 0; j < s; j++)
        {
            word += CHARACTERS[dis(generator) % SIZE];
        }
        randomWords.push_back(word);
    }
    return randomWords;
}

// testy
void test()
{
    ofstream fout;
    fout.open("resultsMax.txt");
    fout << "Size;Tree;Compares" << endl;
    for (int i = 1000; i <= 30000; i += 1000)
    {
        BST tree1;
        RBT tree2;
        Splay tree3;
        vector<string> words = randomString(i, 10);
        sort(words.begin(), words.end());
        for (int j = 0; j < i; j++)
        {
            tree1.insert(words[j]);
            tree1.compares = 0;
            tree2.insert(words[j]);
            tree2.compares = 0;
            tree3.insert(words[j]);
            tree3.compares = 0;
        }
        tree1.find(words[words.size() - 1]);
        fout << i << ";BST;" << tree1.compares << endl;
        tree1.compares = 0;
        tree2.find(words[words.size() - 1]);
        fout << i << ";RBT;" << tree2.compares << endl;
        tree2.compares = 0;
        tree3.find(words[0]);
        fout << i << ";Splay;" << tree3.compares << endl;
        tree3.compares = 0;
    }
    /*vector<string> words;
    ifstream fin;
    ofstream fout;
    //fin.open("aspell_wordlist.txt");
    fin.open("lotr.txt");
    string text;
    while (getline(fin, text, ' '))
    {
        char *conv = &text[0];
        const char *split = strtok(conv, " ;.,:-\n\t!"
                                         "?()");
        while (split != NULL)
        {
            string toInsert(split);
            split = strtok(NULL, ";.,:-\n\t!?"
                                 "()");
            regex pattern("[^a-zA-Z']+");
            string converted = regex_replace(toInsert, pattern, "");
            words.push_back(converted);
        }
    }
    BST tree1;
    RBT tree2;
    Splay tree3;
    fout.open("results4.txt");
    //tree1.load("aspell_wordlist.txt");
    tree1.load("lotr.txt");
    tree1.compares = 0;
    //tree2.load("aspell_wordlist.txt");
    tree2.load("lotr.txt");
    tree2.compares = 0;
    //tree3.load("aspell_wordlist.txt");
    tree3.load("lotr.txt");
    tree3.compares = 0;
    fout << "MIN:" << endl;
    tree1.find(words[0]);
    fout << "BST;" << tree1.compares << endl;
    tree1.compares = 0;
    tree2.find(words[words.size() / 2]);
    fout << "RBT;" << tree2.compares << endl;
    tree2.compares = 0;
    tree3.find(words[words.size() - 1]);
    fout << "Splay;" << tree3.compares << endl;
    tree3.compares = 0;
    fout << "MAX:" << endl;
    tree1.find(words[words.size() - 1]);
    fout << "BST;" << tree1.compares << endl;
    tree1.compares = 0;
    tree2.find(words[words.size() - 1]);
    fout << "RBT;" << tree2.compares << endl;
    tree2.compares = 0;
    tree3.find(words[0]);
    fout << "Splay;" << tree3.compares << endl;
    tree3.compares = 0;
    /* for (int i = 0; i < 1000; i++)
    {
        string word = words[dis(generator) % words.size()];
        tree1.find(word);
        fout << "BST;" << tree1.compares << endl;
        tree1.compares = 0;
        tree2.find(word);
        fout << "RBT;" << tree2.compares << endl;
        tree2.compares = 0;
        tree3.find(word);
        fout << "Splay;" << tree3.compares << endl;
        tree3.compares = 0;
    }
    /*for (int i = 0; i < 5; i++)
    {
        BST tree1;
        RBT tree2;
        Splay tree3;
        random_shuffle(words.begin(), words.end());
        for (int j = 0; j < words.size(); j++)
        {
            tree1.insert(words[j]);
            tree2.insert(words[j]);
            tree3.insert(words[j]);
            tree1.compares = 0;
            tree2.compares = 0;
            tree3.compares = 0;
        }
        for (int j = 0; j < 1000; j++)
        {
            string word = words[dis(generator) % words.size()];
            tree1.find(word);
            fout << i << ";BST;" << tree1.compares << endl;
            tree1.compares = 0;
            tree2.find(word);
            fout << i << ";RBT;" << tree2.compares << endl;
            tree2.compares = 0;
            tree3.find(word);
            fout << i << ";Splay;" << tree3.compares << endl;
            tree3.compares = 0;
        }
    }*/
    fout.close();
    //fin.close();
}


void commands(Tree *tree)
{
    // mapa: kluczem jest komenda a wartoscia para(numer komendy, ile razy zostala wywolana)
    map<string, pair<int, int>> operationMap;
    operationMap["insert"] = {1, 0};
    operationMap["delete"] = {2, 0};
    operationMap["load"] = {3, 0};
    operationMap["find"] = {4, 0};
    operationMap["successor"] = {5, 0};
    operationMap["min"] = {6, 0};
    operationMap["max"] = {7, 0};
    operationMap["inOrder"] = {8, 0};
    int n;
    bool valid = true;
    string operation;
    string argument;
    clock_t begin;
    clock_t end;
    cin >> n;
    begin = clock();
    for (int i = 0; i < n; i++)
    {
        valid = true;
        cin >> operation;
        switch (operationMap[operation].first)
        {
        case 1:
            cin >> argument;
            tree->insert(argument);
            break;
        case 2:
            cin >> argument;
            tree->del(argument);
            break;
        case 3:
            cin >> argument;
            tree->load(argument);
            break;
        case 4:
            cin >> argument;
            tree->find(argument);
            break;
        case 5:
            cin >> argument;
            tree->successor(argument);
            break;
        case 6:
            tree->min();
            break;
        case 7:
            tree->max();
            break;
        case 8:
            tree->inOrder();
            break;
        default:
            valid = false;
            cout << "UNKNOWN OPERATION" << endl;
        }
        operationMap[operation].second++;
        if (!valid)
        {
            operationMap.erase(operation);
        }
    }
    end = clock();

    cerr << "TIME: " << (end - begin) * 1000 / (double)CLOCKS_PER_SEC << endl;
    cerr << "OPERATIONS:" << endl;
    for (const auto &p : operationMap)
    {
        cout << p.first << ": " << p.second.second << endl;
    }
    cout << "MAX FILL: " << tree->maxSize << endl;
    cout << "ACTUAL SIZE: " << tree->actualSize << endl;
    cout << "COMPARES: " << tree->compares << endl;
}

int main(int argc, char *argv[])
{
    Tree *tree;

    if (argc > 2)
    {

        if (strcmp(argv[1], "--type") == 0)
        {
            if (strcmp(argv[2], "bst") == 0)
            {
                cout << "BST" << endl;
                tree = new BST();
            }
            else if (strcmp(argv[2], "rbt") == 0)
            {
                cout << "RBT" << endl;
                tree = new RBT();
            }
            else if (strcmp(argv[2], "splay") == 0)
            {
                cout << "Splay" << endl;
                tree = new Splay();
            }
            else
            {
                cout << "Unknown type: " << argv[2] << endl;
                return -1;
            }
            commands(tree);
        }
        else if (strcmp(argv[1], "test") == 0)
        {
            test();
        }
        else
        {
            cout << "Unknown option: " << argv[1] << endl;
            return -1;
        }
    }
    else
    {
        cout << "Incorrect number of arguments" << endl;
        return -1;
    }

    return 0;
}
