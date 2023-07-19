#include "optimal_path_planning.h"

optimal_path_planning::optimal_path_planning(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    Init();
    Draw();
    ui.label_9->setText(QString::fromLocal8Bit(Weather2Name[Weather] + to_string(T) + "度 "));
}

optimal_path_planning::~optimal_path_planning()
{}

//绘制
void optimal_path_planning::Draw(void)
{
    QPixmap pixmap(":/optimal_path_planning/1.jpg");
    QPainter painter(&pixmap);
    if (isShowLandmark) {
        // 绘制地图
        painter.setPen(QPen(Qt::white, 2));
        for (int i = 0; i < Route.size(); i++) {
            painter.drawLine(Point[Route[i].first], Point[Route[i].second]);
        }
    }
    // 绘制路线
    if (!Planning.empty()) {
        painter.setPen(QPen(Qt::red, 2));
        for (auto& v : Planning[mode_Plan]) {
            for (auto it = v.begin(); it < v.end() - 1; ++it) {
                painter.drawLine(Point[*it], Point[*(it+1)]);
            }
        }
    }
    if (isShowLandmark) {
        // 绘制路口
        painter.setPen(QPen(Qt::blue, 4));
        for (int i = 0; i < Point.size(); i++) {
            painter.drawPoint(Point[i]);
        }
        // 标注建筑
        QFont font("Arial", 8);
        painter.setFont(font);
        painter.setPen(Qt::yellow);
        for (int i = 0; i < Location.size(); i++) {
            painter.drawText(Location[i], QString::fromLocal8Bit(Name[L2M[i]]));
        }
    }
    ui.label->setPixmap(pixmap);
}

