// 用二叉树模拟状态

#define INFINATE 0x3fffffff
#define MAXN 100005
#include <iostream>
#include <string>
#include <cstdio>
#include <sstream>

using namespace std;

struct node{
    node * left;
    node * right;
    int timeStamp;
    int stat;           //0 没有被赋值，1，被允许，2，被拒绝
    node(){
        timeStamp = INFINATE;
        stat = 0;
        left = right = NULL;
    }
};

struct myTree{
    node* root;
    myTree(){
        root = new node();
    }
};

int n,m;

myTree bsTree;

void updateBSTree(int numIdx, int state, int mytime, int mask = 32){
    //从根节点开始
    node * cur = bsTree.root;
    
    for(int i=1;i<=mask;i++){
        int tmp = 1;
        int leftcnt = 32 - i;
        tmp = tmp << leftcnt;
        if(numIdx & tmp){
            node * tmp = cur;
            cur = cur->left;
            if(!cur){
                tmp->left = new node();
                cur = tmp->left;
            }
        }else{
            node * tmp = cur;
            cur = cur->right;
            if(!cur){
                tmp->right = new node();
                cur = tmp->right;
            }
        }
    }
    
    cur->stat = state;
    cur->timeStamp = mytime;
    
}

bool queryBSTree(int finalIdx){
    node * cur = bsTree.root;
    int curState = 0;
    int curTimeStamp = INFINATE;
    for(int i=31;i>=0;i--){
        int mask = 1<<i;
        if(finalIdx & mask){
            cur = cur->left;
        }else{
            cur = cur->right;
        }
        if(!cur){
            break;
        }else{
            if(cur->stat != 0){
                if(cur->timeStamp < curTimeStamp){
                    curState = cur->stat;
                    curTimeStamp = cur->timeStamp;
                }
            }else{
                continue ;
            }
        }
    }
    return curState == 1;
}

int main(){
    cin>>n>>m;
    string str, cmd;
    for(int i = 0;i<n;i++){
        cin>>cmd;
        cin>>str;
        
        int off = 0;
        int num[4]={0};
        int mask = -1;
        int state = 0;
        int finalIdx = 0xffffffff;
        
        if(cmd == "allow"){
            state = 1;
        }else if(cmd == "deny"){
            state = 2;
        }
        
        for(int j=0;j<3;j++){
            int idx = str.find('.', off);
            string msub = str.substr(off, idx-off);     //不包括点
            stringstream ss;
            ss<<msub;
            ss>>num[j];
            off = idx + 1;
        }
        
        if(str.find('/', off)!=-1){
            int idx = str.find('/', off);
            string msub = str.substr(off, idx-off);
            stringstream ss;
            ss<<msub;
            ss>>num[3];
            off = idx + 1;
            msub = str.substr(off);
            stringstream ss2;
            ss2<<msub;
            ss2>>mask;
        }else{
            string msub = str.substr(off);
            stringstream ss;
            ss<<msub;
            ss>>num[3];
        }
        
        if(mask!=-1){
            if(mask == 0){
                continue;
            }
            int maskFlag = (finalIdx << (32-mask));
            int combine = (num[0]<<24 | num[1]<<16 | num[2]<<16 | num[3]);
            finalIdx = maskFlag & combine;
            updateBSTree(finalIdx, state, i, mask);
        }else{
            finalIdx = (num[0]<<24 | num[1]<<16 | num[2]<<16 | num[3]);
            updateBSTree(finalIdx, state, i);
        }
    }
    
    for(int i=0;i<m;i++){
        cin>>str;
        
        int num[4] = {0};
        int off = 0;
        for(int j=0;j<3;j++){
            int idx = str.find('.', off);
            string msub = str.substr(off, idx-off);     //不包括点
            stringstream ss;
            ss<<msub;
            ss>>num[j];
            off = idx + 1;
        }
        
        string tmp = str.substr(off);
        stringstream ss2;
        ss2<<tmp;
        ss2>>num[3];
        int finalIdx = (num[0]<<24 | num[1]<<16 | num[2]<<16 | num[3]);
        if(queryBSTree(finalIdx)){
            cout<<"YES"<<endl;
        }else{
            cout<<"NO"<<endl;
        }
    }
    
    return 0;
}