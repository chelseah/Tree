#include "item.h"
Item::Item(){
  x_=NULL;
}
Item::Item(double x)
  : x_(x){
}

Item::~Item(){
}
void Item :: copy(const Item *nb){
  x_=nb->x_;
}

int Item::Ge(const Item *nb){
  if(x_<nb->x_){
    return 1;
  } else {
    if (x_==nb->x_){
      return 0;
    }
    else {
      return -1;
    }
  }
}
int Item::Better(const Item *nb) {
  return 0;
}
void Item::PrintState(){
  printf("%.2f\n",x_);
}

