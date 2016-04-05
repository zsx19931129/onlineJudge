// 2-sat问题，用2n图，加强连通判定解决，强连通判定用tarjan算法
// 思路：1.根据读入信息，建立有向图以及各限制关系对应的有向边。2.进行强连通分量求解。3.判断
// 是否有同一个点i的两个状态，i0和i1属于同一个强连通分量，如果是则不存在解

#define MAXN 20005
#define MAXM 200005

#include <iostream>
#include <stack>
#include <algorithm>
#include <cstring>

using namespace std;

int n,m;
struct node{
    int x,y,next;
}edge[MAXM << 1];
// Tarjan算法需要用到的一些数据结构，dfn数组记录搜索到该点时的时间（可以理解为该点被搜索的序号）
// low是一个标记数组，表示该点或者以这个点为根的子树能够追溯到最早的栈中节点的次序。
// belong用来判定指定节点属于哪个连通分量
// head数组存储以指定标号开始的所有的边的第一条边的序号
int head[MAXN],dfn[MAXN],low[MAXN],belong[MAXN];
int dfsIndex, tpnum, en;
bool instack[MAXN];
stack<int> mystack;

void addEdge(int x, int y){
    edge[++en].next = head[x];
    head[x] = en;
    edge[en].x = x;
    edge[en].y = y;
}

void input(){
    cin>>n>>m;
    int x,y,s;
    int x0,x1,y0,y1;				//每个顶点对应两个节点
    memset(head, 0, sizeof(head));	//用一个数组串起所有边
    en = 0;
    while(m--){
        cin>>x>>y>>s;
        x0 = x<<1;
        x1 = x<<1 | 1;
        y0 = y<<1;
        y1 = y<<1 | 1;
        if(s){
            // 不能同时为1
            addEdge(x1, y0);
            addEdge(y1, x0);
        }else{
            addEdge(x0, y1);
            addEdge(y0, x1);
        }
    }
    
    //初始化Tarjan算法的变量
    memset(dfn, 0, sizeof(dfn));
    memset(instack, false, sizeof(instack));
    memset(belong, -1, sizeof(belong));
    while(!mystack.empty()){
        mystack.pop();
    }
    dfsIndex = tpnum = 0;
}

void tarjan(int x){
    dfn[x] = low[x] = ++dfsIndex;		//初始化
    instack[x] = true;
    mystack.push(x);
    // 遍历所有边
    int cur;
    for(int i = head[x];i;i=edge[i].next){
        cur = edge[i].y;
        if(!dfn[cur]){
            tarjan(cur);
            low[x] = min(low[x], low[cur]);
        }else{
            if(instack[cur]){
                low[x] = min(low[x], dfn[cur]);
            }
        }
    }
    if(low[x] == dfn[x]){
        tpnum++;
        do{
            x = mystack.top();
            mystack.pop();
            belong[x] = tpnum;
            instack[x] = false;
        }while(low[x] != dfn[x]);
    }
}

bool judge(){
    for(int i=0;i<n;i++){
        if(belong[i<<1] == belong[i<<1 | 1]){
            return false;
        }
    }
    return true;
}

int main(){
    int t;
    cin>>t;
    while(t--){
        input();
        for(int i=0;i<(n<<1);i++){
            //遍历保证所有的连通分量都能被访问
            if(!dfn[i]){
                tarjan(i);
            }
        }
        if(judge()){
            cout<<"Yes"<<endl;
        }else{
            cout<<"No"<<endl;
        }
    }
    return 0;
}
