#define MAXN 101
#include <set>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

int fibonacci[13];

void genFibonacci(){
    fibonacci[0] = 0;
    fibonacci[1] = fibonacci[2] = 1;
    for(int i=2;i<13;i++){
        fibonacci[i] = fibonacci[i-1] + fibonacci[i-2];
    }
}

bool setCmp(string s1, string s2){
    return s1 < s2;
}

int main(){
    bool (*fpt)(string,string) = setCmp;
    set<string, bool (*)(string,string)> mset(fpt);
    genFibonacci();
    string str;
    cin>>str;
    int slen = str.length();
    for(int i=0;i<slen;i++){
        for(int j=i;j<slen;j++){
            int cntArr[26]={0};
            for(int k = i;k <= j;k++){
                cntArr[str[k] - 'a']++;
            }
            
            sort(cntArr, cntArr + 26);
            int k=0;
            for(;cntArr[k] == 0;k++)
                ;
            int diffNum = 26 - k;
            for(int off = 1;off<13;off++){
                if(fibonacci[off] == diffNum){
                    mset.insert(str.substr(i, j-i+1));
                }
            }
        }
    }
    set<string>::iterator it;
    for(it = mset.begin();it != mset.end();it++){
        cout<<*it<<endl;
    }
}