#include "AchievementManager.h"
#include <fstream> 
#include <sstream>
#include <cstring>
#include <cstdlib>
#include <cocos2d.h>

#define COCOS2D_DEBUG 1

using namespace cocos2d;

stringstream ss_convert; // used for covnerting ints to strings, vica versa

AchievementManager::AchievementManager()
{
	m_number_of_achievements = 0;
	achievement_update = false;
}

AchievementManager::~AchievementManager()
{
	for(size_t i = 0; i < m_current_active_achievements.size();i++)
	{
		delete m_current_active_achievements[i];
		m_current_active_achievements[i] = NULL;
	}
}


AchievementManager::AchievementManager(char* dbfileName)
{
	m_number_of_achievements = 0;
	m_db_name = dbfileName;

	achievement_update = false;
}

bool AchievementManager::loadDb(string fileName)
{
	if (&fileName == NULL)
		return false;

	string file_contents[254];
	string file_name_concat = fileName;
//	file_name_concat.append(fileName);

	ifstream hiscore_file(file_name_concat.c_str()); 
	int num_of_achievements = 0;
	if (!hiscore_file.good())
	{
		CCLog("db not loaded from ach");
		return false;
	}
	CCLog("db loaded from ach");
	while(!hiscore_file.eof())
	{
		getline(hiscore_file, file_contents[num_of_achievements]);
		num_of_achievements++;
	}
	num_of_achievements -= 1;

	m_db_name = fileName;
	m_db_contents = file_contents;

	string ach;
	string target;
	string type;
	string temp;
	string id;
	string* db_extract = m_db_contents;
	int start_index = 0;
	for (int i = 0; i < num_of_achievements;i++)
	{
		int end_of_data = db_extract[i].find_first_of('[');
		temp = db_extract[i].substr(start_index, end_of_data);
		end_of_data = db_extract[i].find_first_of(']');
		db_extract[i].erase(start_index, end_of_data + 1);
		ach = temp;

		end_of_data = db_extract[i].find_first_of('[');
		temp = db_extract[i].substr(start_index, end_of_data);

		if (temp == "float")
		{
			type = "float";
		}
		else if (temp == "int")
		{
			type = "int";
		}
		else if(temp.find("bool"))
		{
			type = "bool";
		}
		else if (temp == "string")
		{
			type = "string";
		}
		else if (temp == "void")
		{
			type = "void";
		}
		else
		{
			type = "NULL";
		}
		end_of_data = db_extract[i].find_first_of(']');
		db_extract[i].erase(start_index, end_of_data + 1);

		end_of_data = db_extract[i].find_first_of('[');
		temp = db_extract[i].substr(start_index, end_of_data);
		target = temp;

		end_of_data = db_extract[i].find_first_of(']');
		db_extract[i].erase(start_index, end_of_data + 1);

	//	id = db_extract;
		createAchievementsFromFile(&ach, &target, &type, &id, &num_of_achievements);
	}
	CCLog("db created from ach");
	return true;
}

bool AchievementManager::createAchievementsFromFile(string*ach_text, string*target_v, string*type, string*, int* num_of_ach)
{

		if (*type == "int")
		{

			int target = atoi(target_v->c_str());
			char* text = strdup(ach_text->c_str());

			createAchievement(text, 0, target);
			free(text);
		}
		if (*type == "float")
		{
			float target = atoi(target_v->c_str());
			char* text = strdup(ach_text->c_str());

			createAchievement(text, 0, target);
			free(text);
			
		}
	return true;
}
bool AchievementManager::saveDb(string fileName)
{
	if (&fileName == NULL)
		return false;

	string ach;
	string target;
	string type;
	string db;
	for (size_t i = 0; i < m_current_active_achievements.size(); i++)
	{
		ach = m_current_active_achievements[i]->getAchievementText();
		ss_convert << i;
		db.append(ach + "[TYPE]");
		type = m_current_active_achievements[i]->getType();
		db.append(type + "[TARGET_VALUE]");
		target = m_current_active_achievements[i]->getTargetinString();
		db.append(target + "[ID]" + ss_convert.str()+ "\n");
		ss_convert.str("");
	}
	string txt = fileName;
	//txt.append("db.txt");

	ofstream saveDb(txt.c_str());

	if (saveDb.is_open()) //is the file open?
	{
		saveDb << db; //write the file
		saveDb.close(); //close it
		CCLog("db saved from ach");
		return true;
	}
	else
	{
		CCLog("db not saved from ach");
		return false;
	}

	return true;
}

bool AchievementManager::wipeDb(char* fileName)
{
	return true;
}

bool AchievementManager::setFileLocation(char* file_loc)
{
	m_file_location = file_loc;
	return true;
}

