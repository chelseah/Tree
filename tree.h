#ifndef TREE_H_
#define TREE_H_
#include <vector>
#include <string>
using namespace std;
//#include "item.h"
#include "transit.h"
class Tree{
  public:
    Tree();
    Tree (Item *item);
    ~Tree();
    int  CountNodes();
    void PreorderPrint(vector <string> &outstr);
    void PostorderPrint(vector <string> &outstr);
    void InorderPrint(vector <string> &outstr);
    bool Intree(Tree &node);
    void Insert(Tree &node);
    int root;
    Tree *left;
    Tree *right;   
    Item *item_;
};
#endif
