/*
  id: cxsmarkchan
  PROG: cowtour
  LANG: C++
*/

#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>

using namespace std;

#define MAX 1e100

int X[150];
int Y[150];
int N;

char adj[155][155];
double dist[155][155];
double longest[155];
double diameter[155];
int zone[155];
int n_zone = 0;

double getDist(int p1, int p2){
    return sqrt((double)(X[p1] - X[p2]) * (double)(X[p1] - X[p2])
                + (double)(Y[p1] - Y[p2]) * (double)(Y[p1] - Y[p2]));
}

int main() {
    FILE *fin = fopen("cowtour.in", "r");
    FILE *fout = fopen("cowtour.out", "w");

    fscanf(fin, "%d", &N);
    for(int i = 0; i < N; i++) {
        fscanf(fin, "%d%d", &X[i], &Y[i]);
    }
    for(int i = 0; i < N; i++) {
        fscanf(fin, "%s", adj[i]);
    }

    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            if(adj[i][j] == '1') {
                dist[i][j] = getDist(i, j);
            } else if(i == j) {
                dist[i][j] = 0;
            } else {
                dist[i][j] = MAX;
            }
        }
    }

    for(int k = 0; k < N; k++) {
        for(int i = 0; i < N; i++) {
            for(int j = 0; j < N; j++) {
                if(dist[i][j] > dist[i][k] + dist[k][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    for(int i = 0; i < N; i++) {
        longest[i] = 0;
        for(int j = 0; j < N; j++) {
            if(dist[i][j] < MAX * 0.9 && longest[i] < dist[i][j]) {
                longest[i] = dist[i][j];
            }
        }
    }

    for(int i = 0; i < N; i++) {
        zone[i] = -1;
    }
    memset(diameter, 0, sizeof(diameter));

    int queue[200];
    int qbegin = 0;
    int qend = 0;
    for(int i = 0; i < N; i++) {
        if(zone[i] == -1){
            qbegin = 0;
            qend = 0;
            queue[qend++] = i;
            while(qbegin < qend){
                int tmp = queue[qbegin++];
                zone[tmp] = n_zone;
                if(diameter[n_zone] < longest[tmp]) {
                    diameter[n_zone] = longest[tmp];
                }
                for(int j = 0; j < N; j++) {
                    if(zone[j] == -1 && dist[tmp][j] < MAX * 0.9) {
                        zone[j] = n_zone;
                        queue[qend++] = j;
                    }
                }
            }
            n_zone++;
        }
    }

    double min_link = MAX;

    for(int i = 0; i < N; i++) {
        for(int j = 0; j < i; j++) {
            if(dist[i][j] > MAX * 0.9) {
                double max_tmp = longest[i] + longest[j] + getDist(i, j);
                if(max_tmp < diameter[zone[i]]) {
                    max_tmp = diameter[zone[i]];
                }
                if(max_tmp < diameter[zone[j]]) {
                    max_tmp = diameter[zone[j]];
                }
                if(min_link > max_tmp) {
                    min_link = max_tmp;
                }
            }
        }
    }

    fprintf(fout, "%.6f\n", min_link);

    fclose(fin);
    fclose(fout);
    return 0;
}
