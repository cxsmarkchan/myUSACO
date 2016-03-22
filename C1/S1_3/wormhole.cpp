/*
  id: cxsmarkchan
  PROG: wormhole
  LANG: C++
*/

#include <cstdio>
using namespace std;

int N;
int x[12], y[12];
int match[12];
int next[12];
int now_match = 0;
int num = 0;
int cmp(int i1, int i2){
    if(y[i1] < y[i2]) return -1;
    else if(y[i1] > y[i2]) return 1;
    else if(x[i1] < x[i2]) return -1;
    else if(x[i1] > x[i2]) return 1;
    else return 0;
}

void swap(int i1, int i2){
    int tmp = x[i1];
    x[i1] = x[i2];
    x[i2] = tmp;
    tmp = y[i1];
    y[i1] = y[i2];
    y[i2] = tmp;
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

bool check(){
    for(int i = 0; i < N - 1; i++){
        int cur = i;
        int step = 0;
        while(next[cur] >= 0){
            cur = next[cur];
            cur = match[cur];
            step++;
            if(step > N) return true;
        }
    }
    return false;
}

void search(){
    if(now_match == N){
        if(check() == true){
            num++;
        }
    }else{
        int backup = now_match;
        int next1, next2 = N;
        for(int i = now_match + 1; i < N; i++){
            if(match[i] < 0){
                next1 = i;
                break;
            }
        }
        for(int i = next1 + 1; i < N; i++){
            if(match[i] < 0){
                next2= i;
                break;
            }
        }
        match[now_match] = next1;
        match[next1] = now_match;
        now_match = next2;
        search();
        now_match = backup;
        match[now_match] = match[next1] = -1;
        if(next2 < N){
            for(int i = next2; i < N; i++){
                if(match[i] < 0){
                    match[now_match] = i;
                    match[i] = now_match;
                    now_match = next1;
                    search();
                    now_match = backup;
                    match[now_match] = match[i] = -1;
                }
            }
        }
    }
}

int main(){
    FILE *fin = fopen("wormhole.in", "r");
    FILE *fout = fopen("wormhole.out", "w");

    fscanf(fin, "%d", &N);
    for(int i = 0; i < N; i++){
        fscanf(fin, "%d%d", x + i, y + i);
    }
    sort(0, N);
    for(int i = 0; i < N - 1; i++){
        if(y[i + 1] == y[i]){
            next[i] = i + 1;
        }else{
            next[i] = -1;
        }
    }
    next[N - 1] = -1;

    for(int i = 0; i < N; i++){
        match[i] = -1;
    }

    search();

    fprintf(fout, "%d\n", num);

    fclose(fin);
    fclose(fout);
}
