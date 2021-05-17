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
    std::unique_ptr<std::vector<Vertex *>> _Vertexes; // All the vertexes in the graph
    std::unique_ptr<std::vector<std::vector<int>>> _adjMatrix; // AdjMatrix
  public:
    Graph(): _Vertexes(new std::vector<Vertex *> ),
    _adjMatrix(new std::vector<std::vector<int>>){ _size = 0; }

    void setSize(int size){
      _size = size;
      _Vertexes->reserve(10);
    }

    Vertex *getVertex(int ID){ 
      return (*_Vertexes)[ID];
    }

    std::vector<int> operator[](int index){
      return (*_adjMatrix)[index];
    }
    
    void addVertex(Vertex* vertex){
      _Vertexes->push_back(vertex);
    }

    int getMatrixValue(int Linha, int Coluna){
      return (*_adjMatrix)[Linha][Coluna];
    }
};

int main(){
}







