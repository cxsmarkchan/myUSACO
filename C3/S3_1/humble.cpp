/*
  id: cxsmarkchan
  PROG: humble
  LANG: C++
*/

#include <cstdio>
using namespace std;

#define MAX_K 100
#define MAX_N 100000
#define MAX (((unsigned int)1 << 31) - 1)

int K, N;
unsigned int prime[MAX_K];

inline void swap(unsigned int& x1, unsigned int& x2) {
    int tmp = x1;
    x1 = x2;
    x2 = tmp;
}

struct Heap {
    unsigned int elem[10 * MAX_N];
    int size;
    int max;

    Heap():size(0), max(0){}

    bool push(unsigned int num) {
        if(size >= N && num > max) {
            return false;
        } else {
            if(max <= 0 || num > max) {
                max = num;
            }
            elem[size++] = num;
            int cur = size - 1;
            while(cur != 0) {
                int parent = (cur - 1) / 2;
                if(elem[cur] < elem[parent]) {
                    swap(elem[cur], elem[parent]);
                    cur = parent;
                } else {
                    break;
                }
            }
            return true;
        }
    }

    unsigned int pop() {
        int rtn = elem[0];
        swap(elem[--size], elem[0]);
        int cur = 0;
        while(2 * cur + 1 < size) {
            if(2 * cur + 2 < size) {
                if(elem[cur] > elem[2 * cur + 2]
                   && elem[2 * cur + 1] > elem[2 * cur + 2]) {
                    swap(elem[cur], elem[2 * cur + 2]);
                    cur = 2 * cur + 2;
                } else if(elem[cur] > elem[2 * cur + 1]
                          && elem[2 * cur + 2] > elem[2 * cur + 1]) {
                    swap(elem[cur], elem[2 * cur + 1]);
                    cur = 2 * cur + 1;
                } else {
                    break;
                }
            } else {
                if(elem[cur] > elem[2 * cur + 1]) {
                    swap(elem[cur], elem[2 * cur + 1]);
                }
                break;
            }
        }
        return rtn;
    }
} heap;

int main() {
    FILE *fin = fopen("humble.in", "r");
    FILE *fout = fopen("humble.out", "w");

    fscanf(fin, "%d%d", &K, &N);
    for(int i = 0; i < K; i++) {
        fscanf(fin, "%u", &prime[i]);
    }

    heap.push(1);

    unsigned int humble = 0;
    for(int cur = 0; cur <= N; cur++) {
        humble = heap.pop();

        int k;
        for(k = K - 1; k >= 0; k--) {
            if(humble % prime[k] == 0) break;
        }
        if(k < 0) k = 0;
        for(; k < K; k++) {
            if(humble > MAX / prime[k]) break;
            if(!heap.push(humble * prime[k])) break;
        }
    }

    fprintf(fout, "%u\n", humble);

    fclose(fin);
    fclose(fout);
    return 0;
}
