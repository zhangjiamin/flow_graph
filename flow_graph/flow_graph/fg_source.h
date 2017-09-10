#ifndef __FLOW_GRAPH_SOURCE_H
#define __FLOW_GRAPH_SOURCE_H
#include <string>
#include <iostream>
using namespace std;

#include <boost/thread.hpp>
using namespace boost;

#include "fg_operator.h"

template <typename _OutputDataType, typename _Generator, typename _OutputChannel>
struct source
{
	typedef _OutputDataType	output_data_type;
	typedef _Generator		generator_type;
	typedef _OutputChannel	output_channel_type;
};

template <typename _OutputDataType, typename _Generator, typename _OutputChannel>
struct base_source:public source<_OutputDataType, _Generator, _OutputChannel >, public Operator
{
public:
	base_source()
	{
		m_name      = "source";
	}

	base_source(string name)
	{
		m_name      = name;
	}

public:
	output_channel_type* output_channel()
	{
		return &m_channel;
	}
public:
	void operate()
	{
		m_channel.write(m_generator());
	}
protected:
	generator_type					m_generator;
	output_channel_type				m_channel;
	string							m_name;
};

#endif /* __FLOW_GRAPH_SOURCE_H */