#include "method.h"

method::method(int hour, int minute, vector<int> Way, int Weather, int T, map<pair<int, int>, int> map_method)
{
    tit.hour = hour;
    tit.minute = minute;
    tit.Way = Way;
    tit.Weather = Weather;
    tit.T = T;
    tit.map_Walk = tit.map_Ride = tit.map_Drive = map_method;
    init();
}

method::~method()
{}

void method::init(void)
{
    // 1  ȷ���߷�ʱ���
    tit.Peak.push_back(pair(pair(7, 30), pair(8, 30)));     //���
    tit.Peak.push_back(pair(pair(11, 0), pair(11, 25)));    //�����ڿ��¿�
    tit.Peak.push_back(pair(pair(11, 55), pair(12, 25)));   //���Ľڿ��¿�
    tit.Peak.push_back(pair(pair(13, 40), pair(14, 10)));   //�����Ͽ�
    tit.Peak.push_back(pair(pair(16, 30), pair(16, 55)));   //���߽ڿ��¿�
    tit.Peak.push_back(pair(pair(17, 25), pair(17, 55)));   //�ڰ˽ڿ��¿�
    tit.Peak.push_back(pair(pair(18, 40), pair(19, 10)));   //�����Ͽ�
    tit.Peak.push_back(pair(pair(21, 30), pair(21, 55)));   //��ʮһ�ڿ��¿�

    // 2  ȷ������·��
    tit.Limit.push_back(pair(89, 71)); // 155
    tit.Limit.push_back(pair(70, 71)); // 87
    tit.Limit.push_back(pair(70, 0));  // 86
    tit.Limit.push_back(pair(0, 1));   // 2
    tit.Limit.push_back(pair(1, 2));   // 3
    tit.Limit.push_back(pair(30, 2));  // 30
    tit.Limit.push_back(pair(30, 33)); // 40
    tit.Limit.push_back(pair(33, 38)); // 41
    tit.Limit.push_back(pair(38, 60)); // 139
    tit.Limit.push_back(pair(59, 60)); // 69

    // 3  ȷ��ͣ����
    tit.stopRide.push_back(1);  //ͼ���
    tit.stopRide.push_back(7);  //����
    tit.stopRide.push_back(11); //�Ʊ�
    tit.stopRide.push_back(8);  //����
    tit.stopRide.push_back(12); //����
    tit.stopRide.push_back(15); //��֪¥
    tit.stopRide.push_back(17); //����¥
    tit.stopRide.push_back(19); //����
    tit.stopRide.push_back(20); //���
    tit.stopRide.push_back(22); //���ų���
    tit.stopRide.push_back(24); //����
    tit.stopRide.push_back(25); //��԰
    tit.stopRide.push_back(29); //��԰
    tit.stopRide.push_back(34); //��԰
    tit.stopRide.push_back(37); //��԰ʳ��
    tit.stopRide.push_back(39); //��԰
    tit.stopRide.push_back(40); //��԰
    tit.stopRide.push_back(42); //����
    tit.stopRide.push_back(54); //����
    tit.stopRide.push_back(55); //����¥
    tit.stopRide.push_back(57); //���¥
    tit.stopRide.push_back(63); //����¥
    tit.stopRide.push_back(64); //��԰
    tit.stopRide.push_back(65); //��԰
    tit.stopRide.push_back(69); //�������
    tit.stopRide.push_back(74); //��԰
    tit.stopRide.push_back(75); //��԰
    tit.stopRide.push_back(76); //��԰
    tit.stopRide.push_back(79); //����
    tit.stopRide.push_back(87); //������
    tit.stopRide.push_back(96); //ޥ԰ʳ��
    tit.stopRide.push_back(100); //��Է����
    tit.stopRide.push_back(102); //����
    tit.stopRide.push_back(3);   //��԰
    tit.stopRide.push_back(5);   //÷԰
    tit.stopRide.push_back(27);  //÷԰ʳ��
    tit.stopRide.push_back(68);  //��԰ʳ��
    tit.stopRide.push_back(72);  //��԰ʳ��

    tit.stopDrive.push_back(8);  //����
    tit.stopDrive.push_back(12); //����
    tit.stopDrive.push_back(55); //����¥
    tit.stopDrive.push_back(100); //��Է����
    tit.stopDrive.push_back(37); //��԰ʳ��
    tit.stopDrive.push_back(7);  //����
    tit.stopDrive.push_back(11); //�Ʊ�
    tit.stopDrive.push_back(57); //���¥
    tit.stopDrive.push_back(63); //����¥

    // 4  ɾȥ����ͨ�еĵ�·�����У��ݳ���
    tit.map_Ride.erase(pair(61, 62));  //71
    tit.map_Ride.erase(pair(105, 86)); //138
    tit.map_Ride.erase(pair(68, 70));  //85
    // �ݳ�
    tit.map_Drive.erase(pair(61, 62));  //71
    tit.map_Drive.erase(pair(105, 86)); //138
    tit.map_Drive.erase(pair(68, 70));  //85
    tit.map_Drive.erase(pair(32, 33));  //34

    // 5  ������·״̬
    // 5.1  ���� 
    for (auto& v : tit.map_Walk) {
        // ��������������·״̬
        {
            if (tit.Weather == 1 || tit.Weather == 5 || tit.Weather == 6)
                v.second *= 1.2;
            else if (tit.Weather == 2 || tit.Weather == 3 || tit.Weather == 7 || tit.Weather == 8)
                v.second *= 1.5;
            else
                v.second *= 1;
        }
        // �������µ�����·״̬
        {
            if (tit.T <= 0 || tit.T > 35)
                v.second *= 1.5;
            else if (tit.T <= 15 || tit.T > 25)
                v.second *= 2;
            else
                v.second *= 1;
        }
        // �������¿θ߷������·״̬
        {
            if (tit.isInPeak())
                v.second *= 1.2;
        }
        // �������ٵ������·״̬
        {
            v.second *= 1;
        }
    }
    // 5.2  ����
    for (auto& v : tit.map_Ride) {
        // ��������������·״̬
        {
            if (tit.Weather == 1 || tit.Weather == 6)
                v.second *= 1.2;
            else if (tit.Weather == 5)
                v.second *= 1.5;
            else if (tit.Weather == 2 || tit.Weather == 3 || tit.Weather == 7 || tit.Weather == 8)
                v.second *= 2;
            else
                v.second *= 1;
        }
        // �������µ�����·״̬
        {
            if (tit.T <= 0)
                v.second *= 1.5;
            else if (tit.T <= 15)
                v.second *= 1.2;
            else
                v.second *= 1;
        }
        // �������¿θ߷������·״̬
        {
            if (tit.isInPeak())
                v.second *= 1.5;
        }
        // ����ͣ���������·״̬
        {
            if (!tit.isInStop(v.first, 1))
                v.second *= 1.2;
        }
        // �������ٵ������·״̬
        {
            if (tit.isInLimit(v.first))
                v.second *= 1.2;
        }
    }
    // 5.3  �ݳ�
    for (auto& v : tit.map_Drive) {
        // ��������������·״̬
        {
            if (tit.Weather == 1 || tit.Weather == 6)
                v.second *= 1.2;
            else if (tit.Weather == 2 || tit.Weather == 3 || tit.Weather == 7 || tit.Weather == 8)
                v.second *= 1.5;
            else
                v.second *= 1;
        }
        // �������µ�����·״̬
        {
            v.second *= 1;
        }
        // �������¿θ߷������·״̬
        {
            if (tit.isInPeak())
                v.second *= 2;
        }
        // ����ͣ���������·״̬
        {
            if (!tit.isInStop(v.first, 2))
                v.second *= 1.5;
        }
        // �������ٵ������·״̬
        {
            if (tit.isInLimit(v.first))
                v.second *= 1.5;
        }
    }
}

