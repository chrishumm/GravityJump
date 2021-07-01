#pragma once

#include <iostream>
#include <vector>

using namespace std;

struct metric
{
	int id;
	char* type;
	string text;

	float* float_value; //compare set numbers (distance, etc)
	int* int_value;
	bool* bool_value;

	float float_value_perman; //compare set numbers (distance, etc)
	int int_value_perman;
	bool bool_value_perman;

	bool state_change; //check to see how often a value is changed
	int state_counter;
	float state_counter_float;

	char* time;
};
//Two types of metrics being tracked: 
//1. Basic data (Distance travelled, time, etc)
//2. How often data changes (Deaths, etc)
// Both can be tracked and stored in a small struct

class MetricManager
{
public:
	MetricManager();
	MetricManager(char* db_text_loc);
	bool createMetric(int id,const char* name, int* tracking_value, bool active_metric);
	bool createMetric(int id,const char* name, int* tracking_value, bool state_change, bool active_metric);
	bool createMetric(int id,const char* name, float* tracking_value, bool state_change, bool active_metric);
	bool createMetric(int id, const char* name, bool* tracking_value, bool state_change, bool active_metric);

	bool createMetric(int id, const char* name, bool* tracking_value, bool active_metric);
	bool createMetric(int id,const char* name, float* tracking_value, bool active_metric);
	bool updateMetrics();

	char* getMetricType(float id, bool active_metric);

	float getFloatingValue(float id, bool active_metric);
	const char* getName(float id, bool active_metric);
	int getIntegerValue(float id, bool active_metric);
	int getID(float id, bool active_metric);
	int getNumOfMetrics(bool active_metric);

	vector<float*> getAllFloatingValue(float id, bool active_metric);
	vector<int*> getAllIntegerValue(float id, bool active_metric);

	vector<int*> getAllIDS(bool active_metric);
	vector<int> getNumOfUniqueMetrics(bool active_metric);

	vector<float*> sortSize(vector<float*>);
	vector<int*> sortSize(vector<int*>);

	template<typename T>
	bool swap_values(T& v_1, T& v_2);

	//bool swap_values(float* v_1, float* v_2);

	bool loadMetricStoredData(string db_text_loc);
	bool saveCurrentMetrics(string db);

	bool createMetricsFromFile(string, string, string, string*, int*);
	bool reset_all_metrics_data();

	char* getMetricTime(int id);
	bool delete_metrics();
private:
	vector<metric> current_metrics;//created for running game

	vector<metric> created_metrics;//created from a file to retrieve
	unsigned int m_number_of_metrics;
	string m_db_name;
	string* m_db_contents;
protected:

};