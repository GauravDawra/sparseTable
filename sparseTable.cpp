#include "sparseTable.h"

#include <vector>
#include <iostream>
#include <math.h>

using namespace std;

template<type T>
void sparseTable<T>::buildLog(){
    Log[1] = 0;
    for (int i = 2; i <= N; i++)
        Log[i] = Log[i/2] + 1;
}

template<type T>
void sparseTable<T>::buildST(vector<int>& v){
    int n=v.size();
    for(int i=0;i<n;i++){
        ST[i][0] = v[i];
    }
    int logn = log2(n) + 1;
    for(int k = 1; k <= logn; k++)
        for(int i = 0; i + (1<<k) <= n; i++)
            ST[i][k] = func(ST[i][k-1], ST[i + (1<<(k-1))][k-1]);
}

template<type T>
int sparseTable<T>::queryMinMaxGcd(int L, int R){
    int j = Log[R - L + 1];
    int ans = func(ST[L][j], ST[R - (1 << j) + 1][j]);
    return ans;
}

template<type T>
int sparseTable<T>::querySum(int L, int R){
    int ans = 0;
    int cur = L;
    for(int i=logN;i>=0;i--){
        if(cur + (1<<i) > R + 1) continue;
        ans += ST[cur][i];
        cur += (1<<i);
    }
    return ans;
}

template<type T>
int sparseTable<T>::query(int L, int R){
    if(T == Max || T == Min || T == Gcd) 
        return queryMinMaxGcd(L, R);
    else 
        return querySum(L, R);
}

template class sparseTable<Max>;
template class sparseTable<Min>;
template class sparseTable<Sum>;
template class sparseTable<Gcd>;
