#include <iostream>
#include <memory>
#include <vector>
#include <list>

struct Vertex;


std::vector<std::vector<int>> costs;
std::vector<Vertex> vertexes;



struct Vertex{
    int h, e;
    std::unique_ptr<std::vector<int>> priorityQueue;

    Vertex()
        : h(0), e(0),
              priorityQueue(new std::vector<int>) {}


    std::vector<int>* getAdjs(){
        return priorityQueue.get();
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
        vertexes[i].getAdjs()->reserve(numVertexes);
    }


    for (int i = 1; i <= numVertexes; i++){ // Will populate the cost matrix, create the arcs between vertixes and create the connctions to the X and Y vertixes.
        int costx, costy;
        scanf("%d %d", &costx, &costy);

        costs[0][i] = costx;
        costs[i][numVertexes + 1] = costy;

        vertexes[i].priorityQueue->push_back(numVertexes + 1);
        vertexes[0].priorityQueue->push_back(i);
        vertexes[i].priorityQueue->push_back(0);
    }

    for (int i = 0; i < numCosts; i++){ // Will populate the adj vertixes of each vertex
        int v1, v2, cost;
        scanf("%d %d %d", &v1, &v2, &cost);
        costs[v1][v2] = cost;
        costs[v2][v1] = cost;

        vertexes[v1].priorityQueue->push_back(v2);
        vertexes[v2].priorityQueue->push_back(v1);
    }


}


void pushFlow(int v, int u){ // Will push the avalible flow trough vertexes
    int excess = vertexes[v].e;
    int value = costs[v][u] <= excess || v == 0 ? costs[v][u] : excess;
    costs[v][u] -= value;
    costs[u][v] += value;
    vertexes[v].e -= value;
    vertexes[u].e += value;

}


void initPreFlow(std::list<int>& _queue ){ // Will send the inicial flux to all the vertexes, from the X vertex
    vertexes[0].h = vertexes.size();
    for (int& u : *(vertexes[0].getAdjs()) ){
        pushFlow(0, u);
        _queue.push_back(u);
    }
}


void discharge(int v){ // Will discharge the vertexes in the priorityQueue till they have flux 0.
    Vertex& currentV = vertexes[v];
    while(currentV.e > 0){
        int aux = currentV.getAdjs()->front();

        for(int& u : *(currentV.getAdjs())){
            if ( vertexes[u].h < currentV.h && costs[v][u] > 0 ){
                pushFlow(v, u);
                if (vertexes[v].e == 0)
                    return;
            }
            else if (costs[v][aux] <= 0 || (vertexes[u].h < vertexes[aux].h && costs[v][u] > 0))
                aux = u;
        }
        vertexes[v].h = vertexes[aux].h + 1;
        pushFlow(v,aux);
    }
}


void relabelToFront(){ // The relabel to front algorithm
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


int main(){ // Main func
    processInput(); //Process the Input
    relabelToFront(); // Relabel To Front
    std::cout<< -vertexes[0].e << std::endl; // Print the maxFlow / Result


}
