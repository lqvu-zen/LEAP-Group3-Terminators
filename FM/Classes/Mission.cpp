#include "Mission.h"
#include "Character.h"
#include "Definitions.h"

USING_NS_CC;

Mission::Mission() {
	std::string str = FileUtils::getInstance()->getStringFromFile("res/mission.json");
	CCLOG("s", str.c_str());
	rapidjson::Document doc;
	doc.Parse<0>(str.c_str());
	if (doc.HasParseError()) {
		CCLOG("ERROR!!");
	}
	else {
		if (doc.HasMember("MISSION")) {
			rapidjson::Value& mission = doc["MISSION"];
			for (rapidjson::SizeType i = 0; i < mission.Size(); i++) {
				//CCLOG("ID: %i, Name: %s, State: %d", mission[i]["ID"].GetInt(), mission[i]["NAME"].GetString(), mission[i]["STATE"].GetBool());
				Data tmp;
				tmp.id = mission[i]["ID"].GetInt();
				tmp.request = mission[i]["REQUEST"].GetString();
				tmp.name = mission[i]["NAME"].GetString();
				tmp.begin = mission[i]["BEGIN"].GetInt();
				tmp.end = mission[i]["END"].GetInt();
				tmp.state = mission[i]["STATE"].GetInt();
				tmp.type = mission[i]["TYPE"].GetInt();
				data.push_back(tmp);
			}
		}
	}
	//load reward
	loadReward();
	
	hasMission = false;
	mission = data.at(0);
	index = 0;
}

Mission::Data Mission::getMission() {
	if (hasMission) {
		if (mission.state == 1)
			return mission;
		else {
			hasMission = false;
			return mission;
		}
	}
	else {
		int i = index;
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

Mission::Data Mission::getNowMission() {
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

Mission::Data Mission::get() {
	return mission;
}

void Mission::loadReward() {
	std::string str = FileUtils::getInstance()->getStringFromFile("res/reward.json");
	CCLOG("s", str.c_str());
	rapidjson::Document doc;
	doc.Parse<0>(str.c_str());
	if (doc.HasParseError()) {
		CCLOG("ERROR!!");
	}
	else {
		if (doc.HasMember("REWARD")) {
			rapidjson::Value& reward = doc["REWARD"];
			for (rapidjson::SizeType i = 0; i < reward.Size(); i++) {
				//CCLOG("ID: %i, Name: %s, State: %d", mission[i]["ID"].GetInt(), mission[i]["NAME"].GetString(), mission[i]["STATE"].GetBool());
				Reward tmp;
				tmp.id = reward[i]["ID"].GetInt();
				tmp.idMission = reward[i]["IDMISSION"].GetInt();
				tmp.name = reward[i]["NAME"].GetString();
				tmp.number = reward[i]["NUMBER"].GetInt();
				tmp.type = reward[i]["TYPE"].GetString();
				rewards.push_back(tmp);
			}
		}
	}
}

vector<Mission::Reward> Mission::getReward() {
	vector<Mission::Reward> res;
	for (int i = 0; i < rewards.size(); i++) {
		if (rewards.at(i).idMission == data.at(index).id) {
			res.push_back(rewards.at(i));
		}
	}
	return res;
}

void Mission::updateMission(int type) {
	if (mission.type == type) {
		mission.begin++;
		data.at(index).begin++;
		submitMission();
	}
}

void Mission::reviseMission(int num) {
	mission.begin = num;
	submitMission();
}

void Mission::cancelMission() {
	if (index != data.size()) {
		mission.state = 3;
		data.at(index).state = 3;
		hasMission = false;
	}	
}

void Mission::agreeMission() {
	if (mission.id == data.size() - 2) {
		hasMission = false;
	}
	else {
		hasMission = true;
		data.at(index).state = 1;
		mission.state = 1;
	}
}

void Mission::submitMission() {
	if (mission.begin == mission.end) {
		mission.state = 2;
		data.at(index).state = 2;
	}
}

int Mission::getState() {
	if (hasMission == false) {
		if (mission.id == data.size() - 1) {
			return 2;
		}
		else if (mission.id == data.size() - 3) {
			if (mission.state != 0) {
				return 2;
			}
		}
		if (mission.id == data.size() - 2) {
			return 2;
		}
		return 0;
	}
	else {
		if (mission.id == data.size() - 2) {
			return 1;
		}
		return 2;
	}
}

bool Mission::getProcesstate() {
	return hasMission;
}
void Mission::setProcesstate(bool state) {
	hasMission = state;
}

void Mission::loadMission(int _index, int _id, int _begin, int _state, bool _has) {
	index = _index;
	hasMission = _has;
	data.at(_id).begin = _begin;
	data.at(_id).state = _state;
	mission = data.at(_id);
}

int Mission::getIndexMission() {
	return index;
}

Mission::Data Mission::getMissionCompleted() {
	return data.at(index);
}