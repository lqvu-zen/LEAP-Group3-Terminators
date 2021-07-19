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

    Data getMission() {
        if (hasMission) {
            hasMission = false;
            return mission;
        }
        else {
            int i = 0;
            while (i < data.size()) {
                if (data.at(i).state == 0) {
                    mission = data.at(i);
                    index = i;
                    return mission;
                }
                i++;
            }
            if (i == data.size()) {
                index = i;
                mission = data.at(index - 1);
                return mission;
            }
        }
    }

    Data getNowMission() {
        if (hasMission) {
            if (mission.state == 2) {
                mission = data.at(data.size() - 2);
            }
            return mission;
        }
        else {
            if (index == data.size()) {
                return mission;
            }
            return data.at(0);
        }
        
    }

    void agreeMission();

    void cancelMission();

    void updateMission(int type);

    void submitMission();

    int getState();

    vector<Reward> getReward();
private:
    vector<Data> data;
    Data mission;
    int index;

    vector<Reward> rewards;

    bool hasMission;

    void loadReward();
};

#endif // __MISSION_H__
