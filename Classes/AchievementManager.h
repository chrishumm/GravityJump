#pragma once
#include <iostream>
#include <vector>
#include "Achievement.h"

using namespace std;

class AchievementManager
{
public:
	AchievementManager();
	~AchievementManager();

	AchievementManager(char* dbfileName);

	bool loadDb(string fileName);
	bool saveDb(string fileName);
	bool wipeDb(char* fileName);
	bool setFileLocation(char* m_file_location);
	bool createAchievementsFromFile(string*, string*, string*, string*, int*);

	bool createAchievement(string name, int* current_value, int target_value);
	bool createAchievement(string name, float* current_value, float target_value);
	bool createAchievement(string name, bool* current_value, bool target_value);
	bool createAchievement(string name, char* current_value, string target_value);
	bool createAchievement(string name, void* current_value, void* target_value);

	bool createAchievement(string name, int id);
	bool createAchievement(string name, char* tag);


	unsigned int getSizeofAchievements();
	bool getAchievementStatus(string name, bool is_tag);
	bool getAchievementStatus(int id);

	string getAchievementByName(int id);

	unsigned int getNumofAchievementsByTag(char* tag);
	bool resetAchievement(string name, bool is_tag);
	bool resetAchievement(int id);

	bool changeAchievementPrerequisite(int id, int* current_value, int target_value);
	bool changeAchievementPrerequisite(int id, float* current_value, float target_value);
	bool changeAchievementPrerequisite(int id, bool* current_value, bool target_value);
	bool changeAchievementPrerequisite(int id, char* current_value, string target_value);
	bool changeAchievementPrerequisite(int id, void* current_value, void* target_value);

	bool addCValue(int id, int* current_value);
	bool addCValue(int id, float* current_value);

	bool changeTaggedAchievementPrerequisite(const char* tag, int* current_value, int target_value);
	bool changeTaggedAchievementPrerequisite(const char* tag, float* current_value, float target_value);
	bool changeTaggedAchievementPrerequisite(const char* tag, bool* current_value, bool target_value);
	bool changeTaggedAchievementPrerequisite(const char* tag, char* current_value, string target_value);
	bool changeTaggedAchievementPrerequisite(const char* tag, void* current_value, void* target_value);

	string update_all_achievements();
	bool setUpdateFalse(bool);
private:
	string m_db_name;
	char* m_file_location;
	string* m_db_contents;
	bool achievement_update;
	vector<bool> active;
	unsigned int m_number_of_achievements;
	vector<Achievement*> m_current_active_achievements;
protected:
};