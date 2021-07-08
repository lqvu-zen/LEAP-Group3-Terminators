#ifndef __MISSION_H__
#define __MISSION_H__

#include "cocos2d.h"
#include "json/document.h"
#include "json//rapidjson.h"

using namespace std;



class Mission : public cocos2d::Scene
{
public:
   /* enum class TYPE {
        MONSTER, BOSS, ITEM
    };*/
    
    struct Data
    {
        int id;
        string request;
        string name;
        int type; //Monster : 1, Boss :2, Item: 3.
        int begin;
        int end;
        bool state;
    };
    
    Mission();

    Data getMission() {
        int i = 0;
        while (i < data.size()) {
            if (data.at(i).state == false) {
                mission = data.at(i);
                index = i;
                return mission;
            }
            i++;
        }
    }

    Data getNowMission() {
        if (hasMission) {
            if (mission.state == false)
                return mission;
            else
                return data.at(data.size() - 1);
        }
        else {
            return data.at(0);
        }
    }

    void agreeMission();

    void cancelMission();

    void updateMission(int type);

    void submitMission();

private:
    vector<Data> data;
    Data mission;
    int index;

    bool hasMission;
};

#endif // __MISSION_H__
