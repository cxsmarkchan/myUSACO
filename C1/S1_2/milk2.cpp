/*
  id: cxsmarkchan
  PROG: milk2
  LANG: C++
*/

#include <iostream>
#include <cstdio>
using namespace std;

inline void swap(int& a, int& b){
    int tmp = a;
    a = b;
    b = tmp;
}

void sort(int *left, int *right, int begin, int end){
    if(end - begin <= 1){
        return;
    }

    int middle = (begin + end) / 2;
    swap(left[begin], left[middle]);
    swap(right[begin], right[middle]);

    int tmp = begin + 1;
    int less_end = begin + 1;
    while(tmp < end){
        if(left[tmp] < left[begin]){
            swap(left[tmp], left[less_end]);
            swap(right[tmp], right[less_end]);
            less_end++;
        }
        tmp++;
    }
    less_end--;
    swap(left[begin], left[less_end]);
    swap(right[begin], right[less_end]);

    sort(left, right, begin, less_end);
    sort(left, right, less_end + 1, end);
}

int main(){
    FILE *fin = fopen("milk2.in", "r");
    FILE *fout = fopen("milk2.out", "w");

    int N;
    int left[5000];
    int right[5000];
    fscanf(fin, "%d", &N);
    for(int i = 0; i < N; i++){
        fscanf(fin, "%d%d", left + i, right + i);
    }

    sort(left, right, 0, N);

    int fill[5000];
    int idle[5000];
    fill[0] = right[0] - left[0];
    int n_fill = 1;
    int n_idle = 0;

    for(int i = 1; i < N; i++){
        if(left[i] <= right[i - 1]){ //need merging
            if(right[i] > right[i - 1]){
                fill[n_fill - 1] += right[i] - right[i - 1];
            }else{
                right[i] = right[i - 1];
            }
        }else{
            idle[n_idle++] = left[i] - right[i - 1];
            fill[n_fill++] = right[i] - left[i];
        }
    }

    int max_fill = 0;
    int max_idle = 0;

    for(int i = 0; i < n_fill; i++){
        if(fill[i] > max_fill){
            max_fill = fill[i];
        }
    }
    for(int i = 0; i < n_idle; i++){
        if(idle[i] > max_idle){
            max_idle = idle[i];
        }
    }

    fprintf(fout, "%d %d\n", max_fill, max_idle);

    fclose(fin);
    fclose(fout);

    return 0;
}
