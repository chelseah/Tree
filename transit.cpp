#include "transit.h"
Item::Item(){
//  std::string s1;
//  line_= new std::string();
  line_=NULL;
  p_=NULL;
  dsp_=NULL;
}
Item::Item(std::string * line, double p,double dsp)
  : p_(p),dsp_(dsp){
  //swap(*line_,*line);
  line_ = new string(*line);
//  line_->replace(line_->begin(),line_->end(),*line);
}

Item::~Item(){
  delete line_;
}
void Item::copy(const Item *nb){
  p_=nb->p_;
  if(!line_){
    delete line_;
  }
  line_ = new string(*(nb->line_));
  //  line_= nb->line_;
  dsp_=nb->dsp_;
}

int Item::Ge(const Item *nb){
  if(fabs(p_-nb->p_)/p_<1e-3){    
    return 0;
  } else {
      if(p_<nb->p_){
        return 1;
      } else {
        return -1;
      }
  }
}
int Item::Better(const Item *nb) {
  if(dsp_<nb->dsp_){
    return 1;
  } else {
      return 0;
  }
}
void Item::PrintState(vector <string> &outstr){
  if(outstr.size()==0){
    std::cout << *line_ << '\n';
  } else {
    std::cout << outstr.size() << endl;
    outstr.push_back(*line_); 
    std::cout << "inprint"<<outstr.size() << endl;
  }
  //  std::cout << *line_ << '\n';
}

