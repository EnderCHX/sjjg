#include<bits/stdc++.h>
using namespace std;

#define OK 1
#define Maxint INT_MAX
#define MAX_VERTEX 100
typedef int status ;

typedef struct
{
    char vexs[MAX_VERTEX];
    int arcs[MAX_VERTEX][MAX_VERTEX];
    int vexnum,arcnum;
}Graph;

status LocateVex(Graph G,int u)
{
    int i;
    for(i = 0; i < G.vexnum; i++)
    if(u == G.vexs[i]) return i;
    return -1;  
}

status CreateUDN(Graph &G)
{
    cout << "输入总顶点数，总边数 " << endl;
    cin >> G.vexnum >> G.arcnum;
    cout << "依次输入点的信息" << endl;
    for(int i = 0; i < G.vexnum; i++)
        cin >> G.vexs[i];

    for(int i = 0;i < G.vexnum; i++)    //初始化邻接矩阵，边的权值均为Maxint 
        for(int j = 0; j < G.vexnum; j++)
            G.arcs[i][j] = Maxint;
            
    for(int k = 0; k < G.arcnum; k++)   //构造邻接矩阵 
    {
        char v1, v2;
        int w;
        cin >> v1 >> v2 >> w;       //输入一条边依附的顶点及权值 
        int i = LocateVex(G,v1);
        int j = LocateVex(G,v2); //确定v1，v1在G中的位置，即顶点数组的下标 
        G.arcs[i][j] = w;       //边<v1,v2>的权值置为w 
        G.arcs[j][i] = G.arcs[i][j];	//置<v1,v2>的对称边<v2,v1>的权值为w	
    }
    return OK;
}

status FirstNeightbor(Graph &G, int i)
{
    for(int j = 0; j < G.vexnum; j++)
    {
        if(G.arcs[i][j] > 0 && G.arcs[i][j] != Maxint)
        {
            return j;
        }
    }
    return -1;
}

status NextNeightBor(Graph &G, int i, int j)
{
    for(int k = j + 1; k < G.vexnum; k++)
    {
        if(G.arcs[i][k] > 0 && G.arcs[i][k] != Maxint)
        {
            return k;
        }
    }
    return -1;
}

int FindVex(Graph &G, char u)
{
    for(int i = 0; i < G.vexnum; i++)
    {
        if(G.vexs[i] == u)
        {
            return i;
        }
    }
    return -1;
}

void DFS(Graph &G, int *visited, int i)
{
    int j;
    cout << G.vexs[i] << " ";
    visited[i] = 1;
    for(j = 0; j < G.vexnum; j++)
    {
        if(G.arcs[i][j] != 0 && G.arcs[i][j] != Maxint && !visited[j])
        {
            DFS(G, visited, j);
        }
    }
}

void DFST(Graph &G)
{
    int i, visited[G.vexnum];
    for(i = 0; i < G.vexnum; i++)
    {
        visited[i] = 0;
    }
    for(i = 0; i < G.vexnum; i++)
    {
        if(!visited[i])
        {
            DFS(G, visited, i);
        }
    }
    cout << endl;
}

typedef struct
{
    char data[MAX_VERTEX];
    int front;
    int rear;
}SqQueue;

// 初始化队列
void InitQueue(SqQueue &Q)
{
    Q.front = 0;
    Q.rear = 0;
}

bool EnQueue(SqQueue &Q, char e)
{
    if( ( Q.rear+1 ) % MAX_VERTEX == Q.front )
        return false;
    Q.data[Q.rear]=e;
    Q.rear = (Q.rear+1)%MAX_VERTEX;
    return true;
}

char* DeQueue(SqQueue &Q, char *e)
{
    if( Q.front == Q.rear )
        return NULL;
    *e = Q.data[Q.front];
    Q.front = (Q.front+1)%MAX_VERTEX;
    return e;
}

bool isEmptyQueue(SqQueue &Q)
{
    return Q.front == Q.rear ? true : false;
}

void BFST(Graph &G)
{
    SqQueue Q;
    int i, j, mark, visited[G.vexnum];
    char data;
    for(i = 0; i < G.vexnum;i++)
        visited[i] = false;
    InitQueue(Q);
    for(i=0; i < G.vexnum; i++)
    {
        if(!visited[i])
        {
            visited[i] = 1;
            EnQueue(Q,G.vexs[i]);
            while(!isEmptyQueue(Q))
            {
                DeQueue(Q,&data);  //队首顶点出队，并赋值给data
                cout << data << " ";
                //找所删除顶点的下标，更新该下标值，以便正确找到与出队元素相连的其他顶点
                for( j = 0; j < G.vexnum; j++)
                    if(G.vexs[j] == data )
                        mark = j ;
                //找寻与此顶点相连且未被访问的顶点，逐次标记、打印，并入队
                for(j=0;j<G.vexnum;j++)
                {
                    if(G.arcs[mark][j]==1 && !visited[j])
                    {
                        visited[j] = 1;
                        printf("%c ",G.vexs[j]);
                        EnQueue(Q,G.vexs[j]);
                    }
                }
            }
        }
    }
    cout << endl;
}

int main()
{
    cout << "\033[36m\033[1m";
    Graph G;
    CreateUDN(G);
    cout << "邻接矩阵为：" << endl;
    for(int i = 0; i < G.vexnum; i++)
    {
        for(int j = 0; j < G.vexnum; j++)
        cout << G.arcs[i][j] << " ";
        cout << endl;
    }
    cout << FirstNeightbor(G , 0) << endl;
    cout << NextNeightBor(G, 0, 2) << endl;
    cout << FindVex(G, 'A') << endl;
    DFST(G);
    BFST(G);
    cout << "\033[0m";
    return 0;
}
