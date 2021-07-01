#pragma once
#include <iostream>
using namespace std;

class Achievement
{
public:
	Achievement(unsigned int id, string m_achievement_text);
	Achievement(unsigned int id, string text, char* tag);
	Achievement(unsigned int id, string m_achievement_text, int* current, int target);
	Achievement(unsigned int id, string m_achievement_text, float* current, float target);
	Achievement(unsigned int id, string m_achievement_text, char* current, std::string target);
	Achievement(unsigned int id, string m_achievement_text, bool* current, bool target);
	Achievement(unsigned int id, string m_achievement_text, void* current, void* target);

	bool getStatus();
	string getAchievementText();
	char* getAchevementTag();
	int getID();
	char* getType();
	bool update();
	bool setTag(char* tag);

	float getFloatTarget();
	void* getVoidTarget();
	float getBoolTarget();
	std::string getStringTarget();
	int getIntTarget();

	std::string getTargetinString();

	bool setTargetValue(float*);
	bool setTargetValue(int*);
private:
	int* i_current_value;
	int i_target_value;

	float* f_current_value;
	float f_target_value;

	bool* b_current_value;
	bool b_target_value;

	char* c_current_value;
	std::string c_target_value;

	void* v_current_value;
	void* v_target_value;

	unsigned int m_id;
	string m_achievement_text;
	char* m_tag_name;
	bool m_active;
	int m_type;
	enum type{integer,floating_point,boolean,character,void_pointer};
protected:
};