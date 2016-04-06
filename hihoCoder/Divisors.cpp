// 利用了质因数分解求解因子个数的公式
// 最优解的两个性质，1.较大的质因数的次数一定小于较小质因数的次数。2.质因数最多到41，1到41的质因数
// 乘积大于10^16。

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

vector<int> primTbl;
unsigned long long int n;
unsigned long long int maxCnt = 0;
unsigned long long int res = 1;
const unsigned long long int MAXN = pow(10, 16);

bool isPrim(int n){
    for(int i=2;i<=sqrt(n);i++){
        if(n%i == 0){
            return false;
        }
    }
    return true;
}

void genPrimTbl(){
    for(int i=2;i<=41;i++){
        if(isPrim(i)){
            primTbl.push_back(i);
        }
    }
}

//参数分别表示质因数在向量里的下标，当前的数，当前的因子个数，上一个质因数的次数
void dfs(int primIdx, unsigned long long int curNum, unsigned long long int cnt, int lastNi){
    if(primIdx >= primTbl.size()){
        return ;
    }
    if( (cnt > maxCnt) || (cnt == maxCnt) && (curNum < res) ){
        maxCnt = cnt;
        res = curNum;
    }
    
    int i=1;
    while( (curNum * pow(primTbl[primIdx], i) < n) && (i <= lastNi) ){
        dfs(primIdx+1, curNum*pow(primTbl[primIdx], i), cnt*(i+1), i);
        i++;
    }
}

int main(){
    genPrimTbl();
    cin>>n;
    dfs(0, 1, 1, 64);
    cout<<res<<endl;
}