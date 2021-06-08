# 汤普森法正规式转NFA
## 1. 状态定义
- 首先定义边edge，包括起始点和中止点
```cpp
struct edge
{
	state StartState;
	state EndState;
	char TransSymbol;
};

```
- 随后定义NFA单元，一个边集，以及单元的起始结尾点即可确定一个单元
```cpp
struct cell
{
	edge EdgeSet[MAX];
	int EdgeCount;
	state StartState;
	state EndState;
};
```
## 2. 给输入串加上标记‘+’，为后面中缀转后缀铺垫
+ 遍历输入串，两位两位进行判断
```cpp
for (int i = 0; i < length - 1; i++)
	{
		first = add_string.at(i);
		second = add_string.at(i + 1);
		return_string[return_string_length++] = first;
		//要加的可能性如ab 、 *b 、 a( 、 )b 等情况
		//若第二个是字母、第一个不是'('、'|'都要添加
		if (first != '('&&first != '|'&&is_letter(second))
		{
			return_string[return_string_length++] = '+';
		}
		//若第二个是'(',第一个不是'|'、'(',也要加
		else if (second == '('&&first != '|'&&first != '(')
		{
			return_string[return_string_length++] = '+';
		}
	}
```
## 3. 中缀表达式转后缀表达式
- 定义字符的栈内栈外优先级
- 开始遍历字符串
  - 遇到操作数直接输出
  - 遇到操作符，如果当前字符的栈外优先级大于栈顶元素的栈内优先级，直接压入该元素。否则，一直出栈直到栈顶元素优先级小于该字符
  - 由于左括号一遇到就入栈且当且仅当扫到右括号才出栈的特性，左括号的栈外优先级最高，栈内优先级最低
   
## 4.构造NFA
- 遇到普通字符：直接构造一个cell，然后cell里面包含一条边，边包含两个状态，边的transymbol就是普通字符，最后压入栈。构造一个cell单元是构造NFA中的最基本操作，后续的操作都是在已经构造的cell的基础上，用栈进行合并
- 遇到a|b：新构造两个状态u，v，让u通过a指向b，同理b也如此。
- 遇到ab+：合并a的终止状态和b的起始状态，具体就是让以b的起始状态为起始的每一条边转移到a的终止状态上
- 遇到a*
  - 合并a的起始和终止两个点
  - 构造两个新状态，a放中间，连线是ε