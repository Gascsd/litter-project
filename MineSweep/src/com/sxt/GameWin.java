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
                super.mouseClicked(e);
                switch (GameUtil.state) {
                    case 0 :
                        if(e.getButton() == 1) {
                        GameUtil.MOUSE_X = e.getX();
                        GameUtil.MOUSE_Y = e.getY();
                        GameUtil.LEFT = true;
                        }
                        if(e.getButton() == 3)
                        {
                            GameUtil.MOUSE_X = e.getX();
                            GameUtil.MOUSE_Y = e.getY();
                            GameUtil.RIGHT = true;
                        }
                    case 1 :
                    case 2 :
                        if(e.getButton() == 1) {
                            if(e.getX() > GameUtil.OFFSET + GameUtil.SQUARE_LENGTH * (GameUtil.MAP_W / 2)
                                    && e.getX() < GameUtil.OFFSET + GameUtil.SQUARE_LENGTH * (GameUtil.MAP_W / 2) + GameUtil.SQUARE_LENGTH
                                    && e.getY() > GameUtil.OFFSET
                                    && e.getY() < GameUtil.OFFSET + GameUtil.SQUARE_LENGTH) {
                                mapBottom.reGame();
                                mapTop.reGame();
                                GameUtil.FLAG_NUM = 0;
                                GameUtil.START_TIME = System.currentTimeMillis();
                                GameUtil.state = 0;
                            }
                        }
                        if(e.getButton() == 2){
                            GameUtil.state = 3;
                            begin = true;
                        }
                        break;
                    case 3:
                        if(e.getButton() == 1) {
                            GameUtil.MOUSE_X = e.getX();
                            GameUtil.MOUSE_Y = e.getY();
                            begin = gameSelect.hard();
                        }
                    default:
                }
            }
        });

        while (true) {
            repaint();
            begin();
            try {
                Thread.sleep(40);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }
    void begin() {
        if(begin) {
            begin = false;
            gameSelect.hard(GameUtil.level);
            dispose();
            GameWin gameWin = new GameWin();
            GameUtil.START_TIME = System.currentTimeMillis();
            GameUtil.FLAG_NUM = 0;
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
        GameWin gameWin = new GameWin();
        gameWin.launch();
    }
}
