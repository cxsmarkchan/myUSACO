/*
  id: cxsmarkchan
  PROG: ride
  LANG: C++
*/
#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

int main(){
    FILE *fin = fopen("ride.in", "r");
    FILE *fout = fopen("ride.out", "w");

    char str1[7];
    char str2[7];
    fscanf(fin, "%s%s", str1, str2);


    int len1 = strlen(str1);
    int len2 = strlen(str2);
    long mult1 = 1, mult2 = 1;

    for(int i = 0; i < len1; i++){
        str1[i] -= ('A' - 1);
        mult1 *= str1[i];
    }
    for(int i = 0; i < len2; i++){
        str2[i] -= ('A' - 1);
        mult2 *= str2[i];
    }

    if((mult1 % 47) == (mult2 % 47)){
        fprintf(fout, "GO\n");
    }else{
        fprintf(fout, "STAY\n");
    }

    fclose(fin);
    fclose(fout);
    return 0;
}
