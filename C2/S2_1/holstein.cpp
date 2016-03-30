/*
  id: cxsmarkchan
  PROG: holstein
  LANG: C++
*/

#include <cstdio>
#include <cstdlib>
#include <cstring>

int V;
int req[25];
int G;
int feed[15][25];

inline int getNum(unsigned int n){
    int rem[25];
    memcpy(rem, req, 25 * sizeof(int));
    int num = 0;
    for(int i = 0; i < G; i++){
        if((n & (1 << i)) != 0){
            num++;
            for(int j = 0; j < V; j++){
                rem[j] -= feed[i][j];
            }
        }
    }
    for(int i = 0; i < V; i++){
        if(rem[i] > 0) return -1;
    }
    return num;
}

int main(){
    FILE *fin = fopen("holstein.in", "r");
    FILE *fout = fopen("holstein.out", "w");


    fscanf(fin, "%d", &V);
    for(int i = 0; i < V; i++){
        fscanf(fin, "%d", req + i);
    }
    fscanf(fin, "%d", &G);
    for(int i = 0; i < G; i++){
        for(int j = 0; j < V; j++){
            fscanf(fin, "%d", &feed[i][j]);
        }
    }

    int min_num = G + 1;
    unsigned int min_feed;
    unsigned int max_num = 1 << G;
    for(unsigned int i = 0; i < max_num; i++){
        int num = getNum(i);
        if(num >= 0
           && (num < min_num
               || (num == min_num && i < min_feed))){
            min_num = num;
            min_feed = i;
        }
    }

    int ord[15];
    int cur = 0;
    for(int i = 0; i < G; i++){
        if((min_feed & (1 << i)) != 0){
            ord[cur++] = i + 1;
        }
    }
    fprintf(fout, "%d ", cur);
    for(int i = 0; i < cur; i++){
        fprintf(fout, "%d", ord[i]);
        if(i == cur - 1){
            fprintf(fout, "\n");
        }else{
            fprintf(fout, " ");
        }
    }

    fclose(fin);
    fclose(fout);

    return 0;
}