bool AchievementManager::createAchievement(string name, int* current_value, int target_value)
{
	try
	{
		m_current_active_achievements.push_back(new Achievement(m_number_of_achievements,name,current_value,target_value));
		m_number_of_achievements++;
	}
	catch(...)
	{
		return false;
	}
	return true;
}

bool AchievementManager::createAchievement(string name, float* current_value, float target_value)
{
	try
	{
		m_current_active_achievements.push_back(new Achievement(m_number_of_achievements,name,current_value,target_value));
		m_number_of_achievements++;
		active.push_back(true);
	}
	catch(...)
	{
		return false;
	}
	return true;
}

bool AchievementManager::createAchievement(string name, bool* current_value, bool target_value)
{
	try
	{
		m_current_active_achievements.push_back(new Achievement(m_number_of_achievements,name,current_value,target_value));
		m_number_of_achievements++;
	}
	catch(...)
	{
		return false;
	}
	return true;
}

bool AchievementManager::createAchievement(string name, char* current_value, string target_value)
{
	try
	{
		m_current_active_achievements.push_back(new Achievement(m_number_of_achievements,name,current_value,target_value));
		m_number_of_achievements++;
	}
	catch(...)
	{
		return false;
	}
	return true;
}

bool AchievementManager::createAchievement(string name, void* current_value, void* target_value)
{
	try
	{
		m_current_active_achievements.push_back(new Achievement(m_number_of_achievements,name,current_value,target_value));
		m_number_of_achievements++;
	}
	catch(...)
	{
		return false;
	}
	return true;
}

unsigned int AchievementManager::getSizeofAchievements()
{
	return m_current_active_achievements.size();
}
bool AchievementManager::getAchievementStatus(string name, bool is_tag)
{
	if(is_tag == false)
	{
		for(size_t i = 0; i < getSizeofAchievements();i++)
		{
			if(m_current_active_achievements[i]->getAchievementText() == name)
			{
				return m_current_active_achievements[i]->getStatus();
			}
		}
	}

	return 0;
}

bool AchievementManager::getAchievementStatus(int id)
{
	return m_current_active_achievements[id]->getStatus();
}
bool AchievementManager::resetAchievement(string name, bool is_tag)
{
	return true;
}
bool AchievementManager::resetAchievement(int id)
{
	return true;
}

bool AchievementManager::changeAchievementPrerequisite(int id, int* current_value, int target_value)
{
	return true;
}
bool AchievementManager::changeAchievementPrerequisite(int id, float* current_value, float target_value)
{
	return true;
}
bool AchievementManager::changeAchievementPrerequisite(int id, bool* current_value, bool target_value)
{
	return true;
}
bool AchievementManager::changeAchievementPrerequisite(int id, char* current_value, string target_value)
{
	return true;
}
bool AchievementManager::changeAchievementPrerequisite(int id,void* current_value, void* target_value)
{
	return true;
}

bool AchievementManager::changeTaggedAchievementPrerequisite(const char* tag, int* current_value, int target_value)
{
	return true;
}
bool AchievementManager::changeTaggedAchievementPrerequisite(const char* tag, float* current_value, float target_value)
{
	return true;
}
bool AchievementManager::changeTaggedAchievementPrerequisite(const char* tag, bool* current_value, bool target_value)
{
	return true;
}
bool AchievementManager::changeTaggedAchievementPrerequisite(const char* tag, char* current_value, string target_value)
{
	return true;
}
bool AchievementManager::changeTaggedAchievementPrerequisite(const char* tag, void* current_value, void* target_value)
{
	return true;
}

string AchievementManager::update_all_achievements()
{
	for(size_t i = 0; i < m_current_active_achievements.size();i++)
	{
			if(m_current_active_achievements[i]->update() == true && achievement_update == false && active[i] == true)
				return m_current_active_achievements[i]->getAchievementText();
	}
	return "";
}

bool AchievementManager::setUpdateFalse(bool t)
{
	for(size_t i = 0; i < m_current_active_achievements.size();i++)
	{
		if(m_current_active_achievements[i]->update() == true)
		{
			achievement_update = false;
			active[i] = false;
		}
	}

	return true;
}

bool AchievementManager::addCValue(int id, int* current_value)
{
	for (size_t i = 0; i < m_current_active_achievements.size(); i++)
	{
		if (m_current_active_achievements[i]->getID() == id)
		{
			m_current_active_achievements[i]->setTargetValue(current_value);
			return true;
		}
	}
	return false;
}
bool AchievementManager::addCValue(int id, float* current_value)
{
	for (size_t i = 0; i < m_current_active_achievements.size(); i++)
	{
		if (m_current_active_achievements[i]->getID() == id)
		{
			m_current_active_achievements[i]->setTargetValue(current_value);
			return true;
		}
	}
	return false;
}

string AchievementManager::getAchievementByName(int id)
{
	return m_current_active_achievements[id]->getAchievementText();
}