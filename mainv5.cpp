#include <cstddef>
#include <functional>
#include <iostream>
#include <memory>
#include <vector>
#include <list>
#include <stack>
#include <string>
#include <unordered_map>

struct Vertex;

typedef enum COLOR {WHITE, GRAY, BLACK} color; //enum COLOR that represents the color of the given vertex

std::vector<std::vector<int>> costs;
std::vector<Vertex> vertexes;
std::unordered_map<int, int> cutHash;
std::list<int> cutList;


struct Arc{
    int cap, destId;

    Arc(int c, int id)
            : cap(c), destId(id) {}
};

struct Vertex{
    int h, e;
    color c;
    std::unique_ptr<std::list<Arc>> adjs;
    std::unique_ptr<std::list<int>> priorityQueue;

    Vertex()
        : h(0), e(0), c(WHITE),
              adjs(new std::list<Arc>),
              priorityQueue(new std::list<int>) {}

    void createArc(int cap, int destId){
        adjs->push_back(Arc(cap, destId));
    }

    std::list<int>* getAdjs(){
        return priorityQueue.get();
    }

    std::list<Arc>* getArcs(){
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
        vertexes[i].createArc(costy, numVertexes + 1);

        costs[0][i] = costx;
        costs[i][numVertexes + 1] = costy;

        vertexes[0].priorityQueue->push_back(i);
        vertexes[i].priorityQueue->push_back(numVertexes + 1);
    }

    for (int i = 0; i < numCosts; i++){
        int v1, v2, cost;
        scanf("%d %d %d", &v1, &v2, &cost);
        vertexes[v1].createArc(cost, v2);
        vertexes[v2].createArc(cost, v1);
        costs[v1][v2] = cost;
        costs[v2][v1] = cost;

        vertexes[v1].priorityQueue->push_back(v2);
        vertexes[v2].priorityQueue->push_back(v1);
    }


    for (int i = 1; i < numVertexes + 1; i++)
        vertexes[i].priorityQueue->push_back(0);
}

void BFS(){
    std::list<int> vStack;
    vertexes[0].c = GRAY;
    vStack.push_back(0);
    int v;
    while (!vStack.empty()) {
        v = vStack.front();
        cutList.push_back(v);
        cutHash.insert(v, v);
        vStack.pop_front();
        for (int u : (*(vertexes[v].getAdjs()))) {
            if (vertexes[u].c == WHITE && costs[v][u] > 0){
                vertexes[u].c = GRAY;
                vStack.push_back(u);
            }
        }
        vertexes[v].c = BLACK;
    }
}

int getRes(){
    int res = 0;
    for(int v : cutList){
        for (Arc& arc : (*(vertexes[v].getArcs()))){
            if (cutHash.contains(arc.destId))
                continue;
            else 
                res += arc.cap;
        } 
    }
    return res;
}

int main(){
    processInput();

    for (int i = 0; i < 6; i++){

        std::list<Arc> alo = *(vertexes[i].adjs);
        std::list<Arc>::iterator it;
        std::cout << "Vertice " << i << std::endl;
        for (it = alo.begin(); it != alo.end(); ++it){
            std::cout << it->cap << " ---- " << it->destId << std::endl;
        }

        std::cout << "Priority " << std::endl;
        std::list<int> alo2 = *(vertexes[i].priorityQueue);
        for (int& oioi : alo2){
            std::cout << oioi << " ";
        }
        std::cout << std::endl;
    }
    for(int x = 0; x < 6; x++){
        for(int j = 0; j < 6; j++)
            std::cout << "cost[" << x << "][" << j << "] = " << costs[x][j] << std::endl;
    }
}
 
