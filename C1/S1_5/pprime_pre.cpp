//calculate all the prime palindromes
#include <cstdio>
#include <cstring>
#include <cstdlib>
using namespace std;

#define MAX 100000000

char num[MAX + 1];

bool isPal(int n){
    char str[15];
    sprintf(str, "%d", n);
    int len = strlen(str);
    for(int i = 0; i < len / 2; i++){
        if(str[i] != str[len - 1 - i]) return false;
    }
    return true;
}

int main(){
    FILE *fout = fopen("pprime.cpp_pre", "w");
    memset(num, 0, MAX * sizeof(bool));
    num[0] = num[1] = -1;
    int cur = 0;
    while(cur < MAX +1){
        while(num[cur] != 0) cur++;
        for(int tmp = cur * 2; tmp <= MAX; tmp += cur){
            num[tmp] = -1;
        }
        cur++;
    }
    int n = 0;
    for(int i = 0; i <= MAX; i++){
        if(num[i] == 0 && isPal(i)){
            fprintf(fout, "%d,", i);
            n++;
        }
    }
    printf("%d", n);

    fclose(fout);
    return 0;
}
