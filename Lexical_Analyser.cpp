#include<bits/stdc++.h>
using namespace std;
class Lexical{
    public:
        long long int token=0;
        unordered_map<char,int> elem;
        unordered_map<char,int> symbol;
        unordered_map<char,int> operators;
        unordered_map<char,int> identifiers;
        unordered_map<string, int> operatorsbundle;
        unordered_map<string, int> keyword;
        vector<string> ans;
        Lexical(){
            for(char itr=' ';itr<='~';itr++){
                elem[itr]=1;
            }
            elem['"']=0;
            symbol=elem;
            for(char itr='a';itr<='z';itr++){
                symbol[itr]=0;
                symbol[toupper(itr)]=0;
                identifiers[itr]=1;
                identifiers[toupper(itr)]=1;
            }
            for(char itr='0';itr<='9';itr++){
                symbol[itr]=0;
                identifiers[itr]=1;
            }
            symbol[' ']=0;
            string arr[]={"if", "else", "while", "do", "break", "continue", "int", "double", "float", "return", "char", "case", "long", "short", "typedef", "switch", "unsigned", "void", "static", "struct", "sizeof", "long", "volatile", "typedef", "enum", "const", "union", "extern","bool","endl","main","cin","cout", "vector", "map", "set", "queue", "stack", "unordered_map", "ordered_map", "priority_queue", "new", "for", "string", "signed", "sort", "begin", "end", "reverse", "auto",  "template", "operator", "default", "goto", "register", "asm", "dynamic_cast", "namespace", "reinterpret_cast",	"explicit",	"static_cast", "false",	"catch", "friend",	"private",	"class", "this", "inline", "public", "throw", "const_cast", "delete", "mutable", "protected", "true", "try", "typeid", "typename", "using", "virtual", "wchar_t"};
            for(int i=0;i<end(arr)-begin(arr);i++)
                keyword[arr[i]]=1;
            char op[]={'+', '-', '=', '*', '/', '<', '>', '|', '&', '~', '^', '%', '!'};
            for(int i=0;i<sizeof(op);i++)
                operators[op[i]]=1;
            string opb[]={"+=", "-=", "/=", "*=", "%=", "<<", ">>", "||", "&&", "!=", "<=", ">=", "==", "--", "++"};
            for(int i=0;i<end(opb)-begin(opb);i++)
                operatorsbundle[opb[i]]=1;  
            identifiers['_']=1;
            identifiers['$']=1;  
            symbol['_']=0;
            symbol['$']=0;
        }
        int isoperator(char sym){
            if(operators[sym])
                return 2;
            else if(symbol[sym])   
                return 1;
            else
                return 0;
        }
        int iskeyword(string s){
            if(keyword[s]==1)
                return 1;
            return 0;
        }
        int isIdentifier(string s){
            for(int i=0;i<s.length();i++){
                if(identifiers[s[i]]==0)
                    return 0;
            }
            if(s[0]>='0'&&s[0]<='9')
                return 0;
            return 1;
        }
        int isdigit(char a){
            if(a>='0'&&a<='9')
                return 1;
            return 0;
        }
        void tokenify(string s){
            if(s!=""){
                int flag=1;
                for(int i=0;i<s.length();i++)
                    if(!((s[i]>='0'&&s[i]<='9')||s[i]=='.')){
                        flag=0;
                        break;
                    }
                if(flag==1){
                    ans.push_back(s+": Constant");
                    token++;
                }
                else{
                    if(iskeyword(s)){
                        ans.push_back(s+": Keyword");
                        token++;
                    }
                    else{
                        if(isIdentifier(s)){
                            ans.push_back(s+": Identifier");
                            token++;
                        }
                        else{
                            ans.push_back(s+": Invalid Identifier");
                        }
                    }
                }
            }
        }
        int main(){
            #ifndef ONLINE_JUDGE
                freopen("input.in","r",stdin);
                freopen("output.out","w",stdout);
            #endif
            int commflag=0,stringflag=0,dotflag=0;
            char str[100];
            string s=""; 
            // int no;
            // cin>>no;  
            // cin.ignore(256, '\n');
            while(cin.getline(str,100)){
                s="";
                for(int i=0;i<100&&str[i];i++)
                    s=s+str[i];
                int n=s.length();
                string subs="";
                if(s[0]=='#'){
                    continue;
                }
                for(int i=0;i<n;i++){
                    if(!commflag&&!stringflag){
                        if((i!=n-1&&s[i]=='/'&&s[i+1]=='*')||s[i]=='"'){
                            // Checking Multi Line Comment Start
                            tokenify(subs);
                            subs="";
                            if(s[i]=='"'){
                                subs=subs+'"';
                                stringflag=1;
                            }
                            else{
                                ans.push_back("Multi Line Comment Start");
                                commflag=1;
                            
                            }
                            continue;
                        }
                        if(i!=n-1&&s[i]=='*'&&s[i+1]=='/'){
                            // Checking Single Line Comment
                            tokenify(subs);
                            subs="";
                            ans.push_back("Error: Multi Line Comment Never Started");
                            break;
                        }
                        if(s[i]==' '){
                            // Checking Space
                            tokenify(subs);
                            subs="";
                            continue;
                        }
                        if(i!=n-1&&s[i]=='/'&&s[i+1]=='/'){
                            // Checking Single Line Comment
                            tokenify(subs);
                            subs="";
                            ans.push_back("Single Line Comment Found");
                            break;
                        }
                        if(i!=n-1&&isoperator(s[i])&&isoperator(s[i+1])){
                            // Checking bundle operators
                            string t1="";
                            t1=t1+s[i]+s[i+1];
                            if(operatorsbundle[t1]){
                                tokenify(subs);
                                subs="";
                                t1=t1+": Operator";
                                ans.push_back(t1);
                                token++;
                                i++;
                                continue;
                            }
                            // else{
                            //     ans.push_back("Error: Invalid Operator");
                            //     continue;
                            // }
                        }
                        if(s[i]=='.'&&isdigit(s[i+1])){
                            if(dotflag >= 1){
                                if(dotflag==1)
                                    ans.push_back("Error: Invlaid Constant");
                                while(isdigit(s[i+1])||isdigit(s[i]))
                                    i++;
                                subs = "";
                            }
                            else{
                                dotflag++;
                                subs=subs+s[i];
                                continue;
                            }
                        }
                        if(isoperator(s[i])){
                            // Checking Operators
                            token++;
                            tokenify(subs);
                            subs="";
                            if(isoperator(s[i])==2){
                                string temp=": Operator";
                                temp=s[i]+temp;
                                ans.push_back(temp);
                            }
                            else if(isoperator(s[i])==1){
                                string temp=": Symbol";
                                temp=s[i]+temp;
                                ans.push_back(temp);
                            }
                            continue;
                        }
                        if(elem[s[i]]==1){
                            subs=subs+s[i];
                        }
                        else{
                            // Checking Keywords, Identifiers
                            tokenify(subs);
                            subs="";
                            dotflag = 0;
                        }
                    }
                    else if(commflag){
                        if(i!=n-1&&s[i]=='*'&&s[i+1]=='/'){
                            // Checking Multi Line COmment Endings
                            ans.push_back("Multi Line Comment Ended");
                            commflag=0;
                            i++;
                        }
                    }
                    else{
                        subs=subs+s[i];
                        if(s[i]=='"'){
                            token++;
                            string temp=": String";
                            temp=subs+temp;
                            ans.push_back(temp);
                            subs="";
                            stringflag=0;
                        }
                    }
                }
                if(subs!=""){
                    tokenify(subs);
                    subs="";
                }
            }
            if(commflag){
                ans.push_back("Error: Multi Line Comment Not Closed");
            }
            if(stringflag){
                ans.push_back("Error: String Not Closed");
            }
            for(int j=0;j<ans.size();j++)
                cout<<ans[j]<<endl;
            cout<<token<<endl;
            return 0;
        }
};
int main(){
    Lexical lex;
    lex.main();
}