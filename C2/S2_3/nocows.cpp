/*
  id: cxsmarkchan
  PROG: nocows
  LANG: C++
*/

#include <cstdio>
#include <cstdlib>
#include <cstring>

using namespace std;

int main(){
    FILE *fin = fopen("nocows.in", "r");
    FILE *fout = fopen("nocows.out", "w");

    int N, K;
    fscanf(fin, "%d%d", &N, &K);

    int num[200][100]; //num[i][j] N = i + 1, K = j + 1
    memset(num, 0, sizeof(num));

    num[0][0] = 1;
    //num[i][j]
    // = sum(k=0 to (i - 2), num[k][j - 1] * sum(l < j - 1, num[i - 2 - k][l])) * 2
    // + sum(k=0 to (i - 2), num[k][j - 1] * num[i - 2 - k][j - 1])
    for(int i = 1; i < 200; i++){
        for(int j = 1; j <= i / 2; j++){
            for(int k = 0; k <= i - 2; k++){
                for(int l = 0; l < j - 1; l++){
                    num[i][j] += num[k][j - 1] * num[i - 2 - k][l];
                    num[i][j] %= 9901;
                }
            }
            num[i][j] *= 2;
            num[i][j] %= 9901;
            for(int k = 0; k <= i - 2; k++){
                num[i][j] += num[k][j - 1] * num[i - 2 - k][j - 1];
                num[i][j] %= 9901;
            }
        }
    }
    fprintf(fout, "%d\n", num[N - 1][K - 1]);

    fclose(fin);
    fclose(fout);
    return 0;
}
