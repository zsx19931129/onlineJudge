#include <iostream>
#include <string>
#include <vector>

#define getIndex(str,i) str[i-1]

using namespace std;

//如果用这个函数会TLE
//char& getIndex(string str, int i){
//    return str[i-1];
//}

// 引用避免参数赋值，利用kmp思想加速next向量的求解
// baba | b
// baba
// baba | b
//   ba | b
void generateNextVect(string par, vector<int> &nextVect){
    nextVect[0] = -1;
    nextVect[1] = 0;
    int slen = par.length();
    for(int i=2; i<=slen; i++){
        // k表示匹配过程中横线前最后一位
        int k = i-1;
        bool flag = false;
        while(k>=0){
            //cout<<"in while"<<endl;
            k = nextVect[k];
            if(getIndex(par, k+1) == getIndex(par, i)){
                nextVect[i] = k + 1;
                flag = true;
                break;
            }
        }
        //此时说明横线前无匹配字符
        if(!flag)
            nextVect[i] = 0;
    }
}

// kmp算法实现 ori 源串， par 模式串
int kmp(string ori, string par){
    
    int res = 0;
    int slen = ori.length();
    int plen = par.length();
    // next数组下标从1开始
    vector<int> nextVect(plen + 1, -1);
    generateNextVect(par, nextVect);
    //parOff表示已经匹配的单词索引
    int parOff = 0;
    for(int i=0;i<slen;i++){
        char orich = ori[i];
        //char parch = par[parOff+1];
        char parch = getIndex(par, parOff+1);
        if(orich == parch){
            parOff++;
            if(parOff == plen){
                res++;
                //parOff=0;
                parOff = nextVect[parOff];
            }
        }else{
            //说明匹配失败，需要回溯
            while(parOff>0){
                parOff = nextVect[parOff];
                //parch = par[parOff+1];
                parch = getIndex(par, parOff+1);
                if(orich == parch){
                    //如果发生回溯一定不会有匹配
                    parOff++;
                    break;
                }
            }
        }
    }
    return res;
}

int main(){
    int n;
    cin>>n;
    for(int i=0;i<n;i++){
        string ori, par;
        cin>>par>>ori;
        int cnt = kmp(ori, par);
        cout<<cnt<<endl;
    }
    return 0;
}