//这是一个中缀转后缀的c语言，无使用链表。
//This is a C program, which converts infix to postfix without using linked lists.
#include <stdio.h>

int symbol(int i, int n, int b, int arr[n], char smb[n]);
int foursymbol(int i, int total, char str[i]);
void test(int n, int b, int arr[n], char smb[n]);

int main(){
    int i = 0;//识别字符串
    int c;
    char str[10000];//识别字符串

    int b = 0;
    int n = 0;
    int arr[100000];
    char smb[100000];//以上用于四则运算符

    printf("please write the Infix Expression:");
    do{
        c = getchar();
        str[i] = (char)c;
        if (str[i] != ' '){
            i++;
        }
    }//no problem
    while((char)c != '\n');

    str[i-1] = 'F';

    int total = i-1;
    i = 0;
 
    while(i <= total){//后端,从左往右
        //识别到是数字
        if('0' <= str[i] && str[i] <= '9'){
            putchar(str[i]);

            if(str[i+1] == '+' || str[i+1] == '-' || str[i+1] == '*' || str[i+1] == '/' || str[i+1] == '(' || str[i+1] == ')' || str[i+1] == 'F'){
                putchar(' ');
            
            }
        }
        else{//识别到是运算符
            if(str[i] == '+' || str[i] == '-'){
                arr[n] = 1;
                smb[n] = (char)str[i];
            }
            else if(str[i] == '*' || str[i] == '/'){
                arr[n] = 2;
                smb[n] = (char)str[i];
            }
            else if(str[i] == '('){
                i = foursymbol(i, total, str);
            }

            b = symbol(i, n, b, arr, smb);

           if(0 < arr[n] && arr[n] < 5){//防止出bug，之前老是莫名n++，猎奇哈。
            n++;
           }
        }
        i++;
    }

    if (arr[n] == 0 && arr[n-1] != 0){//感觉没什么用，但当时已经写下来了，能跑就没删if语句
        int a = n - 1; 
        int c = b;//记录当前已经输入了多个四则符号
        while(b < n){//b代表的是已经输入的四则运算符的个数，n代表是总的四则运算符的个数，若b < n,说明还有四则运算符没有输入。
            if(arr[a] > 0 && arr[a] < 3){//保证没有左右括号
                
                putchar(smb[a]);
                if(a != c){
                    putchar(' ');
                }
            }
            a--;
            b++;
        }
    }
    
    printf("\n");
    return 0;
}


//the first function,用于检验输出'（）'以外的运算符
int symbol(int i, int n, int b, int arr[n], char smb[n]){
    if (arr[n-1] >= arr[n] && arr[n] != 0){//判断栈顶的运算符的优先级，与入栈的优先级
        int times = b;
        int a = n-1;
        if(arr[a] < 3 && arr[a] > 0){//保证没有'（'与'）'出现
            while(a > times-1){//times-1是为标记栈中已经输入的四则符号
                
                putchar(smb[a]);
                putchar(' ');
                a--;
                b++;
            }
        }
    }
    return b;
}
//the end of first function

//the second function,用于'()'中的运算符计算
int foursymbol(int i, int total, char str[i]){//识别运算符号
    int b = 0;    
    int n = 0;
    int arrs[100000];
    char smbs[100000];

    while(i <= total){//后端,从左往右
        //识别到是数字
        if('0' <= str[i] && str[i] <= '9'){
            putchar(str[i]);

            if(str[i+1] == '+' || str[i+1] == '-' || str[i+1] == '*' || str[i+1] == '/' || str[i+1] == '(' || str[i+1] == ')'){
                putchar(' ');
            
            }
        }
        else{//识别到是运算符
            if(str[i] == '+' || str[i] == '-'){
                arrs[n] = 1;
                smbs[n] = (char)str[i];
            }
            else if(str[i] == '*' || str[i] == '/'){
                arrs[n] = 2;
                smbs[n] = (char)str[i];
            }
            else if(str[i] == ')'){//识别是),赋值为4
                arrs[n] = 4;
                smbs[n] = (char)str[i];
            }

            b = symbol(i, n,b,arrs,smbs);

            if (arrs[n] == 4){

                if (arrs[n-1] != 0){//感觉没什么用，但当时已经写下来了，能跑就没删if语句
                    int a = n - 1; 
                    while(b < n){//b代表的是已经输入的四则运算符的个数，n代表是总的四则运算符的个数，若b < n,说明还有四则运算符没有输入。
                        if(arrs[a] > 0 && arrs[a] < 3){//保证没有左右括号
                            if(n - b == 1){
                                putchar(smbs[a]);
                            }
                            else if(n - b != 1){
                                if('0' <= str[i-1] && str[i-1] <= '9'){
                                }
                                else{
                                    putchar(' ');
                                }
                                putchar(smbs[a]);
                            }
                            if(str[i+1] != '\n'){
                                putchar(' ');
                            }
                        }
                        a--;
                        b++;
                    }
                }
                break;
            }
            
            if(0 < arrs[n] && arrs[n] < 5){//防止出bug，之前老是莫名n++，猎奇哈。
            n++;
           }
        }
        i++;
    }



    return i;
}
//the end of second fuction

//the thrid function
void test(int n, int b, int arr[n], char smb[n]){
    if (arr[n] == 0 && arr[n-1] != 0){//感觉没什么用，但当时已经写下来了，能跑就没删if语句
        int a = n - 1; 
        while(b < n){//b代表的是已经输入的四则运算符的个数，n代表是总的四则运算符的个数，若b < n,说明还有四则运算符没有输入。
            if(arr[a] > 0 && arr[a] < 3){//保证没有左右括号
                putchar(' ');
                putchar(smb[a]);
            }
            a--;
            b++;
        }
    }
}
//the end of third function
