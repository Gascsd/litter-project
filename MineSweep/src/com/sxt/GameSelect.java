package com.sxt;

import java.awt.*;

/**
 * 难度选择类
 */
public class GameSelect {

    //设置成功返回t 失败返回false
    boolean hard() {
        //鼠标点击在合法的列
        if(GameUtil.MOUSE_X > 100 && GameUtil.MOUSE_X < 400) {
            //鼠标点击对应的行，设置对应的level
            if(GameUtil.MOUSE_Y > 50 && GameUtil.MOUSE_Y < 150) {
                GameUtil.level = 1;
                GameUtil.state = 0;
                return  true;
            }
            if(GameUtil.MOUSE_Y > 200 && GameUtil.MOUSE_Y < 300) {
                GameUtil.level = 2;
                GameUtil.state = 0;
                return  true;
            }
            if(GameUtil.MOUSE_Y > 350 && GameUtil.MOUSE_Y < 450) {
                GameUtil.level = 3;
                GameUtil.state = 0;
                return  true;
            }
        }
        return false;
    }

    //打印难度选择窗口
    void paintSelf(Graphics g) {
        g.setColor(Color.black);//设置难度选择的字体颜色
        g.drawRect(100, 50,300, 100);
        GameUtil.drawWord(g,"简单", 220, 100, 30,Color.black);

        g.drawRect(100, 200,300, 100);
        GameUtil.drawWord(g,"中等", 220, 250, 30,Color.black);

        g.drawRect(100, 350,300, 100);
        GameUtil.drawWord(g,"困难", 220, 400, 30,Color.black);
    }

    //根据对应的level设置雷的个数格子个数（长和宽）
    void hard(int level) {
        switch (level) {
            case 1 -> {
                GameUtil.RAY_MAX = 10;
                GameUtil.MAP_W = 9;
                GameUtil.MAP_H = 9;
            }
            case 2 -> {
                GameUtil.RAY_MAX = 40;
                GameUtil.MAP_W = 16;
                GameUtil.MAP_H = 16;
            }
            case 3 -> {
                GameUtil.RAY_MAX = 80;
                GameUtil.MAP_W = 25;
                GameUtil.MAP_H = 14;
            }
            default -> {
            }
        }
    }
}
