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
};

class TM
{
public:
    vector<string>Q;
    vector<string>S;
    vector<string>G;
    string q0;
    string B;
    vector<string>F;
    int N;
    vector<delta_Func>delta_Funcs;

    TM(vector<string>a,vector<string>b,vector<string>c,string d,string e,vector<string>f,int g,vector<delta_Func>h)
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
    
    bool solve(string input)
    {
        //TODO: implement of TM should be done here
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
    vector<string>S;
    vector<string>G;
    string q0;
    string B;
    vector<string>F;
    int N;
    vector<delta_Func>delta_Funcs;
    for(int i(0);i<raw_input.size();i++)
    {
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
            vector<string>variety;
            Q=split(cut,",");   
            continue;   
        }
        //Meet Input Symbol Set And try yo set S
        if((raw_input[i][0] == '#') && (raw_input[i][1]=='S'))
        {
            string cut=cut_bracket(raw_input[i]);
            vector<string>variety;
            S=split(cut,",");      
            continue;
        }
        //Meet Type Symbol Set And try yo set G
        if((raw_input[i][0] == '#') && (raw_input[i][1]=='G'))
        {
            string cut=cut_bracket(raw_input[i]);
            vector<string>variety;
            G=split(cut,",");      
            continue;
        }
        //Meet Start State and try to set q0
        if((raw_input[i][0] == '#') && (raw_input[i][1]=='q')&& (raw_input[i][2]=='0'))
        {
            q0=raw_input[i].substr(raw_input[i].size()-1,1);
        }

    }
    TM target_TM=TM(Q,S,G,q0,B,F,N,delta_Funcs);
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