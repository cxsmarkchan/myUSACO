/*
  id: cxsmarkchan
  PROG: kimbits
  LANG: C++
*/

#include <cstdio>
#include <cstring>
#include <cstdlib>

using namespace std;

int main() {
    FILE *fin = fopen("kimbits.in", "r");
    FILE *fout = fopen("kimbits.out", "w");

    int N, L;
    unsigned int I;
    fscanf(fin, "%d%d%u", &N, &L, &I);

    int num[31][32];

    memset(num, 0, sizeof(num));

    for(int i = 0; i < N; i++) {
        num[i][0] = 1;
    }
    for(int i = 1; i <= L; i++) {
        num[0][i] = 2;
    }

    for(int i = 1; i < N; i++) {
        for(int j = 1; j <= L; j++) {
            num[i][j] = num[i - 1][j] + num[i - 1][j - 1];
        }
    }

    char elem[35];
    int curL = L;
    for(int i = 0; i < N - 1; i++) {
        if(num[N - 2 - i][curL] < I) {
            I -= num[N - 2 - i][curL];
            elem[i] = '1';
            curL--;
        } else {
            elem[i] = '0';
        }
    }
    if(I == 2) elem[N - 1] = '1';
    else elem[N - 1] = '0';
    elem[N] = 0;

    fprintf(fout, "%s\n", elem);


    fclose(fin);
    fclose(fout);
    return 0;
}
