#include "MetricManager.h"
#include <fstream> 
#include <sstream>
#include <time.h>
#include <algorithm>
#include <cstring>
#include <cstdlib>
#include <cocos2d.h>
#define COCOS2D_DEBUG 1
stringstream ss_convert_metrics;
using namespace cocos2d;
MetricManager::MetricManager()
{
	m_number_of_metrics = 0;
	m_db_name = "metricsdb.txt";
}

MetricManager::MetricManager(char* db_text_loc)
{
	m_number_of_metrics = 0;
	m_db_name = db_text_loc;
}

bool MetricManager::createMetric(int id,const char* name, int* tracking_value, bool active_metric)
{
	
	metric newMetric;
	

	newMetric.id = id;
	newMetric.type = "int";
	newMetric.text = name;
	newMetric.float_value = 0;
	newMetric.int_value = tracking_value;
	newMetric.state_change = false;
	newMetric.state_counter = *newMetric.int_value;
	newMetric.state_counter_float = 0;

	if (active_metric == false)
		created_metrics.push_back(newMetric);
	else
		current_metrics.push_back(newMetric);

	m_number_of_metrics++;
	return true;
}

bool MetricManager::createMetric(int id, const char* name, bool* tracking_value, bool active_metric)
{

	metric newMetric;


	newMetric.id = id;
	newMetric.type = "int";
	newMetric.text = name;
	newMetric.float_value = 0;
	newMetric.bool_value = tracking_value;
	newMetric.state_change = false;
	newMetric.state_counter = 0;
	newMetric.state_counter_float = 0;

	if (active_metric == false)
		created_metrics.push_back(newMetric);
	else
		current_metrics.push_back(newMetric);

	m_number_of_metrics++;
	return true;
}

bool MetricManager::createMetric(int id,const char* name, float* tracking_value, bool active_metric)
{
	
	metric newMetric;


	newMetric.id = id;
	newMetric.type = "float";
	newMetric.state_change = false;
	newMetric.state_counter = 0;
	newMetric.state_counter_float = 0;
	newMetric.int_value = 0;

	if (active_metric == false)
	{
		newMetric.float_value_perman = *tracking_value;
		newMetric.text = name;
		newMetric.float_value = NULL;
		created_metrics.push_back(newMetric);
	}
	else
	{
		newMetric.float_value_perman = 0.0f;
		newMetric.text = name;
		newMetric.float_value = tracking_value;
		current_metrics.push_back(newMetric);
	}

	m_number_of_metrics++;
	return true;
}

bool MetricManager::createMetric(int id,const char* name, int* tracking_value, bool state_change, bool active_metric)
{
	
	metric newMetric;


	newMetric.id = id;
	newMetric.type = "float";
	newMetric.float_value = 0;
	newMetric.state_change = true;
	newMetric.state_counter = 0;
	newMetric.state_counter_float = 0;

	if (active_metric == false)
	{
		newMetric.int_value_perman = *tracking_value;
		newMetric.text = name;
		newMetric.int_value = NULL;
		created_metrics.push_back(newMetric);
	}
	else
	{
		newMetric.int_value_perman = 0;
		newMetric.text = name;
		newMetric.int_value = tracking_value;
		current_metrics.push_back(newMetric);
	}

	m_number_of_metrics++;
	return true;
}

bool MetricManager::createMetric(int id,const char* name, float* tracking_value, bool state_change, bool active_metric)
{

	metric newMetric;

	newMetric.id = id;
	newMetric.type = "float";
	newMetric.text = name;
	newMetric.float_value = tracking_value;
	newMetric.int_value = 0;
	newMetric.state_change = state_change;
	newMetric.state_counter = 0;
	newMetric.state_counter_float = 0;


	if (active_metric == false)
		created_metrics.push_back(newMetric);
	else
		current_metrics.push_back(newMetric);

	m_number_of_metrics++;
	return true;
}

bool MetricManager::createMetric(int id, const char* name, bool* tracking_value, bool state_change, bool active_metric)
{

	metric newMetric;

	newMetric.id = id;
	newMetric.type = "bool";
	newMetric.text = name;
	newMetric.bool_value = tracking_value;
	newMetric.int_value = 0;
	newMetric.state_change = true;
	newMetric.state_counter = 0;
	newMetric.state_counter_float = 0;


	if (active_metric == false)
		created_metrics.push_back(newMetric);
	else
		current_metrics.push_back(newMetric);

	m_number_of_metrics++;
	return true;
}

