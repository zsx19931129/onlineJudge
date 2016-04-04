// 找到一个贪心的性质，按照半径从小到大排序，当遇到不符合条件的情况，分割区间，然后遇到放不进去盘子
// 的情况就停止（会悬空卡在箱子上的情况），如1,2,4,5,6,8,9间隔为1的情况，可以8945612。

#define MAXN 100001
#include <algorithm>
#include <iostream>

using namespace std;

int disks[MAXN];

int main(){
    int n,m,h,r;
    cin>>n>>m>>h>>r;
    for(int i=0;i<n;i++){
        cin>>disks[i];
    }
    sort(disks, disks + n);
    //开始构造模拟
    int ans = 0;
    int s=0;
    if(disks[0]<=r){
        s = 1;
        for(int i=1;i<n;i++){
            if(disks[i] > r + s){
                ans += s;
                break;
            }
            if(disks[i]-disks[i-1] > m){
                ans += s;
                s = 0;
                if(disks[i]>r){
                    //这时候需要检查能不能放入
                    break;
                }
            }
            s++;
            if(i == n-1){
                ans += s;
            }
        }
    }
    
    if(ans > h){
        ans = h;
    }
    cout<<ans<<endl;
    return 0;
}