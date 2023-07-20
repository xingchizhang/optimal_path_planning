# optimal_path_planning
# 个人实训项目_最优路径规划
项目内容仅用作个人记录，部分本人信息已做打码处理  
# 项目描述  
## 实践内容：
根据下列要求实现最优路径规划模拟。  
1、界面友好；  
2、应用场景：安徽大学磬苑校区；  
2、起讫点、出行时间随机设置；  
3、给出步行、骑行和驾车三种出行方式的最优路径、以及缘由（例如天气、气温、停车点、限速点、上下课高峰、出行时间点、以及个性化偏好）；  
4、相关文档完整。  
## 基本要求：
1.针对算法设计与实现的不同类型的外在与内在限制条件，能够明确模块实现技术的关键环节；  
2.算法实现过程中开启多个安全线程计算特征嵌入;  
3.模型能够在三种出行方式中通用。  
## 设计重点：
1.算法所需初始值均为随机生成；  
2.算法实现过程中需要开启多个安全线程；  
3.算法实现过程中，线程共享、同步数据。  
## 实现难点：
1.多个安全线程特征共享；  
2.线程安全开启后，特征嵌入的共享性与及时性方面的处理。  

