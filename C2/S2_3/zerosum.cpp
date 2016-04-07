/*
  id: cxsmarkchan
  PROG: zerosum
  LANG: C++
*/

#include <cstdio>
#include <cstdlib>
#include <cstring>

using namespace std;

FILE *fin = fopen("zerosum.in", "r");
FILE *fout = fopen("zerosum.out", "w");

char dig[] = " +-";

int N;
char ins[8];

void check(){
    int sum = 0;
    int num = 1;
    char prev = '+';
    for(int i = 0; i < N - 1; i++){
        switch(ins[i]){
        case ' ':
            num *= 10;
            num += (i + 2);
            break;
        case '+':
            if(prev == '+') sum += num;
            else sum -= num;
            prev = '+';
            num = i + 2;
            break;
        case '-':
            if(prev == '+') sum += num;
            else sum -= num;
            prev = '-';
            num = i + 2;
            break;
        }
    }
    if(prev == '+') sum += num;
    else sum -= num;
    //fprintf(fout, "%d ", sum);
    if(sum == 0){
        for(int i = 0; i < N - 1; i++){
            fprintf(fout, "%d%c", i + 1, ins[i]);
        }
        fprintf(fout, "%d\n", N);
    }
}

void search(int d){
    if(d == N - 1){
        check();
    }else{
        ins[d] = ' ';
        search(d + 1);
        ins[d] = '+';
        search(d + 1);
        ins[d] = '-';
        search(d + 1);
    }
}

int main(){
    fscanf(fin, "%d", &N);

    search(0);

    fclose(fin);
    fclose(fout);
    return 0;
}
