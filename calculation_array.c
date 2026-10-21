#include <stdio.h>
int determine(char smb, int lvl);
int reg_cal(char smb[3], int num[3], int total, int n);

int main(){
    int row;
    int result[100000];

    scanf("%d", &row);

    for(int i = 0; i < row; i++){
        int num[3], lvl[3]; 
        char smb[3] = {'n', 'n', 'n'}; //初始化为'n'，表示未输入
        int total = 0;
        int equal = 1;

        for(int j = 0; j < 2; j++){
            scanf("%d%c", &num[j], &smb[j]);
            lvl[j] = determine(smb[j], lvl[j]);

            if(smb [j] == '='){
                switch(j){
                    case 0:
                        result[i] = num[0];
                        return 0;
                    case 1:
                        result[i] = reg_cal(smb, num, total, 0);
                        return 0;
                }
            }
        }

        while (true){
            if(equal){
                scanf("%d%c", &num[2], &smb[2]);
                lvl[2] = determine(smb[2], lvl[2]);
            }
        
            if(smb[2] == '='){
                equal = 0;
            }

            if(lvl[0] < lvl[1]){
                num[1] = reg_cal(smb, num, total, 1);
                smb[1] = smb[2];
                lvl[1] = lvl[2];
            }
            else if(lvl[0] >= lvl[1]){
                num[0] = reg_cal(smb, num, total, 0);
                for(int j = 0; j < 2; j++){
                    smb[j] = smb[j + 1];
                    lvl[j] = lvl[j + 1];
                }
                num[1] = num[2];
            }

            if(smb[1] == '='){
                result[i] = reg_cal(smb, num, total, 0);
                break;
            }
        }

    }

    for(int i = 0; i < row; i++, printf("\n")){
        printf("%d", result[i]);
    }

    return 0;
}



int determine(char smb, int lvl)
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

int reg_cal(char smb[3], int num[3], int total, int n){
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