//初始化数据
void optimal_path_planning::Init(void)
{
    srand((unsigned)time(NULL));
    // 1  天气
    Weather = (rand() % (9 - 0 + 1)) + 0;
    Weather2Name[0] = "晴，";
    Weather2Name[1] = "小雨，";
    Weather2Name[2] = "中雨，";
    Weather2Name[3] = "大雨，";
    Weather2Name[4] = "微风，";
    Weather2Name[5] = "大风，";
    Weather2Name[6] = "小雪，";
    Weather2Name[7] = "中雪，";
    Weather2Name[8] = "大雪，";
    Weather2Name[9] = "多云，";

    // 2  时间2温度
    Time2T = {
        {0,(rand() % (5 - 0 + 1)) + 0},
        {1,(rand() % (5 - 0 + 1)) + 0},
        {2,(rand() % (6 - 0 + 1)) + 0},
        {3,(rand() % (6 - 0 + 1)) + 0},
        {4,(rand() % (7 - 2 + 1)) + 2},
        {5,(rand() % (7 - 2 + 1)) + 2},
        {6,(rand() % (8 - 3 + 1)) + 3},
        {7,(rand() % (10 - 4 + 1)) + 4},
        {8,(rand() % (12 - 5 + 1)) + 5},
        {9,(rand() % (16 - 6 + 1)) + 6},
        {10,(rand() % (18 - 6 + 1)) + 6},
        {11,(rand() % (26 - 8 + 1)) + 8},
        {12,(rand() % (30 - 10 + 1)) + 10},
        {13,(rand() % (36 - 12 + 1)) + 12},
        {14,(rand() % (36 - 12 + 1)) + 12},
        {15,(rand() % (30 - 10 + 1)) + 10},
        {16,(rand() % (25 - 8 + 1)) + 8},
        {17,(rand() % (20 - 7 + 1)) + 7},
        {18,(rand() % (20 - 6 + 1)) + 6},
        {19,(rand() % (17 - 6 + 1)) + 6},
        {20,(rand() % (15 - 5 + 1)) + 5},
        {21,(rand() % (12 - 5 + 1)) + 5},
        {22,(rand() % (8 - 3 + 1)) + 3},
        {23,(rand() % (6 - 2 + 1)) + 2}
    };
    hour = (rand() % (18 - 8 + 1)) + 8;
    minute = (rand() % (59 - 0 + 1)) + 0;
    ui.spinBox_2->setValue(minute);
    ui.spinBox->setValue(hour);
    T = Time2T[hour];

    // 3  建筑
    Location[0] = QPoint(343 - 13, 394 + 5); //校医院
    Location[1] = QPoint(397 - 18, 404 + 5); //活动中心
    Location[2] = QPoint(428 - 10, 365 + 5); //梅园
    Location[3] = QPoint(434 - 10, 395 + 5); //松园
    Location[4] = QPoint(480 - 18, 372 + 5); //梅园食堂
    Location[5] = QPoint(495 - 10, 348 + 5); //竹园
    Location[6] = QPoint(398 - 13, 311 + 5); //文典阁
    Location[7] = QPoint(455 - 10, 302 + 5); //笃南
    Location[8] = QPoint(354 - 10, 277 + 5); //笃北
    Location[9] = QPoint(346 - 10, 340 + 5); //桃园
    Location[10] = QPoint(354 - 18, 370 + 5); // 西门超市
    Location[11] = QPoint(309 - 10, 353 + 5); // 桔园
    Location[12] = QPoint(318 - 10, 318 + 5); // 李园
    Location[13] = QPoint(283 - 18, 323 + 5); // 桔园食堂
    Location[14] = QPoint(267 - 18, 302 + 5); // 快递中心
    Location[15] = QPoint(263 - 10, 280 + 5); // 榴园
    Location[16] = QPoint(270 - 18, 258 + 5); // 榴园食堂
    Location[17] = QPoint(234 - 10, 271 + 5); // 枣园
    Location[18] = QPoint(225 - 10, 250 + 5); // 杏园
    Location[19] = QPoint(341 - 10, 414 + 5); // 西门
    Location[20] = QPoint(259 - 13, 218 + 5); // 北篮球场
    Location[21] = QPoint(684 - 13, 262 + 5); // 南篮球场
    Location[22] = QPoint(181 - 10, 187 + 5); // 北体
    Location[23] = QPoint(112 - 13, 137 + 5); // 体育馆
    Location[24] = QPoint(62 - 10, 123 + 5);   // 北门
    Location[25] = QPoint(388 - 13, 183 + 5);  // 行知楼
    Location[26] = QPoint(472 - 13, 200 + 5);  // 艺术楼
    Location[27] = QPoint(444 - 10, 150 + 5);  // 东门
    Location[28] = QPoint(654 - 13, 159 + 5);  // 行政楼
    Location[29] = QPoint(753 - 10, 128 + 5);  // 南门
    Location[30] = QPoint(624 - 10, 284 + 5);  // 南体
    Location[31] = QPoint(754 - 24, 207 + 5);  // 材料科学学院
    Location[32] = QPoint(474 - 10, 263 + 5);  // 博南
    Location[33] = QPoint(358 - 10, 234 + 5);  // 博北
    Location[34] = QPoint(518 - 13, 213 + 5);  // 人文楼
    Location[35] = QPoint(567 - 13, 189 + 5);  // 社科楼
    Location[36] = QPoint(171 - 18, 74 + 5);   // 蕙园食堂
    Location[37] = QPoint(166 - 18, 105 + 5);  // 蕙园8-11
    Location[38] = QPoint(118 - 18, 50 + 5);   // 蕙园1-7
    Location[39] = QPoint(46 - 18, 58 + 5);    // 磬苑宾馆
    Location[40] = QPoint(533 - 10, 341 + 5);  // 槐园
    Location[41] = QPoint(532 - 18, 313 + 5);  // 桂园食堂
    Location[42] = QPoint(563 - 10, 290 + 5);  // 桂园
    Location[43] = QPoint(569 - 10, 318 + 5);  // 枫园
    Location[44] = QPoint(604 - 18, 319 + 5);  // 南7宿舍
    Location[45] = QPoint(323 - 24, 166 + 5);  // 理工楼A-D
    Location[46] = QPoint(258 - 20, 136 + 5);  // 理工楼E-H
    Location[47] = QPoint(318 - 24, 221 + 5);  // 水上报告厅
    Location[48] = QPoint(302 - 13, 284 + 5);  // 北池塘
    Location[49] = QPoint(647 - 13, 94 + 5);   // 南池塘

    // 4  建筑2路口
    L2M[0] = 23;
    L2M[1] = 20;
    L2M[2] = 5;
    L2M[3] = 25;
    L2M[4] = 27;
    L2M[5] = 29;
    L2M[6] = 1;
    L2M[7] = 7;
    L2M[8] = 11;
    L2M[9] = 3;
    L2M[10] = 22;
    L2M[11] = 64;
    L2M[12] = 65;
    L2M[13] = 68;
    L2M[14] = 69;
    L2M[15] = 74;
    L2M[16] = 72;
    L2M[17] = 75;
    L2M[18] = 76;
    L2M[19] = 24;
    L2M[20] = 77;
    L2M[21] = 49;
    L2M[22] = 79;
    L2M[23] = 87;
    L2M[24] = 102;
    L2M[25] = 15;
    L2M[26] = 17;
    L2M[27] = 19;
    L2M[28] = 55;
    L2M[29] = 54;
    L2M[30] = 42;
    L2M[31] = 53;
    L2M[32] = 8;
    L2M[33] = 12;
    L2M[34] = 63;
    L2M[35] = 57;
    L2M[36] = 96;
    L2M[37] = 95;
    L2M[38] = 97;
    L2M[39] = 100;
    L2M[40] = 34;
    L2M[41] = 37;
    L2M[42] = 39;
    L2M[43] = 40;
    L2M[44] = 41;
    L2M[45] = 92;
    L2M[46] = 90;
    L2M[47] = 86;
    L2M[48] = 70;
    L2M[49] = 56;

    // 5  路口2名字
    Name[23] = string("校医院");
    Name[20] = string("活动中心");
    Name[5] = string("梅园");
    Name[25] = string("松园");
    Name[27] = string("梅园食堂");
    Name[29] = string("竹园");
    Name[1] = string("文典阁");
    Name[7] = string("笃南");
    Name[11] = string("笃北");
    Name[3] = string("桃园");
    Name[22] = string("西门超市");
    Name[64] = string("桔园");
    Name[65] = string("李园");
    Name[68] = string("桔园食堂");
    Name[69] = string("快递中心");
    Name[74] = string("榴园");
    Name[72] = string("榴园食堂");
    Name[75] = string("枣园");
    Name[76] = string("杏园");
    Name[24] = string("西门");
    Name[77] = string("北篮球场");
    Name[49] = string("南篮球场");
    Name[79] = string("北体");
    Name[87] = string("体育馆 ");
    Name[102] = string("北门");
    Name[15] = string("行知楼");
    Name[17] = string("艺术楼");
    Name[19] = string("东门");
    Name[55] = string("行政楼");
    Name[54] = string("南门");
    Name[42] = string("南体");
    Name[53] = string("材料科学学院");
    Name[8] = string("博南");
    Name[12] = string("博北");
    Name[63] = string("人文楼");
    Name[57] = string("社科楼");
    Name[96] = string("蕙园食堂");
    Name[95] = string("蕙园8-11");
    Name[97] = string("蕙园1-7");
    Name[100] = string("磬苑宾馆 ");
    Name[34] = string("槐园");
    Name[37] = string("桂园食堂");
    Name[39] = string("桂园 ");
    Name[40] = string("枫园");
    Name[41] = string("南7宿舍");
    Name[92] = string("理工楼A-D");
    Name[90] = string("理工楼E-H");
    Name[86] = string("水上报告厅");
    Name[70] = string("北池塘 ");
    Name[56] = string("南池塘 ");

    // 6  路口
    Point[0] = QPoint(374, 329); //图书馆左侧
    Point[1] = QPoint(394, 337); //图书馆
    Point[2] = QPoint(418, 341); //图书馆右侧
    Point[3] = QPoint(346, 353); //桃园
    Point[4] = QPoint(365, 359); //桃园右侧
    Point[5] = QPoint(427, 379); //梅园
    Point[6] = QPoint(408, 371); //梅园左侧
    Point[7] = QPoint(431, 295); //笃南
    Point[8] = QPoint(441, 257); //博南
    Point[9] = QPoint(437, 273); //博南下方
    Point[10] = QPoint(447, 234); //博南上方
    Point[11] = QPoint(386, 282); //笃北
    Point[12] = QPoint(397, 241); //博北
    Point[13] = QPoint(391, 261); //博北下方
    Point[14] = QPoint(402, 222); //博北上方
    Point[15] = QPoint(411, 189); //行知楼
    Point[16] = QPoint(406, 205); //行知楼下方
    Point[17] = QPoint(458, 194); //艺术楼
    Point[18] = QPoint(452, 217); //艺术楼下方
    Point[19] = QPoint(443, 160); //东门
    Point[20] = QPoint(397, 395); //大活
    Point[21] = QPoint(366, 390); //西门路口
    Point[22] = QPoint(362, 374); //西门超市
    Point[23] = QPoint(350, 405); //校医院
    Point[24] = QPoint(341, 413); //西门
    Point[25] = QPoint(442, 384); //松园
    Point[26] = QPoint(458, 388); //松园右侧
    Point[27] = QPoint(462, 374); //梅园食堂
    Point[28] = QPoint(469, 354); //竹园左侧
    Point[29] = QPoint(492, 361); //竹园
    Point[30] = QPoint(472, 335); //竹园左上
    Point[31] = QPoint(510, 364); //竹园右侧
    Point[32] = QPoint(521, 330); //槐园左侧
    Point[33] = QPoint(506, 318); //槐园左上
    Point[34] = QPoint(534, 333); //槐园
    Point[35] = QPoint(546, 335); //槐园右侧
    Point[36] = QPoint(553, 306); //桂园食堂右侧
    Point[37] = QPoint(539, 302); //桂园食堂
    Point[38] = QPoint(526, 298); //桂园食堂左侧
    Point[39] = QPoint(561, 306); //桂园
    Point[40] = QPoint(573, 310); //枫园
    Point[41] = QPoint(587, 314); //南7宿舍
    Point[42] = QPoint(602, 306); //南体
    Point[43] = QPoint(478, 393); //梅园食堂下方
    Point[44] = QPoint(508, 378); //梅园食堂右下
    Point[45] = QPoint(545, 354); //槐园右下
    Point[46] = QPoint(584, 338); //南7宿舍左下
    Point[47] = QPoint(604, 329); //南7宿舍右下
    Point[48] = QPoint(670, 295); //南体右下
    Point[49] = QPoint(659, 275); //南篮球场
    Point[50] = QPoint(649, 253); //南体右上
    Point[51] = QPoint(719, 271); //南篮球场右下
    Point[52] = QPoint(698, 230); //南篮球场右上
    Point[53] = QPoint(728, 198); //材料科学学院
    Point[54] = QPoint(745, 142); //南门
    Point[55] = QPoint(622, 145); //行政楼
    Point[56] = QPoint(658, 122); //南池塘
    Point[57] = QPoint(587, 198); //社科楼
    Point[58] = QPoint(578, 220); //社科楼下方
    Point[59] = QPoint(560, 259); //桂园上方
    Point[60] = QPoint(541, 282); //桂园左侧
    Point[61] = QPoint(527, 258); //博南右侧
    Point[62] = QPoint(530, 238); //人文楼右侧
    Point[63] = QPoint(508, 232); //人文楼
    Point[64] = QPoint(314, 345); //桔园
    Point[65] = QPoint(318, 330); //李园
    Point[66] = QPoint(296, 342); //桔园左侧
    Point[67] = QPoint(299, 324); //李园左侧
    Point[68] = QPoint(290, 311); //桔园食堂
    Point[69] = QPoint(279, 306); //快递中心
    Point[70] = QPoint(327, 293); //北池塘
    Point[71] = QPoint(304, 250); //笃北左侧
    Point[72] = QPoint(289, 254); //榴园食堂
    Point[73] = QPoint(284, 277); //榴园右侧
    Point[74] = QPoint(265, 273); //榴园
    Point[75] = QPoint(243, 265); //枣园
    Point[76] = QPoint(222, 262); //杏园
    Point[77] = QPoint(250, 240); //北篮球场下方
    Point[78] = QPoint(219, 226); //北篮球场左侧
    Point[79] = QPoint(172, 230); //北体
    Point[80] = QPoint(115, 174); //体育馆下方
    Point[81] = QPoint(204, 271); //杏园下方
    Point[82] = QPoint(257, 324); //快递中心下方
    Point[83] = QPoint(284, 354); //桔园食堂下方
    Point[84] = QPoint(310, 386); //桔园右下
    Point[85] = QPoint(334, 390); //校医院左侧
    Point[86] = QPoint(333, 245); //水上报告厅
    Point[87] = QPoint(156, 154); //体育馆
    Point[88] = QPoint(232, 175); //北体右上
    Point[89] = QPoint(294, 194); //北篮球场右上
    Point[90] = QPoint(240, 149); //理工类E-H
    Point[91] = QPoint(282, 169); //理工楼下方
    Point[92] = QPoint(326, 183); //理工楼A-D
    Point[93] = QPoint(143, 123); //蕙园8-11下方
    Point[94] = QPoint(192, 135); //蕙园8-11右下
    Point[95] = QPoint(206, 106); //蕙园8-11右侧
    Point[96] = QPoint(166, 88);  //蕙园食堂
    Point[97] = QPoint(118, 73);  //蕙园1-7
    Point[98] = QPoint(90, 66);   //蕙园1-7左下
    Point[99] = QPoint(80, 82);   //磬苑宾馆右侧
    Point[100] = QPoint(56, 77);  //磬苑宾馆
    Point[101] = QPoint(84, 109); //体育馆左上
    Point[102] = QPoint(64, 122); //北门
    Point[103] = QPoint(418, 170); //中继结点1
    Point[104] = QPoint(456, 174); //中继结点2
    Point[105] = QPoint(342, 208); //水上报告厅右上

    // 7  道路
    Route[0] = pair(3, 4);   //桃园----------桃园右侧
    Route[1] = pair(4, 0);    //桃园右侧-------图书馆左侧
    Route[2] = pair(0, 1);    //图书馆左侧-----图书馆
    Route[3] = pair(1, 2);    //图书馆--------图书馆右侧
    Route[4] = pair(2, 6);   //图书馆右侧-----梅园左侧
    Route[5] = pair(6, 5);   //梅园左侧-------梅园
    Route[6] = pair(2, 7);   //图书馆右侧-----笃南
    Route[7] = pair(7, 9);   //笃南----------博南下方
    Route[8] = pair(9, 8);   //博南下方-------博南
    Route[9] = pair(8, 10);  //博南----------博南上方
    Route[10] = pair(10, 18);  //博南上方-------艺术楼下方
    Route[11] = pair(18, 17);  //艺术楼下方-----艺术楼
    Route[12] = pair(0, 11);   //图书馆左侧-----笃北
    Route[13] = pair(11, 13);  //笃北----------博北下方
    Route[14] = pair(13, 12);  //博北下方-------博北
    Route[15] = pair(12, 14);  //博北----------博北上方
    Route[16] = pair(14, 16);  //博北上方-------行知楼下方
    Route[17] = pair(16, 15);  //行知楼下方-----行知楼
    Route[18] = pair(4, 22);   //桃园右侧-------西门超市
    Route[19] = pair(22, 21);  //西门超市-------西门路口
    Route[20] = pair(21, 20);  //西门路口-------活动中心
    Route[21] = pair(20, 6);   //活动中心-------竹园左侧
    Route[22] = pair(21, 23);  //西门超市-------校医院
    Route[23] = pair(23, 24);  //校医院---------西门
    Route[24] = pair(5, 25);   //梅园----------松园
    Route[25] = pair(25, 26);  //松园----------松园右侧
    Route[26] = pair(26, 27);  //松园右侧-------梅园食堂
    Route[27] = pair(27, 28);  //梅园食堂-------竹园左侧
    Route[28] = pair(28, 29);  //竹园左侧-------竹园
    Route[29] = pair(28, 30);  //竹园左侧-------竹园左上
    Route[30] = pair(30, 2);   //竹园左上-------图书馆右侧
    Route[31] = pair(29, 31);   //竹园----------竹园右侧
    Route[32] = pair(31, 32);   //竹园右侧-------槐园左侧
    Route[33] = pair(32, 34);   //槐园左侧-------槐园
    Route[34] = pair(32, 33);   //槐园左侧-------槐园左上
    Route[35] = pair(34, 35);   //槐园----------槐园右侧
    Route[36] = pair(35, 36);   //槐园右侧-------桂园食堂右侧
    Route[37] = pair(36, 37);   //桂园食堂右侧----桂园食堂
    Route[38] = pair(37, 38);   //桂园食堂-------桂园食堂左侧
    Route[39] = pair(38, 9);    //桂园食堂左侧----博南下方
    Route[40] = pair(30, 33);   //竹园左上-------槐园左上
    Route[41] = pair(33, 38);   //槐园左上-------桂园食堂左侧
    Route[42] = pair(36, 39);   //桂园食堂右侧----桂园
    Route[43] = pair(39, 40);   //桂园----------枫园
    Route[44] = pair(40, 41);   //枫园----------南7宿舍
    Route[45] = pair(41, 42);   //南7宿舍--------南体
    Route[46] = pair(17, 104);  //艺术楼--------中继结点2
    Route[47] = pair(15, 103);  //行知楼--------中继结点1
    Route[48] = pair(26, 43);   //松园右侧-------梅园食堂下方
    Route[49] = pair(43, 44);   //梅园食堂下方----梅园食堂右下
    Route[50] = pair(44, 45);   //梅园食堂右下----槐园右下
    Route[51] = pair(45, 46);   //槐园右下-------南7宿舍左下
    Route[52] = pair(46, 47);   //南7宿舍左下----南7宿舍右下
    Route[53] = pair(31, 44);   //竹园右侧-------梅园食堂右下
    Route[54] = pair(35, 45);   //槐园右侧-------槐园右下
    Route[55] = pair(41, 46);   //南7宿舍--------南7宿舍左下
    Route[56] = pair(42, 47);   //南体-----------南7宿舍右下
    Route[57] = pair(47, 48);   //南7宿舍右下-----南体右下
    Route[58] = pair(48, 49);   //南体右下--------南篮球场
    Route[59] = pair(49, 50);   //南篮球场--------南体右上
    Route[60] = pair(48, 51);   //南体右下--------南篮球场右下
    Route[61] = pair(51, 52);   //南篮球场右下-----南篮球场右上
    Route[62] = pair(52, 53);   //南篮球场右上-----材料科学大楼
    Route[63] = pair(53, 54);   //材料科学大楼-----南门
    Route[64] = pair(54, 56);   //南门-----------南池塘
    Route[65] = pair(56, 55);   //南池塘---------行政楼
    Route[66] = pair(55, 57);   //行政楼---------社科楼
    Route[67] = pair(57, 58);   //社科楼---------社科楼下方
    Route[68] = pair(58, 59);   //社科楼下方------桂园上方
    Route[69] = pair(59, 60);   //桂园上方--------桂园左侧
    Route[70] = pair(60, 61);   //桂园左侧--------博南右侧
    Route[71] = pair(61, 62);   //博南右侧--------人文楼右侧
    Route[72] = pair(62, 63);   //人文楼右侧------人文楼
    Route[73] = pair(63, 18);   //人文楼---------艺术楼下方
    Route[74] = pair(61, 10);   //博南右侧--------博南上方
    Route[75] = pair(58, 62);   //社科楼下方------人文楼右侧
    Route[76] = pair(59, 50);   //桂园上方--------南体右上
    Route[77] = pair(50, 52);   //南体右上--------南篮球场右上
    Route[78] = pair(10, 14);   //博南上方--------博北上方
    Route[79] = pair(3, 64);    //桃园-----------桔园
    Route[80] = pair(64, 65);   //桔园-----------李园
    Route[81] = pair(64, 66);   //桔园-----------桔园左侧
    Route[82] = pair(66, 67);   //桔园左侧--------李园左侧
    Route[83] = pair(67, 68);   //李园左侧--------桔园食堂
    Route[84] = pair(68, 69);   //桔园食堂--------快递中心
    Route[85] = pair(68, 70);   //桔园食堂--------北池塘
    Route[86] = pair(70, 0);    //北池塘----------图书馆左侧
    Route[87] = pair(70, 71);   //北池塘----------笃北左侧
    Route[88] = pair(71, 72);   //笃北左侧--------榴园食堂
    Route[89] = pair(72, 73);   //榴园食堂--------榴园右侧
    Route[90] = pair(73, 69);   //榴园右侧--------快递中心
    Route[91] = pair(73, 74);   //榴园右侧--------榴园
    Route[92] = pair(74, 75);   //榴园-----------枣园
    Route[93] = pair(75, 76);   //枣园-----------杏园
    Route[94] = pair(75, 77);   //枣园-----------北篮球场下方
    Route[95] = pair(77, 78);   //北篮球场下方-----北篮球场左侧
    Route[96] = pair(78, 79);   //北篮球场左侧-----北体
    Route[97] = pair(79, 80);   //北体-----------体育馆下方
    Route[98] = pair(79, 81);   //北体-----------杏园下方
    Route[99] = pair(81, 76);   //杏园下方--------杏园
    Route[100] = pair(81, 82);  //杏园下方-------快递中心下方
    Route[101] = pair(82, 69);   //快递中心下方----快递中心
    Route[102] = pair(82, 83);   //快递中心下方----桔园食堂下方
    Route[103] = pair(83, 84);   //桔园食堂下方----桔园右下
    Route[104] = pair(83, 66);   //桔园食堂下方----桔园左侧
    Route[105] = pair(84, 85);   //桔园左下-------校医院左侧
    Route[106] = pair(85, 3);    //桔园下方-------桃园
    Route[107] = pair(71, 86);   //笃北左侧-------水上报告厅
    Route[108] = pair(86, 9);    //水上报告厅------博北下方
    Route[109] = pair(67, 65);   //李园左侧-------李园
    Route[110] = pair(72, 77);   //榴园食堂-------北篮球场下方
    Route[111] = pair(43, 29);   //梅园食堂下方----竹园
    Route[112] = pair(80, 87);   //体育馆下方------体育馆
    Route[113] = pair(87, 88);   //体育馆---------北体右上
    Route[114] = pair(88, 89);   //北体右上-------北篮球场右上
    Route[115] = pair(89, 71);   //北篮球场右上----笃北左侧
    Route[116] = pair(89, 105);  //北篮球场右上----水上报告厅右上
    Route[117] = pair(89, 91);   //北篮球场右上----理工楼下方
    Route[118] = pair(91, 92);   //理工楼下方------理工楼A-D
    Route[119] = pair(92, 16);   //理工楼A-D------行知楼下方
    Route[120] = pair(91, 90);   //理工楼下方------理工楼E-H
    Route[121] = pair(90, 88);    //理工楼E-H------北体右上
    Route[122] = pair(90, 94);    //理工楼E-H------蕙园8-11右下
    Route[123] = pair(94, 93);    //蕙园8-11右下----蕙园8-11下方
    Route[124] = pair(94, 95);    //蕙园8-11右下----蕙园8-11右侧
    Route[125] = pair(95, 96);    //蕙园8-11右侧----蕙园食堂
    Route[126] = pair(96, 97);    //蕙园食堂--------蕙园1-7
    Route[127] = pair(97, 98);    //蕙园1-7--------蕙园1-7左下
    Route[128] = pair(98, 99);    //蕙园1-7左下-----磬苑宾馆右侧
    Route[129] = pair(100, 99);   //磬苑宾馆-------磬苑宾馆右侧
    Route[130] = pair(99, 101);   //磬苑宾馆右侧----体育馆左上
    Route[131] = pair(101, 102);  //体育馆左上-----北门
    Route[132] = pair(101, 93);   //体育馆左上------蕙园8-11下方
    Route[133] = pair(87, 93);    //体育馆---------蕙园8-11下方
    Route[134] = pair(88, 78);    //北体右上-------北篮球场左侧
    Route[135] = pair(103, 19);   //中继结点1------东门
    Route[136] = pair(104, 19);   //中继结点2------东门
    Route[137] = pair(105, 14);   //水上报告厅右上---博北上方
    Route[138] = pair(105, 86);   //水上报告厅右上---水上报告厅
    Route[139] = pair(38, 60);    //桂园食堂左侧---桂园左侧
    // 8  地图
    for (int i = 0; i < Route.size(); i++) {
        map_method[Route[i]] = round(sqrt(pow((Point[Route[i].first].x() - Point[Route[i].second].x()), 2) + pow((Point[Route[i].first].y() - Point[Route[i].second].y()), 2)));
    }
}

