/*
  id: cxsmarkchan
  PROG: ttwo
  LANG: C++
*/

#include <cstdio>
#include <cstring>
#include <cstdlib>

using namespace std;

char forest[11][11];
int visit[400][400];

int getNext(int cur);

int main() {
    FILE *fin = fopen("ttwo.in", "r");
    FILE *fout = fopen("ttwo.out", "w");

    memset(visit, 0, sizeof(visit));
    for(int i = 0; i < 10; i++) {
        fscanf(fin, "%s", forest[i]);
    }

    int FJ;
    int cow;
    for(int i = 0; i < 10; i++) {
        for(int j = 0; j < 10; j++) {
            if(forest[i][j] == 'F') {
                FJ = i * 10 + j;
            } else if(forest[i][j] == 'C') {
                cow = i * 10 + j;
            }
        }
    }

    int num = 0;
    bool isloop = true;
    while(!visit[FJ][cow]) {
        if((FJ % 100) == (cow % 100)) {
            isloop = false;
            break;
        } else {
            visit[FJ][cow] = 1;
            FJ = getNext(FJ);
            cow = getNext(cow);
            num++;
        }
    }

    if(isloop) {
        fprintf(fout, "%d\n", 0);
    } else {
        fprintf(fout, "%d\n", num);
    }


    fclose(fin);
    fclose(fout);
    return 0;
}

int getNext(int cur){
    int x, y;
    int direction;
    //FJ
    x = (cur % 100) / 10;
    y = (cur % 100) % 10;
    direction = cur / 100;
    switch(direction) {
    case 0: // north
        if(x > 0 && forest[x - 1][y] != '*') {
            x--;
        } else {
            direction++;
        }
        break;
    case 1: // east
        if(y < 9 && forest[x][y + 1] != '*') {
            y++;
        } else {
            direction++;
        }
        break;
    case 2: // south
        if(x < 9 && forest[x + 1][y] != '*') {
            x++;
        } else {
            direction++;
        }
        break;
    case 3: // west
        if(y > 0 && forest[x][y - 1] != '*') {
            y--;
        } else {
            direction = 0;
        }
        break;
    }
    return direction * 100 + x * 10 + y;
}
