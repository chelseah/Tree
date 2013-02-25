#include "numbers.h"
Number::Number(double x)
  : x_(x){
}

Number::~Number(){
}

int Number::Ge(const Item &nb){
  if(x_<nb.x_){
    return 1;
  } else {
    if (x_==nb.x_){
      return 0;
    }
    else {
      return -1;
    }
  }
}
int Number::Better(const Item &nb) {
  return 0;
}
void Number::PrintState(){
  printf("%.2f\n",x_);
}

