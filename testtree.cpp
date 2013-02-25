#include "tree.h"
#include "item.h"
int main(int argc, char* argv){
  Item* item = new Item(1.0);
  item->PrintState();
  Tree *root = new Tree(item);
  Item* item1 = new Item(3.0);
  Tree *node1 = new Tree(item1);
  root->Insert(*node1);
  Item* item2 = new Item(-1.0);
  Tree *node2 = new Tree(item2);
  root->Insert(*node2);
  root->PreorderPrint();  
  root->PostorderPrint();
  root->InorderPrint();
  delete root;
  delete node1;
  delete node2;
}
