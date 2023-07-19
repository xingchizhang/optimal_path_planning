#include "optimal_path_planning.h"

optimal_path_planning::optimal_path_planning(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    Init();
    Draw();
    ui.label_9->setText(QString::fromLocal8Bit(Weather2Name[Weather] + to_string(T) + "�� "));
}

optimal_path_planning::~optimal_path_planning()
{}

//����
void optimal_path_planning::Draw(void)
{
    QPixmap pixmap(":/optimal_path_planning/1.jpg");
    QPainter painter(&pixmap);
    if (isShowLandmark) {
        // ���Ƶ�ͼ
        painter.setPen(QPen(Qt::white, 2));
        for (int i = 0; i < Route.size(); i++) {
            painter.drawLine(Point[Route[i].first], Point[Route[i].second]);
        }
    }
    // ����·��
    if (!Planning.empty()) {
        painter.setPen(QPen(Qt::red, 2));
        for (auto& v : Planning[mode_Plan]) {
            for (auto it = v.begin(); it < v.end() - 1; ++it) {
                painter.drawLine(Point[*it], Point[*(it+1)]);
            }
        }
    }
    if (isShowLandmark) {
        // ����·��
        painter.setPen(QPen(Qt::blue, 4));
        for (int i = 0; i < Point.size(); i++) {
            painter.drawPoint(Point[i]);
        }
        // ��ע����
        QFont font("Arial", 8);
        painter.setFont(font);
        painter.setPen(Qt::yellow);
        for (int i = 0; i < Location.size(); i++) {
            painter.drawText(Location[i], QString::fromLocal8Bit(Name[L2M[i]]));
        }
    }
    ui.label->setPixmap(pixmap);
}

