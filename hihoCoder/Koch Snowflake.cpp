// 雪花产生的一个性质，新产生的分支会把之前的每一条边一分为2，新产生的两个边在中间，每一条边新产生后都变成四条边
// 所以编号mod 4， 余2或3的话，就是新产生的边，否则除以4，根据mod4是否余0找到在上一层的编号，直到mod4 余 2 3为止
// 或者当前层到了0，返回0

#include <iostream>

using namespace std;

int main(){
    int t;
    cin>>t;
    int tmp;
    for(int i=0;i<t;i++){
        int idx,n;
        cin>>idx>>n;
        tmp = idx;
        bool find = false;
        while(n){
            int remain = tmp%4;
            if(remain == 2 || remain == 3){
                find = true;
                cout<<n<<endl;
                break;
            }else{
                tmp = tmp/4;
                if(remain != 0){
                    tmp++;
                }
            }
            n--;
        }
        if(!find){
            cout<<"0"<<endl;
        }
    }
    return 0;
}