bool MetricManager::updateMetrics()
{
	for (size_t i = 0; i < current_metrics.size(); i++)
	{
		if (current_metrics[i].state_change == true)
		{
			if (current_metrics[i].type == "float")
			{
				current_metrics[i].state_counter_float += *current_metrics[i].float_value;
			}
			else if (current_metrics[i].type == "int")
			{
				current_metrics[i].state_counter += *current_metrics[i].int_value;
			}
			else if (current_metrics[i].type == "bool")
			{
				if (*current_metrics[i].bool_value != current_metrics[i].bool_value_perman)
				{
					current_metrics[i].state_counter++;
					current_metrics[i].bool_value_perman = *current_metrics[i].bool_value;
				}
			}
			else{}
		}
		return true;
	}
	return false;
}
char* MetricManager::getMetricType(float id,bool active_metric)
{
	if (active_metric == true)
		return current_metrics[id].type;
	else
	{
		for (size_t i = 0; i < created_metrics.size(); i++)
		{
			if (created_metrics[i].id == id)
			{
				return created_metrics[i].type;
			}
		}
	}
	return NULL;
}

float MetricManager::getFloatingValue(float id, bool active_metric)
{
	if (active_metric == true)
	{
		for (size_t i = 0; i < current_metrics.size(); i++)
		{
			if (current_metrics[i].id == id)
			{
				if (current_metrics[i].state_change == true)
					return current_metrics[i].state_counter_float;
				else
					return *current_metrics[i].float_value;
			}
		}
	}
	else
		return *created_metrics[id].float_value;

	return NULL;
}
const char* MetricManager::getName(float id, bool active_metric)
{
	if (active_metric == true)
		return current_metrics[id].text.c_str();
	else
	{
		for (size_t i = 0;i <  created_metrics.size(); i++)
		{
			if (created_metrics[i].id == id)
			{
				return created_metrics[i].text.c_str();
			}
		}
	}

	return NULL;
}
int MetricManager::getIntegerValue(float id, bool active_metric)
{
	if (active_metric == true)
		return *current_metrics[id].int_value;
	else
		return *created_metrics[id].int_value;
}
int MetricManager::getID(float id, bool active_metric)
{
	if (active_metric == true)
		return current_metrics[id].id;
	else 
		return created_metrics[id].id;
}

int MetricManager::getNumOfMetrics(bool active_metric)
{
	if (active_metric == true)
		return m_number_of_metrics;
	else
		return created_metrics.size();
}

vector<int> MetricManager::getNumOfUniqueMetrics(bool active_metric)
{
	vector<int>temp;

	if (active_metric == true)
	{
		temp.push_back(m_number_of_metrics);
		return temp;
	}
	else
	{
		temp.push_back(created_metrics[0].id);
		int itrr = 0;
		for (size_t i = 1; i < created_metrics.size(); i++)
		{
			if (temp[itrr] != created_metrics[i].id)
			{
				bool found = false;
				for (size_t x = 0; x < temp.size(); x++)
				{
					if (temp[x] == created_metrics[i].id)
					{
						found = true;
					}
				}
				if (found == false)
				{
					temp.push_back(created_metrics[i].id);
					itrr++;
				}
			}
		}
	}

	return temp;
}
vector<float*> MetricManager::getAllFloatingValue(float id, bool active_metric)
{
	vector<float*> all_float_values_for_id;
	if (active_metric == true)
	{
		for (size_t i = 0; i < current_metrics.size(); i++)
		{
			if (current_metrics[i].id == id)
				all_float_values_for_id.push_back(current_metrics[i].float_value);
			else{}
		}
	}
	else
	{
		for (size_t i = 0; i < created_metrics.size(); i++)
		{
			if (created_metrics[i].id == id)
				all_float_values_for_id.push_back(&created_metrics[i].float_value_perman);
			else{}
		}
	}
	sortSize(all_float_values_for_id);
	return all_float_values_for_id;
}
vector<int*> MetricManager::getAllIntegerValue(float id, bool active_metric)
{
	vector<int*> all_int_values_for_id;
	if (active_metric == true)
	{
		for (size_t i = 0; i < current_metrics.size(); i++)
		{
			if (current_metrics[i].id == id)
				all_int_values_for_id.push_back(current_metrics[i].int_value);
			else{}
		}
	}
	else
	{
		for (size_t i = 0; i < created_metrics.size(); i++)
		{
			if(created_metrics[i].id == id)
			{
				int test = created_metrics[i].state_counter;
				all_int_values_for_id.push_back(&created_metrics[i].state_counter);
			}
			else{}
		}
	}

	return all_int_values_for_id;
}

