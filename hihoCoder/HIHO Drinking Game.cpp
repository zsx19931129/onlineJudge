//找到最小符合条件的T，T可能取值范围是1~k+1，如果是k+1肯定能赢，测试符合条件与否的时间复杂度O(n)，用二分检索，判断
//从1到k范围内的符合条件的最小值，与普通二分检索的区别：如果符合条件，不会从区间中删除这个元素

#define MAXN 100000
#include <iostream>

using namespace std;

int n,k;
int nums[MAXN];

bool howins(int t){
    int wcnt = 0;
    int remain = 0;
    for(int i=0;i<n;i++){
        remain += t;
        if(remain>nums[i]){
            wcnt++;
            remain -= nums[i];
        }else{
            remain = 0;
        }
    }
    return wcnt > n-wcnt;
}

int binSearch(int l, int r){
    if(l == r){
        return l;
    }
    int mid = (l+r)/2;
    if(howins(mid)){
        return binSearch(l, mid);
    }else{
        return binSearch(mid+1,r);
    }
}

int main(){
    cin>>n>>k;
    for(int i=0;i<n;i++){
        cin>>nums[i];
    }
    //二分检索求最小解
    int res = binSearch(1, k+1);
    cout<<res<<endl;
    return 0;
}