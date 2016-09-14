class Solution {
public:
    string trimString(string str, char ch){
        string ret;
        size_t slen = str.length();
        int i=0;
        for(;i<slen && str[i] == ch;++i);
        if(i == slen){
            return "";
        }
        int j=slen-1;
        for(;j>=0 && str[j] == ch;--j);
        return str.substr(i, j-i+1);
    }

    int scanInteger(const string str, int idx){
        int slen = str.length();
        for(;idx<slen && (str[idx]>='0' && str[idx]<='9');++idx);
        return idx;
    }

    bool isExponential(const string &str, int idx){
        int slen = str.length();
        if(idx == slen){
            return false;
        }
        if(str[idx] == '-' || str[idx] == '+'){
            ++idx;
            if(idx == slen){
               return false;
            }
        }
        
        int copy = idx;
        idx = scanInteger(str, idx);
        return (idx == slen) && (idx > copy);
    }

    bool isNumber(string s) {
        s = trimString(s, ' ');
        int slen = s.length();
        if(slen == 0){
            return false;
        }
        int i=0, i2=0;
        if(s[0] == '+' || s[0] == '-'){
            ++i;
        }
        if(i==slen){
            return false;
        }

        bool base = false;
        i2 = scanInteger(s, i);
        if(i2>i){
            base = true;            
        }
        i = i2;

        if(i!=slen){
            if(s[i] == '.'){
                ++i;
                i2 = scanInteger(s, i);
                if(i2>i){
                    base = true;
                }
                i = i2;
                if(i!=slen && (s[i] == 'e' || s[i] == 'E') && base){
                    return isExponential(s, i+1);
                }
            }else if((s[i] == 'e' || s[i] == 'E') && base){
                return isExponential(s, i+1);
            }else{
                return false;
            }     
        }
        return base && (i==slen);
    }
};