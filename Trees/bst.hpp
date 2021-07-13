// drzewo BST
class BST : public Tree
{

private:
    // wskazanie na korzeń
    node *root;

    // dodawanie
    node *insert(string key, node *tree)
    {
        // tworzymy nowy wezel
        node *newNode = new node;
        newNode->key = key;
        newNode->left = NULL;
        newNode->right = NULL;
        newNode->parent = NULL;
        node *element = tree;
        node *parent = NULL;
        // szukamy jego miejsca
        while (element != NULL)
        {
            parent = element;
            compares++;
            if (key <= element->key)
            {
                element = element->left;
            }
            else
            {
                element = element->right;
            }
        }
        // jesli to drzewo bylo puste, to drzewem jest nowy wezel
        if (parent == NULL)
        {
            return newNode;
        }
        else
        {
            // sprawdzamy ktorym synem rodzica jest nowy wezel
            newNode->parent = parent;
            compares++;
            if (key <= parent->key)
            {
                parent->left = newNode;
            }
            else
            {
                parent->right = newNode;
            }
        }
        return tree;
    }

    // szukanie wezla o danym kluczu
    node *find(string key, node *tree)
    {
        // jesli drzewo jest puste
        if (tree == NULL)
        {
            return NULL;
        }
        compares++;
        // jesli znalezlismy szukana wartosc
        if (tree->key == key)
        {
            return tree;
        }
        compares++;
        // jesli szukana wartosc jest mniejsza niz aktualna idziemy w lewo
        if (key < tree->key)
        {
            return find(key, tree->left);
        }
        // else idziemy w prawo
        else
        {
            return find(key, tree->right);
        }
    }

    //szukanie wezla o min kluczu
    node *min(node *tree)
    {
        // idziemy w lewo dopoki drzewo nie bedzie puste
        if (tree == NULL)
        {
            return NULL;
        }
        if (tree->left == NULL)
        {
            return tree;
        }
        return min(tree->left);
    }

    // szukanie wezla o max kluczu
    node *max(node *tree)
    {
        // idziemy w prawo dopoki drzewo nie bedzie puste
        if (tree == NULL)
        {
            return NULL;
        }
        if (tree->right == NULL)
        {
            return tree;
        }
        return max(tree->right);
    }

    // wypisanie drzewo w porzadku rosnacym
    void inOrder(node *tree)
    {
        if (tree != NULL)
        {
            // najpierw wypisujemy lewe podrzewo a potem prawe
            inOrder(tree->left);
            cout << tree->key << endl;
            inOrder(tree->right);
        }
    }

    // szukanie nastepnika wezla o danym kluczu
    node *successor(string key, node *tree)
    {
        // szukamy wezla o danym kluczu
        node *element = find(key, tree);
        // jesli element nie istnieje
        if (element == NULL)
        {
            return NULL;
        }
        // jesli element ma prawe poddrzewo bierzemy min stamtad
        if (element->right != NULL)
        {
            return min(element->right);
        }
        node *parent = element->parent;
        compares++;
        // dopoki element jest prawym synem rodzica to idziemy w gore drzewa
        while (parent != NULL && element == parent->right)
        {
            element = parent;
            parent = parent->parent;
            compares++;
        }
        return parent;
    }

    // usuwanie wezla o danym kluczu
    node *remove(string key, node *tree)
    {
        node *element = tree;
        compares++;
        // szukamy elementu o danym kluczu
        while (element != NULL && key != element->key)
        {
            compares++;
            if (key < element->key)
            {
                element = element->left;
            }
            else
            {
                element = element->right;
            }
            compares++;
        }
        if (element == NULL)
        {
            return tree;
        }
        actualSize--;
        node *son;
        node *succ;
        // jesli element nie ma obu synow
        if (element->left == NULL || element->right == NULL)
        {
            succ = element;
        }
        else
        {
            // bierzemy nastepnik
            succ = successor(element->key, tree);
        }
        // umieszczamy nastepnik w miejscu usuwanego elementu
        // zapamietujemy jego syna, ma max jednego
        if (succ->left != NULL)
        {
            son = succ->left;
        }
        else if (succ->right != NULL)
        {
            son = succ->right;
        }
        else
        {
            son = NULL;
        }
        // syna przejmuje dziadek XD
        if (son != NULL)
        {
            son->parent = succ->parent;
        }
        //jesli nastepnik byl korzeniem
        if (succ->parent == NULL)
            return son;
        else
        {
            // podpiecie syna do dziadka
            compares++;
            if (succ == succ->parent->left)
                succ->parent->left = son;
            else
                succ->parent->right = son;
        }
        // zmiana wartosci
        element->key = succ->key;
        delete succ;
        return tree;
    }

public:
    // przy tworzeniu drzewa jest ono puste
    BST()
    {
        root = NULL;
    }

    void find(string key)
    {
        // jesli nie znajdziemy wartosci
        if (find(key, root) == NULL)
        {
            cout << 0 << endl;
        }
        else
        {
            cout << 1 << endl;
        }
    }

    void min()
    {
        node *value = min(root);
        // jesli drzewo jest puste
        if (value == NULL)
        {
            cout << "" << endl;
        }
        else
        {
            cout << value->key << endl;
        }
    }

    void max()
    {
        node *value = max(root);
        if (value == NULL)
        {
            cout << "" << endl;
        }
        else
        {
            cout << value->key << endl;
        }
    }

    void successor(string key)
    {
        node *value = successor(key, root);
        // jesli nie ma nastepnika
        if (value == NULL)
        {
            cout << "" << endl;
        }
        else
        {
            cout << value->key << endl;
        }
    }

    void insert(string key)
    {
        // akceptujemy tylko litery (' do danych do testu)
        regex pattern("[^a-zA-Z']+");
        // znaki niezgodne z regex usuwamy
        string converted = regex_replace(key, pattern, "");
        root = insert(converted, root);
        actualSize++;
        if (actualSize > maxSize)
        {
            maxSize = actualSize;
        }
    }

    void load(string filename)
    {
        ifstream file;
        file.open(filename);
        string text;
        while (getline(file, text, ' '))
        {
            // konwersja linii z pliku
            char *conv = &text[0];
            const char *split = strtok(conv, " ;.,:-\n\t!"
                                             "?()");
            while (split != NULL)
            {
                string toInsert(split);
                split = strtok(NULL, ";.,:-\n\t!?"
                                     "()");
                insert(toInsert);
            }
        }
        file.close();
        cout << "LOADED" << endl;
    }

    void del(string key)
    {
        root = remove(key, root);
    }

    void inOrder()
    {
        // jesli drzewo jest puste
        if (root == NULL)
        {
            cout << "" << endl;
        }
        else
        {
            inOrder(root);
        }
    }
};