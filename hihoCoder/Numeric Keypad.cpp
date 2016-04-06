// 注意一个规律，限制永远是越来越多，所以只用考虑是不是符合上一位就可以
#define MAXBIT 505
#include <string>
#include <iostream>
#include <cstring>

using namespace std;

int numCoord[10][2] = { {3,1}, {0,0}, {0,1}, {0,2}, {1,0}, {1,1}, {1,2},
    {2,0}, {2,1}, {2,2} } ;

bool numConfirm[10][10];	//判定每个数字是否能够转移
string str;					//每组测试数据对应的字符串
int slen;					//当前字符串长度
int res[MAXBIT];			//存储最后的结果

void genNumConfirm(){
    for(int i=0;i<10;i++){
        for(int j=0;j<10;j++){
            if(numCoord[i][0] <= numCoord[j][0] && numCoord[i][1] <= numCoord[j][1]){
                numConfirm[i][j] = true;
            }else{
                numConfirm[i][j] = false;
            }
        }
    }
}

void init(){
    cin>>str;
    slen = str.length();
    memset(res, 0, sizeof(res));
}

void output(){
    for(int i=0;i<slen;i++){
        cout<<res[i];
    }
    cout<<endl;
}

// 找到第一个符合结果的就是最优解，然后返回
bool dfs(int cur, int last, bool below){
    if(cur >= slen){
        output();
        return true;
    }
    if(below){
        // 将之后的数字全部填充为当前能够到达的最大数字
        int num;
        for(int i=9;i>=0;i--){
            if(numConfirm[last][i]){
                num = i;
                break;
            }
        }
        for(int i=cur;i<slen;i++){
            res[i] = num;
        }
        output();
        return true;
    }
    int curNum = str[cur] - '0';
    for(int i=9;i>=0;i--){
        if(i <= curNum && numConfirm[last][i]){
            res[cur] = i;
            if(dfs(cur+1, i, i<curNum)){
                return true;
            }
        }
    }
    return false;
}

int main(){
    genNumConfirm();
    int t;
    cin>>t;
    while(t--){
        init();
        int cur = 0;
        bool below = false;			//标识是否有高位已经存在低于初始对应数位的情况，比如 300，299，2之后可以取任意数字
        dfs(cur, 1, below);
    }
    return 0;
}