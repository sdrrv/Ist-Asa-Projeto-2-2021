#include <iostream>
#include <memory>
#include <vector>
#include <list>
#include <stack>
#include <string>

class Vertex{
  private:
    int _id;
    int _height;
    int _excess;
    std::unique_ptr<std::list<Vertex *>> _adjVertexes; // all the adj vertices
  public:

    Vertex(int ID) 
      :_id(ID), _height(0), _excess(0),
      _adjVertexes(new std::list<Vertex*>){}

    int getId(){
      return _id;
    }

    int getHeight(){
      return _height;
    }
    
    void setHeight(int h) {
      _height = h;
    }

    int getExcess(){
      return _excess;
    }
    
    void addExcess(int x) {
      _excess += x;
    }

    void rmExcess(int x){
      _excess -= x;
    }

    void addadj(Vertex* v){
      _adjVertexes->pop_front();
    }

    std::list<Vertex *>* getAdjs(){
      return _adjVertexes.get();
    }
};


