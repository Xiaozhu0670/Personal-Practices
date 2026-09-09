//test：12+3*2*(1+4)+5/4+1
#include <stdio.h>

int symbol(int n, int b, int arr[n], char smb[n]);

int main(){
    int i = 0;//识别字符串
    int c;
    char str[10000];//识别字符串

    int left = -1;
    //int a = 0;
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
                arr[n] = 3;
                smb[n] = (char)str[i];
            }
            else if(str[i] == ')'){//识别是),赋值为4
                arr[n] = 4;
                smb[n] = (char)str[i];
            }
            
            if (arr[n] == 3){//识别到'('
                left = n;
                b+=2;//跳过'('前的四则符号，并规定已经输入的四则符号+2.来避免将'('输出。
            }
            
            b = symbol(n,b,arr,smb);

            if (arr[n] == 4){
                putchar(smb[left - 1]);//当有括号出现时，前面已经保证了'（）'中的四则符号全部输出，只缺少了'（'前的四则符号。
            }

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
    printf("\n");
    

    return 0;
}

int symbol(int n, int b, int arr[n], char smb[n]){
    if (arr[n-1] >= arr[n] && arr[n] != 0){//判断栈顶的运算符的优先级，与入栈的优先级
        int times = b;
        int a = n-1;
        while(a > times-1){//保证没有'（'与'）'出现
            if(arr[a] < 3 && arr[a] > 0){//times-1是为标记栈中已经输入的四则符号，！！！这里也是修改的地方，将while与if互换了位置。
                putchar(smb[a]);
                putchar(' ');
            }
            a--;
            b++;
            
        }
    }
    return b;
}