//显示字符串（-1显示路线，0-2显示提示信息）
string optimal_path_planning::GetShow(int mode_Plan) {
    if (mode_Plan == -1) {
        string ShowMid = "";
        for (auto it = Way.begin() + 1; it != Way.end() - 1; ++it) {
            ShowMid += (Name[*it] + " ");
        }
        return ShowMid;
    }
    else {
        string Show = "";
        if (mode_Plan == 0)
            Show += "步行规划:";
        else if (mode_Plan == 1)
            Show += "骑行规划:";
        else
            Show += "驾车规划:";
        // 加入路线
        int j = 1;
        for (auto& v : Planning[mode_Plan]) {
            Show += "\n" + to_string(j) + ": ";
            auto it = v.begin();
            for (; it < v.end() - 1; ++it) {
                // 如果有此地点，则加入显示
                int i = 0;
                for (; i < L2M.size(); i++) {
                    if (L2M[i] == *it) {
                        Show += (Name[*it] + "->");
                        break;
                    }
                }
            }
            j += 1;
            Show += Name[*it];
        }
        Show += "\n规划说明:\n";
        if (mode_Plan == 0) {
            Show += "已为您规划距离最短的路线";
        }
        else if (mode_Plan == 1) {
            Show += "在保证距离相对较短的前提下，已为您规划途中含有更多停车点的路线";
        }
        else {
            Show += "在保证距离相对较短的前提下，已为您规划途中含有更多停车点和更少限速路段的路线";
        }
        Show += "\n温馨提示:";
        Show += "\n 气 温 : ";
        if (T <= 0)
            Show += "寒冷天气，出行注意保暖哦！";
        else if (T <= 15)
            Show += "低温天气，一件外套足矣！";
        else if (T <= 25)
            Show += "温度舒适！";
        else if (T <= 35)
            Show += "高温天气，出行注意遮阳！";
        else
            Show += "炎热天气，尽量减少出行哦！";
        Show += "\n 天 气 : ";
        if (Weather == 1)
            Show += "晴朗天空，出行畅通！";
        else if (Weather == 2 || Weather == 3)
            Show += "中到大雨，注意脚下湿滑，记得带伞！";
        else if (Weather == 4)
            Show += "小风拂面！";
        else if (Weather == 5)
            Show += "刮大风啦，骑行谨慎！";
        else if (Weather == 6)
            Show += "下小雪啦，可以欣赏雪景，但也要注意脚下安全哦！";
        else if (Weather == 7 || Weather == 8)
            Show += "中到大雪，注意路面积雪，谨防摔倒或车辆滑行！";
        else
            Show += "多云天气，出行舒适！";
        return Show;
    }
}

