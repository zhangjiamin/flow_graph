#ifndef __FLOW_GRAPH_CONSUMER_H
#define __FLOW_GRAPH_CONSUMER_H
#include <iostream>
#include <string>
using namespace std;

template <typename _InputDataType>
struct base_consumer
{
	typedef _InputDataType	input_data_type;
};

struct int_consumer: public base_consumer<int>
{
public:
	int_consumer(){}

	void operator()(input_data_type& data)
	{
		if(data % 100000 == 0)
		{
			cout<<data<<endl;
		}
	}
};

struct string_consumer: public base_consumer<string>
{
public:
	string_consumer():m_count(0){}

	void operator()(input_data_type& data)
	{
		m_count++;
		if(m_count%1000 == 0)
		{
			cout<<m_count<<":"<<data<<endl;
			
		}
	}
protected:
	int m_count;
};

#endif /* __FLOW_GRAPH_CONSUMER_H */