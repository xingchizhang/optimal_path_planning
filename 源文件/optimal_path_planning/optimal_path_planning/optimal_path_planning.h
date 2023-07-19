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

    //��ʼ����
    map<int, QPoint> Point; // ·��
    // ��ֵ={id��(·��,·��)}
    map<int, pair<int, int>> Route;  // ��·
    // ��ֵ={(·��,·��)������}
    map<pair<int, int>, int> map_method; //��ͼ�����ڴ���method��
    map<int, QPoint> Location; // ����
    map<int, string> Name;     // ·��-����
    map<int, int> L2M;         // ����-·��

    map<int, string> Weather2Name;   //����-����
    map<int, int> Time2T;            //ʱ��-����

    //������Ϣ
    int Weather = 0; // ��������
    int T = 0;       // ��������
    int hour = 0;    // ����ʱ��
    int minute = 0;  // ����ʱ��
    vector<int> Way = { -1, -1 }; // ����·��

    //ϵͳ����
    int mode = 0; // ���õص�ģʽ
    bool isShowLandmark = true;   // �Ƿ���ʾ�ر�

    //�滮��Ϣ
    vector<vector<vector<int>>> Planning; // �滮·��
    int mode_Plan = 0; // ������ʾ�滮ģʽ

private slots://��Ӧ���ܲۺ���
    void Adjust(void);       //��������ģʽ
    void Delete(void);       //ɾ����;�ص�
    void ShowLandmark(void); //��ʾ�ر�
    void updateWT(void);     //��������
    void affirm(void);       //ȷ�ϣ���ʼ�滮��
    void change(void);       //������ʾ�滮
};