//鼠标点击响应
void optimal_path_planning::mousePressEvent(QMouseEvent* event)
{
    
    QPoint pos = event->pos();  // 获取鼠标点击的位置
    if (pos.x() <= 817 && pos.y() <= 435) {
        int index = -1;
        int dis = 0;
        for (int i = 0; i < Location.size(); i++) {
            int deltaX = pos.x() - Location[i].x();
            int deltaY = pos.y() - Location[i].y();
            int distance = round(sqrt(deltaX * deltaX + deltaY * deltaY));

            if (index == -1) {
                index = i;
                dis = distance;
                continue;
            }

            if (distance < dis) {
                index = i;
                dis = distance;
            }
        }
        if (mode == 0) {
            Way.front() = L2M[index];
            ui.label_7->setText(QString::fromLocal8Bit(Name[Way.front()]));
        }
        else if(mode == 1) {
            Way.back() = L2M[index];
            ui.label_8->setText(QString::fromLocal8Bit(Name[Way.back()]));
        }
        else {
            if (Way[Way.size() - 2] != L2M[index]) {
                Way.insert(Way.end() - 1, L2M[index]);
                ui.textBrowser_4->setText(QString::fromLocal8Bit(GetShow(-1)));
            }
        }
    }
}

//调整设置模式
void optimal_path_planning::Adjust(void)
{
    mode = (mode + 1) % 3;
    if (mode == 0) {
        ui.label_12->setText(QString::fromLocal8Bit("起始位置"));
    }
    else if (mode == 1) {
        ui.label_12->setText(QString::fromLocal8Bit("目标位置"));
    }
    else {
        ui.label_12->setText(QString::fromLocal8Bit("中途位置"));
    }
}

