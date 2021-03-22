#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
typedef struct _GNode
{
    int id;
    int color;
    struct _GNode* next;
} GNode;

typedef struct
{
    int num;
    GNode** heads;
} Graph;

// Create a graph
Graph* CreateGraph(int num); // num is number of vertex(size of heads array)
// Destroy a graph
void DestroyGraph(Graph* pgraph);
// Add an undirected edge from src to dst
void AddEdge(Graph* pgraph, int src, int dest);

// Connect vertices and set color
Graph* MakeGraph(int n, int m);
// visit all regions in the country
void VisitRegionInCountry(Graph* countries, int id, bool* visited);
// Return how many countries, not adjacent and other color -> other country
int HowManyCountries(Graph* pgraph);

int main(void)
{
    int n, m; // n: number of nodes, m: number of edges
    scanf(" %d %d", &n, &m);
    printf("%d", HowManyCountries(MakeGraph(n, m)));
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
    newNode1->color = pgraph->heads[dest]->color;
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
    newNode2->color = pgraph->heads[src]->color;
    newNode2->next = NULL;

    cur = pgraph->heads[dest]; // create a node for src in dest
    while (cur->next != NULL)
        cur = cur->next;
    cur->next = newNode2;
}
// Connect vertices and set color
Graph* MakeGraph(int n, int m)
{
    Graph* graph = CreateGraph(n);
    for (int i = 0; i < n; i++)
    {
        int color;
        scanf(" %d", &color);
        graph->heads[i]->color = color;
    }
    for (int i = 0; i < m; i++)
    {
        int regionA, regionB;
        scanf(" %d %d", &regionA, &regionB); // same pair can be given multiple times
        AddEdge(graph, regionA, regionB); // connect regionA and regionB
    }
    return graph;
}
// visit all regions in the country
void VisitRegionInCountry(Graph* countries, int id, bool* visited)
{
	if (visited[id]) return;
	else
	{
		GNode* cur = countries->heads[id];
		visited[id] = true;
		while (1)
		{
			cur = cur->next;
            if (cur == NULL) break;
			if (visited[cur->id]) continue;
			else VisitRegionInCountry(countries, cur->id, visited);
		}
	}
}
// Return how many countries, not adjacent and other color -> other country
int HowManyCountries(Graph* pgraph)
{
    Graph* countries = CreateGraph(pgraph->num);
    bool* visited = (bool *)malloc(sizeof(bool) * pgraph->num);
    int numOfCountries = 0;
    for (int i = 0; i < pgraph->num; i++)
    {
        GNode* cur = pgraph->heads[i]->next;
        while (cur != NULL)
        {
            if (cur->color == pgraph->heads[i]->color)
                AddEdge(countries, i, cur->id); // two nodes that have same color and adjacent, add
            cur = cur->next;
        }
        visited[i] = false; // all nodes are not visited yet
    }

    // cal the num of countries
    for (int i = 0; i < pgraph->num; i++)
    {
        if (visited[i]) continue;
        else
        {
	        VisitRegionInCountry(countries, i, visited);
            numOfCountries++;
        }
    }
    DestroyGraph(pgraph);
    DestroyGraph(countries);
    free(visited);
    return numOfCountries;
}

/* res: 10
14 33
0 0 0 1 1 2 3 4 1 5 1 3 3 0
5 1
2 1
1 5
2 7
2 3
3 9
1 7
7 3
3 4
1 0
7 0
3 0
0 6
4 6
1 8
6 9
4 9
9 4
9 6
9 6
6 9
8 1
0 6
8 10
2 11
3 11
4 11
9 3
12 13
5 13
5 12
10 12
10 13
*/

/* res: 2
4 4
0 1 0 0
0 1
1 2
2 3
3 0
*/

/* res: 2
5 5
0 0 1 0 0
0 1
1 2
2 3
3 4
4 0
*/

/* res: 2
10 10
0 0 1 0 0 0 0 0 0 0
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