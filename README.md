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
- 遍历字符串
## 4.构造NFA
