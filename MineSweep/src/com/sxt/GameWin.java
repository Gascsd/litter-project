package com.sxt;

import javax.swing.*;
import java.awt.*;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;

public class GameWin extends JFrame {

    int weight = 2 * GameUtil.OFFSET + GameUtil.MAP_W * GameUtil.SQUARE_LENGTH;//设置窗口宽
    int height = 4 * GameUtil.OFFSET + GameUtil.MAP_H * GameUtil.SQUARE_LENGTH;//设置窗口长

    Image offScreenImage = null;

    MapBottom mapBottom = new MapBottom();//new一个MapBottom对象
    MapTop mapTop = new MapTop();//new一个MapTop对象
    GameSelect gameSelect = new GameSelect();//new一个GameSelect对象

    boolean begin = false;//是否开始的标志，false未开始 true开始

    //登陆函数
    void launch() {
        GameUtil.START_TIME = System.currentTimeMillis();//获取到开始时的系统时间
        this.setVisible(true);//设置窗口显示

        //状态为3的时候进行难度选择，否则就进入游戏内窗口
        if(GameUtil.state == 3) {
            this.setSize(500,500);
        }else{
            this.setSize(weight, height);//设置窗口大小
        }
        this.setLocationRelativeTo(null);//设置窗口位置
        this.setTitle("张红涛的扫雷游戏");//设置窗口名字
        this.setDefaultCloseOperation(EXIT_ON_CLOSE);//窗口关闭方法
        //鼠标事件
        this.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseClicked(MouseEvent e) {
                super.mouseClicked(e);//捕捉鼠标信号
                switch (GameUtil.state) {
                    case 0 ://游戏中
                        if(e.getButton() == 1) {//左键
                            //获取到鼠标点击位置，并保存左键状态
                            GameUtil.MOUSE_X = e.getX();
                            GameUtil.MOUSE_Y = e.getY();
                            GameUtil.LEFT = true;
                        }
                        if(e.getButton() == 3)//右键
                        {
                            //获取到鼠标点击位置，并保存右键状态
                            GameUtil.MOUSE_X = e.getX();
                            GameUtil.MOUSE_Y = e.getY();
                            GameUtil.RIGHT = true;
                        }
                    case 1 ://游戏胜利
                    case 2 ://游戏失败
                        if(e.getButton() == 1) {//如果是左键
                            if(e.getX() > GameUtil.OFFSET + GameUtil.SQUARE_LENGTH * (GameUtil.MAP_W / 2)
                                    && e.getX() < GameUtil.OFFSET + GameUtil.SQUARE_LENGTH * (GameUtil.MAP_W / 2) + GameUtil.SQUARE_LENGTH
                                    && e.getY() > GameUtil.OFFSET
                                    && e.getY() < GameUtil.OFFSET + GameUtil.SQUARE_LENGTH) {//如果点击位置在游戏状态位置就重置游戏状态
                                mapBottom.reGame();
                                mapTop.reGame();
                                //刷新旗子数量、开始时间、游戏状态
                                GameUtil.FLAG_NUM = 0;
                                GameUtil.START_TIME = System.currentTimeMillis();
                                GameUtil.state = 0;
                            }
                        }
                        if(e.getButton() == 2){//如果是鼠标中建点击，就回到游戏难度选择的位置
                            GameUtil.state = 3;
                            begin = true;//标志游戏开始
                        }
                        break;
                    case 3://难度选择
                        if(e.getButton() == 1) {//鼠标左键
                            //获取鼠标位置
                            GameUtil.MOUSE_X = e.getX();
                            GameUtil.MOUSE_Y = e.getY();

                            begin = gameSelect.hard();//设置游戏难度、更改游戏状态为开始
                        }
                    default:
                }
            }
        });

        while (true) {//刷新并显示窗口状态
            repaint();
            begin();//
            try {
                Thread.sleep(40);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }
    void begin() {
        if(begin) {//如果游戏已经开始
            begin = false;//释放游戏状态
            gameSelect.hard(GameUtil.level);//根据记录的level初始化游戏难度
            dispose();
            GameWin gameWin = new GameWin();
            GameUtil.START_TIME = System.currentTimeMillis();//获取系统当前时间，更新开始时间
            GameUtil.FLAG_NUM = 0;//重置旗子数量
            //调用重新开始方法，重新开始游戏
            mapBottom.reGame();
            mapTop.reGame();
            gameWin.launch();
        }
    }

    @Override
    public void paint(Graphics g) {
        if (GameUtil.state == 3) {
            g.setColor(Color.white);
            g.fillRect(0,0,500,500);
            gameSelect.paintSelf(g);
        } else {
            offScreenImage = this.createImage(weight, height);
            Graphics gImage = offScreenImage.getGraphics();
            //设置背景颜色
            gImage.setColor(Color.orange);
            gImage.fillRect(0, 0, weight, height);

            mapBottom.paintSelf(gImage);
            mapTop.paintSelf(gImage);
            g.drawImage(offScreenImage, 0, 0, null);
        }
    }

    public static void main(String[] args) {
        GameWin gameWin = new GameWin();//创建一个GameWin对象
        gameWin.launch();//调用launch开始游戏
    }
}
