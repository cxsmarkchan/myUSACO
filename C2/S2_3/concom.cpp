/*
  id: cxsmarkchan
  PROG: concom
  LANG: C++
*/

#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;

int num[100][100];
int tot[100][100];
struct CTRL{
    int x;
    int y;
}ctrl[5000];
int nctrl = 0;

int cmp(int x1, int x2){
    if(ctrl[x1].x < ctrl[x2].x) return -1;
    else if(ctrl[x1].x > ctrl[x2].x) return 1;
    else if(ctrl[x1].y < ctrl[x2].y) return -1;
    else if(ctrl[x1].y > ctrl[x2].y) return 1;
    else return 0;
}

void swap(int x1, int x2){
    CTRL tmp = ctrl[x1];
    ctrl[x1] = ctrl[x2];
    ctrl[x2] = tmp;
}

void sort(int begin, int end){
    if(end - begin <= 1) return;

    int mid = (begin + end) / 2;
    swap(begin, mid);

    int tmp1 = begin + 1;
    int tmp2 = begin + 1;

    while(tmp1 < end){
        if(cmp(tmp1, begin) < 0){
            swap(tmp1++, tmp2++);
        }else{
            tmp1++;
        }
    }
    tmp2--;
    swap(begin, tmp2);

    sort(begin, tmp2);
    sort(tmp2 + 1, end);
}

int main(){
    FILE *fin = fopen("concom.in", "r");
    FILE *fout = fopen("concom.out", "w");

    memset(num, 0, sizeof(num));
    int N;
    fscanf(fin, "%d", &N);
    int tmpi, tmpj, tmpp;
    for(int i = 0; i < N; i++){
        fscanf(fin, "%d%d%d", &tmpi, &tmpj, &tmpp);
        num[tmpi - 1][tmpj - 1] = tmpp;
    }
    memcpy(tot, num, sizeof(num));

    for(int i = 0; i < 100; i++){
        bool b = true;
        while(b){
            b = false;
            for(int j = 0; j < 100; j++){
                if(i == j) continue;
                if(tot[i][j] > 50){
                    b = true;
                    ctrl[nctrl].x = i;
                    ctrl[nctrl++].y = j;
                    for(int k = 0; k < 100; k++){
                        if(tot[i][k] >= 0){
                            tot[i][k] += num[j][k];
                        }
                    }
                    tot[i][j] = -1;
                }
            }
        }
    }

    sort(0, nctrl);

    for(int i = 0; i < nctrl; i++){
        fprintf(fout, "%d %d\n", ctrl[i].x + 1, ctrl[i].y + 1);
    }

    fclose(fin);
    fclose(fout);
    return 0;
}
