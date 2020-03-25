/*
�����ŵ���׺���ʽ������(�����ļӼ��˳�)
��������ȷ�����
Author: xzc
2019.11.29 ����ԭ��ʵ���

���룺
	begin x:= expression ;end$#
�����
	the result of the expression and
	the possible Error Message(s)
���ܣ�
	�ж��������ʽ�ĺϷ��� (����ƥ�䣬�����ŵȵ�)������
���������'(',')'�������Ӽ��˳�����������������ʽ��ֵ
*/
#include <iostream>
#include <cstdio>
#include <iomanip>
#include <cstring>
#include <cmath>
#include <map>
#include <set>
#include <algorithm>
#include <queue>
#include <string>
#include <vector>
#include <deque>
#include <cstdlib>
#include <stack>
#include <cctype>
#include <locale>
#include <iterator>
#include <sstream>
#include <windows.h>
//#define FileInput 1
using namespace std;
#define For(i,a,b) for(int i=(a);i<=(b);++i)
#define Rep(i,a,b) for(int i=(a);i>=(b);--i)
#define _for(i,a,b) for(int i=(a);i<(b);++i)
#define _rep(i,a,b) for(int i=(a);i>(b);--i)
#define Mst(a,b) memset(a,(b),sizeof(a))
#define CL(a) memset(a,0,sizeof(a))
#define LL long long
#define ll long long
#define nullptr NULL
#define pb push_back
#define MP make_pair
#define pii pair<int,int>
#define PLL pair<long long,long long>
//about color 
#define RED    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED)
#define BLUE   SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_BLUE)
#define GREEN  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN)
#define WHITE  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_BLUE|FOREGROUND_GREEN)
#define CYAN   SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_BLUE|FOREGROUND_GREEN)
#define PURPLE SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_BLUE)
#define YELLOW SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN)
#define B_WHITE SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),BACKGROUND_INTENSITY|BACKGROUND_RED)
#define sl Sleep(100)
const double point10[] =
{
	0,0.1,0.01,0.001,0.0001,0.00001,0.000001,
	0.0000001,0.00000001,0.000000001
};
char s[100005]; //�ַ���������
int favor(char ch);
//��������������ȼ�

double cal(double lhs,char op,double rhs);
//����lhs op rhs��Ԫ���ʽ�Ľ��

bool Pop_Cal(stack<int>& Num,stack<char>& op);
//�������������ջ������

void getOperand(int & i,stack<int>& Num,char * s);
//��ȡ������

bool isBracketMatch(int st,int ed,char * s);
//�жϱ��ʽ�����Ƿ�ƥ��

bool emptyBetweenBracket(int st,int ed,char * s);
//��������֮��ɶ��û��

bool checkNoWideChar(int st,int ed,char * s);
//�жϱ��ʽ�Ƿ񲻺�ȫ���ַ�( ֻ�������0-9,.()+-*/ )

void solve(int st,int ed,char * s);
//�����������ʽ�Ľ�������

void showCalExpression();
//��ʾ

//����ʽ��ֵ
/*
Input File(in.txt):

begin a:=2+3*4-10/5;end$#
begin b:=2-3+4*6-10/5*2-1;end$#
begin c:=2+3*((5-1)*8-6)/4-100/50;end$#
begin d:=3*-5+6;end$#
begin e:=(3*4-5)/6+((4/3);end$#;
begin f:=(11+34)/2+()/6;end$#;

*/

/*
output

*/
int main()
{
#ifdef FileInput
	freopen("in.txt","r",stdin);
#endif
	GREEN;
	cout<<"������ɫ��  564/5984*48948 = 496446   --------------------______________\n"; 
	showCalExpression();
	YELLOW;
	WHITE;
	BLUE;
	cout<<">>> ";
	WHITE;
	while(cin.getline(s,100000))
	{
		int len = strlen(s);
		if(!len)
		{
//			YELLOW;
			WHITE;
			cout<<">>>";
			WHITE; 
			continue;
		} 
		int st=0,ed = len;
		if(strcmp(s,"end")==0)
		{
			break;
		}
		if(strcmp(s,"End")==0)
		{
			break;
		}
		if(strcmp(s,"quit")==0)
		{
			break;
		}
		if(strcmp(s,"quit()")==0)
		{
			break;
		}
		if(strcmp(s,"exit")==0)
		{
			break;
		}
		if(strcmp(s,"exit()")==0)
		{
			break;
		}
//		printf("The expression is��\n%s\n",s);
		if(!isBracketMatch(st,ed,s))
		{
			RED;
			printf("The bracket of this expression is not match(���Ų�ƥ��)!\n");
			YELLOW;
			WHITE;
			cout<<">>>";
			WHITE;
			continue;
		}

		if(emptyBetweenBracket(st,ed,s))
		{
			RED;
			printf("There is a bracket which has nothing inside it(�յ�����)\n");
			YELLOW;
			WHITE;
			cout<<">>>";
			WHITE;
			continue;
		}

		if(!checkNoWideChar(st,ed,s))
		{
			RED;
			printf("-->���뺬�в��Ϸ��ַ���\n");
			YELLOW;
			WHITE;
			cout<<">>>";
			WHITE;
			continue;
		}

		solve(st,ed,s);
		YELLOW;
		WHITE;
		BLUE;
		cout<<">>>";
		WHITE;
	}
#ifdef FileInput
	fclose(stdin);
#endif

	return 0;
}


