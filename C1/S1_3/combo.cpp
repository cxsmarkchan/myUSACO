/*
  id: cxsmarkchan
  PROG: combo
  LANG: C++
*/

#include <cstdio>
using namespace std;

int N;
int first[3];
int second[3];
const int len = 125;
int combo[len * 2][3];

int cmp(int *a1, int *a2){
    for(int i = 0; i < 3; i++){
        if(a1[i] < a2[i]) return -1;
        else if(a1[i] > a2[i]) return 1;
    }
    return 0;
}

void swap(int *a1, int *a2){
    for(int i = 0; i < 3; i++){
        int tmp = a1[i];
        a1[i] = a2[i];
        a2[i] = tmp;
    }
}

void sort(int begin, int end){
    if(end - begin <= 1) return;

    int mid = (begin + end) / 2;
    swap(combo[begin], combo[mid]);

    int tmp1 = begin + 1;
    int tmp2 = begin + 1;

    while(tmp1 < end){
        if(cmp(combo[tmp1], combo[begin]) < 0){
            swap(combo[tmp1], combo[tmp2]);
            tmp2++;
        }
        tmp1++;
    }

    tmp2--;
    swap(combo[begin], combo[tmp2]);

    sort(begin, tmp2);
    sort(tmp2 + 1, end);
}

int get(int base, int off){
    int rtn = base + off;
    while(rtn > N) rtn -= N;
    while(rtn < 1) rtn += N;
    return rtn;
}

int main(){
    FILE *fin = fopen("combo.in", "r");
    FILE *fout = fopen("combo.out", "w");


    fscanf(fin, "%d", &N);
    fscanf(fin, "%d%d%d", first, first + 1, first + 2);
    fscanf(fin, "%d%d%d", second, second + 1, second + 2);

    for(int i = 0; i < len * 2; i++){
        int* now;
        if(i < len){
            now = first;
        }else{
            now = second;
        }
        combo[i][0] = get(now[0], (i % 125) % 5 - 2);
        combo[i][1] = get(now[1], ((i % 125) / 5) % 5 - 2);
        combo[i][2] = get(now[2], (i % 125) / 25 - 2);
    }

    sort(0, len * 2);

    int sum = 1;
    for(int i = 1; i < len * 2; i++){
        if(cmp(combo[i], combo[i - 1]) != 0){
            sum++;
        }
    }

    fprintf(fout, "%d\n", sum);

    fclose(fin);
    fclose(fout);
    return 0;
}
