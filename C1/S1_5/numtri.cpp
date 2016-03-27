/*
  id: cxsmarkchan
  PROG: numtri
  LANG: C++
*/

#include <cstdio>
using namespace std;

int numtri[1000][1000];

int main(){
    FILE *fin = fopen("numtri.in", "r");
    FILE *fout = fopen("numtri.out", "w");

    int R;
    fscanf(fin, "%d", &R);

    for(int i = 0; i < R; i++){
        for(int j = 0; j <= i; j++){
            fscanf(fin, "%d", &numtri[i][j]);
        }
    }

    for(int i = R - 2; i >= 0; i--){
        for(int j = 0; j <= i; j++){
            if(numtri[i + 1][j] < numtri[i + 1][j + 1]){
                numtri[i][j] += numtri[i + 1][j + 1];
            }else{
                numtri[i][j] += numtri[i + 1][j];
            }
        }
    }

    fprintf(fout, "%d\n", numtri[0][0]);

    fclose(fin);
    fclose(fout);

    return 0;
}
