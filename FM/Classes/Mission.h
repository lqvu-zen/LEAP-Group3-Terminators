#ifndef __MISSION_H__
#define __MISSION_H__

#include "cocos2d.h"
#include "json/document.h"
#include "json//rapidjson.h"

using namespace std;



class Mission : public cocos2d::Scene
{
public:
    enum class TYPE {
        MONSTER, BOSS, ITEM
    };
    
    struct Reward {
        int id;
        int idMission;
        string name;
        int number;
        string type;
    };

    struct Data {
        int id;
        string request;
        string name;
        int type; //Monster : 1, Boss :2, Item: 3.
        int begin;
        int end;
        int state; //0 - to do mission //1 - doing mission //2 - complete the mission //3 - cancel the mission //4 - notice //5- get rewarded. 
    };
    
    Mission();

    Data getMission();

    Data getNowMission();

    Data get();

    void agreeMission();

    void cancelMission();

    void updateMission(int type);

    void submitMission();

    int getState();

    bool getProcesstate();
    void setProcesstate(bool state);

    int getIndexMission();

    vector<Reward> getReward();
    Data getMissionCompleted();
    void loadMission(int index, int id, int begin, int state, bool has);
private:
    vector<Data> data;
    Data mission;
    int index;

    vector<Reward> rewards;

    bool hasMission;

    void loadReward();
};

#endif // __MISSION_H__
