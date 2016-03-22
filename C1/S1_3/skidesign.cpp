/*
  id: cxsmarkchan
  PROG: skidesign
  LANG: C++
*/

#include <cstdio>
using namespace std;

#define MAX_LEN 1000
int height[MAX_LEN];
int N;
int min_cost = -1;

int main(){
    FILE *fin = fopen("skidesign.in", "r");
    FILE *fout = fopen("skidesign.out", "w");

    fscanf(fin, "%d", &N);
    for(int i = 0; i < N; i++){
        fscanf(fin, "%d", height + i);
    }

    for(int i = 17; i < 100; i++){
        //以第i个为最高
        int cost = 0;
        int hi = i;
        int lo = i - 17;
        for(int j = 0; j < N; j++){
            int tmp = 0;
            if(height[j] > hi){
                tmp = height[j] - hi;
            }else if(height[j] < lo){
                tmp = lo - height[j];
            }
            cost += tmp * tmp;
        }
        if(cost < min_cost || min_cost < 0){
            min_cost = cost;
        }
    }

    fprintf(fout, "%d\n", min_cost);

    fclose(fin);
    fclose(fout);
    return 0;
}
