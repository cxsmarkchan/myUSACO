/*
  id: cxsmarkchan
  PROG: subset
  LANG: C++
*/

#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;

int main()
{
    FILE *fin = fopen("subset.in", "r");
    FILE *fout = fopen("subset.out", "w");

    unsigned int sum[39][391];
    memset(sum, 0, 39 * 391 * sizeof(int));

    sum[0][0] = 1;
    sum[0][1] = 1;
    for(int i = 1; i < 39; i++){
        int sum_max = (i + 1) * (i + 2) / 2;
        if(sum_max > 390) sum_max = 390;
        for(int j = 0; j <= sum_max; j++){
            if(j < i + 1){
                sum[i][j] = sum[i - 1][j];
            }else{
                sum[i][j] = sum[i - 1][j] + sum[i - 1][j - (i + 1)];
            }
        }
    }

    int N;
    fscanf(fin, "%d", &N);

    if(N % 4 == 1){
        fprintf(fout, "0\n");
    }else{
        fprintf(fout, "%u\n", sum[N - 1][N * (N + 1) / 4] / 2);
    }

    fclose(fin);
    fclose(fout);
    return 0;
}
