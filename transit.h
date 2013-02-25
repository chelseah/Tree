#ifndef TRANSIT_H
#define TRANSIT_H
#include "stdio.h"
#include <iostream>
#include <string>
#include <vector>
#include <math.h>
using namespace std;
class Item {
  public:
    Item();
    Item(std::string* line,double p, double dsp,int harm_flag=1);
    ~Item();
    void copy(const Item *nb);
    bool Isharm(const double p);
    int Ge(const Item *nb);
    int Better(const Item *nb);
    void PrintState(vector <string>&outstr);
    string* line_;
    double p_;
    double dsp_;
    int harm_flag_;
};
#endif
