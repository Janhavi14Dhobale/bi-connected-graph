#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int graph[MAX][MAX];
int visited[MAX], disc[MAX], low[MAX], parent[MAX];
int timeD = 0;
int articulationFound = 0;

void DFS(int u, int n) {
    visited[u] = 1;
    disc[u] = low[u] = ++timeD;
    int children = 0;

    for (int v = 0; v < n; v++) {
        if (graph[u][v]) {
            if (!visited[v]) {
                parent[v] = u;
                children++;
                DFS(v, n);

                low[u] = (low[v] < low[u]) ? low[v] : low[u];


                if (parent[u] == -1 && children > 1)
                    articulationFound = 1;

                if (parent[u] != -1 && low[v] >= disc[u])
                    articulationFound = 1;
            }
            else if (v != parent[u]) {

                if (disc[v] < low[u])
                    low[u] = disc[v];
            }
        }
    }
}

int isConnected(int start, int n) {
    for (int i = 0; i < n; i++)
        visited[i] = 0;

    DFS(start, n);

    for (int i = 0; i < n; i++)
        if (!visited[i])
            return 0;

    return 1;
}

int main() {
    int n, edges;
    printf("Enter number of nodes: ");
    scanf("%d", &n);

    printf("Enter number of edges: ");
    scanf("%d", &edges);


    for (int i = 0; i < n; i++) {
        parent[i] = -1;
        for (int j = 0; j < n; j++)
            graph[i][j] = 0;
    }

    printf("Enter edges (u v):\n");
    for (int i = 0; i < edges; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        graph[u][v] = graph[v][u] = 1;
    }


    if (!isConnected(0, n)) {
        printf("Graph is NOT Biconnected (Not connected)\n");
        return 0;
    }


    if (articulationFound)
        printf("Graph is NOT Biconnected (Contains articulation point)\n");
    else
        printf("Graph IS Biconnected\n");

    return 0;
}

