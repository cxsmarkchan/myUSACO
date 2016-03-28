/*
  id: cxsmarkchan
  PROG: castle
  LANG: C++
*/

#include <cstdio>
#include <cstring>
#include <cstdlib>
using namespace std;

//i,x mean the horizontal coordinate(from west to east)
//j,y mean the vertical coordinate(from north to south)

int M, N;
int cast[50][50];
int visit[50][50];
int size[2500];
int num = 0;

void search(int x, int y){
    visit[x][y] = num + 1;
    size[num]++;
    if(x > 0 && cast[x][y] % 2 == 0 && visit[x - 1][y] == 0){
        search(x - 1, y);
    }
    if(x < M - 1 && (cast[x][y] / 4) % 2 == 0 && visit[x + 1][y] == 0){
        search(x + 1, y);
    }
    if(y > 0 && (cast[x][y] / 2) % 2 == 0 && visit[x][y - 1] == 0){
        search(x, y - 1);
    }
    if(y < N - 1 && (cast[x][y] / 8) % 2 == 0 && visit[x][y + 1] == 0){
        search(x, y + 1);
    }
}

void search(){
    for(int x = 0; x < M; x++){
        for(int y = 0; y < N; y++){
            if(visit[x][y] == 0){
                search(x, y);
                num++;
            }
        }
    }
}

int main(){
    FILE *fin = fopen("castle.in", "r");
    FILE *fout = fopen("castle.out", "w");

    memset(size, 0, 2500 * sizeof(int));
    memset(visit, 0, 2500 * sizeof(char));
    fscanf(fin, "%d%d", &M, &N);
    for(int j = 0; j < N; j++){
        for(int i = 0; i < M; i++){
            fscanf(fin, "%d", &cast[i][j]);
        }
    }

    search();


    int max = 0;
    for(int i = 0; i < num; i++){
        if(size[i] > max) max = size[i];
    }

    int max_merge = 0;
    int max_merge_x, max_merge_y;
    char direction;
    for(int i = 0; i < M; i++){
        for(int j = 0; j < N; j++){
            if(i < M - 1 && visit[i][j] != visit[i + 1][j]){
                int sum = size[visit[i][j] - 1] + size[visit[i + 1][j] - 1];
                if(sum > max_merge
                   || (sum == max_merge
                       && (i < max_merge_x
                           || (i == max_merge_x && j > max_merge_y)))){
                    max_merge = sum;
                    max_merge_x = i;
                    max_merge_y = j;
                    direction = 'E';
                }
            }
            if(j > 0 && visit[i][j] != visit[i][j - 1]){
                int sum = size[visit[i][j] - 1] + size[visit[i][j - 1] - 1];
                if(sum > max_merge
                   || (sum == max_merge
                       && (i < max_merge_x
                           || (i == max_merge_x && j >= max_merge_y)))){
                    max_merge = sum;
                    max_merge_x = i;
                    max_merge_y = j;
                    direction = 'N';
                }
            }
        }
    }

    fprintf(fout, "%d\n", num);
    fprintf(fout, "%d\n", max);
    fprintf(fout, "%d\n", max_merge);
    fprintf(fout, "%d %d %c\n", max_merge_y + 1, max_merge_x + 1, direction);

    fclose(fin);
    fclose(fout);
    return 0;
}
