#include <iostream>
#include <string>
#include <stack>
using namespace std;

// colorTag 1 yellow 2 blue 3 red 0 normal

int main(){
    char cstr[1001]={0};
    cin.getline(cstr, 1000);
    stack<int> mystk;
    mystk.push(0);
    int rcnt=0, ycnt=0, bcnt=0;
    string str(cstr);
    int slen = str.length();
    int off=0;
    while(off<slen){
        char ch = str[off];
        if(ch == '<'){
            //颜色标签
            if(str[off + 1] == '/'){
                //是闭标签
                int idx = str.find('>', off);
                mystk.pop();
                off = idx + 1;
            }else{
                //是开标签
                int idx = str.find('>', off);
                string stmp = str.substr(off, idx + 1 - off);
                off = idx + 1;
                if(stmp == "<yellow>"){
                    mystk.push(1);
                }else if(stmp == "<blue>"){
                    mystk.push(2);
                }else if(stmp == "<red>"){
                    mystk.push(3);
                }
            }
        }else{
            if(ch == ' '){
                off++;
                continue;
            }
            int color = mystk.top();
            if(color == 1){
                ycnt++;
            }else if(color == 2){
                bcnt++;
            }else if(color == 3){
                rcnt++;
            }
            off++;
        }
    }
    cout<<rcnt<<" "<<ycnt<<" "<<bcnt<<endl;
    return 0;
}