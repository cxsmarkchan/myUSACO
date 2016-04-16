/*
  id: cxsmarkchan
  PROG: inflate
  LANG: C++
*/

#include <cstdio>
#include <cstring>
#include <cstdlib>

using namespace std;

int main() {
    FILE *fin = fopen("inflate.in", "r");
    FILE *fout = fopen("inflate.out", "w");

    int M;
    int N;
    int points[10000];
    int time[10000];
    int total[10001];
    memset(total, 0, sizeof(points));

    fscanf(fin, "%d%d", &M, &N);
    for(int i = 0; i < N; i++){
        fscanf(fin, "%d%d", &points[i], &time[i]);
    }

    for(int i = 1; i <= M; i++) {
        for(int j = 0; j < N; j++) {
            if(i >= time[j] && total[i] < total[i - time[j]] + points[j]) {
                total[i] = total[i - time[j]] + points[j];
            }
        }
    }

    fprintf(fout, "%d\n", total[M]);

    fclose(fin);
    fclose(fout);
    return 0;
}
