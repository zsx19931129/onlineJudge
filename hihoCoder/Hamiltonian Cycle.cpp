// dp + 位操作
#define MAXN 12

#include <iostream>

using namespace std;

int n,m;

// 每个元素对应的二进制位给出每个顶点的next向量
int edge[MAXN];
//空间换时间，得出二进制对应的顶点
//int p[1 << MAXN];
int cnt=0;
//表示当前顶点为第一维下标、当前访问向量unused为第二维下标时的到终点的方案总数
int dp[MAXN][1<<MAXN];

//计算dp数组和深搜合并
void dfs(int vidx, int unused){
    //如果所有顶点都访问了，则unused为0
    if(!unused){
        // 判断当前顶点是否有到1的边
        cnt += (edge[vidx] & 1);
        return ;
    }
    //全局变量初始化为0
    if(dp[vidx][unused]!=0){
        if(dp[vidx][unused]>0){
            cnt += dp[vidx][unused];
        }
        return ;
    }
    int fcnt = cnt;
    //获得既能到达，又未访问的节点向量
    int rest = unused&edge[vidx];
    for(int i=0;i<n;i++){
        if(rest&(1<<i)){
            dfs(i, unused - (1<<i));
        }
    }
    if(fcnt == cnt)
        dp[vidx][unused] = -1;
    else
        dp[vidx][unused] = cnt - fcnt;
}

int main(){
    cin>>n>>m;
    int v1,v2;
    // for(int i=0;i<n;i++){
    // 	p[1<<i] = i+1;
    // }
    for(int i=0;i<m;i++){
        cin>>v1>>v2;
        edge[v1-1] |= 1 << (v2-1);
    }
    //表示1已经被访问
    dfs(0,(1<<n)-2);
    if(dp[0][(1<<n)-2]<0){
        //没有解决方案的情况
        cout<<0<<endl;
    }else{
        cout<<dp[0][(1<<n)-2]<<endl;
    }
    return 0;
}