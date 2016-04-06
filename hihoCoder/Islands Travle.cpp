// 这个题本身是求单源最短路径，但是如果不对图进行优化，将会是一个n个节点的完全图
// 根据距离公式进行优化：1.合并坐标相同节点，组成团，团内节点距离是0，这个步骤新增加的总边数是O(n)
// 2.连接相邻的节点，相邻节点连接起来一定不会差于跨越相邻节点的连接
// 分别在x和y方向上执行这两个优化，最后得到利用Dijkstra或SPFA算法得到最短路

#define MAXN 100005
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <cstring>

using namespace std;

struct point{
    int x,y,id;
};

bool comp_x(const point &n1, const point &n2){
    return n1.x < n2.x;
}

bool comp_y(const point &n1, const point &n2){
    return n1.y < n2.y;
}

//  构造出的无向有权图的节点，这里不需要x,y坐标
struct node{
    int id;			// 标识这个节点
    int dis;		// 从1出发的节点
    node(int i, int d):id(i),dis(d){}
    bool operator<(const node &n)const{
        return n.dis < dis;
    }
};

int n;
int dis[MAXN];				//djkstra距离向量
point parr[MAXN];			//输入的n个节点的坐标信息
vector<node> mlink[MAXN];	//邻接表存储图


int main(){
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>parr[i].x>>parr[i].y;
        parr[i].id = i;
    }
    sort(parr, parr + n, comp_x);
    for(int i=0;i<n;){
        int j = i+1;
        for(;j<n && parr[j].x == parr[i].x;j++){
            mlink[parr[i].id].push_back(node(parr[j].id, 0));
            mlink[parr[j].id].push_back(node(parr[i].id, 0));
        }
        
        if(j<n){
            mlink[parr[i].id].push_back(node(parr[j].id, parr[j].x - parr[i].x));
            mlink[parr[j].id].push_back(node(parr[i].id, parr[j].x - parr[i].x));
        }
        
        i = j;
    }
    sort(parr, parr + n, comp_y);
    for(int i=0;i<n;){
        int j=i+1;
        for(;j<n && parr[j].y == parr[i].y;j++){
            mlink[parr[i].id].push_back(node(parr[j].id, 0));
            mlink[parr[j].id].push_back(node(parr[i].id, 0));
        }
        if(j<n){
            mlink[parr[i].id].push_back(node(parr[j].id, parr[j].y - parr[i].y));
            mlink[parr[j].id].push_back(node(parr[i].id, parr[j].y - parr[i].y));
        }
        i = j;
    }
    
    // spfa求最短路，这里没有负权，所以在原spfa算法上有一定程度上的简化
    priority_queue<node> pq;
    memset(dis, 0x3f, sizeof(dis));
    dis[0] = 0;
    pq.push(node(0,0));
    while(!pq.empty()){
        node cur = pq.top();
        pq.pop();
        
        if(cur.dis > dis[cur.id]){
            //遇到另一个方向的对应相邻边
            continue ;
        }
        
        if(cur.id == n-1){
            // 已经到n，不需要再继续
            break;
        }
        
        for(int i=0;i<mlink[cur.id].size();i++){
            if(dis[mlink[cur.id][i].id] > cur.dis + mlink[cur.id][i].dis){
                dis[mlink[cur.id][i].id] = cur.dis + mlink[cur.id][i].dis;
                pq.push(node(mlink[cur.id][i].id, dis[mlink[cur.id][i].id]));
            }
        }
    }
    
    cout<<dis[n-1]<<endl;
    return 0;
}