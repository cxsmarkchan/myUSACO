/*
  id: cxsmarkchan
  PROG: sort3
  LANG: C++
*/
#include <cstdio>
#include <cstdlib>
#include <cstring>

int main(){
    FILE *fin = fopen("sort3.in", "r");
    FILE *fout = fopen("sort3.out", "w");

    int N;
    fscanf(fin, "%d", &N);
    int num[1000];
    int match[3][3];
    int n[3] = {0, 0, 0};
    memset(match, 0, 9 * sizeof(int));

    for(int i = 0; i < N; i++){
        fscanf(fin, "%d", &num[i]);
        n[num[i] - 1]++;
    }
    for(int i = 0; i < n[0]; i++){
        match[0][num[i] - 1]++;
    }
    for(int i = n[0]; i < n[0] + n[1]; i++){
        match[1][num[i] - 1]++;
    }
    for(int i = n[0] + n[1]; i < N; i++){
        match[2][num[i] - 1]++;
    }

    int sum = 0;
    int tmp = match[0][1] < match[1][0] ? match[0][1] : match[1][0];
    sum += tmp;
    match[0][1] -= tmp;
    match[1][0] -= tmp;

    tmp = match[1][2] < match[2][1] ? match[1][2] : match[2][1];
    sum += tmp;
    match[1][2] -= tmp;
    match[2][1] -= tmp;

    tmp = match[0][2] < match[2][0] ? match[0][2] : match[2][0];
    sum += tmp;
    match[0][2] -= tmp;
    match[2][0] -= tmp;

    sum += 2 * match[0][1];
    sum += 2 * match[0][2];

    fprintf(fout, "%d\n", sum);

    fclose(fin);
    fclose(fout);
    return 0;
}
