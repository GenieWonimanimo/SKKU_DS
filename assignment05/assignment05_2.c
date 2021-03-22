#include <stdio.h>
#include <stdlib.h>

typedef enum {CONFIRMED, CLOSE, OTHER} STATE;
typedef struct _GNode
{
    int id;
    int dist; // as weigh
    STATE state;
    struct _GNode* next;
} GNode;

typedef struct
{
    int num;
    int MAXDIST;
    GNode** heads;
} Graph;

// Create a graph
Graph* CreateGraph(int num); // num is number of vertex(size of heads array)
// Destroy a graph
void DestroyGraph(Graph* pgraph);
// Add an undirected edge from src to dst
void AddEdge(Graph* pgraph, int src, int dest);

// Connect vertices and set initial state
Graph* MakeGraph(int n, int M, int x, int y);
// Conv OTHER to CLOSE
void ConvOtherToClose(Graph* pgraph, int id, int dist);
// Return how many close contacts
int HowManyClose(Graph* pgraph);

int main(void)
{
    // n: number of people, M: maximum dist from confirmed
    // x: number of confirmed, y: number of connection
    int n, M, x, y;
    scanf(" %d %d %d %d", &n, &M, &x, &y);
    printf("%d", HowManyClose(MakeGraph(n, M, x, y)));
    return 0;
}

// Create a graph
Graph* CreateGraph(int num) // num is number of vertex(size of heads array)
{
    Graph* graph = (Graph *)malloc(sizeof(Graph));
    graph->num = num;
    graph->heads = (GNode **)malloc(sizeof(GNode *) * num);
    for (int i = 0; i < num; i++)
    {
        // Make a dummy node
        graph->heads[i] = (GNode *)malloc(sizeof(GNode));
        graph->heads[i]->next = NULL;
    }
    return graph;
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
    newNode1->dist = pgraph->heads[dest]->dist;
    newNode1->state = pgraph->heads[dest]->state;
    newNode1->next = NULL;

    cur = pgraph->heads[src]; // create a node for dest in src
    while (cur->next != NULL) // unsorted
    {
        cur = cur->next; // pararrel edges
        if (cur->id == newNode1->id) // is newNode already in src?
        {
            free(newNode1);
            return;
        }
    }
    if (cur->id == newNode1->id) // for the last node
    {
        free(newNode1);
        return;
    }
    cur->next = newNode1;

    // graph is undirected, so we don't have to check whether newNode is already in src
    newNode2 = (GNode *)malloc(sizeof(GNode));
    newNode2->id = src;
    newNode2->dist = pgraph->heads[src]->dist;
    newNode2->state = pgraph->heads[src]->state;
    newNode2->next = NULL;

    cur = pgraph->heads[dest]; // create a node for src in dest
    while (cur->next != NULL)
        cur = cur->next;
    cur->next = newNode2;
}
// Connect vertices and set initial state
Graph* MakeGraph(int n, int M, int x, int y)
{
    Graph* graph = CreateGraph(n);
    for (int i = 0; i < n; i++)
    {
        graph->heads[i]->dist = 10000;
        graph->heads[i]->state = OTHER;
    }
    for (int i = 0; i < x; i++)
    {
        int id;
        scanf(" %d", &id);
        graph->heads[id]->dist = 0;
        graph->heads[id]->state = CONFIRMED;
    }
    for (int i = 0; i < y; i++)
    {
        int personA, personB;
        scanf(" %d %d", &personA, &personB); // same pair can be given multiple times
        AddEdge(graph, personA, personB); // connect regionA and regionB
    }
    graph->MAXDIST = M;
    return graph;
}
// Conv OTHER to CLOSE
void ConvOtherToClose(Graph* pgraph, int id, int dist)
{
    if (dist > pgraph->MAXDIST) return;
    else
    {
        GNode* cur = pgraph->heads[id]->next;
        while (cur != NULL)
        {
            if (pgraph->heads[cur->id]->state != CONFIRMED) // we don't have to change or recur func if state is CONFIRMED
            {
                if (dist < pgraph->heads[cur->id]->dist) // is this route is shorter than prev?
                {
                    pgraph->heads[cur->id]->state = CLOSE;
                    pgraph->heads[cur->id]->dist = dist;
                    ConvOtherToClose(pgraph, cur->id, dist + 1); // in the next stack, dist from CONFIRMED be far
                }
            }
            cur = cur->next;
        }
    }    
}
// Return how many close contacts
int HowManyClose(Graph* pgraph)
{
    int numOfClose = 0;
    // conv state of nodes that adjacent with CONFIRMED
    for (int i = 0; i < pgraph->num; i++)
        if (pgraph->heads[i]->state == CONFIRMED)
            ConvOtherToClose(pgraph, i, 1);

    // cal the num of CLOSE
    for (int i = 0; i < pgraph->num; i++)
        if (pgraph->heads[i]->state == CLOSE) numOfClose++;
    
    DestroyGraph(pgraph);
    return numOfClose;
}

/* res: 6
12 2 3 13
0 11 7
0 1
6 0
0 6
2 6
2 8
8 9
2 9
2 3
3 5
3 7
4 7
7 4
3 7
*/

/* res: 4
10 2 1 10
2
0 1
1 2
2 3
3 4
4 5
5 6
6 7
7 8
8 9
9 0
*/

/* shortest dist res: 9
10 4 1 12
0
4 3
0 2
0 4
2 3
1 2
2 5
5 6
6 7
7 8
8 9
2 7
1 0
*/