/*
  id: cxsmarkchan
  PROG: crypt1
  LANG: C++
*/

#include <iostream>
#include <cstdio>
using namespace std;

int N;
int dig[10];
int num[5];
/*
  0 3 4
    1 2
*/

bool check(int num){
    while(num != 0){
        int c = num % 10;
        num /= 10;
        int b = false;
        for(int i = 0; i < N; i++){
            if(c == dig[i]){
                b = true;
                break;
            }
        }
        if(!b){
            return false;
        }
    }
    return true;
}

int search(int now){
    if(now == 5){
        int num1 = num[0] * 100 + num[3] * 10 + num[4];
        int par1 = num1 * num[1];
        int par2 = num1 * num[2];
        int mult = par1 * 10 + par2;
        if(par1 >= 1000 || par2 >= 1000 || mult >= 10000){
            return 0;
        }else{
            if(check(par1) && check(par2) && check(mult)){
                return 1;
            }else{
                return 0;
            }
        }
    }else{
        if(now >= 2 && num[0] * num[1] >= 10) return 0;
        else if(now >= 3 && num[0] * num[2] >= 10) return 0;
        else{
            int tot = 0;
            for(int i = 0; i < N; i++){
                num[now] = dig[i];
                tot += search(now + 1);
            }
            return tot;
        }
    }
}

int main(){
    FILE *fin = fopen("crypt1.in", "r");
    FILE *fout = fopen("crypt1.out", "w");

    //input
    fscanf(fin, "%d", &N);
    for(int i = 0; i < N; i++){
        fscanf(fin, "%d", dig + i);
    }

    fprintf(fout, "%d\n", search(0));

    fclose(fin);
    fclose(fout);
    return 0;
}
