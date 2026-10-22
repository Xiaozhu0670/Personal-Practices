#include <stdio.h>
int determine(char smb, int lvl);
int reg_cal(char smb[3], int num[3], int n);

int main(){
    int row;//计算有多少行
    int result[100000];//用来记录不同式子的结果

    scanf("%d", &row);

    for(int i = 0; i < row; i++){
        int num[3], lvl[3]; //num和lvl分别记录数字大小和符号级别顺序
        char smb[3] = {'n', 'n', 'n'}; //初始化为'n'，表示未输入

        int equal = 1;//检测是否读取到'='

        for(int j = 0; j < 2; j++){
            scanf("%d%c", &num[j], &smb[j]);//读取正整数和四则符号,因为先读数字,所以永远不会出现负数读取
            lvl[j] = determine(smb[j], lvl[j]);

            if(smb [j] == '='){
                switch(j){
                    case 0://如果只有一个数字,那么直接输出结果
                        result[i] = num[0];
                        equal = 0;
                        break;
                    case 1://如果只有两个数字,那直接运用reg_cal计算结果并且返回
                        result[i] = reg_cal(smb, num, 0);
                        equal = 0;//让其跳过while循环，因为在第一或第二个式子便检测到'='
                        break;
                }
            }
        }

        
        if(equal){
        //在读取两次之后,若未读取到'=',而此时只剩下smb、num的第三个元素未读取
            while (true){
                if(equal){
                        scanf("%d%c", &num[2], &smb[2]);
                       lvl[2] = determine(smb[2], lvl[2]);
                }
        
                if(smb[2] == '='){
                    equal = 0;
                }//读取到等号,equal = 0, 使得while下的第一个if语句不在进行, 防止出问题

                if(lvl[0] < lvl[1]){//当smb[1]运算符优先级大于smb[0]时
                    num[1] = reg_cal(smb, num, 1);
                    smb[1] = smb[2];
                    lvl[1] = lvl[2];//将结果赋予num[1]的位置,并将运算的字符与优先级前移,即将smb[2]与lvl[2]赋值给smb[1]和lvl[1]
                }
                else if(lvl[0] >= lvl[1]){
                    num[0] = reg_cal(smb, num, 0);
                    for(int j = 0; j < 2; j++){//将运算的字符与优先级均迁移给同一个数组的前一个元素位置
                        smb[j] = smb[j + 1];
                        lvl[j] = lvl[j + 1];
                    }
                    num[1] = num[2];//单独写,防止num[0]被num[1]覆盖
                }

                if(smb[1] == '='){//此时已迭代到只有两个数字进行四则运算的情况
                    result[i] = reg_cal(smb, num, 0);
                    break;
                }
            }
    }

    }

    for(int i = 0; i < row; i++, printf("\n")){
        printf("%d", result[i]);
    }

    return 0;
}



int determine(char smb, int lvl)//计算smb里面对应运算符号的级别大小
{
    if(smb == '+' || smb == '-'){
        lvl = 1;
    }
    else if(smb == '*' || smb == '/'){
        lvl = 2;
    }
    else if(smb == '='){
        lvl = 0;
    }
    return lvl;
}

int reg_cal(char smb[3], int num[3], int n){//自动计算四则运算并且返回四则结果
    int total;
    switch(smb[n]){
        case '+':
            total = num[n] + num[n + 1];
            break;
        case '-':
            total = num[n] - num[n + 1];
            break;
        case '*':
            total = num[n] * num[n + 1];
            break;
        case '/':
            total = num[n] / num[n + 1];
            break;
    }
    return total;
}

/*

思路总结:
对于式子1+2=,我们可以直接计算1+2的值
而对于式子1+2*3=,我们可以先按照数字与四则运算符的组合来确定,
即拆成'1+','2*','3='这三部分来计算,
又因为'+'的优先级小于'*',那我们应该先计算'2*3',
所以我们使用三个数组来补全两个数组时会出现3无法被同时识别的问题.
而在进行乘法之后我们可以把结果6赋值给数组num[1],'='赋值给smb[1],'2'赋值给lvl[1].
这样子我们就把"1+2*3="化简为"1+6=",此时便是最简单的四则运算.
若大于四个数字,则可以按照116行到117行的步骤来化简成3个数的式子,
最后再化简成2个数的式子.
这蕴含了递归思想.

*/
