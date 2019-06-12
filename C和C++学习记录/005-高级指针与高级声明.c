/*
** from 《C和指针》 学习
** @author: geekac
*/

#include<stdio.h>
#include<stdlib.h>

int f(int a, float b){
    return 1;
}

int main(){

    ///【要点】理解一个高级声明, 抓住优先级关系: () > [] > */&  [注:]()表示函数调用或者聚组
    /*
        从变量名开始, 看左右两边符号优先级进行结合！

        const关键字:  先忽略类型名（编译器解析的时候也是忽略类型名）
                      `近水楼台先得月`，离谁近就修饰谁。
                      const不能单独修饰*, 形如：`* const p` 一定是修饰p

        另一种理解：  变量先和运算符号结合, const永远只修饰后面的内容
                      比如char const *ptr2; const修饰(*ptr2), (*ptr2)是char类型
    */


    /****   0. 指针常量和常量指针  ****/
    const char *ptr1;    //char型【常量指针】
    char const *ptr2;    //等价于上面
    char* const ptr3;    //char型【指针常量】
    /*
    Explanation/解释：
        (1) 区分叫法的方法
                xx指针：  指向xx的指针
                常量指针：指向常量的指针

                xx常量：不可改变内容的常量(对于指针来说, 是所指向的地址不可改变)

        (2) const关键字
                const修饰 `数组/数组指针` 时, 表示数组的所有元素都是只读的！
                const修饰一个变量，一定要给这个变量初始化值，若不初始化，后面就无法初始化。

       【注意】常量指针是说不能通过这个指针改变变量的值，但是可以通过其他引用来改变变量的值
                   int num = 5;
                   const int *p = &num;
                   num = 6;
    */


    /****   1. 命令行参数  int main(int argc, char const *argv[])  ****/
    char const *argv[2];
    /*
    Explanation/解释：
        []优先级大于*, 因此argv是一个数组
        数组元素的类型是指针, 指针指向char const类型。
        因此argv是一个`指向字符常量的指针数组`

       【注】作为函数参数时, 无需指定数组长度, 由数组名退化成指针类型！
    */


    /****   2. 指针数组和数组指针  ****/
    int   *p1[10];   //指针数组
    int (*p2)[10];   //数组指针
    /*
    Explanation/解释：
        由于聚组(), p2先和*结合, 说明p2是一个指针
        [10]说明p2指向的是长度为10的数组, 数组元素的类型是int型
    */


    /****   3. 函数指针  ****/
    int *_fun(int, float);
    int (*pf)(int, float) = &f;
    /*
    Explanation/解释：
        _fun先和函数调用(int, float)结合, 表明_fun是一个函数, 参数类型是int, float
        int*是函数的返回值类型

        由于第一个括号()聚组, pf和*结合, 表明pf是一个指针
        第二个括号(int, float)函数调用, 表明指针指向的是函数, 因此pf是函数指针
        函数的参数类型是int,float 返回值类型是int.

       【非常重要】函数名是个什么？
            函数名在被使用时, 总是由编译器把它转换成函数指针！
            &操作符只是显式地说明了编译器隐式执行的任务。
            int ans;
            ans = f(1, 2.0);
            ans = (*pf)(1, 2.0); //多此一举, 编译器执行函数调用前, 还会转换成指针
            ans = pf(1, 2.0);    //函数调用的本质

           【要点】函数调用前, 会隐式地将函数名转换成函数指针！！！(记住本质)
           【补充】通常所说的xx是一个函数, 即xx是函数名。区别于xx是一个函数指针的说法！


       【注意】函数指针 最常见的两个用途：
            (1) 回调函数(callback function)
            (2) 转换表(jump table)：就是一个函数指针数组
                    #define enum {ADD, SUB, MUL, ...} OPTYPE
                    //等价于：#define ADD 0 #define SUB 1...
                    double (*oper_func[])(double, double) = {add, sub, mul, div, ...}//函数名
                    result = oper_func[oper](opr1, opr2);//oper in OPTYPE

       【重要】 C语言函数只能返回标量, 不能返回数组！
                C语言不支持在函数中定义函数！！

    */

    /****   5. 错误示例  ****/
    int fun()[];    //先和()结合, fun是个函数, 函数返回类型是int数组, 错误！
    int arf[]();    //先和[]结合, arf是个数组, 数组元素的类型是返回值为int的函数, 错误！
                    //这是因为, 元素的类型是函数, 不能保证不同元素的长度相同。==> 数组元素必须具有相同的长度！


    /****   6. 更多实例  ****/
    ///ANSI C要求使用完整的函数原型, 使得声明更加明确。
    int *(*g[])(int,float);
    /*  g先和[]结合, 表明g是一个数组, 数组的类型是指针;函数调用(int,float)表明指针指向函数
    **  int*表明函数的返回类型是整型指针。因此, g是一个`指向返回值为int指针`的函数指针数组。
    */

    int *ab();    //ab是函数, 不是函数指针！区别于 `int (*ab)();`

    int *(*abc())();
    /*  abc先和()结合, 说明abc是一个函数; abc前面的*表明函数返回值类型是指针;
    **  (*abc())解析完成, 看做整体！然后和后面的函数调用()结合, 说明指针指向的是函数
    **  int*是指针指向函数的返回值类型。
    **  所以abc是 返回值为 “返回值为int型指针的函数指针” 的函数
    */

    int (**(*abcd)())();
    /*  abcd先和*结合, 说明abcd是一个指针; 然后(*abcd)和后面的()结合, 说明指针指向函数, abcd是函数指针
    **  **说明函数的返回类型是指针的指针
    **  (**(*abcd)())和后面的()结合, 说明指针的指针指向的是函数, 并且返回值类型是int
    **  所以abcd是 返回值为 “返回值为int的函数指针的指针” 的函数指针！
    */



    /****   999. typdef自定义高级类型  ****/
    typedef int tArray[10];    tArray arr;//arr是含有10个元素的整型数组
    typedef int Matrix[5][5];  Matrix marr;//marr是5×5的整型二维数组
    typedef char *pCharArray[5]; pCharArray parr_c;  //parr_c是char型指针数组类型，数组的长度为5
    typedef int(*multiPIntArr)[5]; multiPIntArr piarr; //piarr是指向int的二维数组的指针类型
    typedef int (*MYFUN)(int, int); //MYFUN是函数指针类型！
    //【总结】
    //在高级声明前面加上typedef 则高级声明的变量名称为 对应的类型声明符号用于声明该类型的变量。

    return 0;
}
