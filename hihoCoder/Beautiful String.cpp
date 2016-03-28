#include <cstdio>
#include <cstring>
#include <iostream>

#define STRINGLEN 10000005

using namespace std;

char strbuf[STRINGLEN];
enum status{step1=0,step2, step3};

inline void
updateStatus(status &curState, int *charCnt, char &curChar,
             const status newState, const int c1, const int c2, const int c3,
             const char newChar){
    curState = newState;
    curChar = newChar;
    *(charCnt+0) = c1;
    *(charCnt+1) = c2;
    *(charCnt+2) = c3;
}

bool detectPattern(int len){
    status curState = step1;
    char curChar = strbuf[0];
    int charCnt[3] = {1};
    for(int i=1;i<len;i++){
        char ch = strbuf[i];
        switch(curState){
            case step1:
                if(ch == curChar){
                    charCnt[0]++;
                }else if(ch == (curChar + 1)){
                    //读到第二个连续字符，更新状态
                    updateStatus(curState, charCnt, curChar, step2, charCnt[0], 1, 0, ch);
                }else{
                    //其他情况，还在step1，重新初始化状态
                    updateStatus(curState, charCnt, curChar, step1, 1, 0, 0, ch);
                }
                break;
            case step2:
                if(ch == curChar){
                    charCnt[1]++;
                    if(charCnt[1]>charCnt[0]){
                        //超过了第一个字符的个数，以当前字符作为step1
                        updateStatus(curState, charCnt, curChar, step1, charCnt[1], 0, 0, ch);
                    }
                }else if(ch == (curChar + 1)){
                    //读到第三个连续字符
                    updateStatus(curState, charCnt, curChar, step3, charCnt[0],charCnt[1], 1, ch);
                }else{
                    //其他字符，回到step1
                    updateStatus(curState, charCnt, curChar, step1, 1, 0, 0, ch);
                }
                break;
            case step3:
                if(ch == curChar){
                    charCnt[2]++;
                    if(charCnt[2] >= charCnt[1]){
                        return true;
                    }
                }else{
                    if(charCnt[2] >= charCnt[1]){
                        return true;
                    }else{
                        if(ch == (curChar + 1)){
                            updateStatus(curState, charCnt, curChar, step3, charCnt[1], charCnt[2], 1, ch);
                        }else{
                            updateStatus(curState, charCnt, curChar, step1, 1, 0, 0, ch);
                        }
                    }
                }
                break;
        }
    }
    if( curState == step3 && charCnt[1] <= charCnt[2])
        return true;
    return false;
}

int main(){
    int n;
    cin>>n;
    int len;
    for(int i=0;i<n;i++){
        cin>>len;
        scanf("%s", strbuf);
        if(detectPattern(len)){
            cout<<"YES"<<endl;
        }else{
            cout<<"NO"<<endl;
        }
    }
}