/*
  id: cxsmarkchan
  PROG: frac1
  LANG: C++
*/

#include <cstdio>
#include <cstring>
#include <cstdlib>

using namespace std;

#define MAX 161 * 161

int nom[MAX];
int denom[MAX];
int num;

int equal(int x1, int x2){
    return nom[x1] * denom[x2] == nom[x2] * denom[x1];
}

int cmp(int x1, int x2){
    int m1 = nom[x1] * denom[x2];
    int m2 = nom[x2] * denom[x1];
    if(m1 < m2) return -1;
    else if(m1 > m2) return 1;
    else if(denom[x1] < denom[x2]) return -1;
    else if(denom[x1] > denom[x2]) return 1;
    else return 0;
}

void swap(int x1, int x2){
    int tmp = nom[x1];
    nom[x1] = nom[x2];
    nom[x2] = tmp;

    tmp = denom[x1];
    denom[x1] = denom[x2];
    denom[x2] = tmp;
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
    swap(tmp2, begin);

    sort(begin, tmp2);
    sort(tmp2 + 1, end);
}

int main(){
    FILE *fin = fopen("frac1.in", "r");
    FILE *fout = fopen("frac1.out", "w");

    memset(nom, 0, MAX * sizeof(int));
    memset(denom, 0, MAX * sizeof(int));

    int N;
    fscanf(fin, "%d", &N);

    num = 0;
    for(int i = 1; i <= N; i++){
        for(int j = 0; j <= N; j++){
            nom[num] = j;
            denom[num++] = i;
        }
    }

    sort(0, num);

    fprintf(fout, "%d/%d\n", nom[0], denom[0]);
    for(int i = 1; i < num; i++){
        if(nom[i] > denom[i]) break;

        if(!equal(i, i - 1)){
            fprintf(fout, "%d/%d\n", nom[i], denom[i]);
        }
    }

    fclose(fin);
    fclose(fout);
    return 0;
}
