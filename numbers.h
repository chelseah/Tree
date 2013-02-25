#ifndef NUMTREE_H
#define NUMTREE_H
#include "stdio.h"
#include "item.h"
class Number : public Item<double>{
  public:
    Number(double x);
    ~Number();
    int Ge(const Item &nb);
    int Better(const Item &nb);
    void PrintState();
};
#endif
