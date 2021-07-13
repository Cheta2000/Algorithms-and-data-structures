class Tree
{
public:
    int maxSize = 0;
    int actualSize = 0;
    long long unsigned int compares = 0;
    virtual void insert(string key) = 0;
    virtual void del(string key) = 0;
    virtual void find(string key) = 0;
    virtual void successor(string key) = 0;
    virtual void min() = 0;
    virtual void max() = 0;
    virtual void load(string filename) = 0;
    virtual void inOrder() = 0;

    Tree() {}
    virtual ~Tree(){};
};