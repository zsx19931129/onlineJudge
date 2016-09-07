class Solution {
public:
    inline void reverseString(string &str){
        size_t slen = str.length();
        for(size_t i=0, j=slen-1;i<j;++i, --j){
            char ch = str[i];
            str[i] = str[j];
            str[j] = ch;
        }
    }
    string addNumString(string ret, string addend, int start){
        // cout<<"ret:"<<ret<<" addend:"<<addend<<" start:"<<start<<endl;
        int rlen = ret.length(), alen = addend.length();
        int offlen = start + alen;
        if(rlen<offlen){
            ret += string(offlen-rlen, '0');
        }
        // cout<<"newret:"<<ret<<endl;
        int carry = 0;
        for(int i=0;i<alen;++i){
            int sub = (ret[i+start] - '0') + (addend[i] - '0') + carry;
            ret[i+start] = char('0' + sub%10);
            carry = sub/10;
        }
        if(carry > 0){
            ret += char('0' + carry);
        }
        // cout<<"ret:"<<ret<<endl;
        return ret;
    }
    string multiply(string num1, string num2) {
        int slen1 = num1.length();
        int slen2 = num2.length();
        string multiplicand, multiplier;
        (slen1 > slen2) ? (multiplicand=num1, multiplier=num2) : (multiplicand=num2, multiplier=num1);
        reverseString(multiplicand);
        reverseString(multiplier);
        
        vector<string> multiplyTable(10, multiplicand);
        multiplyTable[0] = "0";
        for(int i=1;i<=9;++i){
            int carry = 0;
            for(int j=0;j<multiplyTable[i].length();++j){
                int sub = (multiplyTable[i][j] - '0')*i + carry;
                multiplyTable[i][j] = char('0' + sub%10) ;
                carry = sub/10;
            }
            if(carry>0){
                multiplyTable[i] += char('0' + carry);
            }
        }
        // cout<<"---"<<endl;
        // for(int i=1;i<=9;++i){
        //     cout<<multiplyTable[i]<<endl;
        // }
        // cout<<"---"<<endl;

        string ret = "0";
        for(int i=0;i<multiplier.length();++i){
            if(multiplier[i] == '0'){
                continue;
            }
            ret = addNumString(ret, multiplyTable[multiplier[i]-'0'], i);
        }
        reverseString(ret);
        return ret;
    }
};