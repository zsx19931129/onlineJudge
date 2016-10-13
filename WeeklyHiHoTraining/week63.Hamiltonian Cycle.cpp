//
//  main.cpp
//  weeklyhiho
//
//  Created by shaoxiong on 10/2/16.
//  Copyright © 2016 shaoxiong. All rights reserved.
//

#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdio>
#include <stack>
#include <algorithm>
#include <map>
#include <unordered_map>

using namespace std;

#define MAXN 12

int n,m;

int edge[MAXN];         // 每个元素对应的二进制位给出每个顶点的next向量
int cnt = 0;
int dp[MAXN][1<<MAXN];  //表示当前顶点为第一维下标、当前访问向量unused为第二维下标时的到终点的方案总数

//计算dp数组和深搜合并
void dfs(int vidx, int unused){
    //如果所有顶点都访问了，则unused为0
    if(!unused){
        // 判断当前顶点是否有到1的边
        cnt += (edge[vidx] & 1);
        return ;
    }
    if(dp[vidx][unused] != 0){
        if(dp[vidx][unused] > 0){
            cnt += dp[vidx][unused];
        }
        return ;
    }
    int fcnt = cnt;
    int rest = edge[vidx] & unused;
    for(int i=1;i<=n;++i){
        if(rest & (1<<i)){
            dfs(i, unused - (1<<i));
        }
    }
    if(fcnt == cnt){
        dp[vidx][unused] = -1;
    }else{
        dp[vidx][unused] = cnt - fcnt;
    }
}

int main() {
    cin>>n>>m;
    int v1, v2;
    for(int i=0;i<m;++i){
        cin>>v1>>v2;
        edge[v1-1] |= (1<<(v2-1));
    }
    //表示1已经被访问
    dfs(0, (1<<n)-2);
    if(dp[0][(1<<n)-2]<0){
        cout<<0<<endl;
    }else{
        cout<<dp[0][(1<<n)-2]<<endl;
    }
    return 0;
}
