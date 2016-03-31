/*
  id: cxsmarkchan
  PROG: lamps
  LANG: C++
*/

#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;

int num[16] = {0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4};

int N, C;
int state[16][100]; //1-ON, 0-OFF

int on[100];
int num_on = 0;
int off[100];
int num_off = 0;

int solution[16][100];
int num_solution = 0;

int cmp(int x1, int x2){
    for(int i = 0; i < N; i++){
        if(solution[x1][i] < solution[x2][i]) return -1;
        else if(solution[x1][i] > solution[x2][i]) return 1;
    }
    return 0;
}

void copy(int *x1, const int *x2){
    for(int i = 0; i < N; i++){
        x1[i] = x2[i];
    }
}

void sort(){
    int tmp[100];
    for(int i = 1; i < num_solution; i++){
        int j;
        for(j = 0; j < i; j++){
            if(cmp(j, i) > 0) break;
        }
        copy(tmp, solution[i]);
        for(int k = i; k > j; k--){
            copy(solution[k], solution[k - 1]);
        }
        copy(solution[j], tmp);
    }
}

int main(){
    FILE *fin = fopen("lamps.in", "r");
    FILE *fout= fopen("lamps.out", "w");

    memset(on, 0, sizeof(on));
    memset(off, 0, sizeof(off));
    for(int i = 0; i < 16; i++){
        for(int j = 0; j < 100; j++){
            state[i][j] = 1;
        }
    }

    fscanf(fin, "%d%d", &N, &C);
    int tmp;
    while(fscanf(fin, "%d", &tmp), tmp != -1){
        on[num_on++] = tmp;
    }
    while(fscanf(fin, "%d", &tmp), tmp != -1){
        off[num_off++] = tmp;
    }

    for(unsigned int i = 0; i < 16; i++){
        if(num[i] <= C && num[i] % 2 == C % 2){
            if(i % 2 == 1){
                for(int j = 0; j < N; j++){
                    state[i][j] = 1 - state[i][j];
                }
            }
            if((i / 2) % 2 == 1){
                for(int j = 0; j < N; j += 2){
                    state[i][j] = 1 - state[i][j];
                }
            }
            if((i / 4) % 2 == 1){
                for(int j = 1; j < N; j += 2){
                    state[i][j] = 1 - state[i][j];
                }
            }
            if((i / 8) % 2 == 1){
                for(int j = 0; j < N; j += 3){
                    state[i][j] = 1 - state[i][j];
                }
            }
            //check
            int b = true;
            for(int j = 0; j < num_on; j++){
                if(state[i][on[j] - 1] != 1){
                    b = false;
                    break;
                }
            }
            if(b == false) continue;
            for(int j = 0; j < num_off; j++){
                if(state[i][off[j] - 1] != 0){
                    b = false;
                    break;
                }
            }
            if(b == true){
                for(int j = 0; j < N; j++){
                    solution[num_solution][j] = state[i][j];
                }
                num_solution++;
            }
        }
    }

    if(num_solution == 0){
        fprintf(fout, "IMPOSSIBLE\n");
    }else{
        sort();
        for(int i = 0; i < num_solution; i++){
            for(int j = 0; j < N; j++){
                fprintf(fout, "%d", solution[i][j]);
            }
            fprintf(fout, "\n");
        }
    }


    fclose(fin);
    fclose(fout);
    return 0;
}
