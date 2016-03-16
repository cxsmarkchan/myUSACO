/*
  id: cxsmarkchan
  PROG: dualpal
  LANG: C++
*/

#include <iostream>
#include <cstdio>
using namespace std;

//base_n number in reverse order
int getBaseN(int *dest, unsigned int src, int base, int n){
    int dim = 0;
    while(src != 0){
        dest[dim++] = src % base;
        src /= base;
    }
    for(int i = dim; i < n; i++){
        dest[i] = 0;
    }
    return dim;
}

bool isPal(const int *src, int dim){
    for(int i = 0; i < dim / 2; i++){
        if(src[i] != src[dim - 1 - i]){
            return false;
        }
    }
    return true;
}

int main(){
    FILE *fin = fopen("dualpal.in", "r");
    FILE *fout = fopen("dualpal.out", "w");

    int N;
    unsigned int S;
    fscanf(fin, "%d%d", &N, &S);
    S++;

    int num[32];

    while(N > 0){
        int k = 0; // cardinal
        for(int i = 2; i <= 10; i++){
            int dim = getBaseN(num, S, i, 32);
            if(isPal(num, dim)){
                k++;
            }
        }
        if(k >= 2){
            fprintf(fout, "%d\n", S);
            N--;
        }
        S++;
    }
    fclose(fin);
    fclose(fout);
    return 0;
}