//��ʼ������
void optimal_path_planning::Init(void)
{
    srand((unsigned)time(NULL));
    // 1  ����
    Weather = (rand() % (9 - 0 + 1)) + 0;
    Weather2Name[0] = "�磬";
    Weather2Name[1] = "С�꣬";
    Weather2Name[2] = "���꣬";
    Weather2Name[3] = "���꣬";
    Weather2Name[4] = "΢�磬";
    Weather2Name[5] = "��磬";
    Weather2Name[6] = "Сѩ��";
    Weather2Name[7] = "��ѩ��";
    Weather2Name[8] = "��ѩ��";
    Weather2Name[9] = "���ƣ�";

    // 2  ʱ��2�¶�
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

    // 3  ����
    Location[0] = QPoint(343 - 13, 394 + 5); //УҽԺ
    Location[1] = QPoint(397 - 18, 404 + 5); //�����
    Location[2] = QPoint(428 - 10, 365 + 5); //÷԰
    Location[3] = QPoint(434 - 10, 395 + 5); //��԰
    Location[4] = QPoint(480 - 18, 372 + 5); //÷԰ʳ��
    Location[5] = QPoint(495 - 10, 348 + 5); //��԰
    Location[6] = QPoint(398 - 13, 311 + 5); //�ĵ��
    Location[7] = QPoint(455 - 10, 302 + 5); //����
    Location[8] = QPoint(354 - 10, 277 + 5); //�Ʊ�
    Location[9] = QPoint(346 - 10, 340 + 5); //��԰
    Location[10] = QPoint(354 - 18, 370 + 5); // ���ų���
    Location[11] = QPoint(309 - 10, 353 + 5); // ��԰
    Location[12] = QPoint(318 - 10, 318 + 5); // ��԰
    Location[13] = QPoint(283 - 18, 323 + 5); // ��԰ʳ��
    Location[14] = QPoint(267 - 18, 302 + 5); // �������
    Location[15] = QPoint(263 - 10, 280 + 5); // ��԰
    Location[16] = QPoint(270 - 18, 258 + 5); // ��԰ʳ��
    Location[17] = QPoint(234 - 10, 271 + 5); // ��԰
    Location[18] = QPoint(225 - 10, 250 + 5); // ��԰
    Location[19] = QPoint(341 - 10, 414 + 5); // ����
    Location[20] = QPoint(259 - 13, 218 + 5); // ������
    Location[21] = QPoint(684 - 13, 262 + 5); // ������
    Location[22] = QPoint(181 - 10, 187 + 5); // ����
    Location[23] = QPoint(112 - 13, 137 + 5); // ������
    Location[24] = QPoint(62 - 10, 123 + 5);   // ����
    Location[25] = QPoint(388 - 13, 183 + 5);  // ��֪¥
    Location[26] = QPoint(472 - 13, 200 + 5);  // ����¥
    Location[27] = QPoint(444 - 10, 150 + 5);  // ����
    Location[28] = QPoint(654 - 13, 159 + 5);  // ����¥
    Location[29] = QPoint(753 - 10, 128 + 5);  // ����
    Location[30] = QPoint(624 - 10, 284 + 5);  // ����
    Location[31] = QPoint(754 - 24, 207 + 5);  // ���Ͽ�ѧѧԺ
    Location[32] = QPoint(474 - 10, 263 + 5);  // ����
    Location[33] = QPoint(358 - 10, 234 + 5);  // ����
    Location[34] = QPoint(518 - 13, 213 + 5);  // ����¥
    Location[35] = QPoint(567 - 13, 189 + 5);  // ���¥
    Location[36] = QPoint(171 - 18, 74 + 5);   // ޥ԰ʳ��
    Location[37] = QPoint(166 - 18, 105 + 5);  // ޥ԰8-11
    Location[38] = QPoint(118 - 18, 50 + 5);   // ޥ԰1-7
    Location[39] = QPoint(46 - 18, 58 + 5);    // ��Է����
    Location[40] = QPoint(533 - 10, 341 + 5);  // ��԰
    Location[41] = QPoint(532 - 18, 313 + 5);  // ��԰ʳ��
    Location[42] = QPoint(563 - 10, 290 + 5);  // ��԰
    Location[43] = QPoint(569 - 10, 318 + 5);  // ��԰
    Location[44] = QPoint(604 - 18, 319 + 5);  // ��7����
    Location[45] = QPoint(323 - 24, 166 + 5);  // ��¥A-D
    Location[46] = QPoint(258 - 20, 136 + 5);  // ��¥E-H
    Location[47] = QPoint(318 - 24, 221 + 5);  // ˮ�ϱ�����
    Location[48] = QPoint(302 - 13, 284 + 5);  // ������
    Location[49] = QPoint(647 - 13, 94 + 5);   // �ϳ���

    // 4  ����2·��
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

    // 5  ·��2����
    Name[23] = string("УҽԺ");
    Name[20] = string("�����");
    Name[5] = string("÷԰");
    Name[25] = string("��԰");
    Name[27] = string("÷԰ʳ��");
    Name[29] = string("��԰");
    Name[1] = string("�ĵ��");
    Name[7] = string("����");
    Name[11] = string("�Ʊ�");
    Name[3] = string("��԰");
    Name[22] = string("���ų���");
    Name[64] = string("��԰");
    Name[65] = string("��԰");
    Name[68] = string("��԰ʳ��");
    Name[69] = string("�������");
    Name[74] = string("��԰");
    Name[72] = string("��԰ʳ��");
    Name[75] = string("��԰");
    Name[76] = string("��԰");
    Name[24] = string("����");
    Name[77] = string("������");
    Name[49] = string("������");
    Name[79] = string("����");
    Name[87] = string("������ ");
    Name[102] = string("����");
    Name[15] = string("��֪¥");
    Name[17] = string("����¥");
    Name[19] = string("����");
    Name[55] = string("����¥");
    Name[54] = string("����");
    Name[42] = string("����");
    Name[53] = string("���Ͽ�ѧѧԺ");
    Name[8] = string("����");
    Name[12] = string("����");
    Name[63] = string("����¥");
    Name[57] = string("���¥");
    Name[96] = string("ޥ԰ʳ��");
    Name[95] = string("ޥ԰8-11");
    Name[97] = string("ޥ԰1-7");
    Name[100] = string("��Է���� ");
    Name[34] = string("��԰");
    Name[37] = string("��԰ʳ��");
    Name[39] = string("��԰ ");
    Name[40] = string("��԰");
    Name[41] = string("��7����");
    Name[92] = string("��¥A-D");
    Name[90] = string("��¥E-H");
    Name[86] = string("ˮ�ϱ�����");
    Name[70] = string("������ ");
    Name[56] = string("�ϳ��� ");

    // 6  ·��
    Point[0] = QPoint(374, 329); //ͼ������
    Point[1] = QPoint(394, 337); //ͼ���
    Point[2] = QPoint(418, 341); //ͼ����Ҳ�
    Point[3] = QPoint(346, 353); //��԰
    Point[4] = QPoint(365, 359); //��԰�Ҳ�
    Point[5] = QPoint(427, 379); //÷԰
    Point[6] = QPoint(408, 371); //÷԰���
    Point[7] = QPoint(431, 295); //����
    Point[8] = QPoint(441, 257); //����
    Point[9] = QPoint(437, 273); //�����·�
    Point[10] = QPoint(447, 234); //�����Ϸ�
    Point[11] = QPoint(386, 282); //�Ʊ�
    Point[12] = QPoint(397, 241); //����
    Point[13] = QPoint(391, 261); //�����·�
    Point[14] = QPoint(402, 222); //�����Ϸ�
    Point[15] = QPoint(411, 189); //��֪¥
    Point[16] = QPoint(406, 205); //��֪¥�·�
    Point[17] = QPoint(458, 194); //����¥
    Point[18] = QPoint(452, 217); //����¥�·�
    Point[19] = QPoint(443, 160); //����
    Point[20] = QPoint(397, 395); //���
    Point[21] = QPoint(366, 390); //����·��
    Point[22] = QPoint(362, 374); //���ų���
    Point[23] = QPoint(350, 405); //УҽԺ
    Point[24] = QPoint(341, 413); //����
    Point[25] = QPoint(442, 384); //��԰
    Point[26] = QPoint(458, 388); //��԰�Ҳ�
    Point[27] = QPoint(462, 374); //÷԰ʳ��
    Point[28] = QPoint(469, 354); //��԰���
    Point[29] = QPoint(492, 361); //��԰
    Point[30] = QPoint(472, 335); //��԰����
    Point[31] = QPoint(510, 364); //��԰�Ҳ�
    Point[32] = QPoint(521, 330); //��԰���
    Point[33] = QPoint(506, 318); //��԰����
    Point[34] = QPoint(534, 333); //��԰
    Point[35] = QPoint(546, 335); //��԰�Ҳ�
    Point[36] = QPoint(553, 306); //��԰ʳ���Ҳ�
    Point[37] = QPoint(539, 302); //��԰ʳ��
    Point[38] = QPoint(526, 298); //��԰ʳ�����
    Point[39] = QPoint(561, 306); //��԰
    Point[40] = QPoint(573, 310); //��԰
    Point[41] = QPoint(587, 314); //��7����
    Point[42] = QPoint(602, 306); //����
    Point[43] = QPoint(478, 393); //÷԰ʳ���·�
    Point[44] = QPoint(508, 378); //÷԰ʳ������
    Point[45] = QPoint(545, 354); //��԰����
    Point[46] = QPoint(584, 338); //��7��������
    Point[47] = QPoint(604, 329); //��7��������
    Point[48] = QPoint(670, 295); //��������
    Point[49] = QPoint(659, 275); //������
    Point[50] = QPoint(649, 253); //��������
    Point[51] = QPoint(719, 271); //����������
    Point[52] = QPoint(698, 230); //����������
    Point[53] = QPoint(728, 198); //���Ͽ�ѧѧԺ
    Point[54] = QPoint(745, 142); //����
    Point[55] = QPoint(622, 145); //����¥
    Point[56] = QPoint(658, 122); //�ϳ���
    Point[57] = QPoint(587, 198); //���¥
    Point[58] = QPoint(578, 220); //���¥�·�
    Point[59] = QPoint(560, 259); //��԰�Ϸ�
    Point[60] = QPoint(541, 282); //��԰���
    Point[61] = QPoint(527, 258); //�����Ҳ�
    Point[62] = QPoint(530, 238); //����¥�Ҳ�
    Point[63] = QPoint(508, 232); //����¥
    Point[64] = QPoint(314, 345); //��԰
    Point[65] = QPoint(318, 330); //��԰
    Point[66] = QPoint(296, 342); //��԰���
    Point[67] = QPoint(299, 324); //��԰���
    Point[68] = QPoint(290, 311); //��԰ʳ��
    Point[69] = QPoint(279, 306); //�������
    Point[70] = QPoint(327, 293); //������
    Point[71] = QPoint(304, 250); //�Ʊ����
    Point[72] = QPoint(289, 254); //��԰ʳ��
    Point[73] = QPoint(284, 277); //��԰�Ҳ�
    Point[74] = QPoint(265, 273); //��԰
    Point[75] = QPoint(243, 265); //��԰
    Point[76] = QPoint(222, 262); //��԰
    Point[77] = QPoint(250, 240); //�������·�
    Point[78] = QPoint(219, 226); //���������
    Point[79] = QPoint(172, 230); //����
    Point[80] = QPoint(115, 174); //�������·�
    Point[81] = QPoint(204, 271); //��԰�·�
    Point[82] = QPoint(257, 324); //��������·�
    Point[83] = QPoint(284, 354); //��԰ʳ���·�
    Point[84] = QPoint(310, 386); //��԰����
    Point[85] = QPoint(334, 390); //УҽԺ���
    Point[86] = QPoint(333, 245); //ˮ�ϱ�����
    Point[87] = QPoint(156, 154); //������
    Point[88] = QPoint(232, 175); //��������
    Point[89] = QPoint(294, 194); //����������
    Point[90] = QPoint(240, 149); //����E-H
    Point[91] = QPoint(282, 169); //��¥�·�
    Point[92] = QPoint(326, 183); //��¥A-D
    Point[93] = QPoint(143, 123); //ޥ԰8-11�·�
    Point[94] = QPoint(192, 135); //ޥ԰8-11����
    Point[95] = QPoint(206, 106); //ޥ԰8-11�Ҳ�
    Point[96] = QPoint(166, 88);  //ޥ԰ʳ��
    Point[97] = QPoint(118, 73);  //ޥ԰1-7
    Point[98] = QPoint(90, 66);   //ޥ԰1-7����
    Point[99] = QPoint(80, 82);   //��Է�����Ҳ�
    Point[100] = QPoint(56, 77);  //��Է����
    Point[101] = QPoint(84, 109); //����������
    Point[102] = QPoint(64, 122); //����
    Point[103] = QPoint(418, 170); //�м̽��1
    Point[104] = QPoint(456, 174); //�м̽��2
    Point[105] = QPoint(342, 208); //ˮ�ϱ���������

    // 7  ��·
    Route[0] = pair(3, 4);   //��԰----------��԰�Ҳ�
    Route[1] = pair(4, 0);    //��԰�Ҳ�-------ͼ������
    Route[2] = pair(0, 1);    //ͼ������-----ͼ���
    Route[3] = pair(1, 2);    //ͼ���--------ͼ����Ҳ�
    Route[4] = pair(2, 6);   //ͼ����Ҳ�-----÷԰���
    Route[5] = pair(6, 5);   //÷԰���-------÷԰
    Route[6] = pair(2, 7);   //ͼ����Ҳ�-----����
    Route[7] = pair(7, 9);   //����----------�����·�
    Route[8] = pair(9, 8);   //�����·�-------����
    Route[9] = pair(8, 10);  //����----------�����Ϸ�
    Route[10] = pair(10, 18);  //�����Ϸ�-------����¥�·�
    Route[11] = pair(18, 17);  //����¥�·�-----����¥
    Route[12] = pair(0, 11);   //ͼ������-----�Ʊ�
    Route[13] = pair(11, 13);  //�Ʊ�----------�����·�
    Route[14] = pair(13, 12);  //�����·�-------����
    Route[15] = pair(12, 14);  //����----------�����Ϸ�
    Route[16] = pair(14, 16);  //�����Ϸ�-------��֪¥�·�
    Route[17] = pair(16, 15);  //��֪¥�·�-----��֪¥
    Route[18] = pair(4, 22);   //��԰�Ҳ�-------���ų���
    Route[19] = pair(22, 21);  //���ų���-------����·��
    Route[20] = pair(21, 20);  //����·��-------�����
    Route[21] = pair(20, 6);   //�����-------��԰���
    Route[22] = pair(21, 23);  //���ų���-------УҽԺ
    Route[23] = pair(23, 24);  //УҽԺ---------����
    Route[24] = pair(5, 25);   //÷԰----------��԰
    Route[25] = pair(25, 26);  //��԰----------��԰�Ҳ�
    Route[26] = pair(26, 27);  //��԰�Ҳ�-------÷԰ʳ��
    Route[27] = pair(27, 28);  //÷԰ʳ��-------��԰���
    Route[28] = pair(28, 29);  //��԰���-------��԰
    Route[29] = pair(28, 30);  //��԰���-------��԰����
    Route[30] = pair(30, 2);   //��԰����-------ͼ����Ҳ�
    Route[31] = pair(29, 31);   //��԰----------��԰�Ҳ�
    Route[32] = pair(31, 32);   //��԰�Ҳ�-------��԰���
    Route[33] = pair(32, 34);   //��԰���-------��԰
    Route[34] = pair(32, 33);   //��԰���-------��԰����
    Route[35] = pair(34, 35);   //��԰----------��԰�Ҳ�
    Route[36] = pair(35, 36);   //��԰�Ҳ�-------��԰ʳ���Ҳ�
    Route[37] = pair(36, 37);   //��԰ʳ���Ҳ�----��԰ʳ��
    Route[38] = pair(37, 38);   //��԰ʳ��-------��԰ʳ�����
    Route[39] = pair(38, 9);    //��԰ʳ�����----�����·�
    Route[40] = pair(30, 33);   //��԰����-------��԰����
    Route[41] = pair(33, 38);   //��԰����-------��԰ʳ�����
    Route[42] = pair(36, 39);   //��԰ʳ���Ҳ�----��԰
    Route[43] = pair(39, 40);   //��԰----------��԰
    Route[44] = pair(40, 41);   //��԰----------��7����
    Route[45] = pair(41, 42);   //��7����--------����
    Route[46] = pair(17, 104);  //����¥--------�м̽��2
    Route[47] = pair(15, 103);  //��֪¥--------�м̽��1
    Route[48] = pair(26, 43);   //��԰�Ҳ�-------÷԰ʳ���·�
    Route[49] = pair(43, 44);   //÷԰ʳ���·�----÷԰ʳ������
    Route[50] = pair(44, 45);   //÷԰ʳ������----��԰����
    Route[51] = pair(45, 46);   //��԰����-------��7��������
    Route[52] = pair(46, 47);   //��7��������----��7��������
    Route[53] = pair(31, 44);   //��԰�Ҳ�-------÷԰ʳ������
    Route[54] = pair(35, 45);   //��԰�Ҳ�-------��԰����
    Route[55] = pair(41, 46);   //��7����--------��7��������
    Route[56] = pair(42, 47);   //����-----------��7��������
    Route[57] = pair(47, 48);   //��7��������-----��������
    Route[58] = pair(48, 49);   //��������--------������
    Route[59] = pair(49, 50);   //������--------��������
    Route[60] = pair(48, 51);   //��������--------����������
    Route[61] = pair(51, 52);   //����������-----����������
    Route[62] = pair(52, 53);   //����������-----���Ͽ�ѧ��¥
    Route[63] = pair(53, 54);   //���Ͽ�ѧ��¥-----����
    Route[64] = pair(54, 56);   //����-----------�ϳ���
    Route[65] = pair(56, 55);   //�ϳ���---------����¥
    Route[66] = pair(55, 57);   //����¥---------���¥
    Route[67] = pair(57, 58);   //���¥---------���¥�·�
    Route[68] = pair(58, 59);   //���¥�·�------��԰�Ϸ�
    Route[69] = pair(59, 60);   //��԰�Ϸ�--------��԰���
    Route[70] = pair(60, 61);   //��԰���--------�����Ҳ�
    Route[71] = pair(61, 62);   //�����Ҳ�--------����¥�Ҳ�
    Route[72] = pair(62, 63);   //����¥�Ҳ�------����¥
    Route[73] = pair(63, 18);   //����¥---------����¥�·�
    Route[74] = pair(61, 10);   //�����Ҳ�--------�����Ϸ�
    Route[75] = pair(58, 62);   //���¥�·�------����¥�Ҳ�
    Route[76] = pair(59, 50);   //��԰�Ϸ�--------��������
    Route[77] = pair(50, 52);   //��������--------����������
    Route[78] = pair(10, 14);   //�����Ϸ�--------�����Ϸ�
    Route[79] = pair(3, 64);    //��԰-----------��԰
    Route[80] = pair(64, 65);   //��԰-----------��԰
    Route[81] = pair(64, 66);   //��԰-----------��԰���
    Route[82] = pair(66, 67);   //��԰���--------��԰���
    Route[83] = pair(67, 68);   //��԰���--------��԰ʳ��
    Route[84] = pair(68, 69);   //��԰ʳ��--------�������
    Route[85] = pair(68, 70);   //��԰ʳ��--------������
    Route[86] = pair(70, 0);    //������----------ͼ������
    Route[87] = pair(70, 71);   //������----------�Ʊ����
    Route[88] = pair(71, 72);   //�Ʊ����--------��԰ʳ��
    Route[89] = pair(72, 73);   //��԰ʳ��--------��԰�Ҳ�
    Route[90] = pair(73, 69);   //��԰�Ҳ�--------�������
    Route[91] = pair(73, 74);   //��԰�Ҳ�--------��԰
    Route[92] = pair(74, 75);   //��԰-----------��԰
    Route[93] = pair(75, 76);   //��԰-----------��԰
    Route[94] = pair(75, 77);   //��԰-----------�������·�
    Route[95] = pair(77, 78);   //�������·�-----���������
    Route[96] = pair(78, 79);   //���������-----����
    Route[97] = pair(79, 80);   //����-----------�������·�
    Route[98] = pair(79, 81);   //����-----------��԰�·�
    Route[99] = pair(81, 76);   //��԰�·�--------��԰
    Route[100] = pair(81, 82);  //��԰�·�-------��������·�
    Route[101] = pair(82, 69);   //��������·�----�������
    Route[102] = pair(82, 83);   //��������·�----��԰ʳ���·�
    Route[103] = pair(83, 84);   //��԰ʳ���·�----��԰����
    Route[104] = pair(83, 66);   //��԰ʳ���·�----��԰���
    Route[105] = pair(84, 85);   //��԰����-------УҽԺ���
    Route[106] = pair(85, 3);    //��԰�·�-------��԰
    Route[107] = pair(71, 86);   //�Ʊ����-------ˮ�ϱ�����
    Route[108] = pair(86, 9);    //ˮ�ϱ�����------�����·�
    Route[109] = pair(67, 65);   //��԰���-------��԰
    Route[110] = pair(72, 77);   //��԰ʳ��-------�������·�
    Route[111] = pair(43, 29);   //÷԰ʳ���·�----��԰
    Route[112] = pair(80, 87);   //�������·�------������
    Route[113] = pair(87, 88);   //������---------��������
    Route[114] = pair(88, 89);   //��������-------����������
    Route[115] = pair(89, 71);   //����������----�Ʊ����
    Route[116] = pair(89, 105);  //����������----ˮ�ϱ���������
    Route[117] = pair(89, 91);   //����������----��¥�·�
    Route[118] = pair(91, 92);   //��¥�·�------��¥A-D
    Route[119] = pair(92, 16);   //��¥A-D------��֪¥�·�
    Route[120] = pair(91, 90);   //��¥�·�------��¥E-H
    Route[121] = pair(90, 88);    //��¥E-H------��������
    Route[122] = pair(90, 94);    //��¥E-H------ޥ԰8-11����
    Route[123] = pair(94, 93);    //ޥ԰8-11����----ޥ԰8-11�·�
    Route[124] = pair(94, 95);    //ޥ԰8-11����----ޥ԰8-11�Ҳ�
    Route[125] = pair(95, 96);    //ޥ԰8-11�Ҳ�----ޥ԰ʳ��
    Route[126] = pair(96, 97);    //ޥ԰ʳ��--------ޥ԰1-7
    Route[127] = pair(97, 98);    //ޥ԰1-7--------ޥ԰1-7����
    Route[128] = pair(98, 99);    //ޥ԰1-7����-----��Է�����Ҳ�
    Route[129] = pair(100, 99);   //��Է����-------��Է�����Ҳ�
    Route[130] = pair(99, 101);   //��Է�����Ҳ�----����������
    Route[131] = pair(101, 102);  //����������-----����
    Route[132] = pair(101, 93);   //����������------ޥ԰8-11�·�
    Route[133] = pair(87, 93);    //������---------ޥ԰8-11�·�
    Route[134] = pair(88, 78);    //��������-------���������
    Route[135] = pair(103, 19);   //�м̽��1------����
    Route[136] = pair(104, 19);   //�м̽��2------����
    Route[137] = pair(105, 14);   //ˮ�ϱ���������---�����Ϸ�
    Route[138] = pair(105, 86);   //ˮ�ϱ���������---ˮ�ϱ�����
    Route[139] = pair(38, 60);    //��԰ʳ�����---��԰���
    // 8  ��ͼ
    for (int i = 0; i < Route.size(); i++) {
        map_method[Route[i]] = round(sqrt(pow((Point[Route[i].first].x() - Point[Route[i].second].x()), 2) + pow((Point[Route[i].first].y() - Point[Route[i].second].y()), 2)));
    }
}

