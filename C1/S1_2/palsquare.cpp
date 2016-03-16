/*
  id: cxsmarkchan
  PROG: palsquare
  LANG: C++
*/

#include <iostream>
#include <cstdio>
using namespace std;

char num[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};
//返回位数
int getBaseN(int *dest, int src, int base, int n){
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

bool isPalindromic(const int *src, int dim){
    for(int i = 0; i < dim / 2; i++){
        if(src[i] != src[dim - 1 - i]){
            return false;
        }
    }
    return true;
}

void print(FILE *fout, const int *src, int n){
    bool b = false;
    for(int i = n - 1; i >= 0; i--){
        if(b){
            fprintf(fout, "%c", num[src[i]]);
        }else{
            if(src[i] != 0){
                b = true;
                fprintf(fout, "%c", num[src[i]]);
            }
        }
    }
}

int main(){
    FILE *fin = fopen("palsquare.in", "r");
    FILE *fout = fopen("palsquare.out", "w");
    int B;
    fscanf(fin, "%d", &B);

    int origin[20];
    int square[20];

    for(int i = 1; i < 300; i++){
        int dim = getBaseN(square, i * i, B, 20);
        if(isPalindromic(square, dim)){
            getBaseN(origin, i, B, 20);
            print(fout, origin, 20);
            fprintf(fout, " ");
            print(fout, square, 20);
            fprintf(fout, "\n");
        }
    }

    fclose(fin);
    fclose(fout);
    return 0;
}
