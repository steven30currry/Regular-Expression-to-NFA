# ����ɭ������ʽתNFA
## 1. ״̬����
- ���ȶ����edge��������ʼ�����ֹ��
```cpp
struct edge
{
	state StartState;
	state EndState;
	char TransSymbol;
};

```
- �����NFA��Ԫ��һ���߼����Լ���Ԫ����ʼ��β�㼴��ȷ��һ����Ԫ
```cpp
struct cell
{
	edge EdgeSet[MAX];
	int EdgeCount;
	state StartState;
	state EndState;
};
```
## 2. �����봮���ϱ�ǡ�+����Ϊ������׺ת��׺�̵�
+ �������봮����λ��λ�����ж�
```cpp
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
```
## 3. ��׺���ʽת��׺���ʽ
- �����ַ���ջ��ջ�����ȼ�
- �����ַ���
## 4.����NFA
