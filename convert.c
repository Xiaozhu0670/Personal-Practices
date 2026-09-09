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
    while((c = getchar()) != '\n'){
        str[i] = (char)c;
        i++;
    }//no problem
    str[i] = 'F';//基本没啥用，当时还以为有用

    int total = i;
    i = 0;
 
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
        while(b < n){//b代表的是已经输入的四则运算符的个数，n代表是总的四则运算符的个数，若b < n,说明还有四则运算符没有输入。
            if(arr[a] > 0 && arr[a] < 3){//保证没有左右括号
                putchar(' ');
                putchar(smb[a]);
            }
            a--;
            b++;
        }
    }
    

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
    int arr[100000];
    char smb[100000];

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
                arr[n] = 1;
                smb[n] = (char)str[i];
            }
            else if(str[i] == '*' || str[i] == '/'){
                arr[n] = 2;
                smb[n] = (char)str[i];
            }
            else if(str[i] == ')'){//识别是),赋值为4
                arr[n] = 4;
                smb[n] = (char)str[i];
            }

            b = symbol(i, n,b,arr,smb);

            if (arr[n] == 4){

                if (arr[n-1] != 0){//感觉没什么用，但当时已经写下来了，能跑就没删if语句
                    int a = n - 1; 
                    while(b < n){//b代表的是已经输入的四则运算符的个数，n代表是总的四则运算符的个数，若b < n,说明还有四则运算符没有输入。
                        if(arr[a] > 0 && arr[a] < 3){//保证没有左右括号
                            if(n - b == 1){
                                putchar(smb[a]);
                            }
                            else if(n - b != 1){
                                putchar(' ');
                                putchar(smb[a]);
                            }
                            if(str[i+1] != NULL){
                                putchar(' ');
                            }
                        }
                        a--;
                        b++;
                    }
                }
                break;
            }
            
            if(0 < arr[n] && arr[n] < 5){//防止出bug，之前老是莫名n++，猎奇哈。
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
