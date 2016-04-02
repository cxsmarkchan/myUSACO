/*
  id: cxsmarkchan
  PROG: prefix
  LANG: C++
*/

#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;

char prim[210][11];
int len[210];
int np = 0;

char S[210000];
int pre[210000];
int len_s;
char tmp[100];

int main(){
    FILE *fin = fopen("prefix.in", "r");
    FILE *fout = fopen("prefix.out", "w");

    while(1){
        fscanf(fin, "%s", prim[np]);
        len[np] = strlen(prim[np]);
        if(len[np] != 1 || prim[np][0] != '.'){
            np++;
        }else{
            break;
        }
    }
    while(fscanf(fin, "%s", tmp) != EOF){
        strcat(S, tmp);
    }
    len_s = strlen(S);

    pre[len_s] = 0;
    for(int i = len_s - 1; i >= 0; i--){
        pre[i] = 0;
        for(int j = 0; j < np; j++){
            if(i + len[j] <= len_s
               && pre[i] < pre[i + len[j]] + len[j]
               && strncmp(S + i, prim[j], len[j]) == 0){
                pre[i] = pre[i + len[j]] + len[j];
            }
        }
    }
    fprintf(fout, "%d\n", pre[0]);

    fclose(fin);
    fclose(fout);
    return 0;
}
