#ifndef __FLOW_GRAPH_GENERATOR_H
#define __FLOW_GRAPH_GENERATOR_H
#include <string>
using namespace std;

template <typename _OutputDataType>
struct base_generator
{
	typedef _OutputDataType	output_data_type;
};


struct int_generator: public base_generator<int>
{
public:
	int_generator()
	{
		m_val = output_data_type();
	}

	output_data_type& operator()()
	{
		m_val++;
		return m_val;
	}
protected:
	output_data_type m_val;

};

struct string_generator: public base_generator<string>
{
public:
	string_generator()
	{
		m_val = "test";
	}

	output_data_type& operator()()
	{
		m_val.append("a");
		return m_val;
	}
protected:
	output_data_type m_val;

};

#endif /* __FLOW_GRAPH_GENERATOR_H */