//删除中途地点
void optimal_path_planning::Delete(void)
{
    if (Way.size() > 2) {
        Way.erase(Way.end() - 2);
        ui.textBrowser_4->setText(QString::fromLocal8Bit(GetShow(-1)));
    }
}

//显示地标
void optimal_path_planning::ShowLandmark(void)
{
    isShowLandmark = !isShowLandmark;
    if (isShowLandmark) {
        ui.pushButton_3->setText(QString::fromLocal8Bit(" 关 闭 "));
    }
    else {
        ui.pushButton_3->setText(QString::fromLocal8Bit(" 开 启 "));
    }
    Draw();
}

//更新气候
void optimal_path_planning::updateWT(void)
{
    hour = ui.spinBox->value();
    minute = ui.spinBox_2->value();
    T = Time2T[hour];
    ui.label_9->setText(QString::fromLocal8Bit(Weather2Name[Weather] + to_string(T) + "度 "));
}

//确认（开始规划）
void optimal_path_planning::affirm(void)
{
    if (Way.front() >= 0 && Way.back() >= 0) {
        Planning.clear();
        method Q = method(hour, minute, Way, Weather, T, map_method);
        Q.route_Planning();
        Planning = Q.get_Planning();
        Draw();
        mode_Plan = 0;
        ui.textBrowser->setText(QString::fromLocal8Bit(GetShow(mode_Plan)));

    }
}

//更改显示规划
void optimal_path_planning::change(void)
{
    if (!Planning.empty()) {
        mode_Plan = (mode_Plan + 1) % 3;
        ui.textBrowser->setText(QString::fromLocal8Bit(GetShow(mode_Plan)));
        Draw();
    }
}



