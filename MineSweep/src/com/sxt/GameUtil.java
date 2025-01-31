package com.sxt;

import java.awt.*;

/**
 * 工具类
 * 存放静态参数
 * 工具方法
 */
public class GameUtil {

    static int RAY_MAX = 100;

    static int MAP_W = 36;//地图的宽
    static int MAP_H = 17;//地图的高
    static int OFFSET = 45;//雷区偏移量
    static int SQUARE_LENGTH = 50;//格子边长

    //插旗数量
    static int FLAG_NUM = 0;

    //鼠标相关参数
    //坐标
    static int MOUSE_X;
    static int MOUSE_Y;
    //状态
    static boolean LEFT = false;
    static boolean RIGHT = false;

    //游戏状态 0 游戏中 1 胜利 2 失败 3 难度选择
    static int state = 3;
    //游戏难度
    static int level;

    //倒计时
    static long START_TIME;
    static long END_TIME;

    //底层元素 -1 雷 0 空 1-8 表示对应数字
    static int[][] DATA_BOTTOM = new int[MAP_W + 2][MAP_H + 2];

    //顶层元素 -1 无覆盖 0 覆盖 1 插旗 2 插错旗
    static int[][] DATA_TOP = new int[MAP_W + 2][MAP_H + 2];

    //载入图片
    static Image lei = Toolkit.getDefaultToolkit().getImage("imgs/lei.png");
    static Image top = Toolkit.getDefaultToolkit().getImage("imgs/top.png");
    static Image flag = Toolkit.getDefaultToolkit().getImage("imgs/flag.png");
    static Image noflag = Toolkit.getDefaultToolkit().getImage("imgs/noflag.png");

    static Image face = Toolkit.getDefaultToolkit().getImage("imgs/face.png");
    static Image over = Toolkit.getDefaultToolkit().getImage("imgs/over.png");
    static Image win = Toolkit.getDefaultToolkit().getImage("imgs/win.png");

    static Image[] images = new Image[9];
    static {
        for (int i = 1; i <= 8; i++) {
            images[i] = Toolkit.getDefaultToolkit().getImage("imgs/num/" + i + ".png");
        }
    }

    static void drawWord(Graphics g, String str, int x, int y, int size, Color color) {
        g.setColor(color);
        g.setFont(new Font("仿宋", Font.BOLD,size));
        g.drawString(str, x, y);
    }
}
