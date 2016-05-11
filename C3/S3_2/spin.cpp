/*
  id: cxsmarkchan
  PROG: spin
  LANG: C++
*/

#include <cstdio>
#include <cstdlib>
#include <cstring>

using namespace std;

int speed[5];
int num[5];
int start[5][5];
int end[5][5];
int now[5];

int main() {
    FILE *fin = fopen("spin.in", "r");
    FILE *fout = fopen("spin.out", "w");

    for (int i = 0; i < 5; i++) {
        fscanf(fin, "%d%d", &speed[i], &num[i]);
        for (int j = 0; j < num[i]; j++) {
            fscanf(fin, "%d%d", &start[i][j], &end[i][j]);
            end[i][j] += start[i][j];
        }
    }

    memset(now, 0, sizeof(now));

    bool cur_transparent[360];
    bool tot_transparent[360];
    int min_time = -1;

    for (int i = 0; i < 360; i++) {
        for (int j = 0; j < 360; j++) {
            tot_transparent[j] = true;
        }
        for (int j = 0; j < 5; j++) {
            memset(cur_transparent, 0, sizeof(cur_transparent));
            for (int k = 0; k < num[j]; k++) {
                for (int l = start[j][k]; l <= end[j][k]; l++) {
                    cur_transparent[(now[j] + l) % 360] = true;
                }
            }
            for (int k = 0; k < 360; k++) {
                tot_transparent[k] = tot_transparent[k] && cur_transparent[k];
            }
        }

        for (int j = 0; j < 360; j++) {
            if (tot_transparent[j]) {
                min_time = i;
                break;
            }
        }
        if (min_time >= 0) break;

        for (int j = 0; j < 5; j++) {
            now[j] += speed[j];
            now[j] %= 360;
        }
    }

    if (min_time < 0) {
        fprintf(fout, "none\n");
    } else {
        fprintf(fout, "%d\n", min_time);
    }

    fclose(fin);
    fclose(fout);
    return 0;
}
