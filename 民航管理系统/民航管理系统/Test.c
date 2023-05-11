#include "System.h"

void Test()
{
    int input = 0;
    do
    {
        printf("请选择是否进入系统：\n0.退出    1.进入系统\n");
        scanf("%d", &input);
        switch (input)
        {
        case 1:
            printf("进入系统......\n");
            System();
            break;
        case 0:
            printf("退出系统\n");
            break;
        default:
            printf("输入非法，请重新输入\n");
        }
    } while (input);
}

int main()
{
    Test_save();
    return 0;
}
