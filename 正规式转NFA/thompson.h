#ifndef THOMPSON_H
#define THOMPSON_H

#include <iostream>
#include <stdio.h>
#include <cctype>
#include <stack>
#include <string>

using namespace std;

#define MAX 100

//�ڵ㣬����ɽṹ�壬�����Ժ���չ
struct state
{
	char StateName;
};

//�ߣ���ת������'#'��ʾ
struct edge
{
	state StartState;
	state EndState;
	char TransSymbol;
};

//NFA��Ԫ
struct cell
{
	edge EdgeSet[MAX];
	int EdgeCount;
	state StartState;
	state EndState;
};

/***************NFA�ľ���ṹ****************/

struct node
{
	edge* In_edges;
	edge* Out_edges;
	//state
};

/********************************************/

//��������
void input(string&);
int check_legal(string);
int check_character(string);
int check_parenthesis(string);
int is_letter(char);
//��ӡ�+��������ת��׺���ʽ
string add_join_symbol(string);
//��׺ת��׺
string postfix(string);
//���ȼ� in stack priority
int isp(char);
//���ȼ� in coming priority
int scp(char);
//���ʽתNFA
cell express_2_NFA(string);
//���� a|b
cell do_Unite(cell, cell);
//���� ab
cell do_Join(cell, cell);
//���� a*
cell do_Star(cell);
//���� a
cell do_Cell(char);
//��һ����Ԫ�ıߵļ��ϸ��Ƶ���һ����Ԫ
void cell_EdgeSet_Copy(cell&, cell);

//����һ���µ�״̬�ڵ㣬���ڹ���
state new_StateNode();
//��ʾ
void Display(cell);
void Display1(cell Cell);


#endif  //THOMPSON.H