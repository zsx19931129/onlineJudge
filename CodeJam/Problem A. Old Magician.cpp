#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(int argc, const char * argv[]) {
    ifstream in("A-large-practice.in");
    streambuf *cinbuf = cin.rdbuf();    // save old buf
    cin.rdbuf(in.rdbuf());              // redirect std::cin to in.txt
    

    ofstream out("A-large-practice.out");
    streambuf *coutbuf = cout.rdbuf();
    cout.rdbuf(out.rdbuf());
    
    
    int n;
    cin>>n;
    int w, b;
    for(int i=1;i<=n;++i){
        cin>>w>>b;
        string res = "WHITE";
        if(b%2==1){
            res = "BLACK";
        }
        cout<<"Case #"<<i<<": "<<res<<endl;
    }
    
    return 0;
}
