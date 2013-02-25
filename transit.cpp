#include "transit.h"
Item::Item(){
//  std::string s1;
//  line_= new std::string();
  line_=NULL;
  p_=NULL;
  dsp_=NULL;
  harm_flag_=1;
}
Item::Item(std::string * line, double p,double dsp,int harm_flag)
  : p_(p),dsp_(dsp),harm_flag_(harm_flag){
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
  harm_flag_= nb->harm_flag_;
}

int Item::Ge(const Item *nb){
  if(harm_flag_){
    if(fabs(p_-nb->p_)/p_<1e-3){    
      return 0;
    } else {
      if(p_<nb->p_){
        return 1;
      } else {
        return -1;
      }
    }
  } else {
    if(Isharm(nb->p_)){
      return 0;
    } else {
       if(p_<nb->p_){
        return 1;
      } else {
        return -1;
      }

    }
  }
}

bool Item::Isharm(const double p){
  int order;
  double err;
  if(p_>p){
    order = floor(p_/p+0.5);
    err = fabs((p_-order*p)/p_);
  } else {
    order = floor(p/p_+0.5);
    err = fabs((p/order-p_)/p_);
  }
  //cout << order << " " << err << endl;
  if (err<1.e-3) {
    return true;
  } else {
    return false;
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
//    std::cout << outstr.size() << endl;
    outstr.push_back(*line_); 
  //  std::cout << "inprint"<<outstr.size() << endl;
  }
  //  std::cout << *line_ << '\n';
}

