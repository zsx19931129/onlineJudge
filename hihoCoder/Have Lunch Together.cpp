// bfs求符合条件的最短路，思路：首先找到一个solution，然后求solution的最短路，比较最优值，穷举
// 一次从起点开始的bfs就可以求出从起点到所有可行点的最短路径

#define MAXN 102
#define INFINATE 10000
#include <iostream>
#include <string>
#include <queue>
using namespace std;

int cafeMap[MAXN][MAXN];
int n,m;
int startX, startY;
int res = INFINATE;
int offset[4][2] = { {0,-1}, {0,1}, {-1,0}, {1,0} };	//第一维 上下左右， 第二维 x,y
int minDis[MAXN][MAXN];				//存储所有可达点到起点的最短路，记忆化搜索

struct bfsNode{
    int x;
    int y;
    int step;
    bfsNode(int a, int b,int c):x(a),y(b),step(c){}
};

inline void input(){
    //在输入这里做一个优化，把不可能的情况，比如孤立的s直接在输入里排除
    cin>>n>>m;
    //在cafeMap周围加一圈墙，可以避免繁琐的边界判定，空间换时间
    for(int i=0;i<=n+1;i++){
        cafeMap[i][0] = cafeMap[i][m+1] = -1;
    }
    for(int i=0;i<=m+1;i++){
        cafeMap[0][i] = cafeMap[n+1][i] = -1;
    }
    string str;
    for(int i=1;i<=n;i++){
        cin>>str;
        str = " " + str;		//让下标从1开始
        for(int j=1;j<=m;j++){
            if(str[j] == '#' || str[j] == 'P'){
                cafeMap[i][j] = -1;
            }else if(str[j] == '.'){
                cafeMap[i][j] = 0;
            }else if(str[j] == 'S'){
                cafeMap[i][j] = 1;
            }else if(str[j] == 'H'){
                startX = i;
                startY = j;
                cafeMap[i][j] = 0;
            }
        }
    }
    
    //剪枝，去掉不符合条件的S
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(cafeMap[i][j] == 1){
                bool findSec = false;
                for(int k=0;k<4;k++){
                    int newX = i + offset[k][0];
                    int newY = j + offset[k][1];
                    if(cafeMap[newX][newY] == 1){
                        findSec = true;
                        break;
                    }
                }
                if(!findSec){
                    cafeMap[i][j] = -1;
                }
            }
        }
    }
}

//广度优先遍历整个迷宫，求出
inline void bfs(){
    bool visited[MAXN][MAXN];
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            visited[i][j] = false;
        }
    }
    queue<bfsNode> myQueue;
    myQueue.push(bfsNode(startX, startY, 0));
    while(!myQueue.empty()){
        bfsNode item = myQueue.front();
        myQueue.pop();
        visited[item.x][item.y] = true;
        minDis[item.x][item.y] = item.step;
        for(int i=0;i<4;i++){
            int newX = item.x + offset[i][0];
            int newY = item.y + offset[i][1];
            if(cafeMap[newX][newY] == 0 && !visited[newX][newY]){
                myQueue.push(bfsNode(newX, newY, item.step + 1));
            }
        }
    }
}

int getMinDis(int x,int y){
    int ret = INFINATE;
    for(int i=0;i<4;i++){
        int newX = x + offset[i][0];
        int newY = y + offset[i][1];
        if(cafeMap[newX][newY] == 0 && minDis[newX][newY] < ret){
            ret = minDis[newX][newY];
        }
    }
    return ret;
}

inline void solve(){
    bool findSol = false;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(cafeMap[i][j] == 1){
                findSol = true;
                //找到一个空位置，遍历上下左右，找到最短路和另一个位置
                int s1 = getMinDis(i,j);
                int s2 = INFINATE;			//由于经过剪枝，S周围一定有第二个S
                for(int k=0;k<4;k++){
                    int newX = i + offset[k][0];
                    int newY = j + offset[k][1];
                    if(cafeMap[newX][newY] == 1){
                        int tmp = getMinDis(newX, newY);
                        if(tmp<s2){
                            s2 = tmp;
                        }
                    }
                }
                if(s1 + s2 < res){
                    res = s1+s2;
                }
            }
        }
    }
    //加上到位置上的两步
    if(findSol){
        cout<<res+2<<endl;
    }else{
        cout<<"Hi and Ho will not have lunch."<<endl;
    }
}

int main(){
    input();
    bfs();
    solve();
    return 0;
}