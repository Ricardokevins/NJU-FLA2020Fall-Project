#include<iostream>
#include<string>
#include <vector>
#include <string.h>
#include <fstream>
using namespace std;

vector<string> split(const string& str, const string& delim) 
{
	vector<string> res;
	if("" == str) return res;
	char * strs = new char[str.length() + 1] ;
	strcpy(strs, str.c_str()); 
 
	char * d = new char[delim.length() + 1];
	strcpy(d, delim.c_str());
 
	char *p = strtok(strs, d);
	while(p) 
    {
		string s = p; 
		res.push_back(s); 
		p = strtok(NULL, d);
	}
 
	return res;
}

class delta_Func
{
public:
    string cur_state;
    string head;
    string newChar;
    string direction;
    string next_state;
    delta_Func(string a,string b,string c,string d,string e)
    {
        cur_state=a;
        head=b;
        newChar=c;
        direction=d;
        next_state=e;
    }
    void cout_rule()
    {
        cout<<cur_state<<" "<<head<<" "<<newChar<<" "<<direction<<" "<<next_state<<endl;
    }
};

class TM
{
public:
    vector<string>Q;
    vector<char>S;
    vector<char>G;
    string q0;
    char B;
    vector<string>F;
    int N;
    vector<delta_Func>delta_Funcs;

    //parameters during running
    bool verbose_mode;
    vector<string>tapes;
    vector<int>head_pos;
    string cur_state;
    vector<int>leftmost_tag;

    TM(vector<string>a,vector<char>b,vector<char>c,string d,char e,vector<string>f,int g,vector<delta_Func>h,bool verbose_flag)
    {
        Q=a;
        S=b;
        G=c;
        q0=d;
        B=e;
        F=f;
        N=g;
        delta_Funcs=h;
        verbose_mode=verbose_flag;

    }
    
    void Print_state()
    {
        cout<<"State Set"<<endl;
        for(int i(0);i<Q.size();i++)
        {
            cout<<Q[i]<<" ";
        }
        cout<<endl;
    }

    int check_input_legal_or_not(string input)
    {
        for(int i(0);i<input.size();i++)
        {
            int flag=0;
            for(int j(0);j<S.size();j++)
            {
                if(input[i]==S[j])
                {
                    flag=1;
                }
            }
            if(flag==0)
            {
                //cerr << "illegal input\n";
                return i;
            }
        }
        return -1;
        
    }

    void Verbose(int step)
    {
        cout<<std::left<<"Step   : "<<std::left<<step<<endl;
        for(int i(0);i<N;i++)
        {
            vector<int>spaceNum;
            cout<<std::left<<"Index"<<std::left<<i<<std::left<<" : ";
            for(int j(0);j<tapes[i].size();j++)
            {
                int pos=leftmost_tag[i]+j;
                if(pos<0)
                {
                    pos=-pos;
                }
                if(pos<10)
                {
                    spaceNum.push_back(1);
                }
                else
                {
                    if(pos<100)
                    {
                        spaceNum.push_back(2);
                    }
                    
                }
                
                cout<<std::left<<pos<<std::left<<" ";
            }
            cout<<endl;
            cout<<std::left<<"Tape"<<std::left<<i<<std::left<<"  : ";
            for(int j(0);j<tapes[i].size();j++)
            {
                cout<<std::left<<tapes[i][j];
                for(int l(0);l<spaceNum[j];l++)
                {
                    cout<<" ";
                }
            }
            cout<<endl;
            cout<<std::left<<"Head"<<std::left<<i<<"  : ";
            for(int j(0);j<tapes[i].size();j++)
            {
                if(j==head_pos[i])
                {
                    cout<<std::left<<"^"<<std::left;
                }
                else           
                {   
                    cout<<std::left<<" "<<std::left;
                }
                for(int l(0);l<spaceNum[j];l++)
                {
                    cout<<" ";
                }
            }
            cout<<endl;
        }
        cout<<"State  : "<<cur_state<<endl;
        cout<<"---------------------------------------------"<<endl;
    }

