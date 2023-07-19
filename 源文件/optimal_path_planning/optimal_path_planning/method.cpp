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
    // 1  确定高峰时间段
    tit.Peak.push_back(pair(pair(7, 30), pair(8, 30)));     //早八
    tit.Peak.push_back(pair(pair(11, 0), pair(11, 25)));    //第三节课下课
    tit.Peak.push_back(pair(pair(11, 55), pair(12, 25)));   //第四节课下课
    tit.Peak.push_back(pair(pair(13, 40), pair(14, 10)));   //下午上课
    tit.Peak.push_back(pair(pair(16, 30), pair(16, 55)));   //第七节课下课
    tit.Peak.push_back(pair(pair(17, 25), pair(17, 55)));   //第八节课下课
    tit.Peak.push_back(pair(pair(18, 40), pair(19, 10)));   //晚上上课
    tit.Peak.push_back(pair(pair(21, 30), pair(21, 55)));   //第十一节课下课

    // 2  确定限速路段
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

    // 3  确定停车点
    tit.stopRide.push_back(1);  //图书馆
    tit.stopRide.push_back(7);  //笃南
    tit.stopRide.push_back(11); //笃北
    tit.stopRide.push_back(8);  //博南
    tit.stopRide.push_back(12); //博北
    tit.stopRide.push_back(15); //行知楼
    tit.stopRide.push_back(17); //艺术楼
    tit.stopRide.push_back(19); //东门
    tit.stopRide.push_back(20); //大活
    tit.stopRide.push_back(22); //西门超市
    tit.stopRide.push_back(24); //西门
    tit.stopRide.push_back(25); //松园
    tit.stopRide.push_back(29); //竹园
    tit.stopRide.push_back(34); //槐园
    tit.stopRide.push_back(37); //桂园食堂
    tit.stopRide.push_back(39); //桂园
    tit.stopRide.push_back(40); //枫园
    tit.stopRide.push_back(42); //南体
    tit.stopRide.push_back(54); //南门
    tit.stopRide.push_back(55); //行政楼
    tit.stopRide.push_back(57); //社科楼
    tit.stopRide.push_back(63); //人文楼
    tit.stopRide.push_back(64); //桔园
    tit.stopRide.push_back(65); //李园
    tit.stopRide.push_back(69); //快递中心
    tit.stopRide.push_back(74); //榴园
    tit.stopRide.push_back(75); //枣园
    tit.stopRide.push_back(76); //杏园
    tit.stopRide.push_back(79); //北体
    tit.stopRide.push_back(87); //体育馆
    tit.stopRide.push_back(96); //蕙园食堂
    tit.stopRide.push_back(100); //磬苑宾馆
    tit.stopRide.push_back(102); //北门
    tit.stopRide.push_back(3);   //桃园
    tit.stopRide.push_back(5);   //梅园
    tit.stopRide.push_back(27);  //梅园食堂
    tit.stopRide.push_back(68);  //桔园食堂
    tit.stopRide.push_back(72);  //榴园食堂

    tit.stopDrive.push_back(8);  //博南
    tit.stopDrive.push_back(12); //博北
    tit.stopDrive.push_back(55); //行政楼
    tit.stopDrive.push_back(100); //磬苑宾馆
    tit.stopDrive.push_back(37); //桂园食堂
    tit.stopDrive.push_back(7);  //笃南
    tit.stopDrive.push_back(11); //笃北
    tit.stopDrive.push_back(57); //社科楼
    tit.stopDrive.push_back(63); //人文楼

    // 4  删去不能通行的道路（骑行，驾车）
    tit.map_Ride.erase(pair(61, 62));  //71
    tit.map_Ride.erase(pair(105, 86)); //138
    tit.map_Ride.erase(pair(68, 70));  //85
    // 驾车
    tit.map_Drive.erase(pair(61, 62));  //71
    tit.map_Drive.erase(pair(105, 86)); //138
    tit.map_Drive.erase(pair(68, 70));  //85
    tit.map_Drive.erase(pair(32, 33));  //34

    // 5  调整道路状态
    // 5.1  步行 
    for (auto& v : tit.map_Walk) {
        // 根据天气调整道路状态
        {
            if (tit.Weather == 1 || tit.Weather == 5 || tit.Weather == 6)
                v.second *= 1.2;
            else if (tit.Weather == 2 || tit.Weather == 3 || tit.Weather == 7 || tit.Weather == 8)
                v.second *= 1.5;
            else
                v.second *= 1;
        }
        // 根据气温调整道路状态
        {
            if (tit.T <= 0 || tit.T > 35)
                v.second *= 1.5;
            else if (tit.T <= 15 || tit.T > 25)
                v.second *= 2;
            else
                v.second *= 1;
        }
        // 根据上下课高峰调整道路状态
        {
            if (tit.isInPeak())
                v.second *= 1.2;
        }
        // 根据限速点调整道路状态
        {
            v.second *= 1;
        }
    }
    // 5.2  骑行
    for (auto& v : tit.map_Ride) {
        // 根据天气调整道路状态
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
        // 根据气温调整道路状态
        {
            if (tit.T <= 0)
                v.second *= 1.5;
            else if (tit.T <= 15)
                v.second *= 1.2;
            else
                v.second *= 1;
        }
        // 根据上下课高峰调整道路状态
        {
            if (tit.isInPeak())
                v.second *= 1.5;
        }
        // 根据停车点调整道路状态
        {
            if (!tit.isInStop(v.first, 1))
                v.second *= 1.2;
        }
        // 根据限速点调整道路状态
        {
            if (tit.isInLimit(v.first))
                v.second *= 1.2;
        }
    }
    // 5.3  驾车
    for (auto& v : tit.map_Drive) {
        // 根据天气调整道路状态
        {
            if (tit.Weather == 1 || tit.Weather == 6)
                v.second *= 1.2;
            else if (tit.Weather == 2 || tit.Weather == 3 || tit.Weather == 7 || tit.Weather == 8)
                v.second *= 1.5;
            else
                v.second *= 1;
        }
        // 根据气温调整道路状态
        {
            v.second *= 1;
        }
        // 根据上下课高峰调整道路状态
        {
            if (tit.isInPeak())
                v.second *= 2;
        }
        // 根据停车点调整道路状态
        {
            if (!tit.isInStop(v.first, 2))
                v.second *= 1.5;
        }
        // 根据限速点调整道路状态
        {
            if (tit.isInLimit(v.first))
                v.second *= 1.5;
        }
    }
}

mutex mutex1;
void method::Dijkstra(int Start, int End, map<pair<int, int>, int>& map_method, vector<int>&ans, int& flag)
{
    vector<int> distance(106, INT_MAX); //距离
    vector<int> previous(106, -1);      //前驱节点
    // 最小堆处理顶点
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    // 将起点加入优先队列，距离设置为0
    pq.push(make_pair(0, Start));
    distance[0] = 0;
    while (!pq.empty()) {
        int current = pq.top().second;
        pq.pop();
        // 遍历当前顶点的邻居
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
            // 如果找到了更短的路径，则更新距离和前驱节点
            if (newDistance < distance[i]) {
                distance[i] = newDistance;
                previous[i] = current;
                pq.push(make_pair(newDistance, i));
            }
        }
    }
    // 根据前驱节点数组构建最短路径
    int current = End;
    ans.clear();
    while (current != Start) {
        ans.push_back(current);
        current = previous[current];
    }
    ans.push_back(Start);
    // 将最短路径反转，使其按照起点到终点的顺序
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

