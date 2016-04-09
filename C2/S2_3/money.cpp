/*
  id: cxsmarkchan
  PROG: money
  LANG: C++
*/

#include <cstdio>
#include <cstdlib>
#include <cstring>

using namespace std;


int main(){
    FILE *fin = fopen("money.in", "r");
    FILE *fout = fopen("money.out", "w");

    int coin[25];
    int V;
    int N;

    fscanf(fin, "%d%d", &V, &N);
    for(int i = 0; i < V; i++){
        fscanf(fin, "%d", &coin[i]);
    }

    long long num[26][10001];
    memset(num, 0, sizeof(num));
    num[0][0] = 1;
    for(int i = 1; i <= V; i++){
        for(int j = 0; j <= N; j++){
            int tmp = 0;
            for(int tmp = 0; tmp <= j; tmp += coin[i - 1]){
                num[i][j] += num[i - 1][j - tmp];
            }
        }
    }
    fprintf(fout, "%lld\n", num[V][N]);

    fclose(fin);
    fclose(fout);
    return 0;
}
