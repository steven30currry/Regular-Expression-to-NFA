#include "Thompson.h"

int STATE_NUM = 0;

/**���ʽתNFA������,�������յ�NFA���
*/
cell express_2_NFA(string expression)
{
	int length = expression.size();
	char element;
	cell Cell, Left, Right;
	stack<cell> STACK;
	for (int i = 0; i < length; i++)
	{
		element = expression.at(i);
		switch (element)
		{
		case '|':
			Right = STACK.top();
			STACK.pop();
			Left = STACK.top();
			STACK.pop();
			Cell = do_Unite(Left, Right);
			STACK.push(Cell);
			break;
		case '*':
			Left = STACK.top();
			STACK.pop();
			Cell = do_Star(Left);
			STACK.push(Cell);
			break;
		case '+':
			Right = STACK.top();
			STACK.pop();
			Left = STACK.top();
			STACK.pop();
			Cell = do_Join(Left, Right);
			STACK.push(Cell);
			break;
		default:
			Cell = do_Cell(element);
			STACK.push(Cell);
		}
	}
	//cout << "�������!" << endl;
	Cell = STACK.top();
	STACK.pop();

	return Cell;
}

//���� a|b
cell do_Unite(cell Left, cell Right)
{
	edge Edge1;

	for (int i = 0; i < Right.EdgeCount; i++) {
		Edge1 = Right.EdgeSet[i];
		Edge1.StartState.StateName = Left.StartState.StateName;
		Edge1.EndState.StateName = Left.EndState.StateName;
		STATE_NUM -= 2;
		Left.EdgeSet[Left.EdgeCount++] = Edge1;
	}
	return Left;
}
//���� ab
cell do_Join(cell Left, cell Right)
{
	//��left�еĽ���״̬��right�еĿ�ʼ״̬�ϲ�
	for (int i = 0; i < Right.EdgeCount; i++)
	{
		if (Right.EdgeSet[i].StartState.StateName==Right.StartState.StateName)
		{
			Right.EdgeSet[i].StartState = Left.EndState;
			Right.EdgeSet[i].EndState.StateName--;
			Left.EdgeSet[Left.EdgeCount++] = Right.EdgeSet[i];
			STATE_NUM--;
		}
		
	}
	Right.EndState.StateName--;//��Ϊ����Ĳ���ı��������������Ҫ�ٸ�һ��
	Left.EndState = Right.EndState;
	return Left;
}
//���� a*
cell do_Star(cell Cell)
{
	
	edge Edge1, Edge2, Edge3;
	state newState = new_StateNode();
	state left = Cell.StartState;
	state right = Cell.EndState;
	for (int i = 0; i < Cell.EdgeCount; i++) {//���Կ�ͷΪ����������ʼ��ת����β
		if (Cell.EdgeSet[i].StartState.StateName == Cell.StartState.StateName) {
			Cell.EdgeSet[i].StartState.StateName = right.StateName;
		}
	}
	//������ߵ�����˹¡
	Edge2.StartState.StateName = left.StateName;
	Edge2.EndState.StateName = right.StateName;
	Edge2.TransSymbol = '~';
	Cell.EdgeSet[Cell.EdgeCount++] = Edge2;
	//�����ұߵ�����˹¡
	Edge3.StartState.StateName = right.StateName;
	Edge3.EndState.StateName = newState.StateName;
	Edge3.TransSymbol = '~';
	Cell.EdgeSet[Cell.EdgeCount++] = Edge3;
	//����endsstate
	Cell.EndState = Edge3.EndState;
	
	return Cell;
}
//���� a
cell do_Cell(char element)
{
	cell NewCell;
	NewCell.EdgeCount = 0;
	edge NewEdge;
	//����µ���״̬�ڵ�
	state StartState = new_StateNode();
	state EndState = new_StateNode();
	//������
	NewEdge.StartState = StartState;
	NewEdge.EndState = EndState;
	NewEdge.TransSymbol = element;
	//������Ԫ
	NewCell.EdgeSet[NewCell.EdgeCount++] = NewEdge;
	NewCell.StartState = NewCell.EdgeSet[0].StartState;
	NewCell.EndState = NewCell.EdgeSet[0].EndState;//EdgeCount��ʱΪ1
	return NewCell;
}
void cell_EdgeSet_Copy(cell& Destination, cell Source)
{
	int D_count = Destination.EdgeCount;
	int S_count = Source.EdgeCount;
	for (int i = 0; i < S_count; i++)
	{
		Destination.EdgeSet[D_count + i] = Source.EdgeSet[i];
	}
	Destination.EdgeCount = D_count + S_count;
}
/*
����µ�״̬�ڵ㣬ͳһ���������ڹ������ܲ����ظ���״̬
����ӵ�state_set[]������
*/
state new_StateNode()
{
	state newState;
	newState.StateName = STATE_NUM ;//ת���ɴ�д��ĸ
	STATE_NUM++;
	return newState;
}
//��������������ʽ��RegularExpression��Ϊ�ش�����
void input(string &RegularExpression)
{
	//cout << "������������ʽ��  ����������() * |;�ַ�����a~z A~Z��" << endl;
	do
	{
		cin >> RegularExpression;
	} while (!check_legal(RegularExpression));

}
/**��������������ʽ�Ƿ�Ϸ�
*/
int check_legal(string check_string)
{
	if (check_character(check_string) && check_parenthesis(check_string))
	{
		return true;
	}
	return false;
}
/**
���������ַ��Ƿ���� () * | a~z A~Z
�Ϸ�����true,�Ƿ�����false
*/
int check_character(string check_string)
{
	int length = check_string.size();
	for (int i = 0; i < length; i++)
	{
		char check = check_string.at(i);
		if (is_letter(check))//Сд�ʹ�д֮����5���ַ����ʲ��������ж�
		{
			//cout<<"��ĸ �Ϸ�";
		}
		else if (check == '(' || check == ')' || check == '*' || check == '|')
		{
			//cout<<"������ �Ϸ�";
		}
		else
		{
			//cout << "���в��Ϸ����ַ�!" << endl;
			//cout << "����������:" << endl;
			return false;
		}
	}
	return true;
}
/**�ȼ�������Ƿ�ƥ��
*�Ϸ�����true,�Ƿ�����false
*/
int check_parenthesis(string check_string)
{
	int length = check_string.size();
	//char * check = new char[length+1];
	//wcscpy(check, length+1, check_string.c_str());
	string check = check_string;
	stack<int> STACK;
	for (int i = 0; i < length; i++)
	{
		if (check[i] == '(')
			STACK.push(i);
		else if (check[i] == ')')
		{
			if (STACK.empty())
			{
			//	cerr << "�ж����������" << endl;//��ʱ����¼ƥ��λ��location
			//	cout << "����������:" << endl;
				return false;
			}
			else
				STACK.pop();
		}
	}
	if (!STACK.empty())
	{
		//��ʱ����¼ƥ��λ��location
	//	cerr << "�ж����������" << endl;
	//	cout << "����������:" << endl;
		return false;
	}

	return true;
}
/**����Ƿ�����ĸ
�Ƿ���true,����false
*/
int is_letter(char check)
{
	if (check >= 'a'&&check <= 'z' || check >= 'A'&&check <= 'Z')
		return true;
	return false;
}