    //use this function to cut unnessary Empty Tokens
    void formula_tape()
    {
        
        for(int i(0);i<N;i++)
        {
            for(int j(0);j<head_pos[i];)
            {
                if(tapes[i][j]==B && tapes[i].size()!=1)
                {
                    tapes[i].erase(0,1);
                    head_pos[i]-=1;
                    leftmost_tag[i]+=1;
                }
                else
                {
                    break;
                }
            }
            for(int j(tapes[i].size()-1);j>head_pos[i];)
            {
                if(tapes[i][j]==B && tapes[i].size()!=1)
                {
                    tapes[i].pop_back();
                    j--;
                }
                else
                {
                    break;
                }
            }
        }
    }

    int solve(string input)
    {
        int check_result=check_input_legal_or_not(input);
        if(check_result!=-1)
        {
            if(verbose_mode==false)
            {
                cerr << "illegal input\n";
                exit(-1);
            }
            else
            {
                cerr<<"Input: "<<input<<endl;
                cerr<<"===================== ERR ===================="<<endl;
                cerr<<"error: "<<input[check_result]<<" was not declared in the set of input symbols"<<endl;
                cerr<<"Input: "<<input<<endl;
                cerr<<"       ";
                for(int i(0);i<check_result;i++)
                {
                    cerr<<" ";
                }
                cerr<<"^"<<endl;
                exit(-1);
            }
            
        }
        else
        {
            if(verbose_mode==true)
            {
                cout<<"Input: "<<input<<endl;
                cout<<"==================== RUN ===================="<<endl;
            }
        }
        
        int step=0;
        cur_state=q0;
        for(int i(0);i<N;i++)
        {
            string temp_tape;
            temp_tape.push_back(B);
            tapes.push_back(temp_tape);
            head_pos.push_back(0);
            leftmost_tag.push_back(0);
        }
        //init Tape1 especically
        if(input.size()==0)
        {
            input="_";
        }
        tapes[0]=input;
        if(verbose_mode == true)
            Verbose(step);
        
        while(true)
        {
            step+=1;
            int matched_transition_function_pos=-1;
            for(int i(0);i<delta_Funcs.size();i++)
            {      
                int match_flag=1;   
                for(int j(0);j<tapes.size();j++)
                {
                    if(tapes[j][head_pos[j]]!=delta_Funcs[i].head[j])
                    {
                        match_flag=0;
                    }
                }
                if(cur_state==delta_Funcs[i].cur_state&&match_flag==1)
                {
                    matched_transition_function_pos=i;
                    break;
                }
            }
            if(matched_transition_function_pos==-1)
            {
                break;
            }        
            for(int j(0);j<tapes.size();j++)
            {
                tapes[j][head_pos[j]]=delta_Funcs[matched_transition_function_pos].newChar[j];
            }
            for(int i(0);i<head_pos.size();i++)
            {
                if(delta_Funcs[matched_transition_function_pos].direction[i]=='r')
                {
                    head_pos[i]+=1;
                    if(head_pos[i]>=tapes[i].size())
                    {
                        tapes[i].push_back(B);
                    }
                }               
                if(delta_Funcs[matched_transition_function_pos].direction[i]=='l')
                {
                    head_pos[i]-=1;
                    if(head_pos[i]<0)
                    {
                        tapes[i].insert(0,1,B);
                        head_pos[i]=0;
                        leftmost_tag[i]-=1;
                    }
                }
            }

            cur_state=delta_Funcs[matched_transition_function_pos].next_state;

            formula_tape();
            if (verbose_mode==true)
                Verbose(step);
            for(int i(0);i<F.size();i++)
            {
                if(cur_state==F[i])
                {
                    break;
                }
            }
        }
        if(verbose_mode==true)
        {
            cout<<"Result: "<<tapes[0]<<endl;
            cout<<"===================== END ===================="<<endl;
        }
        else
        {
            cout<<tapes[0]<<endl;
        }
        
        
        return 1;
    }

};

// Use this function to cut "{}" and get inside string
string cut_bracket(string a)
{
    int bracket_start_pos=-1;
    int bracket_end_pos=-1;
    for(int j(0);j<a.size();j++)
    {
        if(a[j] == '{')
        {

            bracket_start_pos=j;
        }
        else
        {
            if(a[j]=='}')
            {
                bracket_end_pos=j;
            }
        }
    }
    string cut = a.substr(bracket_start_pos+1,bracket_end_pos-bracket_start_pos-1);
    return cut;
}

