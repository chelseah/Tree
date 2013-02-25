#ifndef NUMTREE_H
#define NUMTREE_H
#include "stdio.h"
class Item {
  public:
    Item();
    Item(double x);
    ~Item();
    void copy(const Item *nb);
    int Ge(const Item *nb);
    int Better(const Item *nb);
    void PrintState();
    double x_;
};
#endif
