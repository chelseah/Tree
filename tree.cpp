#include "tree.h"
Tree::Tree(){
  item_ = new Item();
  root = 0;
  left = NULL;
  right = NULL;
}

Tree::Tree(Item *item)
: item_(item){
  root = 1;
  left = new Tree();
  right = new Tree();
}

Tree::~Tree(){
  delete item_;
  delete left;
  delete right;
}

int Tree::CountNodes(){
  int count;
  if(root==0){
    count=0;
  }
  else{
    count=1;
    count+=left->CountNodes();
    count+=right->CountNodes();
  }
  return count;
}

void Tree::PreorderPrint(vector <string> &outstr){
  if(root!=0){
      item_->PrintState(outstr); 
      left->PreorderPrint(outstr);
      right->PreorderPrint(outstr);
  }
}
void Tree::PostorderPrint(vector <string> &outstr){
  if(root!=0){
      left->PostorderPrint(outstr);
      right->PostorderPrint(outstr);
      item_->PrintState(outstr);
  }
}

void Tree::InorderPrint(vector <string> &outstr){
  if(root!=0){
      //cout << outstr.size() << endl;
      left->InorderPrint(outstr);
      item_->PrintState(outstr);
      cout << outstr.size()<< "in tree" << endl;
      right->InorderPrint(outstr);
  }
}
bool Tree::Intree(Tree &node){
  int cmp;
  if(root==0){
    return false;
  } else {
    cmp = item_->Ge(node.item_);
    if (cmp==0){
    return true;
    } else {
      if (cmp<0){
        return left->Intree(node);
      } 
      else{
        return right->Intree(node);
      }
    }
  }
}
void Tree::Insert(Tree &node){
  int cmp;
  if(root==0){
    item_ ->copy(node.item_);
    root = 1;
    left = new Tree();
    right = new Tree();
  } else {
    cmp  = item_->Ge(node.item_);
    if(cmp<0){
      left->Insert(node);
    } else{
        if(cmp==0){
          if(item_->Better(node.item_)>0){
            item_ ->copy(node.item_);
          }
        } else{ 
          right->Insert(node);
        }
      }
  }
}