TM TM_parser(vector<string> raw_input,bool verbose_flag)
{
    vector<string>Q;
    vector<char>S;
    vector<char>G;
    string q0;
    char B;
    vector<string>F;
    int N;
    vector<delta_Func>delta_Funcs;
    for(int i(0);i<raw_input.size();i++)
    {
        string temp_string=raw_input[i];
        raw_input[i]="";
        //把不是注释的部分都删除，即不拷贝到新的字符串里
        for(int l(0);l<temp_string.size();l++)
        {
            if(temp_string[l]==';')
            {
                break;
            }
            raw_input[i].push_back(temp_string[l]);
        }
        //Hit empty line and skip
        if(raw_input[i].size()==0)
        {
            continue;
        }
        //Hit note which is no need to parse
        if(raw_input[i][0]==';')
        {
            continue;
        }
        if(raw_input[i].size()<6)
        {
            cerr<<"syntax error\n";
            exit(-1);
        }
        //Meet  sate  set line And try to set Q
        if((raw_input[i][0] == '#') && (raw_input[i][1]=='Q')&&(raw_input[i][2]==' ')&&(raw_input[i][3]=='=')&&(raw_input[i][4]==' '))
        {
            string cut=cut_bracket(raw_input[i]);
            Q=split(cut,",");   
            if(Q.size()==0)
            {
                cerr<<"syntax error\n";
                exit(-1);
            }
            //检查一下是不是都是符合规范的

            continue;   
        }
        //Meet Input Symbol Set And try yo set S
        if((raw_input[i][0] == '#') && (raw_input[i][1]=='S')&&(raw_input[i][2]==' ')&&(raw_input[i][3]=='=')&&(raw_input[i][4]==' '))
        {
            string cut=cut_bracket(raw_input[i]);
            vector<string>temp=split(cut,",");  
            for(int j=0;j<temp.size();j++)
            {
                if(temp[j].size()!=1)
                {
                    cerr<<"syntax error\n";
                    exit(-1);
                }
                S.push_back(temp[j][0]);
            }    
            continue;
        }
        //Meet Type Symbol Set And try yo set G
        if((raw_input[i][0] == '#') && (raw_input[i][1]=='G')&&(raw_input[i][2]==' ')&&(raw_input[i][3]=='=')&&(raw_input[i][4]==' '))
        {
            string cut=cut_bracket(raw_input[i]);
            vector<string>temp=split(cut,","); 
            for(int j=0;j<temp.size();j++)
            {
                if(temp[j].size()!=1)
                {
                    cerr<<"syntax error\n";
                    exit(-1);
                }
                G.push_back(temp[j][0]);
            }
            continue;
        }
        //Meet Start State and try to set q0
        if((raw_input[i][0] == '#') && (raw_input[i][1]=='q')&& (raw_input[i][2]=='0')&&(raw_input[i][3]==' ')&&(raw_input[i][4]=='=')&&(raw_input[i][5]==' '))
        {
            q0=raw_input[i].substr(raw_input[i].size()-1,1);
            continue;
        }
        if((raw_input[i][0] == '#') && (raw_input[i][1]=='B')&&(raw_input[i][2]==' ')&&(raw_input[i][3]=='=')&&(raw_input[i][4]==' '))
        {
            string temp=raw_input[i].substr(raw_input[i].size()-1,1);
            B=temp[0];
            if(B!='_')
            {
                cerr<<"syntax error\n";
                exit(-1);
            }
            continue;
        }
        if((raw_input[i][0] == '#') && (raw_input[i][1]=='F')&&(raw_input[i][2]==' ')&&(raw_input[i][3]=='=')&&(raw_input[i][4]==' '))
        {
            string cut=cut_bracket(raw_input[i]);
            F=split(cut,",");      
            continue;
        }
        if((raw_input[i][0] == '#') && (raw_input[i][1]=='N')&&(raw_input[i][2]==' ')&&(raw_input[i][3]=='=')&&(raw_input[i][4]==' '))
        {
            string Num=raw_input[i].substr(5,raw_input[i].size()-5);
            if(Num.size()==0)
            {
                cerr<<"syntax error\n";
                exit(-1);
            }
            // 检查一下到底是不是一个int类型的数字字符串
            for(int j(0);j<Num.size();j++)
            {
                if(Num[j]>='0'&& Num[j]<='9')
                {
                    ;
                }
                else
                {
                    cerr<<"syntax error\n";
                    exit(-1);
                }
            }
            N=stoi(Num);
            continue;  
        }
        else
        {
            vector<string> Tokens=split(raw_input[i]," ");        
            if(Tokens.size()!=5)
            {    
                cerr<<"syntax error\n";
                exit(-1);
            }
            string cur_state=Tokens[0];
            string tape_char=Tokens[1];
            string new_char=Tokens[2];
            string next_direction=Tokens[3];
            string next_state=Tokens[4];
            delta_Func d=delta_Func(cur_state,tape_char,new_char,next_direction,next_state);
            delta_Funcs.push_back(d);  
            
        }
        

    }
    // 上面检查了格式的合法性，这里检查一下内容的合法性
    for(int k(0);k<Q.size();k++)
    {
        for(int l(0);l<Q[k].size();l++)
        {
            int flag=0;
            if(Q[k][l]<='z'&&Q[k][l]>='a')
            {
                flag=1;
            }
            else
            {
                if(Q[k][l]<='Z'&&Q[k][l]>='A')
                {
                    flag=1;
                }
                else
                {
                    if(Q[k][l]<='9'&&Q[k][l]>='0')
                    {
                        flag=1;
                    }
                    else
                    {
                        if(Q[k][l]=='_')
                        {
                            flag=1;
                        }
                        else
                        {
                            cerr<<"syntax error\n";
                            exit(-1);
                        }
                        
                    }
                    
                }
            }
            

        }
    }
    
    for(int k(0);k<S.size();k++)
    {
        if(S[k]==' ')
        {
            cerr<<"syntax error\n";
            exit(-1);
        }
        if(S[k]==',')
        {
            cerr<<"syntax error\n";
            exit(-1);
        }
        if(S[k]==';')
        {
            cerr<<"syntax error\n";
            exit(-1);
        }
        if(S[k]=='{')
        {
            cerr<<"syntax error\n";
            exit(-1);
        }
        if(S[k]=='}')
        {
            cerr<<"syntax error\n";
            exit(-1);
        }
        if(S[k]=='_')
        {
            cerr<<"syntax error\n";
            exit(-1);
        }
        if(S[k]=='*')
        {
            cerr<<"syntax error\n";
            exit(-1);
        }
    }
    
    for(int k(0);k<G.size();k++)
    {
        if(G[k]==' ')
        {
            cerr<<"syntax error\n";
            exit(-1);
        }
        if(G[k]==',')
        {
            cerr<<"syntax error\n";
            exit(-1);
        }
        if(G[k]==';')
        {
            cerr<<"syntax error\n";
            exit(-1);
        }
        if(G[k]=='{')
        {
            cerr<<"syntax error\n";
            exit(-1);
        }
        if(G[k]=='}')
        {
            cerr<<"syntax error\n";
            exit(-1);
        }
        if(G[k]=='*')
        {
            cerr<<"syntax error\n";
            exit(-1);
        }
    }
    
    //接着检查一下部分变量是否在之前建立的状态表里
    int find_q0_flag=0;
    for(int k(0);k<Q.size();k++)
    {
        if(Q[k]==q0)
        {
            find_q0_flag=1;
            break;
        }
    }
    if(find_q0_flag==0)
    {
        cerr<<"syntax error\n";
        exit(-1);
    }
    
    for(int l(0);l<F.size();l++)
    {
        int find_F_flag=0;
        for(int j(0);j<Q.size();j++)
        {
            if(Q[j]==F[l])
            {
                find_F_flag=1;
                break;
            }
        }
        if(find_F_flag==0)
        {
            cerr<<"syntax error\n";
            exit(-1);
        }
    }
    
    //保证纸带数目至少大于0
    if(N<=0)
    {
        cerr<<"syntax error\n";
        exit(-1);
    }
    
    for(int i(0);i<delta_Funcs.size();i++)
    {
        string cur_state=delta_Funcs[i].cur_state;
        string tape_char=delta_Funcs[i].head;
        string new_char=delta_Funcs[i].newChar;
        string next_direction=delta_Funcs[i].direction;
        string next_state=delta_Funcs[i].next_state;
        if(tape_char.size()==new_char.size()&&new_char.size()==next_direction.size()&&next_direction.size()==N)
            {
                //size 符合要求，检查一下里面的内容对不对
                for(int i=0;i<tape_char.size();i++)
                {
                    int flag=0;
                    for(int j(0);j<G.size();j++)
                    {
                        if(G[j]==tape_char[i])
                        {
                            flag=1;
                            break;
                        }
                    }
                    if(flag==0)
                    {
                        
                        cerr<<"syntax error\n";
                        exit(-1);
                    }
                }
                
                for(int i=0;i<new_char.size();i++)
                {
                    int flag=0;
                    for(int j(0);j<G.size();j++)
                    {
                        if(G[j]==new_char[i])
                        {
                            flag=1;
                            break;
                        }
                        
                    }
                    if(flag==0)
                    {
                        
                        cerr<<"syntax error\n";
                        exit(-1);
                    }
                }
               
                for(int i=0;i<next_direction.size();i++)
                {
                    if(next_direction[i]!='r')
                    {
                        if(next_direction[i]!='l')
                        {
                            if(next_direction[i]!='*')
                            {
                                
                                cerr<<"syntax error\n";
                                exit(-1);
                            }
                        }
                    }
                }
                int flag=0;
                for(int i=0;i<Q.size();i++)
                {
                    if(Q[i]==cur_state)
                    {
                        flag=1;
                        break;
                    }
                }
                if (flag==0)
                {
                    
                    cerr<<"syntax error\n";
                    exit(-1);
                }
                int flag1=0;
                for(int i=0;i<Q.size();i++)
                {
                    if(Q[i]==next_state)
                    {
                        flag1=1;
                        break;
                    }
                }
                if (flag1==0)
                {
                    
                    cerr<<"syntax error\n";
                    exit(-1);
                }
            }   
            else
            {
                
                cerr<<"syntax error\n";
                exit(-1);
            }
    }
    TM target_TM=TM(Q,S,G,q0,B,F,N,delta_Funcs,verbose_flag);
    return target_TM;

}

