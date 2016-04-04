// 因为星星比较少，所以一个星座用20个xy坐标和长度宽度，即可表示，比较时，与夜空中的5000颗星依次比较
// 一旦找到就break，每一次不符合就break。最多需要5000*20*20次比较
// stars均按照从左到右，从上到下排列

#define MAXSTARCON 20
#define MAXSTARSKY 5000
#define MAXSKYLEN 1001
#include <iostream>

using namespace std;

class constellation{
public:
    int w,h;
    int stars[MAXSTARCON][2];
    int scnt;
};

class sky{
public:
    int w,h;
    int stars[MAXSTARSKY][2];
    bool skymap[MAXSKYLEN][MAXSKYLEN];
    int scnt;
};

constellation mycons[MAXSTARCON];
sky mysky;
int k;

inline bool inSky(int x, int y){
    return (x>=0 && x<mysky.h) && (y>=0 && y<mysky.w);
}

void inputCons(){
    //读入星座
    cin>>k;
    string str;
    for(int i=0;i<k;i++){
        int coff = 0;
        int th,tw;
        cin>>th>>tw;
        mycons[i].h = th;
        mycons[i].w = tw;
        for(int j=0;j<th;j++){
            cin>>str;
            for(int k=0;k<str.length();k++){
                if(str[k] == '#'){
                    mycons[i].stars[coff][0] = j;
                    mycons[i].stars[coff][1] = k;
                    coff++;
                }
            }
        }
        mycons[i].scnt = coff;
    }
}

void inputSky(){
    //读入夜空
    string str;
    int soff = 0;
    int sh,sw;
    cin>>sh>>sw;
    mysky.h = sh;
    mysky.w = sw;
    for(int i=0;i<sh;i++){
        cin>>str;
        for(int j=0;j<sw;j++){
            if(str[j] == '#'){
                mysky.skymap[i][j] = true;
                mysky.stars[soff][0] = i;
                mysky.stars[soff][1] = j;
                soff++;
            }else{
                mysky.skymap[i][j] = false;
            }
        }
    }
    mysky.scnt = soff;
}

void findCons(){
    for(int i=0;i<k;i++){
        bool find = false;
        for(int j=0;j<mysky.scnt;j++){
            int offsetx = mysky.stars[j][0] - mycons[i].stars[0][0];
            int offsety = mysky.stars[j][1] - mycons[i].stars[0][1];
            int fitcnt = 0;
            bool conflict = false;
            for(int li = 0;li<mycons[i].h;li++){
                for(int lj = 0;lj<mycons[i].w;lj++){
                    int newx = li + offsetx;
                    int newy = lj + offsety;
                    if(!inSky(newx, newy)){
                        //超出边界
                        //conflict = true;
                        //break;
                        continue;
                    }else{
                        if(mysky.skymap[newx][newy]){
                            //有星星
                            if(mycons[i].stars[fitcnt][0] == li && mycons[i].stars[fitcnt][1] == lj){
                                fitcnt++;
                            }else{
                                //conflict = true;
                                //break;
                            }
                        }
                    }
                }
                if(conflict){
                    break;
                }
            }
            if(!conflict && fitcnt == mycons[i].scnt){
                find = true;
                break;
            }
        }
        if(find){
            cout<<"Yes"<<endl;
        }else{
            cout<<"No"<<endl;
        }
    }
}

int main(){
    inputCons();
    inputSky();
    findCons();
    return 0;
}