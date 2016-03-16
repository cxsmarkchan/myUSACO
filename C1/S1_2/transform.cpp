/*
  id: cxsmarkchan
  PROG: transform
  LANG: C++
*/

#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
using namespace std;

//degree: 0->0 1->90 2->180 3->270
void rotate(char dest[][11], const char src[][11], int N, int degree){
    switch(degree){
    case 0:
        for(int i = 0; i < N; i++){
            strcpy(dest[i], src[i]);
        }
        break;
    case 1:
        for(int i = 0; i < N; i++){
            for(int j = 0; j < N; j++){
                dest[i][j] = src[N - 1 - j][i];
            }
            dest[i][N] = 0;
        }
        break;
    case 2:
        for(int i = 0; i < N; i++){
            for(int j = 0; j < N; j++){
                dest[i][j] = src[N - 1 - i][N - 1 - j];
            }
            dest[i][N] = 0;
        }
        break;
    case 3:
        for(int i = 0; i < N; i++){
            for(int j = 0; j < N; j++){
                dest[i][j] = src[j][N - 1 - i];
            }
            dest[i][N] = 0;
        }
        break;
    }
}

void reflect(char str[][11], int N){
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N / 2; j++){
            str[i][j] ^= str[i][N - 1 - j] ^= str[i][j] ^= str[i][N - 1 - j];
        }
    }
}

bool isEqual(const char str1[][11], const char str2[][11], int N){
    for(int i = 0; i < N; i++){
        if(strcmp(str1[i], str2[i]) != 0){
            return false;
        }
    }
    return true;
}

void myreturn(FILE* fin, FILE* fout, int n){
    fprintf(fout, "%d\n", n);
    fclose(fin);
    fclose(fout);
    exit(0);
}

int main(){
    FILE* fin = fopen("transform.in", "r");
    FILE* fout = fopen("transform.out", "w");

    int N;
    char before[10][11];
    char after[10][11];
    char tmp[10][11];
    char tmp2[10][11];

    fscanf(fin, "%d", &N);
    for(int i = 0; i < N; i++){
        fscanf(fin, "%s", before[i]);
    }
    for(int i = 0; i < N; i++){
        fscanf(fin, "%s", after[i]);
    }

    rotate(tmp, before, N, 1);
    if(isEqual(tmp, after, N)){
        myreturn(fin, fout, 1);
    }

    rotate(tmp, before, N, 2);
    if(isEqual(tmp, after, N)){
        myreturn(fin, fout, 2);
    }

    rotate(tmp, before, N, 3);
    if(isEqual(tmp, after, N)){
        myreturn(fin, fout, 3);
    }

    rotate(tmp, before, N, 0);
    reflect(tmp, N);
    if(isEqual(tmp, after, N)){
        myreturn(fin, fout, 4);
    }

    rotate(tmp, before, N, 0);
    reflect(tmp, N);
    rotate(tmp2, tmp, N, 1);
    if(isEqual(tmp2, after, N)){
        myreturn(fin, fout, 5);
    }
    rotate(tmp2, tmp, N, 2);
    if(isEqual(tmp2, after, N)){
        myreturn(fin, fout, 5);
    }
    rotate(tmp2, tmp, N, 3);
    if(isEqual(tmp2, after, N)){
        myreturn(fin, fout, 5);
    }

    rotate(tmp, before, N, 0);
    if(isEqual(tmp, after, N)){
        myreturn(fin, fout, 6);
    }

    myreturn(fin, fout, 7);
}