vector<float*> MetricManager::sortSize(vector<float*> f)
{
	vector<float*> temp;

	size_t n = f.size() + 1;
	for (size_t k = 1; k < n; k++)
	{
		for (size_t i = 0; i <n - 1 - k; i++)
		{
			if (*f[i]> *f[i + 1])
			{
				swap_values(f[i], f[i + 1]);
			}
		}
	}
	return f;
}
vector<int*> MetricManager::sortSize(vector<int*> i)
{
	return i;
}

template<typename T>
bool MetricManager::swap_values(T& v_1, T& v_2)
{
	T temp_v;
	if (v_1 > v_2)
	{
		temp_v = v_1;
		v_1 = v_2;
		v_2 = temp_v;
		return true;
	}
	else if (v_1 < v_2)
	{
		temp_v = v_2;
		v_2 = v_1;
		v_1 = temp_v;
		return true;
	}
	else
	{
		return false;
	}
	return false;
}

bool MetricManager::loadMetricStoredData(string db_text_loc)
{
	if (db_text_loc == "")
		return false;

	//CCLog(db_text_loc);
	string file_contents[254];
	string file_name_concat = db_text_loc;
	//	file_name_concat.append(fileName);
	m_db_name = db_text_loc;
	ifstream hiscore_file(file_name_concat.c_str());
	int num_of_metrics = 0;
	if (!hiscore_file.good())
	{
	//	CCLog(file_name_concat);
		CCLog("Fail to load High Scores");
		return false;
	}
	CCLog("SUCESS TO LOAD METRICS");
	//CCLog(file_name_concat.c_str());

	while (!hiscore_file.eof() && hiscore_file.good())
	{
		getline(hiscore_file, file_contents[num_of_metrics]);
		num_of_metrics++;
	}
	num_of_metrics -= 1;

	m_db_name = db_text_loc;
	m_db_contents = file_contents;

	string metric_name[254];
	string metric_data[254];
	string type[254];
	string temp;
	string id;
	string* db_extract = m_db_contents;
	int start_index = 0;
	for (int i = 0; i < num_of_metrics; i++)
	{
		int end_of_data = db_extract[i].find_first_of('[');
		temp = db_extract[i].substr(start_index, end_of_data);
		end_of_data = db_extract[i].find_first_of(']');
		db_extract[i].erase(start_index, end_of_data + 1);
		metric_name[i] = temp;

		end_of_data = db_extract[i].find_first_of('[');
		temp = db_extract[i].substr(start_index, end_of_data);

		if (temp == "float")
		{
			type[i] = "float";
		}
		else if (temp == "int")
		{
			type[i] = "int";
		}
		else if (temp == "bool")
		{
			type[i] = "bool";
		}
		else
		{
			type[i] = "NULL";
		}
		end_of_data = db_extract[i].find_first_of(']');
		db_extract[i].erase(start_index, end_of_data + 1);

		end_of_data = db_extract[i].find_first_of('[');
		temp = db_extract[i].substr(start_index, end_of_data);
		metric_data[i] = temp;

		end_of_data = db_extract[i].find_first_of(']');
		db_extract[i].erase(start_index, end_of_data + 1);

		end_of_data = db_extract[i].find_first_of('[');
		int end = db_extract[i].size();
		db_extract[i].erase(end_of_data , end);

		id = db_extract[i];
		createMetricsFromFile(metric_name[i], metric_data[i], type[i], &id, &num_of_metrics);
	}
	return true;
}

bool MetricManager::createMetricsFromFile(string metric_name, string metric_data, string metric_type, string* string_id, int* number_of_metrics)
{
	for (int i = 0; i < *number_of_metrics; i++)
	{
		if (metric_name != "")
		{
			int id = atoi(string_id[i].c_str());


			if (metric_type == "int")
			{
				int target = atoi(metric_data.c_str());

				createMetric(id, metric_name.c_str(), &target, false);
				return true;
			}
			if (metric_type == "float")
			{
				float target = atof(metric_data.c_str());
				createMetric(id, metric_name.c_str(), &target, false);
				return true;
			}
			if (metric_type == "bool")
			{
				bool value;
				if ((metric_data.c_str() == "false"))
					value = false;
				else
					value = true;

				int target = atoi(metric_data.c_str());

				createMetric(id, metric_name.c_str(), &target, false);
				return true;
			}
		}
	}
	return false;
}


