#include <cstddef>
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

class Graph{
  private:
    int _size;
    std::unique_ptr<std::list<Vertex *>> _Vertexes; // All the vertexes in the graph
    std::unique_ptr<std::vector<std::vector<int>> > _adjMatrix; // AdjMatrix
  public:
    Graph(): _Vertexes(new std::list<Vertex *> ),
    _adjMatrix(new std::vector<std::vector<int>>){ _size = 0; }

    void setSize(int size){
      _size = size;
      _Vertexes->reverse(_size);
    }

    Vertex *getVertex(int ID){ // Se mudarmos o _Vertexes para um vector podemos aceder a cada vertice em O(1), esta assim porque n quero alterar sem te perguntar primeiro.
      for (Vertex *vertex : *_Vertexes){
        if(vertex->getId() == ID)
          return vertex;
      }
      return NULL;
    }
    
    void addVertex(Vertex* vertex){
      _Vertexes->push_front(vertex);
    }

    int getMatrixValue(int Linha, int Coluna){
      return (*_adjMatrix)[Linha][Coluna];
    }
};







