#include "tree.h"
#include "transit.h"
#include <string.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
vector<string> &split(const string &s, char delim, vector<string> &elems) {
  stringstream ss(s);
  string item;
  while(getline(ss, item, delim)) {
    elems.push_back(item);
  }
  return elems;
}
vector<string> split(const string &s, char delim) {
  vector<string> elems;
  return split(s, delim, elems);
}
int main(int argc, char* argv){
/*
 * std::string a,b,c;
 * a = "a1";
 * b = "b1";
 * c = "c1";
 * Item* item = new Item(&a,1.0,1.0);
 * item->PrintState();
 * Tree *root = new Tree(item);
 * Item* item1 = new Item(&b,1.5,3.0);
 * Tree *node1 = new Tree(item1);
 * root->Insert(*node1);
 * Item* item2 = new Item(&c,-1.0,0.5);
 * Tree *node2 = new Tree(item2);
 * root->Insert(*node2);
 * root->PreorderPrint();  
 * root->PostorderPrint();
 * root->InorderPrint(); */
    ifstream in;
    int colp = 2, coldsp = 14,pmax =5,ap,np;
    double p,dsp;
    ap=0;
    string ID("HAT-317-0002127");
    string ext(".blsanal");
    string infile;
    //cout << ID << endl;
    Item *item;
    Tree *root = new Tree();
    string line;
    vector <string> data;
    for (np=0;np<pmax;np++){
      sprintf(&infile[0],"%s.AP%d.P%d%s",ID.c_str(),ap,np,ext.c_str());
      //infile << ID << ".AP" << ap << ".P" << np << ".blsanal"; 
      //in.open("HAT-317-0002127.AP0.P0.blsanal");
      //in.open("HAT-317-0002127.AP0.P0.blsanal");
      in.open(&infile[0]);
      if(!in){
       exit(1);
      }
      while(!in.eof()){
        getline(in,line);
        if(line.compare(0,1,"#") and !line.empty()){
         data = split(line,'\t'); 
         p = atof(data[colp].c_str());
         dsp = atof(data[coldsp].c_str());
         Item *newitem = new Item(&line,p,dsp);
         Tree *node = new Tree(newitem);
         root->Insert(*node);
         delete node;
      //   printf("nb of nodes %d\n",nb);
       }
        if(!in) break;
      }
      in.close();
    }
    root->InorderPrint(); 
    delete root;
}