//��ʾ�ַ�����-1��ʾ·�ߣ�0-2��ʾ��ʾ��Ϣ��
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
            Show += "���й滮:";
        else if (mode_Plan == 1)
            Show += "���й滮:";
        else
            Show += "�ݳ��滮:";
        // ����·��
        int j = 1;
        for (auto& v : Planning[mode_Plan]) {
            Show += "\n" + to_string(j) + ": ";
            auto it = v.begin();
            for (; it < v.end() - 1; ++it) {
                // ����д˵ص㣬�������ʾ
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
        Show += "\n�滮˵��:\n";
        if (mode_Plan == 0) {
            Show += "��Ϊ���滮������̵�·��";
        }
        else if (mode_Plan == 1) {
            Show += "�ڱ�֤������Խ϶̵�ǰ���£���Ϊ���滮;�к��и���ͣ�����·��";
        }
        else {
            Show += "�ڱ�֤������Խ϶̵�ǰ���£���Ϊ���滮;�к��и���ͣ����͸�������·�ε�·��";
        }
        Show += "\n��ܰ��ʾ:";
        Show += "\n �� �� : ";
        if (T <= 0)
            Show += "��������������ע�ⱣůŶ��";
        else if (T <= 15)
            Show += "����������һ���������ӣ�";
        else if (T <= 25)
            Show += "�¶����ʣ�";
        else if (T <= 35)
            Show += "��������������ע��������";
        else
            Show += "�����������������ٳ���Ŷ��";
        Show += "\n �� �� : ";
        if (Weather == 1)
            Show += "������գ����г�ͨ��";
        else if (Weather == 2 || Weather == 3)
            Show += "�е����꣬ע�����ʪ�����ǵô�ɡ��";
        else if (Weather == 4)
            Show += "С����棡";
        else if (Weather == 5)
            Show += "�δ���������н�����";
        else if (Weather == 6)
            Show += "��Сѩ������������ѩ������ҲҪע����°�ȫŶ��";
        else if (Weather == 7 || Weather == 8)
            Show += "�е���ѩ��ע��·���ѩ������ˤ���������У�";
        else
            Show += "�����������������ʣ�";
        return Show;
    }
}

