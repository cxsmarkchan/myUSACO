/*
  id: cxsmarkchan
  PROG: gift1
  LANG: C++
*/
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

int match(char name[][15], char* tmp, int n){
    for(int i = 0; i < n; i++){
        if(strcmp(name[i], tmp) == 0){
            return i;
        }
    }
}

int main(){
    FILE *fin = fopen("gift1.in", "r");
    FILE *fout = fopen("gift1.out", "w");

    char name[10][15];
    int account[10];
    int n;

    fscanf(fin, "%d", &n);

    for(int i = 0; i < n; i++){
        fscanf(fin, "%s", name[i]);
        account[i] = 0;
    }

    char tmp[15];
    int money, num;
    for(int i = 0; i < n; i++){
        fscanf(fin, "%s", tmp);
        fscanf(fin, "%d%d", &money, &num);
        if(num > 0){
            account[match(name, tmp, n)] -= (money - money % num);
            money /= num;
            for(int j = 0; j < num; j++){
                fscanf(fin, "%s", tmp);
                account[match(name, tmp, n)] += money;
            }
        }
    }

    //output
    for(int i = 0; i < n; i++){
        fprintf(fout, "%s %d\n", name[i], account[i]);
    }

    fclose(fin);
    fclose(fout);

    return 0;
}
