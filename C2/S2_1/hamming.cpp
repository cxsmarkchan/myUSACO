/*
  id: cxsmarkchan
  PROG: hamming
  LANG: C++
*/

#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;

int N, B, D;
unsigned int max;
int cur = 0;
unsigned int num[64];
int dist[256];

bool check(int cur){
    if(cur == 0) return true;
    for(int i = 0; i < cur; i++){
        if(dist[num[cur] ^ num[i]] < D) return false;
    }
    return true;
}

bool search(){
    unsigned int tmp = num[cur];
    bool rtn;
    if(cur == N) return true;
    if(cur > 0){
        num[cur] = num[cur - 1];
    }

    cur++;

    while(!check(cur - 1)){
        num[cur - 1]++;
        if(num[cur - 1] == max){
            cur--;
            return false;
        }
    }

    while(search() == false){
        do{
            num[cur - 1]++;
            if(num[cur - 1] == max){
                cur--;
                return false;
            }
        }while(!check(cur - 1));
    }

    cur--;
    return true;
}

int main(){
    FILE *fin = fopen("hamming.in", "r");
    FILE *fout = fopen("hamming.out", "w");

    fscanf(fin, "%d%d%d", &N, &B, &D);
    max = 1 << B;

    memset(dist, 0, 256 * sizeof(int));
    memset(num, 0, 64 * sizeof(unsigned int));
    for(unsigned int i = 0; i < 256; i++){
        for(int j = 0; j < 8; j++){
            if((i & (1 << j)) > 0){
                dist[i]++;
            }
        }
    }

    search();

    int tmp = 0;
    for(int i = 0; i < N; i++){
        fprintf(fout, "%u", num[i]);
        tmp++;
        if(i == N - 1){
            fprintf(fout, "\n");
        }else if(tmp < 10){
            fprintf(fout, " ");
        }else{
            tmp = 0;
            fprintf(fout, "\n");
        }
    }

    fclose(fin);
    fclose(fout);
    return 0;
}
