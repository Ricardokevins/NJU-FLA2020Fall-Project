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
	//先将要切割的字符串从string类型转换为char*类型
	char * strs = new char[str.length() + 1] ; //不要忘了
	strcpy(strs, str.c_str()); 
 
	char * d = new char[delim.length() + 1];
	strcpy(d, delim.c_str());
 
	char *p = strtok(strs, d);
	while(p) 
    {
		string s = p; //分割得到的字符串转换为string类型
		res.push_back(s); //存入结果数组
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

int TM_parser(vector<string> input)
{

    return 0;
}

TM get_TM(string input)
{
    //TODO: to parse the file and get Turing Machhine here
    // Use This function to get turgin machine
    // Just read the file first and pass content to parser

    vector<string>Q;
    vector<string>S;
    vector<string>G;
    string q0;
    string B;
    vector<string>F;
    int N;
    vector<delta_Func>delta_Funcs;

    vector<string>raw_input;
    ifstream in(input);
    string line;
    cout<<input<<endl;
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
    
    
    TM target_TM=TM(Q,S,G,q0,B,F,N,delta_Funcs);
    return target_TM;


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