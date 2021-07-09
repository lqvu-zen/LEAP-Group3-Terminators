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
        if (hasMission) {
            return mission;
            hasMission = false;
        }
        else {
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
    }

    Data getNowMission() {
        if (hasMission) {
            if (mission.state == true)
                mission = data.at(data.size() - 1);
            return mission;
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
