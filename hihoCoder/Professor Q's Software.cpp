// 模拟题，一个优化，提前算出每个software启动一次，对各个软件启动次数增加的分量，考虑到内存，不太可行...

#define MAXN 100005
#define MAXM 100005
#define MOD 142857

#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
#include <map>

using namespace std;

struct sNode{
    int idx;                //对应的索引
    int cnt;
    int rstat[3];
    sNode(){
        cnt=0;
        rstat[0] = rstat[1] = rstat[2] = -1;
    }
    sNode(int i, int c, int r1 = -1, int r2 = -1, int r3 = -1):idx(i), cnt(c){
        rstat[0] = r1;
        rstat[1] = r2;
        rstat[2] = r3;
    }
};

int n,m,t;
int softwareCnt[MAXM]={0};
int initArr[MAXN]={0};
map<int, vector<sNode>> i2node;

void init(){
    memset(softwareCnt, 0, sizeof(softwareCnt));
    i2node.clear();
}

void process(int in){
    if(i2node.find(in) == i2node.end()){
        return ;
    }
    for(int i=0;i<i2node[in].size();i++){
        int idx = i2node[in][i].idx;
        softwareCnt[idx]++;
        softwareCnt[idx] %= 142857;
        int cnt = i2node[in][i].cnt;
        for(int j=0;j<cnt;j++){
            process(i2node[in][i].rstat[j]);
        }
    }
}

int main(){
    int r1,r2,r3, in, rcnt;
    scanf("%d", &t);
    for(int i=0;i<t;i++){
        init();
        scanf("%d%d",&m,&n);
        for(int j=0;j<n;j++){
            scanf("%d",&initArr[j]);
        }
        
        for(int j=0;j<m;j++){
            scanf("%d%d",&in,&rcnt);
            if(rcnt == 0){
                i2node[in].push_back(sNode(j,0));
            }else if(rcnt == 1){
                scanf("%d",&r1);
                i2node[in].push_back(sNode(j, 1, r1));
            }else if(rcnt == 2){
                scanf("%d%d",&r1, &r2);
                i2node[in].push_back(sNode(j, 2, r1, r2));
            }else if(rcnt == 3){
                scanf("%d%d%d",&r1,&r2,&r3);
                i2node[in].push_back(sNode(j, 3, r1,r2,r3));
            }
        }
        
        for(int j=0;j<n;j++){
            process(initArr[j]);
        }
        
        printf("%d", softwareCnt[0]);
        for(int j=1;j<m;j++){
            printf(" %d",softwareCnt[j]);
        }
        printf("\n");
    }
    return 0;
}