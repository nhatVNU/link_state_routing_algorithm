#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_SERVERS 100 // MAX FILE LUU TREN SERVER
#define MAX_CONNECTIONS 10000 // MAX CONNECT

struct Edge {
    int src, dest, weight; // dinh? nguon`, dinh? dich, trong so
};

struct Graph {
    int V, E; // so luong dinh? va so luong canh
    struct Edge edge[MAX_CONNECTIONS]; // Danh sách canh
};

void printPath(int parent[], int j) {
    // In ra duong di ngan nhat' tu dinh nguon den dinh j
    if (parent[j] == -1)
        return;
    printPath(parent, parent[j]);
    printf("%d -> ", j);
}

void printSolution(int dist[], int n, int parent[], int src) {
    // In ra khoang cách tu dinh? nguon den các dinh? con` lai và duong di ngan nhat tuong ung
    printf("File server \t Dis from dinh \t sortest way \n");
    for (int i = 0; i < n; i++) {
        printf("%d \t\t %d \t\t\t\t ", i, dist[i]);
        printPath(parent, i);
        printf("%d\n", src);
    }
}

void dijkstra(struct Graph* graph, int src) {
    int V = graph->V;
    int dist[V]; // Luu khoang cach ngan nhat tu dinh nguon den cac dinh khac
    int parent[V]; // Luu dinh? cha cua? moi dinh? trong duong di ngan nhat
    bool sptSet[V]; // Mang danh' dau' dinh? da~ duoc xet
    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX, sptSet[i] = false;
        parent[i] = -1;
    }
    dist[src] = 0; // DIS NGUON -> NGUON = 0
    for (int count = 0; count < V - 1; count++) {
        int u, min = INT_MAX;
        for (int v = 0; v < V; v++) {
            if (!sptSet[v] && dist[v] <= min) {
                min = dist[v], u = v;
            }
        }
        sptSet[u] = true; // DANH DAU DINH DA DC XET
        for (int i = 0; i < graph->E; i++) {
            int v = graph->edge[i].src;
            int w = graph->edge[i].dest;
            int weight = graph->edge[i].weight;
            if (!sptSet[w] && dist[v] != INT_MAX && dist[v] + weight < dist[w]) {
                // UPDATE KHOANG CACH VA DINH? CHA CUA? DINH? DICH'
                dist[w] = dist[v] + weight;
                parent[w] = v;
            }
        }
    }
    printSolution(dist, V, parent, src); // KET QUA
}

int main() {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    int n, m;
    printf("Nhap so luong file server va so luong ket noi: ");
    scanf("%d %d", &n, &m);
    graph->V = n;
    graph->E = m;
    printf("Nhap thong tin cac ket noi:\n");
    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        graph->edge[i].src = u;
        graph->edge[i].dest = v;
        graph->edge[i].weight = w;
    }
    int src = 0; // File server nguon
    dijkstra(graph, src); // Dijkstra

    return 0;
}


