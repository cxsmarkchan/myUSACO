/*
  id: cxsmarkchan
  PROG: maze1
  LANG: C++
*/

#include <cstdio>
#include <cstring>
#include <cstdlib>

using namespace std;


int adj[3800][4];
int n_adj[3800];
int dist[2][3800];
int ex[2];
char maze[201][100];
int found[2][3800];

int W, H;

int main() {
    FILE *fin = fopen("maze1.in", "r");
    FILE *fout = fopen("maze1.out", "w");

    char buf[100];
    fgets(buf, 100, fin);
    sscanf(buf, "%d%d", &W, &H);
    for(int i = 0; i < 2 * H + 1; i++) {
        fgets(maze[i], 100, fin);
    }

    memset(n_adj, 0, sizeof(n_adj));

    //find exit
    int tmp = 0;
    for(int j = 0; j < W; j++) {
        if(maze[0][2 * j + 1] == ' ') {
            ex[tmp++] = j;
            maze[0][2 * j + 1] = '-';
        }
        if(maze[2 * H][2 * j + 1] == ' ') {
            ex[tmp++] = (H - 1) * W + j;
            maze[2 * H][2 * j + 1] = '-';
        }
    }
    for(int i = 0; i < H; i++) {
        if(maze[2 * i + 1][0] == ' ') {
            ex[tmp++] = i * W;
            maze[2 * i + 1][0] = '|';
        }
        if(maze[2 * i + 1][2 * W] == ' ') {
            ex[tmp++] = i * W + W - 1;
            maze[2 * i + 1][2 * W] = '|';
        }
    }

    for(int i = 0; i < H; i++) {
        for(int j = 0; j < W; j++) {
            int st = i * W + j;
            // north
            if(maze[2 * i][2 * j + 1] == ' ') {
                adj[st][n_adj[st]++] = (i - 1) * W + j;
            }
            // south
            if(maze[2 * i + 2][2 * j + 1] == ' ') {
                adj[st][n_adj[st]++] = (i + 1) * W + j;
            }
            // west
            if(maze[2 * i + 1][2 * j] == ' ') {
                adj[st][n_adj[st]++] = i * W + j - 1;
            }
            // east
            if(maze[2 * i + 1][2 * j + 2] == ' '){
                adj[st][n_adj[st]++] = i * W + j + 1;
            }
        }
    }

    //Dijkstra
    int num = W * H;
    for(int i = 0; i < num; i++) {
        dist[0][i] = dist[1][i] = 10000;
    }
    memset(found, 0, sizeof(found));
    dist[0][ex[0]] = 0;
    dist[1][ex[1]] = 0;
    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < num; j++) {
            int min = 10000;
            int minst = -1;
            for(int k = 0; k < num; k++) {
                if(found[i][k] == 0 && dist[i][k] < min) {
                    min = dist[i][k];
                    minst = k;
                }
            }
            found[i][minst] = 1;
            for(int k = 0; k < n_adj[minst]; k++) {
                if(dist[i][adj[minst][k]] > dist[i][minst] + 1) {
                    dist[i][adj[minst][k]] = dist[i][minst] + 1;
                }
            }
        }
    }

    int maxroute = 0;
    for(int i = 0; i < num; i++) {
        int tmp = dist[0][i];
        if(dist[1][i] < tmp) tmp = dist[1][i];
        if(maxroute < tmp) maxroute = tmp;
    }

    fprintf(fout, "%d\n", maxroute + 1);

    fclose(fin);
    fclose(fout);
    return 0;
}

