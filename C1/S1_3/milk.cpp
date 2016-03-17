/*
  id: cxsmarkchan
  PROG: milk
  LANG: C++
*/

#include <iostream>
#include <cstdio>
using namespace std;

void swap(int *a, int *b){
    int tmp = *a;
    *a = *b;
    *b = tmp;
}
void sort(int *price, int *amount, int begin, int end){
    if(end - begin <= 1) return;

    int mid = (begin + end) / 2;
    swap(price + begin, price + mid);
    swap(amount + begin, amount + mid);

    //partition
    int tmp1 = begin + 1;
    int tmp2 = begin + 1;
    while(tmp1 < end){
        if(price[tmp1] < price[begin]){
            swap(price + tmp1, price + tmp2);
            swap(amount + tmp1, amount + tmp2);
            tmp2++;
        }
        tmp1++;
    }
    tmp2--;
    swap(price + begin, price + tmp2);
    swap(amount + begin, amount + tmp2);

    //recursive
    sort(price, amount, begin, tmp2);
    sort(price, amount, tmp2 + 1, end);
}

int main(){
    FILE *fin = fopen("milk.in", "r");
    FILE *fout = fopen("milk.out", "w");

    int N, M;
    int price[5000];
    int amount[5000];

    fscanf(fin, "%d%d", &N, &M);
    for(int i = 0; i < M; i++){
        fscanf(fin, "%d%d", price + i, amount + i);
    }

    sort(price, amount, 0, M);

    //greedy
    int tot = 0;
    for(int i = 0; i < M; i++){
        if(N > amount[i]){
            N -= amount[i];
            tot += amount[i] * price[i];
        }else{
            tot += N * price[i];
            break;
        }
    }

    fprintf(fout, "%d\n", tot);

    fclose(fin);
    fclose(fout);
    return 0;
}
