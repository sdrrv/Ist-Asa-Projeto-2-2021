#include <iostream>
#include <memory>
#include <vector>
#include <list>

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
    std::unique_ptr<std::list<Arc>> adjs;
    std::unique_ptr<std::list<int>> priorityQueue;

    Vertex()
        : h(0), e(0),
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

void processInput(){ // will process the input given into the vertexes list and cost matrix.
    int numVertexes, numCosts;
    scanf("%d %d", &numVertexes, &numCosts); // Will recive the num os vertices and the number of connections.

    costs.reserve(numVertexes + 2);
    for (int i = 0; i < numVertexes + 2; i++){ // Creates the matrix costs
        costs.push_back(std::vector<int>());
        costs[i].reserve(numVertexes + 2);
        for (int j = 0; j < numVertexes + 2; j++)
            costs[i].push_back(0);
    }

   vertexes.reserve(numVertexes + 2);
    for (int i = 0; i < numVertexes + 2; i++){ // Creates the vertexes
        vertexes.push_back(Vertex());
    }


    for (int i = 1; i <= numVertexes; i++){ // Will populate the cost matrix, create the arcs between vertixes and create the connctions to the X and Y vertixes.
        int costx, costy;
        scanf("%d %d", &costx, &costy);
        vertexes[0].createArc(costx, i);
        vertexes[i].createArc(costy, numVertexes + 1);

        costs[0][i] = costx;
        costs[i][numVertexes + 1] = costy;

        vertexes[i].priorityQueue->push_back(numVertexes + 1);
        vertexes[0].priorityQueue->push_back(i);
        vertexes[i].priorityQueue->push_back(0);
    }

    /*for (int i = 1; i < numVertexes + 1; i++) // Will add the Vertex X to the priority Queue of all the vertexes.
        vertexes[i].priorityQueue->push_back(0);*/

    for (int i = 0; i < numCosts; i++){ // Will 
        int v1, v2, cost;
        scanf("%d %d %d", &v1, &v2, &cost);
        vertexes[v1].createArc(cost, v2);
        vertexes[v2].createArc(cost, v1);
        costs[v1][v2] = cost;
        costs[v2][v1] = cost;

        vertexes[v1].priorityQueue->push_back(v2);
        vertexes[v2].priorityQueue->push_back(v1);
    }


}


void pushFlow(int v, int u){
    int excess = vertexes[v].e;
    int value = costs[v][u] <= excess || v == 0 ? costs[v][u] : excess;
    costs[v][u] -= value;
    costs[u][v] += value;
    vertexes[v].e -= value;
    vertexes[u].e += value;

}


void initPreFlow(std::list<int>& _queue ){
    vertexes[0].h = vertexes.size();
    for (Arc& arc : *(vertexes[0].getArcs()) ){
        pushFlow(0, arc.destId);
        _queue.push_back(arc.destId);
    }
}



void discharge(int v){
    Vertex& currentV = vertexes[v];
    while(currentV.e > 0){
        int aux = currentV.getAdjs()->front();
        bool newHeight = true;
        for(int& u : *(currentV.getAdjs())){
            if ( vertexes[u].h < currentV.h && costs[v][u] > 0 ){
                pushFlow(v, u);
                newHeight = false;
                break;
            }
            else if (costs[v][aux] <= 0 || (vertexes[u].h < vertexes[aux].h && costs[v][u] > 0))
                aux = u;
        }
        if (newHeight){
            vertexes[v].h = vertexes[aux].h + 1;
            pushFlow(v,aux);
        }
    }
}


void relabelToFront(){
    std::list<int> _queue;
    initPreFlow(_queue);
    std::list<int>::iterator iter = _queue.begin();
    int oldHeight;
    while (iter != _queue.end()){
        oldHeight = vertexes[*iter].h;
        discharge(*iter);
        if(vertexes[*iter].h > oldHeight){
            int value = *iter;
            _queue.erase(iter);
            _queue.push_front(value);
            iter = _queue.begin();
        }
        iter++;
    }
}


int main(){
    processInput();
    relabelToFront();
    std::cout<< -vertexes[0].e << std::endl; // Podiamos tambem usar o numVertexes + 1.
    

}

