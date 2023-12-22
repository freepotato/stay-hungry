// 后缀四则运算计算器
// 1. 读入中缀表达式, 转化为后缀表达式
// 2. 将后缀表达式计算为结果
// 步骤一: 要求一个 运算符 栈和一个 输出队列
//  对于操作数, 直接添加到输出队列
//  对于运算符: 
//      栈为空, 压入
//      栈不为空, 如果高于栈顶优先级, 压入
//      否则依次弹出栈顶, 直到 栈为空 或 遇到更低优先级符号
//  左括号, 压入
//  右括号, 依次弹出栈顶直到遇到左括号
// 步骤二: 要求一个 数字 栈
//  对于操作数, 压入栈
//  对于运算符, 弹出顶部两数进行计算, 入队

#include <iostream>
#include <stack>
#include <queue>
#include <string>
#define OPERATOR -1
#define NUMBER 0
#define LEFTCIRCLE 2
#define RIGHTCIRCLE 3
#define PLUS 1
#define MINUS 2
#define MULTIPLY 3
#define DEVIDE 4


// std::string:
// 属性：

// size()： 返回字符串中字符的数量。
// length()： 返回字符串的长度。
// empty()： 判断字符串是否为空。
// c_str()： 返回指向以 null 结尾的字符数组的指针。
// 方法：

// operator[]： 通过索引访问字符串中的字符。
// at()： 安全地通过索引访问字符串中的字符，会进行范围检查。
// append()： 将字符串附加到另一个字符串的末尾。
// substr()： 返回子字符串。
// find()： 在字符串中查找子字符串。
// replace()： 替换字符串中的一部分。
// erase()： 删除字符串的一部分。

typedef int status;
std::string mid2right(const std::string& mid);
double calculate(const std::string& right);
status analysis(const char& x);
int prior(const char& x);
double AddDigit(const std::string& x, int& pos);


// 中缀转后缀
std::string mid2right(const std::string& mid)
{
    // 初始化运算符栈和输出队列
    std::stack<char> charStack;

    std::string right;
    // 步骤一
    for(int i = 0; i < mid.size(); i++){
        std::string unit;
        // 依次处理
        if(isdigit((int)mid[i])){
            unit = std::to_string(AddDigit(mid, i));
            right = right + unit + " ";
        }else if(analysis(mid[i] == OPERATOR)){ 
            if(charStack.empty()){ // 栈为空, 压入运算符
                charStack.push(mid[i]);
            }else{ // 栈不为空
                while(prior(mid[i]) > prior(charStack.top())){
                    right += charStack.top();
                    charStack.pop();
                }
                charStack.push(mid[i]);
            }
        }else if(analysis(mid[i] == LEFTCIRCLE)){ // 左括号, 压入
            charStack.push(mid[i]);
        }else if(analysis(mid[i] == RIGHTCIRCLE)){
            while(analysis(charStack.top() != LEFTCIRCLE)){ // 右括号, 依次出栈直到左括号
                right += charStack.top();
                charStack.pop();
            }
            charStack.pop();
        }
        
    }
    return right;
}

// 计算结果
double calculate(const std::string& right)
{
    // 初始化
    std::stack<double> numStack;
    double res = 0;
    
    // 步骤二
    for(int i = 0; i < right.size(); i++){
        int l, r, num;
        // if(isdigit((int)right[i])){ // 数字则压入
        //     numStack.push((double)(right[i] - '0'));
        // }
        if(isdigit((int)right[i])){ // 数字则压入
            numStack.push(static_cast<double>(std::stoi(right.substr(i))));
            // Move i to the end of the number
            i += right.substr(i).find_first_not_of("0123456789") - 1;
        }else{
            if (numStack.size() >= 2) {
            r = numStack.top();
            numStack.pop();
            l = numStack.top();
            numStack.pop();
            }
            switch (right[i])
            {
            case '+': num = r + l; break;
            case '-': num = r - l; break;
            case '*': num = r * l; break;
            case '/': num = r / l; break;
            default: num = 0; break;
            }
            numStack.push((double)(right[i] - '0'));      
        }
        if(numStack.size() == 1){
            res = numStack.top();
            numStack.pop();
        }
    }

    return res;
}


// 判断符号类型: 数字, 运算符, 左、右括号
status analysis(const char& x)
{
    if(std::isdigit(x) == 0){
        return NUMBER;
    }else if(x == '('){
        return LEFTCIRCLE;
    }else if(x == ')'){
        return RIGHTCIRCLE;
    }else if(x == '+' || x == '-' || x == '*' || x == '/'){
        return OPERATOR;
    }
    return -1;
}

int prior(const char& x)
{
    if(analysis(x) == OPERATOR){
        if(x == '+' || x == '-'){
            return 0;
        }else{
            return 1;
        }
    }
    return -1;
}

double AddDigit(const std::string& x, int& pos)
{
    int num = 0;
    while(isdigit(x[pos])){
        num = num * 10 + (x[pos] - '0');
        pos++;
    }
    return num;
}

status DefineOperator(const char& x){
    if(x == '+'){
        return PLUS;
    }else if(x == '-'){
        return MINUS;
    }else if(x == '*'){
        return MULTIPLY;
    }else if(x == '/'){
        return DEVIDE;
    }
    return 0;
}
int main()
{
    std::string mid;
    double res;
    std::cout << "Enter a string:" << std::endl;
    std::getline(std::cin, mid);
    std::string right = mid2right(mid);
    res = calculate(right);
    std::cout << res;
    return 0;
}