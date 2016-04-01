// 找到规律，子Panel的宽度减去自身宽度越大，越靠上
// 先构造树形结构，然后深度优先搜索，根据子树的宽度从左到右排序

#define MAXN 1000

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class row{
public:
    int rowId;				//行id，需要用这个id区索引panel，因为所有panel都是由id引出
    int expandLength;		//这个行的扩展宽度
    row():rowId(-1),expandLength(0){}
    row(int id):rowId(id),expandLength(0){}
};

class section{
public:
    vector<row> rows;		//这个section包含的所有列
    int selfLength;			//这个section自身的长度
    int expandLength;		//展开子菜单之后的最优长度sr1
    int delta;				//子菜单之后的长度与自身的差值
    section():selfLength(0),expandLength(0),delta(0){}
};

class panel{
public:
    vector<section> sections;	//这个panel包含的所有panel的情况
    vector<int> rowIds;			//读入该panel内的rowId，用于辅助构建panel
};

panel myPanels[MAXN];

void makePanel(panel &p){
    if(p.rowIds.size() == 0){
        //说明没有子菜单，子panel为空
        return ;
    }
    
    p.sections.push_back(section());					//新建一个section，至少一个
    int sectionId = 0;
    
    //构造出这个panel所有的sections，每个section包含所有的row
    for(int i=0;i != p.rowIds.size();i++){
        if(p.rowIds[i]==0){
            p.sections.push_back(section());
            sectionId++;
        }else{
            p.sections[sectionId].rows.push_back(row(p.rowIds[i]));
        }
    }
}

bool sortByExpandLength(const row &x, const row &y){
    return x.expandLength > y.expandLength;
}

bool sortByDelta(const section &a, const section &b){
    return a.delta > b.delta;
}

//深度优先搜索得到这个rowId对应的panel的扩展长度
int dfs(panel &p){
    //首先得到所有section的最优解，然后再根据delta重新调整，得到这个panel的最优解，返回ret
    
    //ret表示该panel的最小展开长度
    int ret = 0;
    
    for(int i=0;i<p.sections.size();i++){
        for(int j=0;j<p.sections[i].rows.size();j++){
            //求出section中每个row的扩展长度
            p.sections[i].rows[j].expandLength = dfs(myPanels[p.sections[i].rows[j].rowId]);
        }
        sort(p.sections[i].rows.begin(), p.sections[i].rows.end(), sortByExpandLength);
        
        int low = 0;
        for(int j=0;j != p.sections[i].rows.size();j++){
            if(j + p.sections[i].rows[j].expandLength > low){
                //不需要-1，因为j从0开始
                low = j + p.sections[i].rows[j].expandLength;
            }
        }
        
        p.sections[i].expandLength = low;
        p.sections[i].selfLength = p.sections[i].rows.size();
        p.sections[i].delta = p.sections[i].expandLength - p.sections[i].selfLength;
        
        //返回的高度至少是区间的高度
        ret += p.sections[i].selfLength;
    }
    
    sort(p.sections.begin(), p.sections.end(), sortByDelta);
    
    //section之间有跨度
    int curLine = 0;
    for(int i=0;i<p.sections.size();i++){
        if(ret < curLine + p.sections[i].expandLength){
            ret = curLine + p.sections[i].expandLength;
        }
        curLine += p.sections[i].selfLength;
    }
    
    return ret;
}

int main(){
    int n, numOfChilds, id;
    cin>>n;
    //总共n+1行
    for(int i=0;i<=n;i++){
        cin>>numOfChilds;
        while(numOfChilds--){
            cin>>id;
            if(id == 0){
                //如果是0，表示边界，不计入总数，补偿1
                numOfChilds++;
            }
            myPanels[i].rowIds.push_back(id);
        }
        makePanel(myPanels[i]);
    }
    cout<<dfs(myPanels[0])<<endl;
    return 0;
}