
#include "thompson.h"

//������
int main()
{
	string Regular_Expression = "(a|b)*abb";
	cell NFA_Cell;
	Regular_Expression = "(a|b)*abb";
	//��������
	input(Regular_Expression);//������Ҫ������
	//��ӡ�+��������ת��׺���ʽ
	Regular_Expression = add_join_symbol(Regular_Expression);
	//��׺ת��׺
	Regular_Expression = postfix(Regular_Expression);
	//���ʽתNFA
	NFA_Cell = express_2_NFA(Regular_Expression);
	//��ʾ
	
	Display1(NFA_Cell);

	system("pause");
	return 0;
}