bool MetricManager::saveCurrentMetrics(string db_loc)
{
	CCLog("Saving Metrics");
	//CCLog(db_loc.c_str());

	m_db_name = db_loc;
	time_t timer;
	time(&timer);
	struct tm* time_output = localtime(&timer);

	string current_time;
	ss_convert_metrics << (time_output->tm_year + 1900);
	current_time.append(ss_convert_metrics.str() + "/");
	ss_convert_metrics.str("");
	ss_convert_metrics << time_output->tm_mon + 1;
	current_time.append(ss_convert_metrics.str() + "/");
	ss_convert_metrics.str("");
	ss_convert_metrics << time_output->tm_mday;
	current_time.append(ss_convert_metrics.str() + "/");
	ss_convert_metrics.str("");
	ss_convert_metrics << time_output->tm_hour;
	current_time.append(ss_convert_metrics.str() + ":");
	ss_convert_metrics << time_output->tm_min;
	if (time_output->tm_hour > 12)
		current_time.append(ss_convert_metrics.str() + "PM");
	else
		current_time.append(ss_convert_metrics.str() + "AM");


	string metric_name;
	string metric_data;
	string type;
	string db;
	for (size_t i = 0; i < current_metrics.size(); i++)
	{
		metric_name = current_metrics[i].text;
		
		db.append(metric_name + "[TYPE]");
		type = current_metrics[i].type;
		db.append(type + "[CURRENT_VALUE]");
		ss_convert_metrics.str("");
		if (type == "float")
		{
			
			if (current_metrics[i].state_change == true)
			{
				ss_convert_metrics << current_metrics[i].state_counter_float;
				metric_data = ss_convert_metrics.str();
			}
			else
			{
				ss_convert_metrics << *current_metrics[i].float_value;
				metric_data = ss_convert_metrics.str();
			}
		}
		else if (type == "int")
		{
			if (current_metrics[i].state_change == true)
			{
				ss_convert_metrics << current_metrics[i].state_counter;
				metric_data = ss_convert_metrics.str();
			}
			else
			{
				ss_convert_metrics << *current_metrics[i].int_value;
				metric_data = ss_convert_metrics.str();
			}
		}
		else if (type == "bool")
		{
			if (current_metrics[i].state_change == true)
			{
				ss_convert_metrics << current_metrics[i].state_counter;
				metric_data = ss_convert_metrics.str();
			}
			else
			{
				ss_convert_metrics << *current_metrics[i].int_value;
				metric_data = ss_convert_metrics.str();
			}
		}
		else{}
		ss_convert_metrics.str("");
		ss_convert_metrics << current_metrics[i].id;
		db.append(metric_data + "[ID]" + ss_convert_metrics.str());
		ss_convert_metrics.str("");

		db.append("[TIME]" + current_time + "\n");
	}
	m_db_name = "metricsdb.txt";

	string txt = "metricsdb.txt";

	ofstream saveDb(txt.c_str(), std::ios::app);

	if (saveDb.is_open()) //is the file open?
	{
		saveDb << db; //write the file
		saveDb.close(); //close it
		return true;

	//	CCLog(m_db_name.c_str());
	}
	else
	{
		CCLog("Fail write");
	//	CCLog(m_db_name.c_str());
		return false;
	}

	return true;
}

bool MetricManager::reset_all_metrics_data()
{
	for (size_t i = 0; i < current_metrics.size(); i++)
	{
		if (current_metrics[i].state_change == true)
		{
			if (current_metrics[i].type == "float")
			{
				current_metrics[i].state_counter_float = 0.0f;
			}
			else if (current_metrics[i].type == "int")
			{
				current_metrics[i].state_counter = 0.0f;
			}
		}
		else
		{
			
		}
	}
	return true;
}

vector<int*> MetricManager::getAllIDS(bool active_metric)
{
	vector<int*> current_metric_ids;
	if (active_metric == false)
	{
		for (size_t i = 0; i < created_metrics.size(); i++)
			current_metric_ids.push_back(&created_metrics[i].id);
	}

	return current_metric_ids;
}

bool MetricManager::delete_metrics()
{
	remove(m_db_name.c_str());

	return true;
}

char* MetricManager::getMetricTime(int id)
{
	for (size_t i = 0; i < created_metrics.size(); i++)
	{
		if (id == created_metrics[i].id)
		{
			return created_metrics[i].time;
		}
	}
}