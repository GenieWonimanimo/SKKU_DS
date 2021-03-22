/*
complete graph -> all vertices are adjacent to any other vertices
undirected -> n(n-1)/2 edges
directed -> n(n-1) edges

Dense graph
|E| = |V|^2
represented as an adjacency matrix

Spare graph
|E| << |V|^2 or |E| = |V|
represented as an adjacency list

Complexity of graph algo is typically defined in terms of
Number of vertices |V|, number of edges|E|, or both


Adjacency Matrix
allocate |v| * |V| matrix M
M[i][j] = 1 if there is an edge between vi and vj
undirected -> symmetric
directed -> unsymemetric

Adjacenct List
allocate an array called heads
heads[i] points to a linked list of nodes connected to vi

nodes in adjacency list == edges in graph
*/
#include <stdio.h>

typedef struct _GNode
{
    int id;
    struct _GNode* next;
} GNode;

typedef struct
{
    int num;
    GNode** heads;
} Graph;

// Create a graph
void CreateGraph(Graph* pgraph, int num); // num is number of vertex(size of heads array)
// Destroy a graph
void DestroyGraph(Graph* pgraph);
// Add an undirected edge from src to dst
void AddEdge(Graph* pgraph, int src, int dest);
// Print a graph for each vertex
void PrintGraph(Graph* pgraph);

// DFS and BFS is also used to count the number of vertices in the connected component
// Depth first search (use stack)
/*
visit the start vertex
visit one of unvisited vertices neighboring to the start vertex
repeat step 2 until there is no more unvisited vertex
if there is no more unvisited vertex, go back one step and visit another unvisited vertex
*/
void DFS(Graph* pgraph); 
// Breadth first search (use queue)
/*
visit the start vertex
visit all unvisited vertices neighboring to the start vertex
repeat step 2 until there is no unvisited vertex
*/
void BFS(Graph* pgraph);

int main(void)
{

    return 0;
}

// Create a graph
void CreateGraph(Graph* pgraph, int num) // num is number of vertex(size of heads array)
{
    pgraph->num = num;
    pgraph->heads = (GNode **)malloc(sizeof(GNode *) * num);
    for (int i = 0; i < num; i++)
    {
        // Make a dummy node
        pgraph->heads[i] = (GNode *)malloc(sizeof(GNode));
        pgraph->heads[i]->next = NULL;
    }
}
// Destroy a graph
void DestroyGraph(Graph* pgraph)
{
    for (int i = 0; i < pgraph->num; i++)
    {
        GNode* cur = pgraph->heads[i];
        while (cur != NULL)
        {
            GNode* temp = cur;
            cur = cur->next;
            free(temp);
        }
    }
    free(pgraph->heads);
}
// Add an undirected edge from src to dst
void AddEdge(Graph* pgraph, int src, int dest)
{
    GNode* newNode1, *newNode2, *cur;
    newNode1 = (GNode *)malloc(sizeof(GNode));
    newNode1->id = dest;
    newNode1->next = NULL;

    cur = pgraph->heads[src]; // create a node for dest in src
    while (cur->next != NULL) // unsorted
        cur = cur->next; // pararrel edges
    cur->next = newNode1;

    newNode2 = (GNode *)malloc(sizeof(GNode));
    newNode2->id = src;
    newNode2->next = NULL;

    cur = pgraph->heads[dest]; // create a node for src in dest
    while (cur->next != NULL)
        cur = cur->next;
    cur->next = newNode2;
}
// Print a graph for each vertex
void PrintGraph(Graph* pgraph);

// Depth first search
/*
void DFS(Graph* pgraph)
{
    Stack stack;
    bool* visited = (bool *)malloc(sizeof(bool) * pgraph->num);
    for (int i = 0; i < pgraph->num; i++)
        visited[i] = false; // make all vertices unvisited
    
    InitStack(&stack);
    Push(&stack, 0); // Push the initial vertex
    while (!IsSEmpty(&stack))
    {
        GNode* cur;
        int vtx = SPeek(&stack);
        Pop(&stack);

        // skip if the vertex has been visited
        if (visited[vtx]) continue;
        else
        {
            visited[vtx] = true;
            printf("%d ", vtx);
        }

        // Push the vertex if it has not been visited
        cur = pgraph->heads[vtx]->next;
        while (cur != NULL)
        {
            if (!visited[cur->id])
                Push(&stack, cur->id);
            cur = cur->next;
        }
    }
}
*/
// Breadth first search
/*
void BFS(Graph* pgraph)
{
    Queue queue
    bool* visited = (bool *)malloc(sizeof(bool) * pgraph->num);
    for (int i = 0; i < pgraph->num; i++)
        visited[i] = false; // Make all vertices unvisited

    InitQueue(&queue);
    EnQueue(&queue, 0); // Enqueue the initial vertex
    while (!IsQEmpty(&queue))
    {
        GNode* cur;
        int vtx = QPeek(&queue);
        DeQueue(&queue);

        // Skip if the vertex has been visited
        if (visited[vtx]) continue;
        else
        {
            visited[vtx] = true;
            printf("%d ", vtx);
        }

        // Enqueue the vertex if it has been unvisited
        cur = pgraph->heads[vtx]->next;
        while (cur != NULL)
        {
            if (!visited[cur->id])
                EnQueue(&queue, cur->id);
            cur = cur->next;
        }
    } 
}
*/