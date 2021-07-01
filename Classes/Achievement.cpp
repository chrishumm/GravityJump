#include "Achievement.h"
#include <sstream>

std::stringstream convert_to_string;

Achievement::Achievement(unsigned int id, string text)
{
	m_id = id;
	m_achievement_text = text;
}

Achievement::Achievement(unsigned int id, string text, char* tag)
{
	m_id = id;
	m_achievement_text = text;
	m_tag_name = tag;
}

Achievement::Achievement(unsigned int id, string text, int* current, int target)
{
	m_id = id;
	m_type = integer;
	i_current_value = current;
	i_target_value = target;
	m_achievement_text = text;

	m_tag_name = "Unsorted";
}
Achievement::Achievement(unsigned int id, string text, float* current, float target)
{
	m_id = id;
	m_type = floating_point;
	f_current_value = current;
	f_target_value = target;
	m_achievement_text = text;

	m_tag_name = "Unsorted";
}
Achievement::Achievement(unsigned int id, string text, char* current, std::string target)
{
	m_id = id;
	m_type = character;
	c_current_value = current;
	c_target_value = target;
	m_achievement_text = text;

	m_tag_name = "Unsorted";
}

Achievement::Achievement(unsigned int id, string text, bool* current, bool target)
{
	m_id = id;
	m_type = boolean;
	b_current_value = current;
	b_target_value = target;
	m_achievement_text = text;

	m_tag_name = "Unsorted";
}

Achievement::Achievement(unsigned int id, string text, void* current, void* target)
{
	m_id = id;
	m_type = void_pointer;
	v_current_value = current;
	v_target_value = target;
	m_achievement_text = text;

	m_tag_name = "Unsorted";
}
bool Achievement::getStatus()
{
	return m_active;
}
bool Achievement::update()
{
	switch(m_type)
	{
	case integer:
		{
			if(*i_current_value >= i_target_value)
				return true;
			else
				return false;
		}
		break;
	case floating_point:
		{
			if(*f_current_value >= f_target_value)
				return true;
			else
				return false;
		}
		break;
	case boolean:
		{
			if(*b_current_value == b_target_value)
				return true;
			else
				return false;
		}
		break;
	case character:
		{
			if(c_current_value == c_target_value.c_str())
				return true;
			else
				return false;
		}
		break;
	case void_pointer:
		{
			if(v_current_value == v_target_value)
				return true;
			else
				return false;
		}
		break;
	default:
		{
			return false;
		}
	break;
	}
}

string Achievement::getAchievementText()
{
	return m_achievement_text;
}

int Achievement::getID()
{
	return m_id;
}

bool Achievement::setTag(char* tag)
{
	try
	{
		m_tag_name = tag;
	}
	catch(...)
	{
		return false;
	}

	return true;
}

char* Achievement::getAchevementTag()
{
	return m_tag_name;
}

char* Achievement::getType()
{
	switch (m_type)
	{
	case integer:
	{
		return "int";
	}
		break;
	case floating_point:
	{
		return "float";
	}
		break;
	case boolean:
	{
		return "bool";
	}
		break;
	case character:
	{
		return "string";
	}
		break;
	case void_pointer:
	{
		return "void";
	}
		break;
	}
	return "NULL";
}

std::string Achievement::getTargetinString()
{
	convert_to_string.str("");
	std::string temp = "";
	switch (m_type)
	{
	case integer:
	{
		convert_to_string << i_target_value;
		temp = convert_to_string.str();
		return temp;
	}
		break;
	case floating_point:
	{
		convert_to_string << f_target_value;
		temp = convert_to_string.str();
		return temp;
	}
		break;
	case boolean:
	{
		if (b_target_value == true)
			temp = "true";
		else
			temp = "false";

		return temp;
	}
		break;
	case character:
	{
		return c_target_value;
	}
		break;
	case void_pointer:
	{
		convert_to_string << v_target_value;
		temp = convert_to_string.str();
		return temp;
	}
		break;
	}

	return "NULL";
}

float Achievement::getFloatTarget()
{
	return f_target_value;
}

void* Achievement::getVoidTarget()
{
	return v_target_value;
}

float Achievement::getBoolTarget()
{
	return b_target_value;
}

std::string Achievement::getStringTarget()
{
	return c_target_value;
}

int Achievement::getIntTarget()
{
	return i_target_value;
}

bool Achievement::setTargetValue(float* floatt)
{
	f_current_value = floatt;
	return true;
}
bool Achievement::setTargetValue(int* inter)
{
	i_current_value = inter;
	return true;
}