#include <time.h>
#include <stdlib.h>

int kBLOCK_SIZE = 100;

struct intArrayTuple {
    int* arr;
    int i;
};

struct intArrayTuple generate_superincreasing(){
    int arr[kBLOCK_SIZE];
    int sum = 0;
    for(int i = 0; i <n; ++i){
        int r  = rand() + sum + 1;
        arr[i] = r;
        sum += r;
    }
    struct intArrayTuple res = {arr, sum};
    return res;
}

int gcd(int m, int n){
    while(n > 0){
        int r = m % n;
        m = n;
        n = r;
    }
    return m;
}

int generate_coprime(int n){ // relies on the fact that two random numbers have a 60% chance of being coprime
    int p = rand();
    if(gcd(n, p) == 1)
        return p;
    generate_coprime(n);
}

int* get_public_key(int* W, int q, int r){
    int B[kBLOCK_SIZE];
    for(int i = 0; i < kBLOCK_SIZE; ++i){
        B[i] = r*W[i] % q;
    }
    return B;
}

int main(){
    srand(time(NULL));
    struct intArrayTuple superincreasing = generate_superincreasing();
    int q = rand() + superincreasing.i + 1;
    int r = generate_coprime(q);
    int* B = get_public_key(superincreasing.arr, q, r);

}