mutex mutex1;
void method::Dijkstra(int Start, int End, map<pair<int, int>, int>& map_method, vector<int>&ans, int& flag)
{
    vector<int> distance(106, INT_MAX); //����
    vector<int> previous(106, -1);      //ǰ���ڵ�
    // ��С�Ѵ�����
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    // �����������ȶ��У���������Ϊ0
    pq.push(make_pair(0, Start));
    distance[0] = 0;
    while (!pq.empty()) {
        int current = pq.top().second;
        pq.pop();
        // ������ǰ������ھ�
        for (int i = 0; i < 106; ++i) {
            if (i == current) {
                continue;
            }
            int newDistance = -1;
            if (map_method.find(make_pair(current, i)) != map_method.end()) {
                newDistance = distance[current] + map_method[make_pair(current, i)];
            }
            else if (map_method.find(make_pair(i, current)) != map_method.end()) {
                newDistance = distance[current] + map_method[make_pair(i, current)];
            }
            else {
                continue;
            }
            // ����ҵ��˸��̵�·��������¾����ǰ���ڵ�
            if (newDistance < distance[i]) {
                distance[i] = newDistance;
                previous[i] = current;
                pq.push(make_pair(newDistance, i));
            }
        }
    }
    // ����ǰ���ڵ����鹹�����·��
    int current = End;
    ans.clear();
    while (current != Start) {
        ans.push_back(current);
        current = previous[current];
    }
    ans.push_back(Start);
    // �����·����ת��ʹ�䰴����㵽�յ��˳��
    reverse(ans.begin(), ans.end());
    mutex1.lock();
    flag += 1;
    mutex1.unlock();
}

void method::createThread(method* W)
{
    
    vector<vector<int> >wayWalk(W->tit.Way.size() - 1);
    vector<vector<int> >wayRide(W->tit.Way.size() - 1);
    vector<vector<int> >wayDrive(W->tit.Way.size() - 1);
    W->tit.flagWalk = W->tit.flagRide = W->tit.flagDrive = 0;
    for (int i = 0; i < W->tit.Way.size() - 1; i++) {
        thread t1(W->Dijkstra, W->tit.Way[i], W->tit.Way[i + 1], ref(W->tit.map_Walk), ref(wayWalk[i]), ref(W->tit.flagWalk));
        t1.detach();
        thread t2(W->Dijkstra, W->tit.Way[i], W->tit.Way[i + 1], ref(W->tit.map_Ride), ref(wayRide[i]), ref(W->tit.flagRide));
        t2.detach();
        thread t3(W->Dijkstra, W->tit.Way[i], W->tit.Way[i + 1], ref(W->tit.map_Drive), ref(wayDrive[i]), ref(W->tit.flagDrive));
        t3.detach();
    }
    W->tit.Planning.clear();
    W->tit.Planning.resize(3);

    while (W->tit.flagWalk < W->tit.Way.size() - 1);
    W->tit.Planning[0] = wayWalk;
    while (W->tit.flagRide < W->tit.Way.size() - 1);
    W->tit.Planning[1] = wayRide;
    while (W->tit.flagDrive < W->tit.Way.size() - 1);
    W->tit.Planning[2] = wayDrive;
}

void method::route_Planning(void)
{
    thread t(createThread, this);
    t.join();
}

vector<vector<vector<int>>> method::get_Planning(void)
{
    return tit.Planning;
}

bool method::get_flag(void)
{
    return ((tit.flagWalk == tit.Way.size() - 1) && (tit.flagRide == tit.Way.size() - 1) && (tit.flagDrive == tit.Way.size() - 1));
}

