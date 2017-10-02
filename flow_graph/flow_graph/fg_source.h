#ifndef __FLOW_GRAPH_SOURCE_H
#define __FLOW_GRAPH_SOURCE_H
#include <string>
#include <iostream>
#include <vector>
using namespace std;

#include <boost/thread.hpp>
using namespace boost;

template <typename _Generator, typename _OutputChannel, typename _Strategy>
struct source
{
	typedef _Generator		generator_type;
	typedef _OutputChannel	output_channel_type;
	typedef _Strategy		strategy_type;
};

template <typename _Generator, typename _OutputChannel, typename _Strategy>
struct base_source:public source<_Generator, _OutputChannel, _Strategy >
{
public:
	base_source(){m_name = "source";}
	~base_source()
	{
		for(int i=0;i<m_output_channels.size();++i)
		{
			delete m_output_channels[i];
		}
	}
public:
	void setname(string name){m_name = name;}
	string getname(){return m_name;}

	void setup(int number_input, int number_output)
	{
		for(int i=0;i<number_output;++i)
		{
			m_output_channels.push_back(new output_channel_type());
		}
	}

	output_channel_type* output_channel(int index)
	{
		return m_output_channels[index];
	}

	void operate()
	{
		m_strategy(m_generator, m_output_channels);
	}
protected:
	generator_type					m_generator;
	vector<output_channel_type*>	m_output_channels;
	strategy_type					m_strategy;
	string							m_name;
};

#endif /* __FLOW_GRAPH_SOURCE_H */