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

    vector<string>tapes;
    vector<int>head_pos;
    string cur_state;

    TM(vector<string>a,vector<char>b,vector<char>c,string d,char e,vector<string>f,int g,vector<delta_Func>h)
    {
        Q=a;
        S=b;
        G=c;
        q0=d;
        B=e;
        F=f;
        N=g;
        delta_Funcs=h;

        
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

    bool check_input_legal_or_not(string input)
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
                cerr << "illegal input\n";
                return false;
            }
        }
        return true;
        
    }

    void Verbose()
    {
        for(int i(0);i<N;i++)
        {
            cout<<"Index "<<i<<" : ";
            for(int j(0);j<tapes[i].size();j++)
            {
                cout<<j<<" ";
            }
            cout<<endl;
            cout<<"Tape  "<<i<<" : ";
            for(int j(0);j<tapes[i].size();j++)
            {
                cout<<tapes[i][j]<<" ";
            }
            cout<<endl;
            cout<<"Head  "<<i<<" : ";
            for(int j(0);j<tapes[i].size();j++)
            {
                if(j==head_pos[i])
                {
                    cout<<"^"<<" ";
                }
                else           
                {
                    cout<<" "<<" ";
                }
            }
            cout<<endl;
        }
        cout<<"State   : "<<cur_state<<endl;
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

    bool solve(string input)
    {
        //TODO: implement of TM should be done here
        if(check_input_legal_or_not(input)!=true)
        {
            return false;
        }
        int Step=0;
        cur_state=q0;
        for(int i(0);i<N;i++)
        {
            string temp_tape;
            temp_tape.push_back(B);
            tapes.push_back(temp_tape);
            head_pos.push_back(0);
        }
        //init Tape1 especically
        tapes[0]=input;
        Verbose();
        int step=0;
        while(true)
        {
            if(step>50)
            {
                break;
            }
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
            else
            {
                delta_Funcs[matched_transition_function_pos].cout_rule();
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
                    }
                }
            }
            cur_state=delta_Funcs[matched_transition_function_pos].next_state;
            formula_tape();
            Verbose();
            for(int i(0);i<F.size();i++)
            {
                if(cur_state==F[i])
                {
                    break;
                }
            }
        }
        return true;
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

TM TM_parser(vector<string> raw_input)
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
        //Meet  sate  set line And try to set Q
        if((raw_input[i][0] == '#') && (raw_input[i][1]=='Q'))
        {
            string cut=cut_bracket(raw_input[i]);
            Q=split(cut,",");   
            continue;   
        }
        //Meet Input Symbol Set And try yo set S
        if((raw_input[i][0] == '#') && (raw_input[i][1]=='S'))
        {
            string cut=cut_bracket(raw_input[i]);
            vector<string>temp=split(cut,",");  
            for(int j=0;j<temp.size();j++)
            {
                S.push_back(temp[j][0]);
            }    
            continue;
        }
        //Meet Type Symbol Set And try yo set G
        if((raw_input[i][0] == '#') && (raw_input[i][1]=='G'))
        {
            string cut=cut_bracket(raw_input[i]);
            vector<string>temp=split(cut,","); 
            for(int j=0;j<temp.size();j++)
            {
                G.push_back(temp[j][0]);
            }         
            continue;
        }
        //Meet Start State and try to set q0
        if((raw_input[i][0] == '#') && (raw_input[i][1]=='q')&& (raw_input[i][2]=='0'))
        {
            q0=raw_input[i].substr(raw_input[i].size()-1,1);
            continue;
        }
        if((raw_input[i][0] == '#') && (raw_input[i][1]=='B'))
        {
            string temp=raw_input[i].substr(raw_input[i].size()-1,1);
            B=temp[0];
            continue;
        }
        if((raw_input[i][0] == '#') && (raw_input[i][1]=='F'))
        {
            string cut=cut_bracket(raw_input[i]);
            F=split(cut,",");      
            continue;
        }
        if((raw_input[i][0] == '#') && (raw_input[i][1]=='N'))
        {
            N=stoi(raw_input[i].substr(raw_input[i].size()-1,1));
            continue;  
        }
        else
        {
            vector<string> Tokens=split(raw_input[i]," "); 
            if(Tokens.size()!=5)
            {
                cout<<"Hit Bad Trap"<<endl;
                continue;
            }
            string cur_state=Tokens[0];
            string tape_char=Tokens[1];
            string new_char=Tokens[2];
            string next_direction=Tokens[3];
            string next_state=Tokens[4];
            if(tape_char.size()==new_char.size()&&new_char.size()==next_direction.size()&&next_direction.size()==N)
            {
                ;
            }
            else
            {
                cout<<"Hit Bad Trap"<<endl;
                continue;
            }
            delta_Func d=delta_Func(cur_state,tape_char,new_char,next_direction,next_state);
            delta_Funcs.push_back(d);  
        }
        


    }
    TM target_TM=TM(Q,S,G,q0,B,F,N,delta_Funcs);
    target_TM.Print_state();
    return target_TM;

}

TM get_TM(string input)
{
    //TODO: to parse the file and get Turing Machhine here
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
        cout <<"no such file" << endl;
    }
    return TM_parser(raw_input);

}

int TM_Solve(string raw_TM,string raw_input)
{
    //Get input string
    //And filename of Turing machine
    TM solver=get_TM(raw_TM);
    solver.solve(raw_input);
    return 1;
}

int comandline_parser(string input)
{
    bool stderr_log=false;
    vector<string>result=split(input," ");
    if(result.size()==0)
    {
        return -1;
    }
    if(result[0]!="turing")
    {
        return -1;
    }
    if(result[1]=="--help")
    {
        cout<<"usage: turing [-v|--verbose] [-h|--help] <tm> <input>"<<endl;
        return 1;
    }
    if(result[1]=="-v"||result[1]=="--verbose")
    {
        stderr_log=true;
        if(result.size()!=4)
        {
            return -1;
        }
        else
        {
            string raw_TM=result[2];
            string raw_input=result[3];
            TM_Solve(raw_TM,raw_input);
        }
        
    }
    if(result.size()!=3)
    {

        return -1;
    }
    else
    {
        string raw_TM=result[1];
        string raw_input=result[2];
        TM_Solve(raw_TM,raw_input);
        return -1;
    }
    
    return 0;

}

  
/*
testcase
turing --help
turing palindrome_detector_2tapes.tm 100010001
*/

int main()
{
    while(1)
    {
        cout<<"$ ";
        string input;
        getline(cin, input);
        comandline_parser(input);
    }
    return 1;
}