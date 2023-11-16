package com.sxt;

import java.awt.*;

/**
 * 顶层地图类
 * 绘制顶层组件
 * 判断逻辑
 */
public class MapTop {

    //格子位置的坐标
    int temp_x;
    int temp_y;

    //重置游戏
    void reGame() {
        for (int i = 1; i <= GameUtil.MAP_W; i++) {
            for (int j = 1; j <= GameUtil.MAP_H; j++) {
                GameUtil.DATA_TOP[i][j] = 0;//顶层数组重置
            }
        }
    }

    //判断逻辑
    void logic() {
        //初始化格子位置坐标为0
        temp_x = 0;
        temp_y = 0;
        if(GameUtil.MOUSE_X > GameUtil.OFFSET && GameUtil.MOUSE_Y > 3 * GameUtil.OFFSET) {//防止点击上方和左方也翻开的情况
            temp_x = (GameUtil.MOUSE_X - GameUtil.OFFSET) / GameUtil.SQUARE_LENGTH + 1;
            temp_y = (GameUtil.MOUSE_Y - GameUtil.OFFSET * 3) / GameUtil.SQUARE_LENGTH + 1;
        }

        if(temp_x >= 1 && temp_x <= GameUtil.MAP_W && temp_y >= 1 && temp_x <= GameUtil.MAP_H) {//点击的位置合法
            if(GameUtil.LEFT) {//左键点击
                //覆盖，则翻开
                if(GameUtil.DATA_TOP[temp_x][temp_y] == 0) {
                    GameUtil.DATA_TOP[temp_x][temp_y] = -1;
                }
                spaceOpen(temp_x,temp_y);//递归翻开
                GameUtil.LEFT = false;//释放左键状态
            }
            if(GameUtil.RIGHT) {//右键点击
                //覆盖则插旗
                if(GameUtil.DATA_TOP[temp_x][temp_y] == 0) {
                    GameUtil.DATA_TOP[temp_x][temp_y] = 1;//修改顶层状态
                    GameUtil.FLAG_NUM++;//修改当前棋盘上的旗子数
                }
                //插旗则取消
                else if(GameUtil.DATA_TOP[temp_x][temp_y] == 1) {
                    GameUtil.DATA_TOP[temp_x][temp_y] = 0;//修改顶层状态
                    GameUtil.FLAG_NUM--;//修改当前棋盘上的旗子数
                }
                //如果点击到的是数字，就递归翻开
                else if(GameUtil.DATA_TOP[temp_x][temp_y] == -1) {
                    numOpen(temp_x, temp_y);//递归翻开
                }
                GameUtil.RIGHT = false;//释放鼠标右键状态
            }
        }
        boom();//判断是否输（雷是否炸了）
        victory();//判断是否赢
    }
    //数字翻开
    void numOpen(int x, int y) {
        int count = 0;//记录旗子数
        if(GameUtil.DATA_BOTTOM[x][y] > 0) {
            //遍历底层数组，记录旗子数量
            for (int i = x-1; i <= x+1; i++) {
                for (int j = y - 1; j <= y + 1; j++) {
                    if(GameUtil.DATA_TOP[i][j] == 1) {
                        count++;
                    }
                }
            }
            //如果旗子数量=底层对应的数字（所有的雷都被排除出来）
            if(count == GameUtil.DATA_BOTTOM[x][y]) {
                //遍历周围八个位置的顶层结果
                for (int i = x-1; i <= x+1; i++) {
                    for (int j = y - 1; j <= y + 1; j++) {
                        if(GameUtil.DATA_TOP[i][j] != 1) {//如果没有插旗就变成无覆盖
                            GameUtil.DATA_TOP[i][j] = -1;
                        }
                        //必须在雷区中
                        if (i >=1 && j >= 1 && i < GameUtil.MAP_W && y < GameUtil.MAP_H) { //这里要不要加上等于
                            spaceOpen(i,j);//递归翻开
                        }
                    }
                }
            }
        }
    }
    //失败判定 true表示失败
    boolean boom() {
        if(GameUtil.FLAG_NUM == GameUtil.RAY_MAX) {//如果旗子数量等于雷数量
            for (int i = 1; i <= GameUtil.MAP_W; i++) {
                for (int j = 1; j <= GameUtil.MAP_H; j++) {
                    if(GameUtil.DATA_TOP[i][j] == 0) {//翻开所有覆盖的位置
                        GameUtil.DATA_TOP[i][j] = -1;
                    }
                }
            }
        }
        for (int i = 1; i <= GameUtil.MAP_W; i++) {
            for (int j = 1; j <= GameUtil.MAP_H; j++) {
                if(GameUtil.DATA_BOTTOM[i][j] == -1 && GameUtil.DATA_TOP[i][j] == -1) {//如果存在底层是雷并且顶层无覆盖的情况
                    //此时游戏失败
                    GameUtil.state = 2;//更新游戏状态
                    setBoom();//显示处所有的雷
                    return true;
                }
            }
        }
        return false;
    }

