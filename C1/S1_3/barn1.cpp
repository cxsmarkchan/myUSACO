/*
  id: cxsmarkchan
  PROG: barn1
  LANG: C++
*/

#include <iostream>
#include <cstdio>
using namespace std;

void swap(int *a1, int *a2){
    int tmp = *a1;
    *a1 = *a2;
    *a2 = tmp;
}
//sort [begin, end)
void sort(int* arr, int begin, int end){
    if(end - begin <= 1) return;

    int mid = (begin + end) / 2;
    swap(arr + begin, arr + mid);

    int tmp1 = begin + 1;
    int tmp2 = begin + 1;

    while(tmp1 < end){
        if(arr[tmp1] < arr[begin]){
            swap(arr + tmp1, arr + tmp2);
            tmp2++;
        }
        tmp1++;
    }
    tmp2--;
    swap(arr + tmp2, arr + begin);

    sort(arr, begin, tmp2);
    sort(arr, tmp2 + 1, end);
}

int main(){
    FILE *fin = fopen("barn1.in", "r");
    FILE *fout = fopen("barn1.out", "w");

    int M, S, C;
    int occ[200];
    int dist[200];

    fscanf(fin, "%d%d%d", &M, &S, &C);
    for(int i = 0; i < C; i++){
        fscanf(fin, "%d", occ + i);
    }

    int len = S;

    sort(occ, 0, C);
    len -= (occ[0] - 1);
    len -= (S - occ[C - 1]);

    for(int i = 0; i < C - 1; i++){
        dist[i] = occ[i + 1] - occ[i] - 1;
    }

    sort(dist, 0, C - 1);
    for(int i = 0; i < M - 1 && i < C - 1; i++){
        len -= dist[C - 2 - i];
    }

    fprintf(fout, "%d\n", len);

    fclose(fin);
    fclose(fout);
    return 0;
}
