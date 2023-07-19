#pragma once

#include "vector"
#include "string"
#include "windows.h"
#include "map"
#include <queue>
#include <iostream>
#include "thread"
#include "mutex"
using namespace std;

//出行信息表(Travel information table)
typedef struct TIT {
	map<pair<int, int>, int> map_Walk;  //步行地图
	map<pair<int, int>, int> map_Ride;  //骑行地图
	map<pair<int, int>, int> map_Drive; //驾车地图

	vector<int> stopRide;  // 停车点
	vector<int> stopDrive; // 停车点
	vector<pair<int, int>> Limit; // 限速路段
	vector<pair<pair<int, int>, pair<int, int>>> Peak; // 高峰时间段

	vector<int> Way;   // 出行路线

	vector<vector<vector<int>>> Planning; //规划路线
	int flagWalk = 0, flagRide = 0, flagDrive = 0;

	int Weather; // 天气
	int T;       // 气温
	int hour;    // 出行时间
	int minute;  // 出行时间

	// 当前时间是否在某个时间段中
	bool isInPeriod(pair<pair<int, int>, pair<int, int>> b) const {
		if (hour > b.first.first && hour < b.second.first)
			return true;
		else if (hour == b.first.first && minute >= b.first.second)
			return true;
		else if (hour == b.second.first && minute <= b.second.second)
			return true;
		else
			return false;
	}
	// 当前时间是否在高峰时间段中
	bool isInPeak() const {
		for (const auto& v : Peak) {
			if (isInPeriod(v))
				return true;
		}
		return false;
	}
	// 该道路是否是限速路段
	bool isInLimit(pair<int, int> a) const {
		for (const auto& v : Limit) {
			if (a == v || a == pair(v.second, v.first))
				return true;
		}
		return false;
	}
	// 该道路周围是否含有停车点（flag = 1判断骑行；flag!=1判断驾车）
	bool isInStop(pair<int, int> a, int flag) const {
		if (flag == 1) {
			for (const auto& v : stopRide) {
				if (v == a.first || v == a.second)
					return true;
			}
			return false;
		}
		else {
			for (const auto& v : stopDrive) {
				if (v == a.first || v == a.second)
					return true;
			}
			return false;
		}
	}
}TIT;

class method {
public:
	method(int hour, int minute, vector<int> Way, int Weather, int T, map<pair<int, int>, int> map_method);
	~method();
	void init(void);	//数据初始化（包括调整地图信息）

	//规划两点之间的最优路径
	static void Dijkstra(int Start, int End, map<pair<int, int>, int>& map_method, vector<int>& ans, int& flag);	
	static void createThread(method*);				//创建安全线程
	void route_Planning(void);						//路径规划
	vector<vector<vector<int>>> get_Planning(void); //返回规划路线
	bool get_flag(void);

private:
	TIT tit;
};