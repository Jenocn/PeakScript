# PeakScript  
 

## 最新版本

版本|链接
-|-
1.2.5|[peak1.2.5.zip](https://jenocn.github.io/peak/peak1.2.5.zip)

## 介绍  

PeakScript是一个脚本语言,在第一次加载脚本时创建一组运行时的对象,之后的调用不会多次进行代码解析,从而运行效率非常好,和大多数脚本语言一样,使用动态类型,支持`number`,`bool`,`string`,`null`,`array`几种类型,支持代码块`{}`,支持常见的`if - else if - else`和`for`,`foreach`,`while`,`do - while`循环,此外还增加了一个`loop`指定次数的循环,支持`break`,`continue`,`return`控制语句,支持`function`函数,支持`try - catch - finally`, 支持常见的算术表达式和关系表达式,支持自增自减运算符  
  
---  
  
## 语句结束符     
* `\n`的换行 或 `;`分号为一条语句的结束符  
  
## 变量声明     
#### **`var`或`the`**    
用于声明一个变量  
例如:  
`var num = 0;` 表示声明一个名为num的变量,并初始化为数值0  
`var num;` 表示声明一个名为num的变量,默认值为null    
  
## 变量声明&赋值符    
#### **`set`**    
检查一个变量是否存在,不存在则声明,存在则直接赋值    
例如:    
```  
set value = 0; // 声明一个value变量  
set value = "Hello World"; // value已经存在,则直接赋值  
```  
  
## 常量声明    
#### `const` 用于声明一个常量    
可以直接作为声明符,后可跟变量声明符    
例如:  
`const num = 10;` 声明一个num常量    
`const var num = 10;`  亦可,同上    
  
## 赋值    
当变量声明之后,则可以直接赋值    
例如:`num = 99;`  
  
## 数据类型     
PeakScript使用的是动态数据类型,number,bool,string,null,array    
#### `number`类型    
常见的小数,整数和负数    
  
#### `bool`类型    
`true`或`false`两种值,提供两种别名`yes`,`no`    
  
#### `string`类型    
字符串类型,字符串类型符号**有3种**,分别为:  
上点号: **\`Hello World`**  
双引号: **"Hello World"**  
单引号: **'Hello World'**  
不同的符号之间可以嵌套  
  
#### `null`类型    
表示空    
  
#### `array`类型  
表示一个数组,数组的声明符号为`[]`中括号,数组中可以存在不同的数据类型,也可以嵌套数组  
例如:  
`var arr = [1, "Hello", false, null, [1, 2]];`  
数组可以通过下标访问:  
例如:  
`arr[0]`,`arr[4][0]`  
数组下标可以是任何返回整数的表达式  
例如:  
`var i = 0;` `arr[i];` `arr[1 + 1];`   
  
## 算术表达式    
常规的`+`,`-`,`*`,`/`,`%`,`(`,`)`  
  
## 关系表达式    
常规的`>`,`>=`,`<`,`<=`,`==`,`!=`,  
  
## 逻辑表达式    
常规的`||`,`&&`,提供两种别名`and`,`or`  
  
## 自赋值表达式    
常规的`+=`,`-=`,`*=`,`/=`,`%=`    
  
## 自增,自减运算符    
`++`,`--`,与c++一样,符号前置时返回计算后的值,符号后置时返回计算前的值  

## 非运算符  
`!`,非运算符后可跟表达式或变量,返回这个表达式的非值
  
## 代码块    
与大多数语言一样,在当前作用域下新建一个**作用域空间**,代码块中可以访问上面的变量和函数,代码块中的变量遵循**就近原则**  
例如:  
```  
var num = 10;  
{  
    var num = 9;  
    echo num; // 9  
}  
echo num; // 10  
```  
代码块`{`,`}`也可以使用关键字`begin`,`end`表示  
  
## 条件语句    
`if`,`else if`,`else`    
if后可跟表达式,表达式可以有`(`,`)`,也可以不写,执行的代码若只有一条语句可以不写大括号`{`,`}`  
例如:  
```  
if (true) {  
} else if (true) {  
} else {  
}  
```  
  
## 循环语句    
#### `loop`循环    
指定次数的循环    
例如:  
```  
loop(3) {  
    echo "Hello"; // 将会循环3次    
}  
```  
支持得到当前的下标:  
```  
loop(i in 3) {  
    echo i; // 将会打印 0 1 2  
}  
```  
跟if一样,可以有`(`,`)`,也可以不写,后面只有一条语句可以不写大括号(后面的循环语句都一样)    
  
#### `while`循环    
常规的while循环,与c++一样    
```  
var num = 0;  
while (num < 10) {  
	// todo...  
	num++;  
}  
```  
  
#### `do - while`循环    
常规的,先执行一遍,然后判断条件    
例如常见用法:  
```  
do {  
	// todo...  
} while (false);  
```  
  
#### `foreach`循环    
此循环只可用在数组上  
例如:  
```  
var arr = [1, 2, 3, 4];  
foreach(var item in arr) {  
	echo item; // 遍历输出    
}  
```  
此循环可以简写为for:  
```  
for (item in arr) {  
	echo item; // 遍历输出  
}  
```  
  
#### `for`循环  
常规的,例如:  
```  
for (var i = 0; i < 10; ++i) {  
	echo i; // 0 ~ 9  
}  
```  
  
#### `break`和`continue`  
循环中遇到`break`则直接跳出当前循环,遇到`continue`则立即执行下一次循环    
  
#### 语句的简写    
例如:  
```  
var arr = [1, 2, 3];  
for item in arr echo item;  
loop i in 3 echo i;  
```  
  
## 函数    
函数声明,前置声明符号`function`可写可不写  
例如声明一个返回两个数总和的函数:  
```  
sum(a, b) {  
	return a + b;  
}  
var ret = sum(1, 2); // 返回3  
```  

支持函数重载:  
```
sum(a, b, c) {
	return a + b + c;
}
```

## 异常处理      
```  
try {  
	// 执行语句  
} catch {  
	// 若try当中存在错误的语句,则执行  
} finally {  
	// 无论如何最后都会执行  
}  
```  
  
## 注释    
单行注释: `//`或`#`  
多行注释:`/*`与`*/`之间  

## 内置函数   
#### echo命令    
用于打印变量的值或者函数的说明    
例如:
`echo "Hello World"; // Hello World`  

#### print函数  
同`echo`但print作为一个函数存在 
例如:  
`print("Hello"); // Hello`   

#### type函数  
返回当前参数数值类型的字符串  
例如:
`type(""); // 返回 string`  
`type(0); // 返回 number`  
`type(true); // 返回 bool`  
`type(null); // 返回 null`  
`type([1]); // 返回 array`  
`type(print); // 返回 function`  

#### is_xxx函数  
判断一个变量是否为某个类型的值  
例如:   
`is_null(); // 返回是否为null`   
`is_string(); // 返回是否为string`   
`is_number(); // 返回是否为number`   
`is_bool(); // 返回是否为bool`   
`is_array(); // 返回是否为array`   
`is_function(); // 返回是否为function`   

