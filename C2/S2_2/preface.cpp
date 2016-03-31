/*
  id: cxsmarkchan
  PROG: preface
  LANG: C++
*/

#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;

int num[4][10][7]={{{0},{1},{2},{3},{1,1},{0,1},{1,1},{2,1},{3,1},{1,0,1}},
                   {{0},{0,0,1},{0,0,2},{0,0,3},{0,0,1,1},{0,0,0,1},{0,0,1,1},{0,0,2,1},{0,0,3,1},{0,0,1,0,1}},
                   {{0},{0,0,0,0,1},{0,0,0,0,2},{0,0,0,0,3},{0,0,0,0,1,1},{0,0,0,0,0,1},{0,0,0,0,1,1},{0,0,0,0,2,1},{0,0,0,0,3,1},{0,0,0,0,1,0,1}},
                   {{0},{0,0,0,0,0,0,1},{0,0,0,0,0,0,2},{0,0,0,0,0,0,3}}};

int main(){
    FILE *fin = fopen("preface.in", "r");
    FILE *fout = fopen("preface.out", "w");

    int N;
    fscanf(fin, "%d", &N);

    int sum[7];
    memset(sum, 0, 7 * sizeof(int));

    for(int i = 0; i <= N; i++){
        int tmp = i;
        for(int j = 0; j < 4; j++){
            for(int k = 0; k < 7; k++){
                sum[k] += num[j][tmp % 10][k];
            }
            tmp /= 10;
        }
    }

    int tot = 6;
    while(sum[tot] == 0) tot--;

    int ch[7] = {'I', 'V', 'X', 'L', 'C', 'D', 'M'};

    for(int i = 0; i <= tot; i++){
        fprintf(fout, "%c %d\n", ch[i], sum[i]);
    }

    fclose(fin);
    fclose(fout);
    return 0;
}
