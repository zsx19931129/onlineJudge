// 序列出现的顺序不确定，所以统一排序比较

#include <iostream>
#include <algorithm>
#include <string>
#include <cmath>
using namespace std;

int main(){
    int seq[3];
    cin>>seq[0]>>seq[1]>>seq[2];
    sort(seq, seq + 3);
    string str;
    cin>>str;
    int slen = str.length();
    int cr = 0, cy = 0, cb = 0;
    int curCnt = 0;
    int res = 0;
    int sub[3] = {0};
    for(int i=0;i<slen;i++){
        curCnt++;
        if(curCnt>res){
            res = curCnt;
        }
        if(str[i] == 'R'){
            cr++;
        }else if(str[i] == 'Y'){
            cy++;
        }else if(str[i] == 'B'){
            cb++;
        }
        sub[0] = abs(cr - cy);
        sub[1] = abs(cy - cb);
        sub[2] = abs(cb - cr);
        sort(sub, sub+3);
        bool fit = true;
        for(int j=0;j<3;j++){
            if(seq[j] != sub[j]){
                fit = false;
                break;
            }
        }
        if(fit){
            cr = cy = cb = 0;
            curCnt = 0;
        }
    }
    cout<<res<<endl;
    return 0;
}