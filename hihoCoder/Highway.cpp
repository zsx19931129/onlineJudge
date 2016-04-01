// 智商碾压.....需要充分利用条件，后一辆车不能通过前一辆车，将一个区间划分成x[i],x[j],....y[j],y[i]
// 仔细考虑x[i],x[j],....y[i],y[j]的情况
#define MAXN 1001

#define max(x,y) ({				\
typeof(x) _x = (x);			\
typeof(y) _y = (y);			\
(void) (&_x == &_y);		\
_x > _y ? _x : _y;			\
})

#include <iostream>
#include <algorithm>
#include <iomanip>

using namespace std;

int x[MAXN],y[MAXN],v[MAXN];
int p[MAXN],r[MAXN];
//ans按顺序存储离开时间,t存储最晚离开时间，索引与p数组对应
float ans[MAXN],t[MAXN];

bool comp(const int a, const int b){
    return x[a] > x[b];
}

int main(){
    int n;
    cin>>n;
    int a,b,c;
    for(int i=0;i<n;i++){
        cin>>x[i]>>y[i]>>v[i];
        p[i] = y[i];
        r[i] = i;
    }
    //按x[i]从大到小排序
    sort(r,r+n,comp);
    //按y[i]从小到大排序，方便遍历x[i],y[i]之间所有的y[j]，x[j]如果在x[i]后面，会被更新
    sort(p,p+n);
    
    for(int i=0;i<n;i++){
        //这个循环计算ans[idx]
        float curt = 0.0f;
        int idx = r[i];
        int curLoc = x[idx];
        for(int j=0;j<n;j++){
            if(p[j]>curLoc){
                curt += (float)(p[j] - curLoc)/v[idx];
                curLoc = p[j];
                curt = max(curt, t[j]);
                //不论r[j]在r[i]前或后都对
                t[j] = curt;
                if(p[j] == y[idx]){
                    ans[idx] = t[j];
                    break;
                }
            }
        }
    }
    cout<<fixed<<setprecision(2);
    
    for(int i=0;i<n;i++){
        
        cout<<ans[i]<<endl;
    }
    
    return 0;
}