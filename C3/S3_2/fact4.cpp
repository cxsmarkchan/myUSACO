/*
  id: cxsmarkchan
  PROG: fact4
  LANG: C++
*/

#include <cstdio>
#include <cstring>
#include <cstdlib>

using namespace std;

#define MAX 4220

int main() {
    FILE *fin = fopen("fact4.in", "r");
    FILE *fout = fopen("fact4.out", "w");

    int N;
    fscanf(fin, "%d", &N);

    int n_factor2 = 0;
    int n_factor5 = 0;
    int n_factor10;

    for(int i = 1; i <= N; i++) {
        int tmp = i;
        while(tmp % 2 == 0) {
            n_factor2++;
            tmp /= 2;
        }
        while(tmp % 5 == 0) {
            n_factor5++;
            tmp /= 5;
        }
    }
    n_factor10 = (n_factor2 < n_factor5) ? n_factor2 : n_factor5;
    n_factor2 = n_factor5 = n_factor10;

    int num[N];
    for(int i = 0; i < N; i++) {
        num[i] = i + 1;
        while(n_factor2 > 0 && num[i] % 2 == 0) {
            n_factor2--;
            num[i] /= 2;
        }
        while(n_factor5 > 0 && num[i] % 5 == 0) {
            n_factor5--;
            num[i] /= 5;
        }
    }

    int last_digit = 1;
    for(int i = 0; i < N; i++) {
        last_digit *= num[i];
        last_digit %= 10;
    }

    fprintf(fout, "%d\n", last_digit);

    fclose(fin);
    fclose(fout);
    return 0;
}
