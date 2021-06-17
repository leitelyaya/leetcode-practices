/*
有效数字（按顺序）可以分成以下几个部分：

一个 小数 或者 整数
（可选）一个 'e' 或 'E' ，后面跟着一个 整数
小数（按顺序）可以分成以下几个部分：

（可选）一个符号字符（'+' 或 '-'）
下述格式之一：
至少一位数字，后面跟着一个点 '.'
至少一位数字，后面跟着一个点 '.' ，后面再跟着至少一位数字
一个点 '.' ，后面跟着至少一位数字
整数（按顺序）可以分成以下几个部分：

（可选）一个符号字符（'+' 或 '-'）
至少一位数字
部分有效数字列举如下：

["2", "0089", "-0.1", "+3.14", "4.", "-.9", "2e10", "-90E3", "3e+7", "+6e-1", "53.5e93", "-123.456e789"]
部分无效数字列举如下：

["abc", "1a", "1e", "e3", "99e2.5", "--6", "-+3", "95a54e53"]
给你一个字符串 s ，如果 s 是一个 有效数字 ，请返回 true 。

 

示例 1：

输入：s = "0"
输出：true
示例 2：

输入：s = "e"
输出：false
示例 3：

输入：s = "."
输出：false
示例 4：

输入：s = ".1"
输出：true
 

提示：

1 <= s.length <= 20
s 仅含英文字母（大写和小写），数字（0-9），加号 '+' ，减号 '-' ，或者点 '.' 。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/valid-number
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define DEBUG printf
#define bool int
#define true 1
#define false 0

enum NumberElement {
  START, //开始
  OPT_FLAG, // 正负号
  POINT_FLAG, // 点
  E_FLAG, // 科学记数
  E_OPT_FLAG, // 科学记数正负号
  INTEGRAL_PART, // 整数部分
  INTEGRAL_POINT_PART, // 整数附带.部分
  FLOAT_PART, // 小数部分
  E_PART, // 科学记数部分
};

bool isNumber(char * s){
  DEBUG("string: %s\n", s);

  enum NumberElement prevElem = START;
  enum NumberElement currElem = START;
  int string_array_length = strlen(s);
  char curr;
  for (int i=0; i<string_array_length; i++) {
    // 继续检测下一个
    prevElem = currElem;

    curr = s[i];
    DEBUG("char: %c\n", curr);
    switch(s[i]) {
      case '-':
      case '+':
        // 正负号只允许在最前或者科学记数法之后
        if (prevElem == START) {
          currElem = OPT_FLAG;
        }
        else if (prevElem == E_FLAG) {
          currElem = E_OPT_FLAG;
        }
        else {
          DEBUG("It's not allow '+/-' here, char:%c.\n", curr);
          return false;
        }
        break;
      case '.':
        // 点允许在开头（允许有正负号）、整数部分之后
        if (prevElem == INTEGRAL_PART) {
          // 允许在数字之后，加一个'.'
          currElem = INTEGRAL_POINT_PART;
        }
        else if (prevElem == START || prevElem == OPT_FLAG) {
          currElem = POINT_FLAG;
        }
        else {
          DEBUG("It's not allow '.' here, char:%c.\n", curr);
          return false;
        }
        
        break;
      case 'e':
      case 'E':
        // 科学记数法E允许在整数部分、小数部分之后
        if (prevElem != INTEGRAL_PART && prevElem != INTEGRAL_POINT_PART && prevElem != FLOAT_PART) {
          DEBUG("It's not allow 'e/E' here, char:%c.\n", curr);
          return false;
        }
        currElem = E_FLAG;
        break;
      case '0':case '1':case '2':
      case '3':case '4':case '5':
      case '6':case '7':case '8':
      case '9':
        // 如果检测到数字
        switch(prevElem) {
          case START:
          case OPT_FLAG:
          case INTEGRAL_PART:
            // 在开头、符号之后，是整数；在整数部分后，也还是整数
            currElem = INTEGRAL_PART;
            break;
          case INTEGRAL_POINT_PART:
          case POINT_FLAG:
          case FLOAT_PART:
            // 在点之后，是小数部分；在小数部分后，也还是小数
            currElem = FLOAT_PART;
            break;
          case E_FLAG:
          case E_PART:
          case E_OPT_FLAG:
            // 在e之后，是科学记数法部分；在科学记数法部分后，也是科学技术法
            currElem = E_PART;
            break;
        }
        break;
      default:
        // 不允许其他字符
        DEBUG("It's not allow other char here, char:%c.\n", curr);
        return false;
    }
  }

  // 停止时的状态
  if (currElem == INTEGRAL_PART || currElem == FLOAT_PART || currElem == E_PART || currElem == INTEGRAL_POINT_PART) {
    return true;
  }
  
  DEBUG("It's not allow finish state, char:%c, prevElem:%d, currElem:%d.\n", curr, prevElem, currElem);
  return false;
}

int main(int argc, char const *argv[])
{
  char *ss[24] = {
    "2", "0089", "-0.1", "+3.14", "4.", 
    "-.9", "2e10", "-90E3", "3e+7", "+6e-1", 
    "53.5e93", "-123.456e789", "abc", "1a", "1e", 
    "e3", "99e2.5", "--6", "-+3", "95a54e53", 
    ".", "-.", "46.e3", "6.3.0"};

  for (int i=0; i<24; i++) {
    bool output = isNumber(ss[i]);
    DEBUG("result: %s=%d\n", ss[i], output);
  }
  return 0;
}

// "." => false !
// "46.e3" => true !
// "6.3.0" => false !
