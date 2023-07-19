#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_optimal_path_planning.h"
#include <Qwidget>
#include "QMouseEvent"
#include <QPainter>
#include <map>
#include <string>
#include "algorithm"
#include "random"
#include "method.h"
using namespace std;

class optimal_path_planning : public QMainWindow
{
    Q_OBJECT

public:
    optimal_path_planning(QWidget *parent = nullptr);
    ~optimal_path_planning();

    void Draw(void);
    void Init(void);

    string GetShow(int mode);

protected:
    void mousePressEvent(QMouseEvent* event) override;

private:
    Ui::optimal_path_planningClass ui;

    //初始数据
    map<int, QPoint> Point; // 路口
    // 键值={id，(路口,路口)}
    map<int, pair<int, int>> Route;  // 道路
    // 键值={(路口,路口)，距离}
    map<pair<int, int>, int> map_method; //地图（用于传给method）
    map<int, QPoint> Location; // 建筑
    map<int, string> Name;     // 路口-名字
    map<int, int> L2M;         // 建筑-路口

    map<int, string> Weather2Name;   //气候-名字
    map<int, int> Time2T;            //时间-气温

    //出行信息
    int Weather = 0; // 保存气候
    int T = 0;       // 保存气温
    int hour = 0;    // 出行时间
    int minute = 0;  // 出行时间
    vector<int> Way = { -1, -1 }; // 出行路线

    //系统设置
    int mode = 0; // 设置地点模式
    bool isShowLandmark = true;   // 是否显示地标

    //规划信息
    vector<vector<vector<int>>> Planning; // 规划路线
    int mode_Plan = 0; // 设置显示规划模式

private slots://相应功能槽函数
    void Adjust(void);       //调整设置模式
    void Delete(void);       //删除中途地点
    void ShowLandmark(void); //显示地标
    void updateWT(void);     //更新气候
    void affirm(void);       //确认（开始规划）
    void change(void);       //更改显示规划
};
