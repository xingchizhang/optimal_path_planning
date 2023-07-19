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

//������Ϣ��(Travel information table)
typedef struct TIT {
	map<pair<int, int>, int> map_Walk;  //���е�ͼ
	map<pair<int, int>, int> map_Ride;  //���е�ͼ
	map<pair<int, int>, int> map_Drive; //�ݳ���ͼ

	vector<int> stopRide;  // ͣ����
	vector<int> stopDrive; // ͣ����
	vector<pair<int, int>> Limit; // ����·��
	vector<pair<pair<int, int>, pair<int, int>>> Peak; // �߷�ʱ���

	vector<int> Way;   // ����·��

	vector<vector<vector<int>>> Planning; //�滮·��
	int flagWalk = 0, flagRide = 0, flagDrive = 0;

	int Weather; // ����
	int T;       // ����
	int hour;    // ����ʱ��
	int minute;  // ����ʱ��

	// ��ǰʱ���Ƿ���ĳ��ʱ�����
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
	// ��ǰʱ���Ƿ��ڸ߷�ʱ�����
	bool isInPeak() const {
		for (const auto& v : Peak) {
			if (isInPeriod(v))
				return true;
		}
		return false;
	}
	// �õ�·�Ƿ�������·��
	bool isInLimit(pair<int, int> a) const {
		for (const auto& v : Limit) {
			if (a == v || a == pair(v.second, v.first))
				return true;
		}
		return false;
	}
	// �õ�·��Χ�Ƿ���ͣ���㣨flag = 1�ж����У�flag!=1�жϼݳ���
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
	void init(void);	//���ݳ�ʼ��������������ͼ��Ϣ��

	//�滮����֮�������·��
	static void Dijkstra(int Start, int End, map<pair<int, int>, int>& map_method, vector<int>& ans, int& flag);	
	static void createThread(method*);				//������ȫ�߳�
	void route_Planning(void);						//·���滮
	vector<vector<vector<int>>> get_Planning(void); //���ع滮·��
	bool get_flag(void);

private:
	TIT tit;
};