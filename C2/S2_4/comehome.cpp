/*
  id: cxsmarkchan
  PROG: comehome
  LANG: C++
*/

#include <cstdio>
#include <cstring>
#include <cstdlib>
using namespace std;

int mapping[128];
int withcow[128];
int dist[52][52];

int main() {
    FILE *fin = fopen("comehome.in", "r");
    FILE *fout = fopen("comehome.out", "w");

    for(int i = 0; i < 26; i++) {
        mapping['A' + i] = i;
        mapping['a' + i] = i + 26;
    }
    memset(withcow, 0, sizeof(withcow));

    int N;

    for(int i = 0; i < 52; i++) {
        for(int j = 0; j < 52; j++) {
            dist[i][j] = 1000000000;
        }
    }
    for(int i = 0; i < 52; i++) {
        dist[i][i] = 0;
    }
    fscanf(fin, "%d", &N);
    for(int i = 0; i < N; i++) {
        char buf[3];
        char a, b;
        int c;
        fscanf(fin, "%s", buf);
        a = buf[0];
        fscanf(fin, "%s", buf);
        b = buf[0];
        fscanf(fin, "%d", &c);
        int x1 = mapping[a];
        int x2 = mapping[b];
        if(x1 <= 24) withcow[x1] = 1;
        if(x2 <= 24) withcow[x2] = 1;

        if(dist[x1][x2] > c) dist[x2][x1] = dist[x1][x2] = c;
    }

    for(int k = 0; k < 52; k++) {
        for(int i = 0; i < 52; i++) {
            for(int j = 0; j < 52; j++) {
                if(dist[i][j] > dist[i][k] + dist[k][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    int min_dist = 100000000;
    int min_cow;
    for(int i = 0; i < 25; i++) {
        if(withcow[i] && min_dist > dist[i][25]) {
            min_dist = dist[i][25];
            min_cow = i;
        }
    }

    fprintf(fout, "%c %d\n", 'A' + min_cow, min_dist);

    fclose(fin);
    fclose(fout);
    return 0;
}
