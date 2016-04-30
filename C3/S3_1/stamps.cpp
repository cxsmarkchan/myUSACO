/*
  id: cxsmarkchan
  PROG: stamps
  LANG: C++
*/

#include <cstdio>
#include <cstring>
#include <cstdlib>

using namespace std;

#define MAX 2000000
unsigned char num[MAX + 20000];
unsigned char is_stamp[10000];
int stamp[50];

int main() {
    FILE *fin = fopen("stamps.in", "r");
    FILE *fout = fopen("stamps.out", "w");

    memset(num, 0, sizeof(num));
    memset(is_stamp, 0, sizeof(is_stamp));

    int K, N;
    fscanf(fin, "%d%d", &K, &N);
    for(int i = 0; i < N; i++) {
        fscanf(fin, "%d", &stamp[i]);
        is_stamp[stamp[i] - 1] = 1;
    }

    for(int i = 0; i < MAX; i++) {
        // i + 1
        if(i < 10000 && is_stamp[i]) num[i] = 1;
        if(num[i] > 0 && num[i] < K) {
            for(int j = 0; j < N; j++) {
                if(num[i + stamp[j]] > num[i] || num[i + stamp[j]] == 0) {
                    num[i + stamp[j]] = num[i] + 1;
                }
            }
        }
    }

    int longest = 0;
    int cur_length = 0;
    for(int i = 0; i < MAX; i++) {
        if(num[i] > 0) {
            cur_length++;
            if(cur_length > longest) longest = cur_length;
        } else {
            cur_length = 0;
        }
    }

    fprintf(fout, "%d\n", longest);

    fclose(fin);
    fclose(fout);
    return 0;
}