    //显示所有的雷和旗子的位置是否正确
    void setBoom() {
        for (int i = 1; i <= GameUtil.MAP_W; i++) {
            for (int j = 1; j <= GameUtil.MAP_H; j++) {
                //底层是雷，顶层不是旗，显示雷
                if(GameUtil.DATA_BOTTOM[i][j] == -1 && GameUtil.DATA_TOP[i][j] != 1) {
                    GameUtil.DATA_TOP[i][j] = -1;
                }
                //底层不是雷，顶层不是旗，显示插错棋
                if(GameUtil.DATA_BOTTOM[i][j] != -1 && GameUtil.DATA_TOP[i][j] == 1) {
                    GameUtil.DATA_TOP[i][j] = 2;
                }
            }
        }
    }

    //胜利判断 true表示胜利
    boolean victory() {
        //统计未打开格子数
        int countSpace = 0;
        for (int i = 1; i <= GameUtil.MAP_W; i++) {
            for (int j = 1; j <= GameUtil.MAP_H; j++) {
                if(GameUtil.DATA_TOP[i][j] != -1) {
                    countSpace++;
                }
            }
        }
        //如果未打开的格子数和雷的数量一样
        if(countSpace == GameUtil.RAY_MAX) {
            GameUtil.state = 1;//此时游戏胜利
            for (int i = 1; i <= GameUtil.MAP_W; i++) {
                for (int j = 1; j <= GameUtil.MAP_H; j++) {
                    //所有未翻开，变成旗子
                    if(GameUtil.DATA_TOP[i][j] == 0) {
                        GameUtil.DATA_TOP[i][j] = 1;
                    }
                }
            }
            return true;
        }
        return false;
    }

    //打开空格
    void spaceOpen(int x, int y) {
        if(GameUtil.DATA_BOTTOM[x][y] == 0) {
            for (int i = x-1; i <= x+1; i++) {
                for (int j = y-1; j <= y+1; j++) {
                    //覆盖才递归
                    if(GameUtil.DATA_TOP[i][j] != -1) {
                        if(GameUtil.DATA_TOP[i][j] == 1) {
                            GameUtil.FLAG_NUM--;
                        }
                        GameUtil.DATA_TOP[i][j] = -1;
                        //必须在雷区中
                        if (i >=1 && j >= 1 && i < GameUtil.MAP_W && y < GameUtil.MAP_H) { //这里要不要加上等于
                            spaceOpen(i,j);//递归打开
                        }
                    }
                }
            }
        }
    }
    //绘制方法
    void paintSelf(Graphics g) {
        logic();//调用logic，更新所有的顶层结果
        //遍历顶层的状态，根据不同的数据绘制不同格子的图像
        for (int i = 1; i <= GameUtil.MAP_W; i++) {
            for (int j = 1; j <= GameUtil.MAP_H; j++) {
                //覆盖
                if(GameUtil.DATA_TOP[i][j] == 0) {
                    g.drawImage(GameUtil.top,
                            GameUtil.OFFSET + (i-1)* GameUtil.SQUARE_LENGTH + 1,
                            GameUtil.OFFSET * 3 + (j-1) * GameUtil.SQUARE_LENGTH + 1,
                            GameUtil.SQUARE_LENGTH - 2,
                            GameUtil.SQUARE_LENGTH - 2,
                            null);
                }
                //插旗
                if(GameUtil.DATA_TOP[i][j] == 1) {
                    g.drawImage(GameUtil.flag,
                            GameUtil.OFFSET + (i-1)* GameUtil.SQUARE_LENGTH + 1,
                            GameUtil.OFFSET * 3 + (j-1) * GameUtil.SQUARE_LENGTH + 1,
                            GameUtil.SQUARE_LENGTH - 2,
                            GameUtil.SQUARE_LENGTH - 2,
                            null);
                }
                //插错棋
                if(GameUtil.DATA_TOP[i][j] == 2) {
                    g.drawImage(GameUtil.noflag,
                            GameUtil.OFFSET + (i-1)* GameUtil.SQUARE_LENGTH + 1,
                            GameUtil.OFFSET * 3 + (j-1) * GameUtil.SQUARE_LENGTH + 1,
                            GameUtil.SQUARE_LENGTH - 2,
                            GameUtil.SQUARE_LENGTH - 2,
                            null);
                }
            }
        }
    }
}
