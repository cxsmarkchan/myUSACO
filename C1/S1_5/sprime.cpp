/*
  id: cxsmarkchan
  PROG: sprime
  LANG: C++
*/

#include <cstdio>
#include <cstring>
#include <cstdlib>
using namespace std;

#define MAX 65536

int sprime[2][MAX];
int n_s[8];
int digit[4] = {1, 3, 7, 9};

bool isprime(int n){ // n >= 10
    for(int i = 2; i * i <= n; i++){
        if(n % i == 0) return false;
    }
    return true;
}

void search(int n){
    if(n == 0){
        n_s[0] = 4;
        sprime[0][0] = 2;
        sprime[0][1] = 3;
        sprime[0][2] = 5;
        sprime[0][3] = 7;
    }else{
        for(int i = 0; i < n_s[n - 1]; i++){
            for(int j = 0; j < 4; j++){
                int tmp = sprime[(n - 1) % 2][i] * 10 + digit[j];
                if(isprime(tmp)){
                    sprime[n % 2][n_s[n]++] = tmp;
                }
            }
        }
    }
}

int main(){
    FILE *fin = fopen("sprime.in", "r");
    FILE *fout = fopen("sprime.out", "w");

    memset(n_s, 0, 8 * sizeof(int));

    int N;
    fscanf(fin, "%d", &N);
    for(int i = 0; i < N; i++){
        search(i);
    }

    for(int i = 0; i < n_s[N - 1]; i++){
        fprintf(fout, "%d\n", sprime[(N - 1) % 2][i]);
    }

    fclose(fin);
    fclose(fout);
    return 0;
}
