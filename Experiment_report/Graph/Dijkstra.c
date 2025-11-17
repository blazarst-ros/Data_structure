#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#define MAXNUM 100
#define INFI 99999999
int Graphmatrix[MAXNUM][MAXNUM]; // initialized by 0
int Dijk[MAXNUM];                // initialized by INFI
bool Done[MAXNUM];
int cnt = 0; // Counting True numbers in Done array
typedef struct edge
{
    int V1, V2;
    int weight;
} Edge;
typedef struct sure
{
    int vertex;
    int dist;
} Sure;
Sure s;
void InsertEdge(int edgenum,FILE *fp);
void Dijkstra(int vertexnum);
void Enumerate(int vertexnum, FILE * fo);
int min(int a, int b);
int main()
{
    FILE * fp=fopen("Example.txt","r");
    FILE * fo=fopen("Print.txt","w");
    for (int i = 0; i < MAXNUM; i++)
    {
        for (int j = 0; j < MAXNUM; j++)
        {
            Graphmatrix[i][j] = INFI; // 初始化为无穷大（无连接）
        }
        Graphmatrix[i][i] = 0; // 顶点到自身距离为0
    }
    s.dist = 0;
    s.vertex = 0;
    Dijk[0] = 0;
    memset(Done, 0, sizeof(Done));
    int vertexnum, edgenum;
    fscanf(fp,"%d %d", &vertexnum, &edgenum);
    for (int i = 1; i < vertexnum; i++)
        Dijk[i] = INFI;

    
    InsertEdge(edgenum,fp);
    Dijkstra(vertexnum);
    Enumerate(vertexnum,fo);
    return 0;
}
void InsertEdge(int edgenum,FILE *fp)
{
    for (int i = 0; i < edgenum; i++)
    {
        Edge E;
        fscanf(fp,"%d %d %d", &E.V1, &E.V2, &E.weight);
        Graphmatrix[E.V1][E.V2] = E.weight;
        Graphmatrix[E.V2][E.V1] = E.weight;
    }
}

void Dijkstra(int vertexnum)
{
    while (1)
    {

        // Enumerate Adjacent Nodes
        for (int i = 0; i < vertexnum; i++)
        {
            if (Graphmatrix[s.vertex][i] != INFI)
            {
                Dijk[i] = min(s.dist + Graphmatrix[s.vertex][i], Dijk[i]);
            }
        }
        // search For Surely Lowest Vertex
        s.dist = INFI;
        for (int i = 0; i < vertexnum; i++)
        {
            
            if (Dijk[i] < s.dist&&!Done[i])
            {
                s.dist = Dijk[i];
                s.vertex = i;
            }
        }
        Done[s.vertex] = true;
        cnt++;
        if (cnt == vertexnum)
            break;
    }
}
void Enumerate(int vertexnum,FILE* fo)
{
    for (int i = 0; i < vertexnum; i++)
    {
        fprintf(fo,"%d To Oringin's min Distance is %d\n", i, Dijk[i]);
    }
}
int min(int a, int b)
{
    if (a - b < 0)
        return a;
    return b;
}