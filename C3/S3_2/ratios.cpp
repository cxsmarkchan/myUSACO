/*
  id: cxsmarkchan
  PROG: ratios
  LANG: C++
*/

#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;

int main() {
    FILE *fin = fopen("ratios.in", "r");
    FILE *fout = fopen("ratios.out", "w");

    int goal[3];
    int given[3][3];

    for (int i = 0; i < 3; i++) {
        fscanf(fin, "%d", &goal[i]);
    }
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            fscanf(fin, "%d", &given[i][j]);
        }
    }

    int sum[3];
    int min_i = 0, min_j = 0, min_k = 0, min_goal = 0;
    int min_num = 0;
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 100; j++) {
            for (int k = 0; k < 100; k++) {
                bool b = true;
                for (int l = 0; l < 3; l++) {
                    sum[l] = i * given[0][l] + j * given[1][l] + k * given[2][l];
                    if (goal[l] == 0) {
                        if (sum[l] > 0) b = false;
                    } else {
                        if (sum[l] % goal[l] != 0) b = false;
                    }
                    if (b == false) break;
                }
                if (!b) continue;
                int cur = 0;
                while (goal[cur] == 0) cur++;
                int tmp = sum[cur] / goal[cur];
                if ((goal[1] == 0 || tmp == sum[1] / goal[1])
                    && (goal[2] == 0 || tmp == sum[2] / goal[2])) {
                    if (min_num == 0 || min_num > i + j + k) {
                        min_num = i + j + k;
                        min_i = i;
                        min_j = j;
                        min_k = k;
                        min_goal = tmp;
                    }
                }
            }
        }
    }

    if (min_num > 0) {
        fprintf(fout, "%d %d %d %d\n", min_i, min_j, min_k, min_goal);
    } else {
        fprintf(fout, "NONE\n");
    }

    fclose(fin);
    fclose(fout);
    return 0;
}
