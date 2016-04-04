// 树形dp，dp(i,j)表示节点i选择j个子节点（包括自己）拥有的最大值
// dp(i,0) = 0(表示不选该i节点)，dp(i,1) = val[i];(这个节点本身的权值)
// 遍历自己的子节点，对每个子节点，计算dp(i,1)到dp(i,m)
// 转移方程：dp(i, x + y) = max(dp(i,x) + dp(i,y), dp(i, x + y))
// 一个trick，给推荐的景点一个很大的权值，最后计算时候如果发现没有取到所有的推荐景点说明无解
// 题中下标从1开始

#define MAXN 101
#define RCMAUG 100000

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

int val[MAXN];
vector<int> mymap[MAXN];		//用一个vector数组来模拟图(此处为树)
int dp[MAXN][MAXN];

int n,k,m;


void dfs(int cur, int root){
    dp[cur][0] = 0;
    dp[cur][1] = val[cur];
    
    //遍历所有子节点
    for(int i=0;i<mymap[cur].size();i++){
        int child = mymap[cur][i];
        //避免递归调用，无向图是双向的
        if(child == root){
            continue;
        }
        //保证子节点的相关状态都已经求出
        dfs(child, cur);
        
        // 泛化分组背包问题
        for(int j=m;j>=1;j--){
            for(int k=1;k<=j;k++){
                if(dp[child][j-k] == -1 || dp[cur][k] == -1){
                    continue;
                }
                dp[cur][j] = max(dp[cur][j], dp[cur][k] + dp[child][j-k]);
            }
        }
    }
}

int main(){
    cin>>n>>k>>m;
    for(int i=1;i<=n;i++){
        cin>>val[i];
    }
    // 为推荐景点赋高权值
    int rcm;
    for(int i=1;i<=k;i++){
        cin>>rcm;
        val[rcm] += RCMAUG;
    }
    // 输入连通树
    int v1,v2;
    for(int i=0;i<n-1;i++){
        cin>>v1>>v2;
        //无向图
        mymap[v1].push_back(v2);
        mymap[v2].push_back(v1);
    }
    // -1 的二进制 11111111 所以可以用memset统一赋值-1
    memset(dp, -1, sizeof(dp));
    dfs(1, -1);
    int res = dp[1][m];
    res -= k*RCMAUG;
    if(res < 0){
        cout<<"-1"<<endl;
    }else{
        cout<<res<<endl;
    }
    return 0;
}