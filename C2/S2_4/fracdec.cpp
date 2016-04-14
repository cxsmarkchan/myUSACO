/*
  id: cxsmarkchan
  PROG: fracdec
  LANG: C++
*/

#include <cstdio>
#include <cstring>
#include <cstdlib>
using namespace std;

#define DIGIT 30000
#define RADIX 100000

int getDim(const long long int* num) {
    for(int i = DIGIT - 1; i >= 0; i--) {
        if(num[i] != 0) return i + 1;
    }
}

int remainder(const long long int* num, int mod) {
    int dim = getDim(num);
    int rem = 0;
    for(int i = dim - 1; i >= 0; i--) {
        rem *= RADIX;
        rem += num[i];
        rem %= mod;
    }
    return rem;
}

void mult_add(long long int* num, int factor, int adder = 0) {
    for(int i = 0; i < DIGIT; i++) {
        num[i] *= factor;
    }
    num[0] += adder;
    for(int i = 0; i < DIGIT - 1; i++) {
        num[i + 1] += num[i] / RADIX;
        num[i] %= RADIX;
    }
}

void divide(long long int *num, int dividend) {
    int dim = getDim(num);
    for(int i = dim - 1; i > 0; i--){
        num[i - 1] += (num[i] % dividend) * RADIX;
        num[i] /= dividend;
    }
    num[0] /= dividend;
}


int main() {
    FILE *fin = fopen("fracdec.in", "r");
    FILE *fout = fopen("fracdec.out", "w");

    int N, D;
    char str[DIGIT * 5 + 20];
    int pos = 0;
    fscanf(fin, "%d%d", &N, &D);

    pos += sprintf(str + pos, "%d.", N / D);
    N %= D;
    if(N == 0) {
        pos += sprintf(str + pos, "0");
    } else {
        while(D % 10 == 0 && N % 10 == 0) {
            D /= 10;
            N /= 10;
        }
        while(D % 10 == 0) {
            D /= 10;
            pos += sprintf(str + pos, "%d", N / D);
            N %= D;
        }
        while(D % 2 == 0) {
            D /= 2;
            N *= 5;
            if(N % 10 == 0) N /= 10;
            else {
                pos += sprintf(str + pos, "%d", N / D);
                N %= D;
            }
        }
        while(D % 5 == 0) {
            D /= 5;
            N *= 2;
            if(N % 10 == 0) N /= 10;
            else {
                pos += sprintf(str + pos, "%d", N / D);
                N %= D;
            }
        }

        // cycling part
        if(D != 1) {
            int nDigit = 1;
            int rem = 9 % D;
            int dim;
            char format[10];

            while(rem != 0) {
                rem *= 10;
                rem += 9;
                rem %= D;
                nDigit++;
            }

            long long int div[DIGIT];
            memset(div, 0, sizeof(div));

            for(dim = 0; dim < nDigit / 5; dim++) {
                div[dim] = 99999;
            }
            switch(nDigit % 5) {
            case 0:
                dim--;
                strcpy(format, "(%05d");
                break;
            case 1:
                div[dim] = 9;
                strcpy(format, "(%01d");
                break;
            case 2:
                div[dim] = 99;
                strcpy(format, "(%02d");
                break;
            case 3:
                div[dim] = 999;
                strcpy(format, "(%03d");
                break;
            case 4:
                div[dim] = 9999;
                strcpy(format, "(%04d");
                break;
            }
            dim++;

            divide(div, D);
            mult_add(div, N);

            pos += sprintf(str + pos, format, div[dim - 1]);
            for(int i = dim - 2; i >= 0; i--) {
                pos += sprintf(str + pos, "%05d", div[i]);
            }
            pos += sprintf(str + pos, ")");
        }
    }

    char printbuf[100];
    for(int i = 0; i < pos; i += 76) {
        strncpy(printbuf, str + i, 76);
        printbuf[76] = '\0';
        fprintf(fout, "%s", printbuf);
        fprintf(fout, "\n");
    }

    fclose(fin);
    fclose(fout);
    return 0;
}
