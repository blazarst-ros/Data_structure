#include<stdio.h>
#include<stdlib.h>
#include <stdbool.h>
#include<string.h>
#define MaxNum 100
bool visited[MaxNum];
//Edge defination(only for input)
typedef struct Enode * PtEN;
struct  Enode
{
    int V1,V2;
    int weight;
};
typedef PtEN Edge;

//Adjacent Node defination(store both relationship and weight)
typedef struct Adjnode * PtAdjN;
struct Adjnode
{
    int AdjV; //number of the node
    PtAdjN Next;
    int weight;
};

//Head Node Defination
typedef struct Vnode
{
    PtAdjN FirstEdge;
    int data;
}AdjList[MaxNum];

//Truly Graph (Integrated Data type)
typedef struct GNode *PtrToGNode;
struct GNode{
    int Nv;
    int Ne;
    AdjList G;
};
typedef PtrToGNode LGraph;

LGraph CreateGraph(int vertexnum);
void InsertEdge(LGraph Graph,Edge E); //LGgraph is an Pointer 
void DFS(LGraph G,int V);

int main()
{
    memset(visited,0,sizeof(bool)*MaxNum);
    int vertexnum,edgenum;
    scanf("%d %d",&vertexnum,&edgenum);
    LGraph Graph=CreateGraph(vertexnum);
    Graph->Ne=edgenum;
    Graph->Nv=vertexnum;
    for(int i=0;i<edgenum;i++){
        Edge E=(Edge)malloc(sizeof(struct Enode));//U must allocate a space for a pointer
        scanf("%d %d %d",&E->V1,&E->V2,&E->weight);
        InsertEdge(Graph,E);
        free(E);
    }
    DFS(Graph,0);

    return 0;
}

LGraph CreateGraph(int vertexnum){
    LGraph Graph;
    int v;//Create an Graph without any Edge
    Graph = (LGraph)malloc(sizeof(struct GNode));
    Graph->Nv=vertexnum;
    Graph->Ne=0;  //without edge
    for(v=0;v<Graph->Nv;v++){
        Graph->G[v].FirstEdge=NULL;
        Graph->G[v].data=v;
    }

    return Graph;
}
void InsertEdge(LGraph Graph,Edge E){ //U Shall Create an Edge type in Cycle! (V1->V2)
    //1.insert Edge Node in the type of PtAdjN
    PtAdjN Newnode;//a pointer point to Edge Node
    Newnode=(PtAdjN)malloc(sizeof(struct Adjnode));//get a space while assign a value to pointer
    Newnode->AdjV=E->V2;//to store which the edge point to instead of inserting into LGraph
    Newnode->weight=E->weight;
    //insert into LGraph
    Newnode->Next=Graph->G[E->V1].FirstEdge;
    Graph->G[E->V1].FirstEdge=Newnode;//Newnode is a pointer
    

    Newnode=(PtAdjN)malloc(sizeof(struct Adjnode));
    Newnode->AdjV=E->V1;
    Newnode->weight=E->weight;
    Newnode->Next=Graph->G[E->V2].FirstEdge;
    Graph->G[E->V2].FirstEdge=Newnode;

    //double edged graph;
}
void DFS(LGraph Graph,int V){
    printf("Now Visiting Vertex : %d \n",V);
    visited[V]=true;
    PtAdjN Ptr = Graph->G[V].FirstEdge;
    while(Ptr){
        if(!visited[Ptr->AdjV]){
            DFS(Graph,Ptr->AdjV);
        }
        Ptr=Ptr->Next;
    }
    if(!Ptr)
    
    printf(" %d is Over!\n",V);
}