#include <cstddef>
#include <iostream>
#include <memory>
#include <vector>
#include <list>
#include <stack>
#include <string>

struct Vertex;

std::vector<std::vector<int>> costs;
std::vector<Vertex> vertexes;

struct Arc{
    int cap, destId;

    Arc(int c, int id)
            : cap(c), destId(id) {}
};

struct Vertex{
    int h, e;
    std::unique_ptr<std::list<std::unique_ptr<Arc>>> adjs;
    std::unique_ptr<std::list<int>> priorityQueue;

    Vertex()
            : h(0), e(0),
              adjs(new std::list<std::unique_ptr<Arc>>),
              priorityQueue(new std::list<int>) {}

    void createArc(int cap, int destId){
        adjs->push_back(std::unique_ptr<Arc>(new Arc(cap, destId)));
    }

    std::list<std::unique_ptr<Arc>>* oi(){
        return adjs.get();
    }
};

void processInput(){
    int numVertexes, numCosts;
    scanf("%d %d", &numVertexes, &numCosts);

    costs.reserve(numVertexes + 2);
    for (int i = 0; i < numVertexes + 2; i++){
        costs.push_back(std::vector<int>());
        costs[i].reserve(numVertexes + 2);
        for (int j = 0; j < numVertexes + 2; j++)
            costs[i].push_back(0);
    }

    vertexes.reserve(numVertexes + 2);
    for (int i = 0; i < numVertexes + 2; i++){
        vertexes.push_back(Vertex());
    }


    for (int i = 1; i <= numVertexes; i++){
        int costx, costy;
        scanf("%d %d", &costx, &costy);
        vertexes[0].createArc(costx, i);
        vertexes[i].createArc(costy, numVertexes + 2);

        costs[0][i] = costx;
        costs[i][numVertexes + 2] = costy;
    }

    for (int i = 0; i < numCosts; i++){
        int v1, v2, cost;
        scanf("%d %d %d", &v1, &v2, &cost);
        vertexes[v1].createArc(cost, v2);
        vertexes[v2].createArc(cost, v1);
        costs[v1][v2] = cost;
        costs[v2][v1] = cost;
    }
}

int main(){
    processInput();

    for (int i = 0; i < 6; i++){

        std::list<std::unique_ptr<Arc>> alo = (*vertexes[i].oi());
        std::list<std::unique_ptr<Arc>>::iterator it;
        for (it = alo.begin(); it != alo.end(); ++it){
            std::cout << it->get()->cap << " ---- " << it->get()->destId << std::endl;
        }

        for(int x = 0; x < 6; x++){
            for(int j = 0; j < 6; j++)
                std::cout << "cost[" << x << "][" << j << "] = " << costs[x][j] << std::endl;
        }
    }
}