int favor(char ch)
{
	switch (ch)
	{
		case '#':
			return 0;
			break;

		case '+':
		case '-':
			return 5;
			break;

		case '*':
		case '/':
			return 6;
			break;

		case '(':
			return 1;
			break;

		case ')':
			return 66;
			break;

		default:
			RED;
			cout<<"Error! Illegal Operator"<<ch<<"!\n";
			WHITE;
			return 100;
			break;
	}
	RED;
	cout<<"Error!\n";
	WHITE;
	return 100;
}

double cal(double lhs,char op,double rhs,bool& ok)
{
	ok = true;
	switch (op)
	{
		case '+':
			return lhs+rhs;
			break;

		case '-':
			return lhs-rhs;
			break;

		case '*':
			return lhs*rhs;
			break;

		case '/':
			if(fabs(rhs)<1e-8)
			{
				RED;
				cout<<"Logical Error! Divided by zero!(����0)\n";
				WHITE;
				ok = false;
				return -1000000000;
			}
			return lhs/rhs;
			break;
	}
	return 0;
}

bool Pop_Cal(stack<double>& Num,stack<char>& op)
{
	if(Num.empty())
	{
		RED;
		cout<<"Input Error!\n";
		WHITE;
		return false;
	}
	double rhs = Num.top();
	Num.pop();

	if(Num.empty())
	{
		RED;
		cout<<"Input Error!\n";
		WHITE;
		return false;
	}
	double lhs = Num.top();
	Num.pop();

	char oper = op.top();
	op.pop();

	bool yes = true;
	double ans = cal(lhs,oper,rhs,yes);
	if(!yes)
	{
		return false;
	}
	Num.push(ans);
//	cout<<lhs<<" "<<oper<<" "<<rhs<<" = "<<ans<<endl;
	return true;
}

void getOperand(int & i,stack<double>& Num,char * s)
{
	long long x=0;
	int k=i;
	bool hasPoint = false;
	for(; s[k]!=';'; ++k)
	{
		if(s[k]=='.')
		{
			hasPoint = true;
			break;
		}
		else if(isdigit(s[k]))
		{
			x = x*10+s[k]-'0';
		}
		else
		{
			break;
		}
	}

	double y = 0;
	if(hasPoint)
	{
		k++;
		int cnt = 0;
		for(; s[k]!=';'&&isdigit(s[k]); ++k)
		{
			y = y+point10[++cnt]*(s[k]-'0');
		}
	}

	i=k-1;
	y += x;
	Num.push(y);
}

bool isBracketMatch(int st,int ed,char * s)
{
	stack<char> Stack;
	for(int i=st; i<ed; ++i)
	{
		switch (s[i])
		{
			case '(':
				Stack.push(s[i]);
				break;
			case ')':
				if(Stack.empty()) return false;
				Stack.pop();
				break;
		}
	}
	return (Stack.empty());
}

bool emptyBetweenBracket(int st,int ed,char * s) //��������֮��ɶ��û��
{
	for(int i=st; i<ed-1; ++i)
	{
		if(s[i]=='('&&s[i+1]==')')
		{
			return true;
		}
	}
	return false;
}

bool checkNoWideChar(int st,int ed,char * s)
{
	bool okay = true;
	for(int i=st; okay&&i<ed; ++i)
	{
		if(isdigit(s[i]))
		{
			continue;
		}
		switch (s[i])
		{
			case ' ':
				break;

			case '+':
				break;

			case '-':
				break;

			case '*':
				break;

			case '/':
				break;

			case '.':
				break;

			case '(':
				break;

			case ')':
				break;

			default:
				int last = i+2;
				if(isdigit(s[i+1])||isalpha(s[i+1]))
				{
					last = i+1;
				}
				else
				{
					switch (s[i])
					{
						case '+':
							last = i+1;
							break;

						case '-':
							last = i+1;
							break;

						case '*':
							last = i+1;
							break;

						case '/':
							last = i+1;
							break;

						case '(':
							last = i+1;
							break;

						case ')':
							last = i+1;
							break;

						case ' ':
							last = i+1;
							break;

						case '\0':
							last = i+1;
							break;

						default:
							last = i+2;
					}
				}
				char tmp = s[last];
				s[last] = '\0';
				RED;
				cout<<"\'"<<s+i<<"\'";
				s[last] = tmp;
				okay = false;
				break;
		}
	}
	return okay;
}

