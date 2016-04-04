#include <iostream>

using namespace std;

int fullTaxSeg[6];
int startWage[7] = {0, 1500, 4500, 9000, 35000, 55000, 80000};
int rate[7] = {3,10,20,25,30,35,45};

void genTaxTbl(){
    for(int i=1;i<=6;i++){
        int sub = startWage[i] - startWage[i-1];
        fullTaxSeg[i-1] = sub*rate[i-1]/100;
    }
}

int main(){
    genTaxTbl();
    double m;
    cin>>m;
    int off=0;
    double tmp = m;
    while(off < 6 && tmp>fullTaxSeg[off]){
        tmp -= fullTaxSeg[off++];
    }
    int aug = tmp*100/rate[off];
    int wage = 3500 + startWage[off] + aug;
    cout<<wage<<endl;
    return 0;
}