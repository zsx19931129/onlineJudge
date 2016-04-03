// 首先可以很直观的想到dfs的解法，记录当前和，最大数，gcd(利用如果符合题意则gcd(mul,M)==M)的性质
// 由此可以想到用记忆化搜索，用一个三维数组去存储状态，记忆化搜索一般情况下都可以转化成动态规划的问题
// 难点在于想出dp的转移方程

// 1+2..+14>100，所以用dfs最多14层

// 根据一个gcd性质的推论 如果gcd(mul, M)==k,则mul = p*k, M = q*k,p和q互质
// 所以gcd(mul*l,M)=gcd(l*k*p,k*q)=kgcd(l*p,q)，因为p和q互质，所以gcd(l*p,q)=gcd(l,q)
// 所以gcd(mul*l,M)=kgcd(l,q)=gcd(k*l,k*q)= gcd(k*l,M), 因为k*l最大50*100，可以用一个5000的数组预处理


#define MOD 1000000007
#define MAXN 101
#define MAXM 51
#include <iostream>

using namespace std;

int n,m;
int dp[MAXN][MAXN][MAXM];			//分别为当前和，最大数，当前gcd值
int gcdTbl[MAXN*MAXM];				//存储所有与M最大公约数可能要用到的情况

int gcd(int a, int b){
    if(b==0){
        return a;
    }else{
        return gcd(b,a%b);
    }
}

inline void genGcdTbl(){
    for(int i=0;i<MAXN*MAXM;i++){
        if(i>m)
            gcdTbl[i] = gcd(i,m);
        else{
            gcdTbl[i] = gcd(m,i);
        }
    }
}

int main(){
    cin>>n>>m;
    genGcdTbl();
    dp[0][0][1] = 1;
    //正向dp，逐个求解，注意边界的取值
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            for(int k=1;k<=m;k++){
                if(dp[i][j][k]>0){
                    //当前这个dp状态有解，可以用它来推其他解
                    for(int l=j+1;l<=n-i;l++){
                        dp[i+l][l][gcdTbl[l*k]] = (dp[i][j][k] + dp[i+l][l][gcdTbl[l*k]])%MOD;
                    }
                }
            }
        }
    }
    int res = 0;
    for(int i=1;i<=n;i++){
        res += dp[n][i][m];
    }
    cout<<res<<endl;
    return 0;
}