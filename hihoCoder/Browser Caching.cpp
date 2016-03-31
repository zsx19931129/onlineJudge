// 构建minheap数据结构(数组实现)，节点的值包括string(作为这个节点的id)，访问数值(越大代表越近访问)
// 为了快速找到一个网址在minheap中的位置，可以用map来存储每个节点在minheap中的索引

#define MAXM 5005
#define MAXN 20001

#include <iostream>
#include <map>

using namespace std;

map<string, int> netMap;		//位置快速索引

class heapNode{
public:
    string id;
    int ts;			//本题中决定了ts不可能相等
    heapNode():ts(0){}
    void update(string newid, int newts){
        id = newid;
        ts = newts;
    }
    void update(int newts){
        ts = newts;
    }
};

class minHeap{
public:
    int size;					//当前堆的元素个数
    int max;					//堆的最大容量
    heapNode buf[MAXM];			//用数组实现最小堆
    minHeap():size(0), max(0){}
    void swapNode(int nidx1, int nidx2){
        string stmp = buf[nidx1].id;
        buf[nidx1].id = buf[nidx2].id;
        buf[nidx2].id = stmp;
        
        int ttmp = buf[nidx1].ts;
        buf[nidx1].ts = buf[nidx2].ts;
        buf[nidx2].ts = ttmp;
    }
    void shifDown(int curIdx){
        //只要调用shiftDown就一定到最底
        int tmp = curIdx;
        int lch = 2*curIdx+1 < size ? 2*curIdx+1 : -1;
        int rch = 2*curIdx+2 < size ? 2*curIdx+2 : -1;
        while(lch != -1 || rch != -1){
            //找到两个儿子节点中较小的一个
            int cmin = MAXN;
            bool left = true;
            if(lch != -1){
                cmin = buf[lch].ts < cmin ? buf[lch].ts : cmin;
            }
            if(rch != -1){
                //cmin = buf[rch].ts < cmin ? buf[rch].ts : cmin;
                //left = false;
                if(buf[rch].ts < cmin){
                	cmin = buf[rch].ts;
                	left = false;
                }
            }
            if(left){
                netMap[buf[tmp].id] = lch;
                netMap[buf[lch].id] = tmp;
                swapNode(tmp, lch);
                tmp = lch;
            }else{
                netMap[buf[tmp].id] = rch;
                netMap[buf[rch].id] = tmp;
                swapNode(tmp, rch);
                tmp = rch;
            }
            lch = 2*tmp+1 < size ? 2*tmp+1 : -1;
            rch = 2*tmp+2 < size ? 2*tmp+2 : -1;
        }
    }
};

minHeap myHeap;					//最小堆

int main(){
    int n,m;
    cin>>n>>m;
    myHeap.max = m;
    string netstr;
    map<string, int>::iterator iter;
    
    for(int i=0;i<n;i++){
        cin>>netstr;
        if(netMap.find(netstr) != netMap.end()){
            // 命中，不需要删除添加元素
            cout<<"Cache"<<endl;
            int curIdx = netMap[netstr];
            myHeap.buf[curIdx].update(i);
            myHeap.shifDown(curIdx);
        }else{
            // miss，需要添加元素
            cout<<"Internet"<<endl;
            if(myHeap.size == myHeap.max){
                //当heap满时，需要出堆最顶元素（直接赋值），同时从map中去掉索引，添加新索引
                //同时新添加元素从根shiftDown
                
                iter = netMap.find(myHeap.buf[0].id);
                netMap.erase(iter);
                
                myHeap.buf[0].update(netstr, i);
                
                netMap[netstr] = 0;
                
                myHeap.shifDown(0);
            }else{
                //新添加的元素一定可以放在最后
                myHeap.buf[myHeap.size].update(netstr, i);
                netMap[netstr] = myHeap.size;
                myHeap.size++;
            }
        }
    }
    return 0;
}