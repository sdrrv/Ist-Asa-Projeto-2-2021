#include <cstddef>
#include <iostream>
#include <memory>
#include <vector>
#include <list>
#include <stack>
#include <string>


struct Arc{
  int _cap,_ID;

  Arc(int cap, int ID){
    _cap = cap;
    _ID = ID;
  }
};


struct Vertex{
  int h, e;
  std::list<std::unique_ptr<Arc>> _arcs;

 

  void addArc(int cap, int id){
    _arcs.push_front( new std::unique_ptr<Arc> (cap, id));
  }

};


std::vector<std::list>
