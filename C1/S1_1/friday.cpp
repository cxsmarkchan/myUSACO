/*
  id: cxsmarkchan
  PROG: friday
  LANG: C++
*/

#include <iostream>
#include <cstdio>
using namespace std;

// 0..6 Sat..Fri
//int non_leap[] = {3, 3, 6, 1, 3, 6, 2, 5, 0, 3, 5, 1};
//int leap[] = {3, 4, 0, 2, 4, 0, 3, 6, 1, 4, 6, 2};
int non_leap[] = {3, 0, 3, 2, 3, 2, 3, 3, 2, 3, 2, 3};
int leap[] = {3, 1, 3, 2, 3, 2, 3, 3, 2, 3, 2, 3};

bool isLeap(int n){
    if(n % 400 == 0 || (n % 100 != 0 && n % 4 == 0)){
        return true;
    }else{
        return false;
    }
}

int main(){
    FILE *fin = fopen("friday.in", "r");
    FILE *fout = fopen("friday.out", "w");
    
    int N;
    fscanf(fin, "%d", &N);
    
    int day[7] = {0, 0, 0, 0, 0, 0, 0};
    int state = 0;
    
    for(int i = 0; i < N; i++){
        if(isLeap(1900 + i)){
            for(int j = 0; j < 12; j++){
                day[state]++;
                state += leap[j];
                state %= 7;
            }
        }else{
            for(int j = 0; j < 12; j++){
                day[state]++;
                state += non_leap[j];
                state %= 7;
            }
        }
    }
    
    for(int i = 0; i < 7; i++){
        fprintf(fout, "%d", day[i]);
        if(i == 6){
            fprintf(fout, "\n");
        }else{
            fprintf(fout, " ");
        }
    }
    
    fclose(fin);
    fclose(fout);
    
    return 0;
}
