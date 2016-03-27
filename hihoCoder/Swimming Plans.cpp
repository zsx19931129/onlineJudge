#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;



class event{
public:
    //开始时间
    int t;
    //选择的泳道
    int l;
    //一个调度对应的最晚开始时间或最早开始时间，用一个变量标识，初识为0经过最晚+1，
    //经过最早-1，如果=0表示这条泳道可用
    int x;
};

//处理一个调度，每个调度会产生4个事件，同向情况下两个，逆向情况下两个，每种情况的最早和最晚
void addEvent(vector<vector<event> > &eventSequence, int t, int l, int n, int d, const int sl, const int idx){
    int earlyidx = 2*idx;
    int lateidx = 2*idx + 1;
    //同向时，根据速度分类
    if(l==sl){
        // 最晚事件
        eventSequence[d][lateidx].t = t-1;
        eventSequence[d][lateidx].l = n;
        eventSequence[d][lateidx].x = 1;
        
        //最早事件
        eventSequence[d][earlyidx].t = t + 1;
        eventSequence[d][earlyidx].l = n;
        eventSequence[d][earlyidx].x = -1;
    }else if(l>sl){
        eventSequence[d][lateidx].t = t;
        eventSequence[d][lateidx].l = n;
        eventSequence[d][lateidx].x = 1;
        
        eventSequence[d][earlyidx].t = t + l - sl;
        eventSequence[d][earlyidx].l = n;
        eventSequence[d][earlyidx].x = -1;
    }else if(l<sl){
        eventSequence[d][lateidx].t = t - sl + l;
        eventSequence[d][lateidx].l = n;
        eventSequence[d][lateidx].x = 1;
        
        eventSequence[d][earlyidx].t = t;
        eventSequence[d][earlyidx].l = n;
        eventSequence[d][earlyidx].x = -1;
    }
    
    //逆向的事件
    eventSequence[1 - d][lateidx].t = t - sl;
    eventSequence[1 - d][lateidx].l = n;
    eventSequence[1 - d][lateidx].x = 1;
    
    eventSequence[1 - d][earlyidx].t = t + l;
    eventSequence[1 - d][earlyidx].l = n;
    eventSequence[1 - d][earlyidx].x = -1;
}

bool cmp(const event &a, const event &b){
    // if(a.t < b.t){
    // 	return true;
    // }else if(a.t == b.t){
    // 	if(a.x == -1){
    // 		return true;
    // 	}
    // }
    return (a.t<b.t) or (a.t == b.t && a.x == -1);
}


void sortEvent(vector<vector<event> > &eventSequence){
    int size1 = eventSequence.size();
    int size2 = eventSequence[0].size();
    
    for(int i=0;i<size1;i++){
        sort(eventSequence[i].begin(), eventSequence[i].end(), cmp);
    }
}


int main(){
    int tasks;
    cin>>tasks;
    for(int i=0;i<tasks;i++){
        int st,sl,sr,nLanes,qplans;
        cin>>st>>sl>>sr>>nLanes>>qplans;
        
        // 两个方向已处理过的事件数量
        int offset[2] = {0};
        // steven当前的方向
        int direction = 0;
        int curTime = st;
        // 记录每条泳道的标记方便快速判断可用性
        vector<vector<int> > laneFree(2, vector<int>(nLanes, 0));
        
        
        //记录所有的事件，两个方向，二维最大值与qplans的数目有关
        //利用stl动态创建二维数组
        vector<vector<event> > eventSequence(2, vector<event>(2*qplans));   //stl中预分配二维
        //vector<vector<event> > eventSequence(2);
        
        // 处理输入，qplans个其他调度
        for(int j=0;j<qplans;j++){
            int qt,ql,qn,qd;
            cin>>qt>>ql>>qn>>qd;
            addEvent(eventSequence, qt,ql,qn,qd, sl, j);
        }
        
        // 按时序排序事件
        sortEvent(eventSequence);
        
        while(sr){
            bool found = false;
            while(offset[direction]<2*qplans){
                // 获取当前事件向量
                event curEvent = eventSequence[direction][offset[direction]];
                if(curEvent.t < curTime){
                    //当前时间已经经过这个事件
                    laneFree[direction][curEvent.l] += curEvent.x;
                    //处理完这个事件
                    offset[direction]++;
                }else{
                    // 当前时间没有到达任何事件向量
                    for(int k = 0;k<nLanes;k++){
                        if(laneFree[direction][k] == 0){
                            found = true;
                            // 使用泳道
                            curTime += sl;
                            break;
                        }
                    }
                    if(found){
                        //保持当前的事件
                        break;
                    }
                    //此时表示在0~curEvent.t中没有可用的泳道
                    curTime = curEvent.t;
                    laneFree[direction][curEvent.l] += curEvent.x;
                    offset[direction]++;
                }
            }
            // 表明该方向的事件已经处理完，此时只有steven一个人
            if(!found){
                curTime += sl;
            }
            direction = 1 - direction;
            sr--;
        }
        cout<<curTime<<endl;
    }
    
}