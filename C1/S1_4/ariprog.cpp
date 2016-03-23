/*
  id: cxsmarkchan
  PROG: ariprog
  LANG: C++
*/

#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;

#define MAX_M 250
#define MAX_SQ MAX_M * MAX_M * 2

int bisquare[MAX_M * MAX_M];
char is_square[MAX_M * MAX_M * 2];
int ari_diff[10000];
int ari_first[10000];
int num_ari = 0;
int max = 0;
int num_sq = 0;

FILE *fin, *fout;
int N, M;

inline void swap(int a1, int a2){
    int tmp = ari_diff[a1];
    ari_diff[a1] = ari_diff[a2];
    ari_diff[a2] = tmp;

    tmp = ari_first[a1];
    ari_first[a1] = ari_first[a2];
    ari_first[a2] = tmp;
}

inline int cmp(int a1, int a2){
    if(ari_diff[a1] < ari_diff[a2]) return -1;
    else if(ari_diff[a1] > ari_diff[a2]) return 1;
    else if(ari_first[a1] < ari_first[a2]) return -1;
    else if(ari_first[a1] > ari_first[a2]) return 1;
    else return 0;
}

void sort(int begin, int end){
    if(end - begin <= 1) return;

    int mid = (begin + end) / 2;
    swap(begin, mid);

    int tmp1 = begin + 1;
    int tmp2 = begin + 1;
    while(tmp1 < end){
        if(cmp(tmp1, begin) < 0){
            swap(tmp1++, tmp2++);
        }else{
            tmp1++;
        }
    }
    tmp2--;
    swap(begin, tmp2);

    sort(begin, tmp2);
    sort(tmp2 + 1, end);
}

int main(){
    fin = fopen("ariprog.in", "r");
    fout = fopen("ariprog.out", "w");

    fscanf(fin, "%d%d", &N, &M);
    memset(is_square, 0, sizeof(char) * MAX_SQ);

    for(int i = 0; i <= M; i++){
        for(int j = i; j <= M; j++){
            int tmp = i * i + j * j;
            if(is_square[tmp] == 0){
                is_square[tmp] = 1;
                bisquare[num_sq++] = tmp;
                if(tmp > max) max = tmp;
            }
        }
    }
    for(int i = 0; i < num_sq; i++){
        for(int j = i + 1; j < num_sq; j++){
            int first;
            int diff;
            if(bisquare[i] < bisquare[j]){
                first = bisquare[i];
                diff = bisquare[j] - bisquare[i];
            }else{
                first = bisquare[j];
                diff = bisquare[i] - bisquare[j];
            }
            if(first + (N - 1) * diff > max){
                continue;
            }
            bool b = true;
            int tmp = first;
            for(int k = 1; k < N; k++){
                tmp += diff;
                if(is_square[tmp] == 0){
                    b = false;
                    break;
                }
            }
            if(b){
                ari_diff[num_ari] = diff;
                ari_first[num_ari++] = first;
            }
        }
    }

    sort(0, num_ari);

    if(num_ari == 0){
        fprintf(fout, "NONE\n");
    }else{
        for(int i = 0; i < num_ari; i++){
            fprintf(fout, "%d %d\n", ari_first[i], ari_diff[i]);
        }
    }

    fclose(fin);
    fclose(fout);
    return 0;
}