/**��ӽ���������+����������׺ת��׺���ʽ
���� abb->a+b+b
*/
string add_join_symbol(string add_string)
{
	/*  ������ֹ��\0
	string check_string = "abcdefg\0aaa";
	cout<<check_string<<endl;
	int length = check_string.size();
	char * check = new char[2*length];
	strcpy(check,check_string.c_str());
	cout<<check<<endl;
	char *s = "ssss\0  aa";
	cout<<s<<endl;
	string a(s);
	cout<<a<<endl;
	*/
	int length = add_string.size();
	int return_string_length = 0;
	char *return_string = new char[2 * length + 2];//���������
	char first, second;
	for (int i = 0; i < length - 1; i++)
	{
		first = add_string.at(i);
		second = add_string.at(i + 1);
		return_string[return_string_length++] = first;
		//Ҫ�ӵĿ�������ab �� *b �� a( �� )b �����
		//���ڶ�������ĸ����һ������'('��'|'��Ҫ���
		if (first != '('&&first != '|'&&is_letter(second))
		{
			return_string[return_string_length++] = '+';
		}
		//���ڶ�����'(',��һ������'|'��'(',ҲҪ��
		else if (second == '('&&first != '|'&&first != '(')
		{
			return_string[return_string_length++] = '+';
		}
	}
	//�����һ���ַ�д��
	return_string[return_string_length++] = second;
	return_string[return_string_length] = '\0';
	string STRING(return_string);
	//cout << "��'+'��ı��ʽ��" << STRING << endl;
	return STRING;
}
/*
�������ȼ�����򣺣�1���������ڣ��������⣻��2�����ȼ��ɸߵ��ͣ��հ���|��+����3��ͬ����������ҡ�
���ȼ���
	 #	(	*	|	+	)
isp  0	1	7	5	3	8
icp	 0	8	6	4	2	1
*/

/*********************��������ȼ���ϵ��********************/
/*
	c1\c2	(	*	|	+	)	#

	(		<	<	<	<	=	>

	*		<	>	>	>	>	>

	|		<	<	>	>	>	>

	+		<	<	<	>	>	>

	#		<	<	<	<	<	=
*/
/***********************************************************/

