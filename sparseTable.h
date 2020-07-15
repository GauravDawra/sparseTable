#pragma once

#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

enum type{
    Max = 0,
    Min,
    Sum, 
    Gcd
};

template<type T>
class sparseTable{
    const static int N = 200010;
    const static int logN = 18;
    vector<vector<int> > ST;
    int Log[N + 1];

    static int min(int a, int b){ return (a<b)?a:b; }
    static int max(int a, int b){ return (a>b)?a:b; }
    static int sum(int a, int b){ return a+b; }
    static int gcd(int a, int b){ if(a==0) return b; return gcd(b%a, a); }
    int (*func)(int, int);

    void buildST(vector<int>& v);
    void buildLog();
    int queryMinMaxGcd(int L, int R);
    int querySum(int L, int R);
public:
    sparseTable(vector<int>& v){
        vector<int> c(logN + 1);
        ST.assign(N, c);

        if(T == Max) func = max;
        else if(T == Min) func = min;
        else if(T == Sum) func = sum;
        else func = gcd;

        buildLog();
        buildST(v);
    }
    int query(int L, int R);
    inline vector<vector<int> >& getST(){ return ST; }
};
