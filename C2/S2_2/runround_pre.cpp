/*
  id: cxsmarkchan
  PROG: runround
  LANG: C++
*/

#include <cstdio>
#include <cstring>
#include <cstdlib>
using namespace std;

bool check(unsigned long num){
    char dig[15];
    sprintf(dig, "%d", num);
    int len = strlen(dig);
    for(int i = 0; i < len; i++){
        if(dig[i] == '0') return false;
        for(int j = 0; j < i; j++){
            if(dig[i] == dig[j]) return false;
        }
    }
    int tmp = 0;
    while(dig[tmp] != 0){
        int c = dig[tmp] - '0';
        dig[tmp] = 0;
        tmp += c;
        tmp %= len;
    }
    if(tmp != 0) return false;
    for(int i = 0; i < len; i++){
        if(dig[i] != 0) return false;
    }

    return true;
}

int main(){
    FILE *fout = fopen("runround.cpp_pre", "w");

    int num = 0;
    //There are no runaround number larger than 100000000.
    //If not, the number should have 9 digits, which are 1-9.
    //However, if the the pointer goes to 9, it will wrap over 9 digits, which implies a cycle.
    for(unsigned int i = 1; i < 100000000; i++){
        if(check(i)){
            fprintf(fout, "%u,", i);
            num++;
        }
    }
    fprintf(fout, "\n%d", num);

    fclose(fout);
    return 0;
}
