class RBT : public Tree
{

private:
    colorNode *root;
    // extraNull to NULL ale o kolorze czarnym, potrzebne
    colorNode *extraNull;

    colorNode *insert(string key, colorNode *tree)
    {
        colorNode *newNode = new colorNode;
        newNode->key = key;
        newNode->left = extraNull;
        newNode->right = extraNull;
        newNode->parent = NULL;
        // docelowo dodawany wezel jest czerwony
        newNode->color = RED;
        colorNode *element = tree;
        colorNode *parent = NULL;
        while (element != extraNull)
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
        if (parent == NULL)
        {
            // jesli to root to jest czarny
            newNode->color = BLACK;
            return newNode;
        }
        else
        {
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
        if (newNode->parent->parent == NULL)
        {
            return tree;
        }
        // naprawa drzewa aby zachowala zasady rbt
        // bst property
        // kazda trasa tyle samo czarnych
        // po czerwonym czarne
        tree = insertFix(tree, newNode);
        return tree;
    }

    // naprawa drzewa po dodaniu
    colorNode *insertFix(colorNode *tree, colorNode *inserted)
    {
        colorNode *uncle;
        compares++;
        // dopoki rodzice naprawianego wierzcholka jest czerowny
        while (inserted->parent->color == RED)
        {
            compares++;
            // jesli rodzic jest prawym synem dziadka
            if (inserted->parent == inserted->parent->parent->right)
            {
                // wujek wtedy jest lewym synem dziadka
                uncle = inserted->parent->parent->left;
                compares++;
                // jesli wujek jest czerowny
                if (uncle->color == RED)
                {
                    // recolor
                    uncle->color = BLACK;
                    inserted->parent->color = BLACK;
                    inserted->parent->parent->color = RED;
                    inserted = inserted->parent->parent;
                }
                // jesli wujek jest czarny
                else
                {
                    compares++;
                    // jesli naprawiany wierzcholek jest lewym synem
                    if (inserted == inserted->parent->left)
                    {
                        // staje sie swoim rodzicem i right rotate
                        inserted = inserted->parent;
                        tree = right_rotate(tree, inserted);
                    }
                    // recolor i left rotate na dziadku
                    inserted->parent->color = BLACK;
                    inserted->parent->parent->color = RED;
                    tree = left_rotate(tree, inserted->parent->parent);
                }
            }
            // analogicznie
            else
            {
                uncle = inserted->parent->parent->right;
                compares++;
                if (uncle->color == RED)
                {
                    uncle->color = BLACK;
                    inserted->parent->color = BLACK;
                    inserted->parent->parent->color = RED;
                    inserted = inserted->parent->parent;
                }
                else
                {
                    compares++;
                    if (inserted == inserted->parent->right)
                    {
                        inserted = inserted->parent;
                        tree = left_rotate(tree, inserted);
                    }
                    inserted->parent->color = BLACK;
                    inserted->parent->parent->color = RED;
                    tree = right_rotate(tree, inserted->parent->parent);
                }
            }
            compares++;
            if (inserted == tree)
            {
                break;
            }
            compares++;
        }
        tree->color = BLACK;
        return tree;
    }

    colorNode *find(string key, colorNode *tree)
    {
        if (tree == extraNull)
        {
            return NULL;
        }
        compares++;
        if (tree->key == key)
        {
            return tree;
        }
        compares++;
        if (key < tree->key)
        {
            return find(key, tree->left);
        }
        else
        {
            return find(key, tree->right);
        }
    }

    colorNode *min(colorNode *tree)
    {
        if (tree == extraNull)
        {
            return NULL;
        }
        if (tree->left == extraNull)
        {
            return tree;
        }
        return min(tree->left);
    }

    colorNode *max(colorNode *tree)
    {
        if (tree == extraNull)
        {
            return NULL;
        }
        if (tree->right == extraNull)
        {
            return tree;
        }
        return max(tree->right);
    }

    void inOrder(colorNode *tree)
    {
        if (tree != extraNull)
        {
            inOrder(tree->left);
            cout << tree->key << endl;
            inOrder(tree->right);
        }
    }

    colorNode *successor(string key, colorNode *tree)
    {
        colorNode *element = find(key, tree);
        if (element == NULL)
        {
            return NULL;
        }

        if (element->right != extraNull)
        {
            return min(element->right);
        }
        colorNode *parent = element->parent;
        compares++;
        while (parent != NULL && element == parent->right)
        {
            element = parent;
            parent = parent->parent;
            compares++;
        }
        return parent;
    }

    colorNode *remove(string key, colorNode *tree)
    {
        colorNode *element = tree;
        compares++;
        while (element != extraNull && key != element->key)
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
        if (element == extraNull)
        {
            return tree;
        }
        actualSize--;
        colorNode *son;
        colorNode *succ;
        if (element->left == extraNull || element->right == extraNull)
        {
            succ = element;
        }
        else
        {
            succ = successor(element->key, tree);
        }
        if (succ->left != extraNull)
        {
            son = succ->left;
        }
        else if (succ->right != extraNull)
        {
            son = succ->right;
        }
        else
        {
            son = extraNull;
        }
        son->parent = succ->parent;
        if (succ->parent == NULL)
            return son;
        else
        {
            compares++;
            if (succ == succ->parent->left)
                succ->parent->left = son;
            else
                succ->parent->right = son;
        }
        // przepinamy i wartosc i kolor
        element->color = succ->color;
        element->key = succ->key;
        compares++;
        // jesli wezel ktory wszedl na miejsce usunietego jest czarny to trzeba to naprawic
        if (succ->color == BLACK)
        {
            tree = deleteFix(tree, son);
        }
        delete succ;
        return tree;
    }

    // naprawa po usunieciu wezla
    colorNode *deleteFix(colorNode *tree, colorNode *deleted)
    {
        colorNode *sibling;
        compares += 2;
        // dopoki nie dojdzemy do korzenia i naprawiany wierzcholek jest czarny
        while (deleted != tree && deleted->color == BLACK)
        {
            compares++;
            // jesli naprawiany jest lewym synem
            if (deleted->parent->left == deleted)
            {
                // blizniak jest prawym synem
                sibling = deleted->parent->right;
                compares++;
                // jesli blizniak jest czerowny
                if (sibling->color == RED)
                {
                    // recolor i left rotate na rodzicu
                    sibling->color = BLACK;
                    deleted->parent->color = RED;
                    tree = left_rotate(tree, deleted->parent);
                    // teraz kto inny jest blizniakiem
                    sibling = deleted->parent->right;
                }
                compares += 2;
                // jesli obaj synowie blizniaka sa czarni
                if (sibling->right->color == BLACK && sibling->left->color == BLACK)
                {
                    // zmiana koloru blizniaka
                    sibling->color = RED;
                    // idziemy w gore
                    deleted = deleted->parent;
                }
                else
                {
                    compares++;
                    // jesli tylko prawy syn blizniaka jest czarny
                    if (sibling->right->color == BLACK)
                    {
                        // recolor i right rotate na blizniaku
                        sibling->left->color == BLACK;
                        sibling->color = RED;
                        tree = right_rotate(tree, sibling);
                        sibling = deleted->parent->right;
                    }
                    // recolor i left rotate na rodzicu naprawianego
                    sibling->color = deleted->parent->color;
                    deleted->parent->color = BLACK;
                    sibling->right->color = BLACK;
                    tree = left_rotate(tree, deleted->parent);
                    deleted = tree;
                }
            }
            // analogicznie
            else
            {
                sibling = deleted->parent->left;
                compares++;
                if (sibling->color == RED)
                {
                    sibling->color = BLACK;
                    deleted->parent->color = RED;
                    tree = right_rotate(tree, deleted->parent);
                    sibling = deleted->parent->left;
                }
                compares += 2;
                if (sibling->left->color == BLACK && sibling->right->color == BLACK)
                {
                    sibling->color = RED;
                    deleted = deleted->parent;
                }
                else
                {
                    compares++;
                    if (sibling->left->color == BLACK)
                    {
                        sibling->right->color = BLACK;
                        sibling->color = RED;
                        tree = left_rotate(tree, sibling);
                        sibling = deleted->parent->left;
                    }
                    sibling->color = deleted->parent->color;
                    deleted->parent->color = BLACK;
                    sibling->left->color = BLACK;
                    tree = right_rotate(tree, deleted->parent);
                    deleted = tree;
                }
            }
            deleted->color = BLACK;
        }
        return tree;
    }

    // lewa rotacja
    colorNode *
    left_rotate(colorNode *tree, colorNode *rotated)
    {
        // wierzcholek ktory bedzie na gorze po rotacji to prawy syn tego na ktorym jest rotacja
        colorNode *top = rotated->right;
        // nowy prawy syn rotowanego to lewy syn tego co bedzie na gorze
        rotated->right = top->left;
        // jesli ten co bedzie na gorze ma lewego syna
        if (top->left != extraNull)
        {
            // ojciec lewego syna gory to teraz rotowany
            top->left->parent = rotated;
        }
        // rodzic gory to stary rodzic rotowanego
        top->parent = rotated->parent;
        // jesli rotowany byl korzeniem
        if (rotated->parent == NULL)
        {
            tree = top;
        }
        // jesli rotowaony byl lewym synem
        else if (rotated == rotated->parent->left)
        {
            compares++;
            rotated->parent->left = top;
        }
        else
        {
            compares++;
            rotated->parent->right = top;
        }
        // lewy syn gory to teraz rotowany
        top->left = rotated;
        // rodzic rotowanego to teraz gora
        rotated->parent = top;
        return tree;
    }

    // prawa rotacja
    colorNode *right_rotate(colorNode *tree, colorNode *rotated)
    {
        colorNode *top = rotated->left;
        rotated->left = top->right;
        if (top->right != extraNull)
        {
            top->right->parent = rotated;
        }
        top->parent = rotated->parent;
        if (rotated->parent == NULL)
        {
            tree = top;
        }
        else if (rotated == rotated->parent->right)
        {
            compares++;
            rotated->parent->right = top;
        }
        else
        {
            compares++;
            rotated->parent->left = top;
        }
        top->right = rotated;
        rotated->parent = top;
        return tree;
    }

public:
    // musimy stworzyc extraNulla i umiescic jako korzen
    RBT()
    {
        extraNull = new colorNode;
        extraNull->key = "undefinied";
        extraNull->left = NULL;
        extraNull->right = NULL;
        extraNull->color = BLACK;
        root = extraNull;
    }

    void find(string key)
    {
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
        colorNode *value = min(root);
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
        colorNode *value = max(root);
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
        colorNode *value = successor(key, root);
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
        regex pattern("[^a-zA-Z']+");
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
        if (root == extraNull)
        {
            cout << "" << endl;
        }
        else
        {
            inOrder(root);
        }
    }
};