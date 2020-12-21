#include <time.h>
#include <stdlib.h>
#include <cmath>

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

int encrypt_bitstring(char* m, int* B){
    int sum = 0;
    for(int i = 0; i < kBLOCK_SIZE; ++i){
        sum += B[i]*m[i];
    }
    return sum;
}

int extended_euclidean(int a, int b, int* x, int* y){
    if (a==0){
        *x = 0;
        *y = 1;
        return b;
    }
    int x1, y1;
    int g = extended_euclidean(b % a, a, &x1, &y1);
    *x = y1 - (b/a) * x1;
    *y = x1;
    return g;
}

int mod_inverse(int r, int q){ // extended euclidean algorithm finds: ax + by = gcd(a, b)
                               // because r and q are coprime we find rx + qy = 1, x is multiplicative inverse of r mod q
    int x, y;
    int g = extended_euclidean(r, q, &x, &y);
    return (x % q + q) % q;
}

struct intArrayTuple greedy_superincreasing_subsetsum(int* W, int target_sum){
    int X[kBLOCK_SIZE];
    int length = 0;
    int pos = kBLOCK_SIZE - 1;
    while(target_sum > 0){
        while(W[pos--] > target_sum);
        target_sum -= W[pos+1];
        X[length++] = pos+1;
    }
    struct intArrayTuple res = {X, length};
    return res;
}

int decrypt(char* c, int* B, int* W, int q, int r){
    int r_prime = mod_inverse(r, q);
    int c_prime = (c * r_prime) % q;
    struct intArrayTuple subsetsum_solution = greedy_superincreasing_subsetsum(W, c_prime);
    int m = 0;
    for(int i = 0; i < subsetsum_solution.i; ++i){
        m += pow(2, kBLOCK_SIZE - subsetsum_solution.arr[i]);
    }
    return m;
}

int main(){
    srand(time(NULL));
    struct intArrayTuple superincreasing = generate_superincreasing();
    int q = rand() + superincreasing.i + 1;
    int r = generate_coprime(q);
    int* B = get_public_key(superincreasing.arr, q, r);

}