void solve(int st,int ed,char * s)
{
	stack<double> Num;
	stack<char> op;
	bool ok = true;
	op.push('#');
	if(s[st]=='-'||s[st]=='+')
	{
		Num.push(0);
	}
	for(int i=st; i<ed; ++i)
	{
		if(s[i]==' ') continue;
		if(isdigit(s[i])) //�ǲ�����
		{
			getOperand(i,Num,s);
		}
		else
		{
			char ch = s[i];
			switch (ch)
			{
				case '(':
					op.push('(');
					break;

				case ')':
					while(op.top()!='(')
					{
						ok = Pop_Cal(Num,op);
						if(!ok) return;
					}
					op.pop();
					break;

				case '+':
				case '-':
				case '*':
				case '/':
					while(favor(op.top())>=favor(ch))
					{
						ok = Pop_Cal(Num,op);
						if(!ok) return;
					}
					op.push(ch);
					break;

				default:
					cout<<"Input Error! \'"<<ch<<"\' is illegal!\n";
					return;
					break;
			}
		}
	}
	while(op.top()!='#')
	{
		ok = Pop_Cal(Num,op);
		if(!ok)
		{
			return;
		}
	}
	CYAN;
	for(int i=st; i<ed; ++i)
	{
		if(s[i]==' ')
		{
			continue;
		}
		else
		{
			printf("%c",s[i]);
		}
	}
	printf(" = ");
	double result = Num.top();
	long long rrr = floor(result);
	if(fabs(result-floor(result))<1e-7)
	{
		cout<<rrr<<endl;
	}
	else
	{
//		if(rrr>=1000000)
//		{
		char stmp[30];
		sprintf(stmp,"%.6f",result-rrr); ///�����Ǹ���� 
		///��һ��stmp��Ϊ�������洢�𰸵�С������
		///��sprintf()��С������д���ַ���֮��
		///Ȼ���ֶ�ȥ��ǰ���0.�����ַ�
		///������������ȡ����long long�ͱ���rrr���洢
		///�����ʱ���������������֣������С���㣬�������С������
		///���ԶԴ��С�����ֵ��ַ�����Ӻ���ǰɨ�裬�Ӷ�ȥ��ĩβ�Ķ����0 
		int len = strlen(stmp);
		for(int i=len-1;i>=2;--i)
		{
			if(stmp[i]!='0')
			{
				stmp[i+1] = '\0';
				break;	
			} 
		} 
		cout<<rrr<<"."<<(stmp+2)<<endl<<endl; 
//		}
//		else
//		{
//			printf("%.4f\n",result);
//		}
//		if(result>10000000)
	}
}

void showCalExpression()
{
	BLUE;
	YELLOW;
	GREEN;
	PURPLE;
	RED;
	CYAN;
	YELLOW;
	cout<<" ____________________________________________________________________________"<<endl;
	cout<<"|                            ";
	GREEN;
	cout<<"�������ʽ����ϵͳ                              ";
	YELLOW;
	cout<<"|"<<endl;
	cout<<"|----------------------------------------------------------------------------|"<<endl;
	cout<<"| - ��ϵͳ֧��ʵ���ļӼ��˳���������                                         |"<<endl;
	cout<<"| - ����Ļ����>>>����ʾ����ʱ�򼴿ɿ�ʼ����Ҫ������������ʽ                |"<<endl;
	cout<<"| - ���븡������ʱ��,С��������������λ��(���˾���Ҳ��������)              |"<<endl;
	cout<<"| - ֧�ָ����������룬ÿ�������������������Ϊ0��Ҳ����ʡ���������� 0.6 is ok|"<<endl;
	cout<<"| - ֧�����ŵ����룬��ֻ���ǰ�ǵ�Ӣ�����š����� (32.5 +3*(5-4.7))-10/4 is ok|"<<endl;
	cout<<"| - ���ʽ֮������пո�     ";
	CYAN;
	cout<<"2*5 - 3/ 2+7 *(1484/78)  is also ok             ";
	YELLOW;
	cout<<"|"<<endl;
	cout<<"| - ���Ҫ�˳�ϵͳ��ֻ��Ҫ����end,End,quit,quit(),exit,exit()֮������һ������|"<<endl;
	cout<<"|----------------------------------------------------------------------------|"<<endl;
	cout<<"|__________________________designed_by_xzc___________________________________|"<<endl;
	cout<<endl;
	WHITE;
}
