/*
  id: cxsmarkchan
  PROG: milk3
  LANG: C++
*/

#include <cstdio>
#include <cstring>
#include <cstdlib>
using namespace std;

int A, B, C;
int state[21][21][21];
int endstate[21];
int len = 0;

void search(int a, int b, int c){
    if(state[a][b][c] == 0){
        state[a][b][c] = 1;
        if(a == 0){
            endstate[len++] = c;
        }
        if(a > 0){
            if(a + b > B){
                search(a + b - B, B, c);
            }else{
                search(0, a + b, c);
            }
            if(a + c > C){
                search(a + c - C, b, C);
            }else{
                search(0, b, a + c);
            }
        }
        if(b > 0){
            if(a + b > A){
                search(A, a + b - A, c);
            }else{
                search(a + b, 0, c);
            }
            if(b + c > C){
                search(a, b + c - C, C);
            }else{
                search(a, 0, b + c);
            }
        }
        if(c > 0){
            if(a + c > A){
                search(A, b, a + c - A);
            }else{
                search(a + c, b, 0);
            }
            if(b + c > B){
                search(a, B, b + c - B);
            }else{
                search(a, b + c, 0);
            }
        }
    }
}

void sort(int len){
    for(int i = 0; i < len; i++){
        int j;
        int tmp = endstate[i];
        for(j = 0; j < i; j++){
            if(tmp < endstate[j]){
                break;
            }
        }
        for(int k = i; k > j; k--){
            endstate[k] = endstate[k - 1];
        }
        endstate[j] = tmp;
    }
}

int main(){
    FILE *fin = fopen("milk3.in", "r");
    FILE *fout = fopen("milk3.out", "w");

    memset(state[0][0], 0, 21 * 21 * 21 * sizeof(int));

    fscanf(fin, "%d%d%d", &A, &B, &C);

    search(0, 0, C);
    sort(len);

    for(int i = 0; i < len; i++){
        fprintf(fout, "%d", endstate[i]);
        if(i < len - 1){
            fprintf(fout, " ");
        }
    }
    fprintf(fout, "\n");

    return 0;
}
