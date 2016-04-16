/*
  id: cxsmarkchan
  PROG: agrinet
  LANG: C++
*/

#include <cstdio>
#include <cstring>
#include <cstdlib>

using namespace std;

int N;
int cost[100][100];

int dist[100];

int total = 0;

int main() {
    FILE *fin = fopen("agrinet.in", "r");
    FILE *fout = fopen("agrinet.out", "w");

    fscanf(fin, "%d", &N);
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            fscanf(fin, "%d", &cost[i][j]);
        }
    }

    for(int i = 0; i < N; i++) {
        dist[i] = cost[0][i];
    }

    for(int k = 0; k < N; k++) {
        int min = 1000000;
        int min_i;
        for(int i = 0; i < N; i++) {
            if(dist[i] > 0 && min > dist[i]) {
                min = dist[i];
                min_i = i;
            }
        }
        total += dist[min_i];
        dist[min_i] = 0;
        for(int i = 0; i < N; i++) {
            if(cost[min_i][i] < dist[i]) dist[i] = cost[min_i][i];
        }
    }

    fprintf(fout, "%d\n", total);


    fclose(fin);
    fclose(fout);
    return 0;
}
