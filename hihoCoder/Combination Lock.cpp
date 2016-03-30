#include <iostream>
#include <string>
#include <cstdio>

using namespace std;

int main(){
    int n,m;
    cin>>n>>m;
    string str;
    cin>>str;
    //使得下标从1开始
    str = " " + str;
    for(int i=0;i<m;i++){
        int cmdType;
        string nouse;
        cin>>nouse>>cmdType;
        int l,r,k;
        switch(cmdType){
            case 1:
            {
                char X;
                cin>>l>>r>>X;
                for(int i=l;i<=r;i++){
                    str[i] = X;
                }
                break;
            }
            case 2:
            {
                cin>>l>>r>>k;
                k %= 26;
                for(int j=l;j<=r;j++){
                    int tmp = ((str[j]-'A') + k)%26 + 'A';
                    str[j] = tmp;
                }
                break;
            }
                
            case 3:
            {
                cin>>k;
                string subl = str.substr(1, k);
                string subr = str.substr(k+1, n-k);
                str = " " + subr + subl;
                break;
            }
                
            case 4:
            {
                cin>>l>>r;
                int add = 1;
                for(int j=l;j<=r;j++){
                    int tmp = (str[j]-'A' + add)%26 + 'A';
                    str[j] = tmp;
                    add++;
                    if(add == 26){
                        add = 0;
                    }
                }
                break;
            }
        }
    }
    str = str.substr(1, n);
    cout<<str<<endl;
    return 0;
}