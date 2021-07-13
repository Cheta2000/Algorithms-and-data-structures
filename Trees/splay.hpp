class Splay : public Tree
{

private:
    node *root;

    node *insert(string key, node *tree)
    {
        node *newNode = new node;
        newNode->key = key;
        newNode->left = NULL;
        newNode->right = NULL;
        newNode->parent = NULL;
        node *element = tree;
        node *parent = NULL;
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
        if (parent == NULL)
        {
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
        // naprawa drzewa
        // nowo dodany wezel musi stac sie korzeniem
        tree = splay(tree, newNode);
        return tree;
    }

    // umieszczenie node w korzeniu z zachowaniem bst property
    node *splay(node *tree, node *node)
    {
        // dopoki node nie jest korzeniem
        while (node->parent != NULL)
        {
            // jesli nie ma dziadka
            if (node->parent->parent == NULL)
            {
                compares++;
                // jesli jest lewym synem
                if (node == node->parent->left)
                {
                    // rotacja zig - prawa
                    tree = right_rotate(tree, node->parent);
                }
                else
                {
                    // rotacja zag -lewa
                    tree = left_rotate(tree, node->parent);
                }
            }
            // jesli jest lewym synem i rodzic jest lewym synem
            else if (node == node->parent->left && node->parent == node->parent->parent->left)
            {
                compares += 2;
                // rotacja zig zig - 2x prawa
                tree = right_rotate(tree, node->parent->parent);
                tree = right_rotate(tree, node->parent);
            }
            // jesli jest prawym synem i rodzice jest prawym synem
            else if (node == node->parent->right && node->parent == node->parent->parent->right)
            {
                compares += 4;
                // rotacja zag zag- 2x lewa
                tree = left_rotate(tree, node->parent->parent);
                tree = left_rotate(tree, node->parent);
            }
            // jesli jest prawym synem a rodzic lewym
            else if (node == node->parent->right && node->parent == node->parent->parent->left)
            {
                compares += 6;
                // rotacja zig zag - lewa prawa
                tree = left_rotate(tree, node->parent);
                tree = right_rotate(tree, node->parent);
            }
            // jesli jest lewym synem a rodzic prawym
            else
            {
                compares += 8;
                // rotacja zag zig - prawa lewa
                tree = right_rotate(tree, node->parent);
                tree = left_rotate(tree, node->parent);
            }
        }
        return tree;
    }

    node *right_rotate(node *tree, node *rotated)
    {
        node *top = rotated->left;
        rotated->left = top->right;
        if (top->right != NULL)
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

    node *left_rotate(node *tree, node *rotated)
    {
        node *top = rotated->right;
        rotated->right = top->left;
        if (top->left != NULL)
        {
            top->left->parent = rotated;
        }
        top->parent = rotated->parent;
        if (rotated->parent == NULL)
        {
            tree = top;
        }
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
        top->left = rotated;
        rotated->parent = top;
        return tree;
    }

    node *min(node *tree)
    {
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

    node *max(node *tree)
    {
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

    void inOrder(node *tree)
    {
        if (tree != NULL)
        {
            inOrder(tree->left);
            cout << tree->key << endl;
            inOrder(tree->right);
        }
    }
    node *find(string key, node *tree)
    {
        if (tree == NULL)
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

    node *successor(string key, node *tree)
    {
        node *element = find(key, tree);
        if (element == NULL)
        {
            return NULL;
        }

        if (element->right != NULL)
        {
            return min(element->right);
        }
        node *parent = element->parent;
        compares++;
        while (parent != NULL && element == parent->right)
        {
            element = parent;
            parent = parent->parent;
            compares++;
        }
        return parent;
    }

    node *remove(string key, node *tree)
    {
        node *element = tree;
        compares++;
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
        // usuwany element idzie do korzenia drzewa
        tree = splay(tree, element);
        // "dzielimy" drzewo na dwie czesci
        node *subTree1;
        node *subTree2;
        // jesli usuwany element ma prawego syna
        if (element->right != NULL)
        {
            // tworzymy tam pierwsze podrzewo bez rodzica
            subTree1 = element->right;
            subTree1->parent = NULL;
        }
        else
        {
            subTree1 = NULL;
        }
        // na poczatku drugie poddrzewo to cale drzewo
        subTree2 = element;
        // zrywamy polaczenie z prawym poddrzewem(jest tam juz pierwsze)
        subTree2->right = NULL;
        // usuwamy wezel
        element = NULL;
        delete element;
        // jesli usuwany element mial lewego syna
        if (subTree2->left != NULL)
        {
            // lewy syn traci rodzica
            subTree2->left->parent = NULL;
        }
        // jesli nie bylo lewego syna
        if (subTree2->left == NULL)
        {
            // cale nowe drzewo to poddrzewo pierwsze
            return subTree1;
        }
        // jesli poddrzewo pierwsze jest puste
        if (subTree1 == NULL)
        {
            // cale nowe drzewo to poddrzewo drugie
            return subTree2;
        }
        // szukamy maxa w lewym synu drugiego poddrzewa
        node *maxNode = max(subTree2->left);
        // nowe drzewo ma tego maxa w wierzcholku
        tree = splay(tree, maxNode);
        // prawy syn wierzcholka to pierwsze poddrzewo
        maxNode->right = subTree1;
        subTree1->parent = maxNode;
        tree = maxNode;
        return tree;
    }

public:
    Splay()
    {
        root = NULL;
    }

    void find(string key)
    {
        node *found = find(key, root);
        if (found == NULL)
        {
            cout << 0 << endl;
        }
        else
        {
            cout << 1 << endl;
            // po znalezieniu wierzcholka wywolujemy na nim splaya zeby stal sie korzeniem!
            root = splay(root, found);
        }
    }

    void min()
    {
        node *value = min(root);
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