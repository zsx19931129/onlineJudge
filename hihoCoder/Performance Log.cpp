//一份记录是否错误，包含：
// 1 记录的时间必须严格递增
// 2 一个函数的结束时间不能比启动时间更早
// 3 函数的start和end不对应
// 4 函数不能出现交叉的情况

#include <iostream>
#include <string>
#include <queue>
#include <stack>
#include <map>
#include <sstream>

using namespace std;

class funcNode{
public:
    string start;
    string end;
    funcNode(string str1 = "", string str2 = "")
    :start(str1), end(str2){}
};

inline int getNumFromTime(const int h, const int m, const int s){
    return h*3600 + m*60 + s;
}

string getDuration(string start, string end){
    int t[3] = {0};
    start[2] = start[5] = ' ';
    end[2] = end[5] = ' ';
    
    istringstream iss(start);
    iss>>t[0]>>t[1]>>t[2];
    int beginNum = getNumFromTime(t[0],t[1],t[2]);
    iss.clear();
    iss.str(end);
    iss>>t[0]>>t[1]>>t[2];
    int endNum = getNumFromTime(t[0],t[1],t[2]);
    
    int dtime = endNum - beginNum;
    
    t[0] = dtime/3600;
    //t[1] = (dtime/60)%60;
    t[1] = (dtime%3600)/60;
    t[2] = dtime%60;
    
    ostringstream oss;
    if(t[0]<=9){
        oss<<"0";
    }
    oss<<t[0];
    for(int i=1;i<=2;i++){
        oss<<":";
        if(t[i]<=9){
            oss<<"0";
        }
        oss<<t[i];
    }
    string res = oss.str();
    return res;
}

int main(){
    int n;
    cin>>n;
    string funcName, timestamp, cmd;
    
    // 标识dfs顺序
    queue<string> flist;
    //判断是否合理
    stack<string> fstack;
    // 用于快速索引
    map<string, funcNode> fmap;
    
    //标识是否合法
    bool legal = true;
    //标识是否合法
    string curTimeStamp="";
    for(int i=0;i<n;i++){
        cin>>funcName>>timestamp>>cmd;
        if(!legal){
            continue;
        }
        // 判断时间是否合法
        if(timestamp < curTimeStamp){
            legal = false;
            continue;
        }else{
            curTimeStamp = timestamp;
        }
        if(cmd == "START"){
            // 入栈、入队
            fstack.push(funcName);
            flist.push(funcName);
            fmap[funcName] = funcNode(timestamp);
        }else if(cmd == "END"){
            if(fstack.empty()){
                legal = false;
                continue;
            }
            string tmp = fstack.top();
            if(funcName != tmp){
                legal = false;
                continue;
            }
            fstack.pop();
            if(fmap[funcName].start > timestamp){
                legal = false;
                continue;
            }
            fmap[funcName].end = timestamp;
        }
    }
    
    if(!fstack.empty()){
        legal = false;
    }
    if(!legal){
        cout<<"Incorrect performance log"<<endl;
    }else{
        while(!flist.empty()){
            string tmp = flist.front();
            flist.pop();
            string duration = getDuration(fmap[tmp].start, fmap[tmp].end);
            cout<<tmp<<" "<<duration<<endl;
        }
    }
    return 0;
}