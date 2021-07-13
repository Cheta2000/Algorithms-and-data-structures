#include <iostream>
#include <string.h>
#include <regex>
#include <fstream>
#include <stdio.h>
#include <vector>
#include <random>
using namespace std;

// wezel zwykly
struct node
{
    string key;
    node *left;
    node *right;
    node *parent;
};

enum Color
{
    BLACK,
    RED
};

// wezel drzewa rbt
struct colorNode : node
{
    string key;
    colorNode *left;
    colorNode *right;
    colorNode *parent;
    Color color;
};

class BST;
class RBT;
class Splay;
class Tree;