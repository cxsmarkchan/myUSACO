/*
  id: cxsmarkchan
  PROG: namenum
  LANG: C++
*/

#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

int map[26] = {2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5, 5, 6, 6, 6, 7, -1, 7, 7, 8, 8, 8, 9, 9, 9, -1};

int main(){
    FILE* fin = fopen("namenum.in", "r");
    FILE* fout = fopen("namenum.out", "w");
    FILE* fdict = fopen("dict.txt", "r");

    char name[5000][13];
    int id[5000][12];

    //input
    int N = 0;
    while(fscanf(fdict, "%s", name[N]) != EOF){
        N++;
    }
    //translate names to ids
    for(int i = 0; i < N; i++){
        for(int j = 0; j < 12; j++){
            id[i][j] = 0;
        }
    }
    for(int i = 0; i < N; i++){
        int len = strlen(name[i]);
        for(int j = 0; j < len; j++){
            id[i][j] = map[name[i][j] - 'A'];
        }
    }

    char key[13];
    int key_int[12];
    bool has_match= false;
    //input id
    fscanf(fin, "%s", key);
    for(int i = 0; i < 12; i++){
        key_int[i] = 0;
    }
    for(int i = 0; i < strlen(key); i++){
        key_int[i] = key[i] - '0';
    }

    //match ids
    for(int i = 0; i < N; i++){
        int b = true;
        for(int j = 0; j < 12; j++){
            if(key_int[j] != id[i][j]){
                b = false;
            }
        }
        if(b == true){
            has_match = true;
            fprintf(fout, "%s\n", name[i]);
        }
    }

    //NONE
    if(!has_match){
        fprintf(fout, "NONE\n");
    }

    fclose(fin);
    fclose(fout);
    fclose(fdict);
    return 0;
}
