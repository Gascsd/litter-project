package com.sxt;

/**
 * 初始化地雷
 */
public class BottomRay {

    //存放坐标
    static int[] rays = new int[GameUtil.RAY_MAX * 2];
    //地雷坐标
    int x,y;//创建变量用于保存坐标
    //是否放置
    boolean isPlace = true;//标志生成的位置是否合法

    //生成雷
    void newRay() {
        for (int i = 0; i < GameUtil.RAY_MAX * 2; i = i + 2) {
            //随机生成坐标
            x= (int) (Math.random() * GameUtil.MAP_W + 1);//1-12
            y= (int) (Math.random() * GameUtil.MAP_H + 1);

            //判断坐标是否合法
            for (int j = 0; j < i; j += 2) {
                if(x == rays[j] && y == rays[j+1]) {
                    i = i - 2;
                    isPlace = false;
                    break;
                }
            }
            //如果坐标合法就把坐标放入数组
            if(isPlace){
                rays[i] = x;
                rays[i + 1] = y;
            }
            isPlace = true;//释放标记合法状态的变量
        }

        for (int i = 0; i < GameUtil.RAY_MAX * 2; i = i + 2) {
            GameUtil.DATA_BOTTOM[rays[i]][rays[i + 1]] = -1;//把所有合法的位置的雷填充进去
        }
    }
}
