/*
  id: cxsmarkchan
  PROG: contact
  LANG: C++
*/

#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;

#define MAX 16382

char str[200005];
int A, B, N;

int begin_num[13];
void init_begin_num() {
    int tmp = 2;
    for(int i = 0; i < 13; i++) {
        begin_num[i] = tmp - 2;
        tmp *= 2;
    }
}

struct Sub {
    int num;
    char substr[13];
    int len; //length of substr
    int bin; //binary number of substr

    bool operator<(const Sub& _right) {//actually greater than
        if(num > _right.num) return true;
        else if(num < _right.num) return false;
        else if(len < _right.len) return true;
        else if(len > _right.len) return false;
        else return bin < _right.bin;
    }
}sub[MAX];

void init_sub() {
    for(int i = 0; i < 12; i++) {
        char buf[10];
        sprintf(buf, "%%0%dlld", i + 1);
        for(int j = begin_num[i]; j < begin_num[i + 1]; j++) {
            sub[j].num = 0;
            sub[j].len = i + 1;
            sub[j].bin = j - begin_num[i];
            long long num2 = 0;
            int num10 = sub[j].bin;
            long long digit = 1;
            while(num10 > 0) {
                num2 += (num10 % 2) * digit;
                digit *= 10;
                num10 /= 2;
            }
            sprintf(sub[j].substr, buf, num2);
        }
    }
}

int str2bin(char *begin, int len) {
    int tmp = 0;
    for(int i = 0; i < len; i++) {
        tmp = tmp * 2 + (begin[i] - '0');
    }
    return tmp;
}

void swap(int x1, int x2) {
    Sub tmp = sub[x1];
    sub[x1] = sub[x2];
    sub[x2] = tmp;
}

void sort(int begin, int end) {
    if(end - begin <= 1) return;

    int mid = (begin + end) / 2;
    swap(begin, mid);

    int tmp1 = begin + 1;
    int tmp2 = begin + 1;
    while(tmp1 < end) {
        if(sub[tmp1] < sub[begin]) {
            swap(tmp1++, tmp2++);
        } else {
            tmp1++;
        }
    }
    tmp2--;
    swap(tmp2, begin);

    sort(begin, tmp2);
    sort(tmp2 + 1, end);
}

int main() {
    FILE *fin = fopen("contact.in", "r");
    FILE *fout = fopen("contact.out", "w");

    init_begin_num();
    init_sub();

    fscanf(fin, "%d%d%d", &A, &B, &N);

    int len = 0;
    char buf[100];
    fscanf(fin, "%s", buf);
    while(!feof(fin)) {
        strcpy(str + len, buf);
        len += strlen(buf);
        fscanf(fin, "%s", buf);
    }

    for(int i = 0; i < len; i++) {
        int j_max = B;
        if(i + j_max > len) j_max = len - i;
        for(int j = A - 1; j < j_max; j++) {
            sub[begin_num[j] + str2bin(str + i, j + 1)].num++;
        }
    }

    sort(0, MAX);

    int cur_place = 0;

    for(int ord = 0; ord < N; ord++) {
        if(sub[cur_place].num == 0) break;
        fprintf(fout, "%d\n", sub[cur_place].num);

        int num = sub[cur_place].num;
        int inner_ord = 0;
        while(sub[cur_place].num == num) {
            if(inner_ord == 0) {
                fprintf(fout, "%s", sub[cur_place].substr);
            } else if(inner_ord < 5) {
                fprintf(fout, " %s", sub[cur_place].substr);
            } else {
                fprintf(fout, " %s\n", sub[cur_place].substr);
            }
            inner_ord++;
            inner_ord %= 6;
            cur_place++;
        }
        if(inner_ord != 0) {
            fprintf(fout, "\n");
        }
    }

    fclose(fin);
    fclose(fout);
    return 0;
}