//�������Ӧ
void optimal_path_planning::mousePressEvent(QMouseEvent* event)
{
    
    QPoint pos = event->pos();  // ��ȡ�������λ��
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

//��������ģʽ
void optimal_path_planning::Adjust(void)
{
    mode = (mode + 1) % 3;
    if (mode == 0) {
        ui.label_12->setText(QString::fromLocal8Bit("��ʼλ��"));
    }
    else if (mode == 1) {
        ui.label_12->setText(QString::fromLocal8Bit("Ŀ��λ��"));
    }
    else {
        ui.label_12->setText(QString::fromLocal8Bit("��;λ��"));
    }
}

//ɾ����;�ص�
void optimal_path_planning::Delete(void)
{
    if (Way.size() > 2) {
        Way.erase(Way.end() - 2);
        ui.textBrowser_4->setText(QString::fromLocal8Bit(GetShow(-1)));
    }
}

//��ʾ�ر�
void optimal_path_planning::ShowLandmark(void)
{
    isShowLandmark = !isShowLandmark;
    if (isShowLandmark) {
        ui.pushButton_3->setText(QString::fromLocal8Bit(" �� �� "));
    }
    else {
        ui.pushButton_3->setText(QString::fromLocal8Bit(" �� �� "));
    }
    Draw();
}

//��������
void optimal_path_planning::updateWT(void)
{
    hour = ui.spinBox->value();
    minute = ui.spinBox_2->value();
    T = Time2T[hour];
    ui.label_9->setText(QString::fromLocal8Bit(Weather2Name[Weather] + to_string(T) + "�� "));
}

//ȷ�ϣ���ʼ�滮��
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

//������ʾ�滮
void optimal_path_planning::change(void)
{
    if (!Planning.empty()) {
        mode_Plan = (mode_Plan + 1) % 3;
        ui.textBrowser->setText(QString::fromLocal8Bit(GetShow(mode_Plan)));
        Draw();
    }
}



