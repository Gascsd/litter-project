package com.sxt;

import java.awt.*;

/**
 * 顶层地图类
 * 绘制顶层组件
 * 判断逻辑
 */
public class MapTop {

    //格子位置
    int temp_x;
    int temp_y;

    //重置游戏
    void reGame() {
        for (int i = 1; i <= GameUtil.MAP_W; i++) {
            for (int j = 1; j <= GameUtil.MAP_H; j++) {
                GameUtil.DATA_TOP[i][j] = 0;
            }
        }
    }

    //判断逻辑
    void logic() {

        temp_x = 0;
        temp_y = 0;
        if(GameUtil.MOUSE_X > GameUtil.OFFSET && GameUtil.MOUSE_Y > 3 * GameUtil.OFFSET) {//防止点击上方和左方也翻开的情况
            temp_x = (GameUtil.MOUSE_X - GameUtil.OFFSET) / GameUtil.SQUARE_LENGTH + 1;
            temp_y = (GameUtil.MOUSE_Y - GameUtil.OFFSET * 3) / GameUtil.SQUARE_LENGTH + 1;
        }

        if(temp_x >= 1 && temp_x <= GameUtil.MAP_W
            && temp_y >= 1 && temp_x <= GameUtil.MAP_H) {
            if(GameUtil.LEFT) {
                //覆盖，则翻开
                if(GameUtil.DATA_TOP[temp_x][temp_y] == 0) {
                    GameUtil.DATA_TOP[temp_x][temp_y] = -1;
                }
                spaceOpen(temp_x,temp_y);
                GameUtil.LEFT = false;
            }
            if(GameUtil.RIGHT)
            {
                //覆盖则插旗
                if(GameUtil.DATA_TOP[temp_x][temp_y] == 0) {
                    GameUtil.DATA_TOP[temp_x][temp_y] = 1;
                    GameUtil.FLAG_NUM++;
                }
                //插旗则取消
                else if(GameUtil.DATA_TOP[temp_x][temp_y] == 1) {
                    GameUtil.DATA_TOP[temp_x][temp_y] = 0;
                    GameUtil.FLAG_NUM--;
                }
                else if(GameUtil.DATA_TOP[temp_x][temp_y] == -1) {
                    numOpen(temp_x, temp_y);
                }
                GameUtil.RIGHT = false;
            }
        }
        boom();
        victory();
    }
    //数字翻开
    void numOpen(int x, int y) {
        int count = 0;//记录旗子数
        if(GameUtil.DATA_BOTTOM[x][y] > 0) {
            for (int i = x-1; i <= x+1; i++) {
                for (int j = y - 1; j <= y + 1; j++) {
                    if(GameUtil.DATA_TOP[i][j] == 1) {
                        count++;
                    }
                }
            }
            if(count == GameUtil.DATA_BOTTOM[x][y]) {
                for (int i = x-1; i <= x+1; i++) {
                    for (int j = y - 1; j <= y + 1; j++) {
                        if(GameUtil.DATA_TOP[i][j] != 1) {
                            GameUtil.DATA_TOP[i][j] = -1;
                        }
                        //必须在雷区中
                        if (i >=1 && j >= 1 && i < GameUtil.MAP_W && y < GameUtil.MAP_H) { //这里要不要加上等于
                            spaceOpen(i,j);
                        }
                    }
                }
            }
        }
    }
    //失败判定 true表示失败
    boolean boom() {
        if(GameUtil.FLAG_NUM == GameUtil.RAY_MAX) {
            for (int i = 1; i <= GameUtil.MAP_W; i++) {
                for (int j = 1; j <= GameUtil.MAP_H; j++) {
                    if(GameUtil.DATA_TOP[i][j] == 0) {
                        GameUtil.DATA_TOP[i][j] = -1;
                    }
                }
            }
        }
        for (int i = 1; i <= GameUtil.MAP_W; i++) {
            for (int j = 1; j <= GameUtil.MAP_H; j++) {
                if(GameUtil.DATA_BOTTOM[i][j] == -1 && GameUtil.DATA_TOP[i][j] == -1) {
                    GameUtil.state = 2;
                    setBoom();
                    return true;
                }
            }
        }
        return false;
    }

    void setBoom() {
        for (int i = 1; i <= GameUtil.MAP_W; i++) {
            for (int j = 1; j <= GameUtil.MAP_H; j++) {
                //底层是雷，顶层不是旗，显示
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
        if(countSpace == GameUtil.RAY_MAX) {
            GameUtil.state = 1;
            for (int i = 1; i <= GameUtil.MAP_W; i++) {
                for (int j = 1; j <= GameUtil.MAP_H; j++) {
                    //未翻开，变成棋
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
                            spaceOpen(i,j);
                        }
                    }
                }
            }
        }
    }
    //绘制方法
    void paintSelf(Graphics g) {
        logic();
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
