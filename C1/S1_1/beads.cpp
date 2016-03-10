/*
  id: cxsmarkchan
  PROG: beads
  LANG: C++
*/
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

int main(){
    FILE *fin = fopen("beads.in", "r");
    FILE *fout = fopen("beads.out", "w");

    int N;
    char beads[700];
    fscanf(fin, "%d", &N);
    fscanf(fin, "%s", beads);
    for(int i = 0; i < N; i++){
        beads[N + i] = beads[i];
    }

    int now = 0;
    for(int i = 0; i < 2 * N; i++){
        if(beads[i] == 'w'){
            if(now != 0){
                beads[i] = now - 32;
            }else{
                now = 0;
            }
        }else{
            now = beads[i];
        }
    }
    now = 0;
    for(int i = 2 * N - 1; i >= 0; i--){
        if(beads[i] == 'R'){
            if(now == 'r'){
                beads[i] = 'r';
            }else{
                beads[i] = 'w';
            }
        }else if(beads[i] == 'B'){
            if(now == 'b'){
                beads[i] = 'b';
            }else{
                beads[i] = 'w';
            }
        }else{
            now = beads[i];
        }
    }

    now = 0;
    int max = 0;
    int num[5] = {0, 0, 0, 0, 0}; //r, b, white_front, white_mid, white_back
    for(int i = 0; i < 2 * N; i++){
        if(beads[i] == 0) continue;

        if(beads[i] != now){
            int sum = num[0] + num[1] + num[2] + num[3] + num[4];
            if(sum > max){
                max = sum;
            }
            if(now == 'w'){
                num[2] = num[3];
                num[3] = num[4];
                num[4] = 0;
                if(beads[i] == 'r'){
                    num[0] = 0;
                }else{
                    num[1] = 0;
                }
            }else{
                switch(beads[i]){
                case 'r':
                    num[2] = num[3];
                    num[3] = num[4];
                    num[0] = 0;
                    break;
                case 'b':
                    num[2] = num[3];
                    num[3] = num[4];
                    num[1] = 0;
                    break;
                }
            }
            num[4] = 0;
        }
        switch(beads[i]){
        case 'r':
            num[0]++;
            break;
        case 'b':
            num[1]++;
            break;
        case 'w':
            num[4]++;
            break;
        }
        now = beads[i];
    }
    if(max == 0 || max > N){
        max = N;
    }

    fprintf(fout, "%d\n", max);

    fclose(fin);
    fclose(fout);

    return 0;
}