TM get_TM(string input,bool verbose_flag)
{
    // parse the file and get Turing Machhine here
    // Use This function to get turgin machine
    // Just read the file first and pass content to parser

    vector<string>raw_input;
    ifstream in(input);
    string line;
    if(in) 
    {
        while (getline (in, line)) 
        { 
            raw_input.push_back(line);
        }
    }
    else 
    {
        cerr <<"syntax error\n";
        exit(-1);
    }
    return TM_parser(raw_input,verbose_flag);

}

int TM_Solve(string raw_TM,string raw_input,bool verbose_flag)
{
    //Get input string
    //And filename of Turing machine
    TM solver=get_TM(raw_TM,verbose_flag);
    int res=solver.solve(raw_input);
    return res;;
}

int comandline_parser(vector<string> result)
{
    bool stderr_log=false;
    if(result.size()<2)
    {
        cerr <<"syntax error\n" ;
        exit(-1);
    }
    if(result[0]!="turing"&&result[0]!="./turing")
    {
        cerr <<"syntax error\n";
        exit(-1);
    }
    if(result[1]=="--help"||result[1]=="-h")
    {
        cout<<"usage: turing [-v|--verbose] [-h|--help] <tm> <input>"<<endl;
        return 1;
    }
    if(result[1]=="-v"||result[1]=="--verbose")
    {
        stderr_log=true;
        if(result.size()!=4)
        {
            cerr <<"syntax error\n";
            exit(-1);
        }
        else
        {
            string raw_TM=result[2];
            string raw_input=result[3];
            int res=TM_Solve(raw_TM,raw_input,true);
            return res;
        }
        
    }
    if(result.size()!=3)
    {

        cerr <<"syntax error\n";
        exit(-1);
    }
    else
    {
        string raw_TM=result[1];
        string raw_input=result[2];
        int res=TM_Solve(raw_TM,raw_input,false);
        return res;
    }
    
    return 0;

}

int main(int argc,char *argv[])
{
    vector<string> param;
    for(int i=0;i<argc;i++)
    {
        string temp=argv[i];
        param.push_back(temp);
    }
    string command;
    for(int i(0);i<param.size();i++)
    {
        command+=param[i];
        command+=" ";
    }
    int res=comandline_parser(param);
    if(res!=1)
    {
        return -1;
    }
    else
    {
        return 1;
    }
    return 0;
}