//in stack priority  ջ�����ȼ���ջ�����ַ������ȼ�
int isp(char c)
{
	switch (c)
	{
	case '#': return 0;
	case '(': return 1;
	case '*': return 7;
	case '|': return 5;
	case '+': return 3;
	case ')': return 8;
	}
	//���ߵ���һ����˵��������
	//cerr << "ERROR!" << endl;
	return false;
}
//in coming priority ջ�����ȼ�����ǰɨ�赽���ַ������ȼ�
int icp(char c)
{
	switch (c)
	{
	case '#': return 0;
	case '(': return 8;
	case '*': return 6;
	case '|': return 4;
	case '+': return 2;
	case ')': return 1;
	}
	//���ߵ���һ����˵��������
	//cerr << "ERROR!" << endl;
	return false;
}
/**��׺���ʽת��׺���ʽ
*/
string postfix(string e)
{
	//�趨e�����һ������ʽ��#�������䡰#��һ��ʼ�ȷ���ջs��ջ��
	e = e + "#";

	stack<char> s;
	char ch = '#', ch1, op;
	s.push(ch);
	//��һ���ַ�
	string out_string = "";
	int read_location = 0;
	ch = e.at(read_location++);
	while (!s.empty())
	{
		if (is_letter(ch))
		{
			out_string = out_string + ch;
			//cout<<ch;
			ch = e.at(read_location++);
		}
		else
		{
			//cout<<"�����������"<<ch<<endl;
			ch1 = s.top();
			if (isp(ch1) < icp(ch))
			{
				s.push(ch);
				//cout<<"ѹջ"<<ch<<"  ��ȡ��һ��"<<endl;
				ch = e.at(read_location++);
			}
			else if (isp(ch1) > icp(ch))
			{
				op = s.top();
				s.pop();
				//cout<<"��ջ"<<op<<" ��ӵ�����ַ���"<<endl;
				out_string = out_string + op;
				//cout<<op;
			}
			else  //�������ȼ���ȵ����
			{
				op = s.top();
				s.pop();
				//cout<<"��ջ"<<op<<"  ������ӵ������ַ���"<<endl;

				if (op == '(')
					ch = e.at(read_location++);
			}
		}
	}

	//cout << "��׺���ʽ��" << out_string << endl;
	return out_string;
}
/*
	��ʾNFA
*/
void Display(cell Cell)
{
	cout << "NFA �ı�����" << Cell.EdgeCount << endl;
	cout << "NFA ����ʼ״̬��" << Cell.StartState.StateName << endl;
	cout << "NFA �Ľ���״̬��" << Cell.EndState.StateName << endl;
	for (int i = 0; i < Cell.EdgeCount; i++)
	{
		cout << "��" << i + 1 << "���ߵ���ʼ״̬��" << Cell.EdgeSet[i].StartState.StateName
			<< "  ����״̬��" << Cell.EdgeSet[i].EndState.StateName
			<< "  ת������" << Cell.EdgeSet[i].TransSymbol << endl;
	}
	cout << "����" << endl;
}
void Display1(cell Cell) {
	int begin = Cell.StartState.StateName;
	int end = Cell.EndState.StateName;
	int cnt = Cell.EdgeCount;
	Cell.EndState.StateName = 'Y';
	Cell.StartState.StateName = 'X';
	cout << "X ";
	for (int j = 0; j < cnt; j++) {
		if (Cell.EdgeSet[j].StartState.StateName == 0) {
			cout << "X-" << Cell.EdgeSet[j].TransSymbol << "->" << Cell.EdgeSet[j].EndState.StateName-1 << " ";
		}
	}
	cout << endl << "Y" << endl;



	for (int i = begin+1; i < end; i++) {
		int flag = 1;
		for (int j = 0; j < cnt; j++) {
			if (Cell.EdgeSet[j].StartState.StateName==i&&Cell.EdgeSet[j].TransSymbol == '~') {
				if (flag) {
					cout << i - 1 << " ";
					flag = 0;
				}
				cout << i - 1 << "-" << Cell.EdgeSet[j].TransSymbol << "->" << Cell.EdgeSet[j].EndState.StateName - 1 << " ";
				Cell.EdgeSet[j].StartState.StateName = 2342423;
			}
		}
		for (int j = 0; j < cnt; j++) {
			if (Cell.EdgeSet[j].StartState.StateName == i) {
				if (flag) {
					cout << i-1 << " ";
					flag = 0;
				}
				cout << i-1 << "-" << Cell.EdgeSet[j].TransSymbol << "->" << Cell.EdgeSet[j].EndState.StateName-1 << " ";
			}
		}
		if (!flag)cout << endl;

	}
}