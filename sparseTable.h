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
    inline vector<int>& getST(){ return ST; }
};

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