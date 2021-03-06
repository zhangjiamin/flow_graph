#ifndef __FLOW_GRAPH_FILTER_H
#define __FLOW_GRAPH_FILTER_H

#include <vector>
using namespace std;

#include <boost/thread.hpp>
using namespace boost;

template <typename _InputChannel, typename _Transformer, typename _OutputChannel, typename _Strategy>
struct filter
{
	typedef _InputChannel	input_channel_type;
	typedef _Transformer	transformer_type;
	typedef _OutputChannel	output_channel_type;
	typedef _Strategy		strategy_type;
};

template <typename _InputChannel, typename _Transformer, typename _OutputChannel, typename _Strategy>
struct base_filter:public filter<_InputChannel, _Transformer, _OutputChannel, _Strategy>
{
public:
	base_filter(){m_name = "filter";}
	~base_filter()
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
		for(int i=0;i<number_input;++i)
		{
			m_input_channels.push_back(0);
		}

		for(int i=0;i<number_output;++i)
		{
			m_output_channels.push_back(new output_channel_type());
		}
	}

	output_channel_type* const output_channel(int index)
	{
		return m_output_channels[index];
	}

	void input_channel(int index, input_channel_type* channel)
	{
		m_input_channels[index] = channel;
	}
public:
	void operate()
	{
		m_strategy(m_input_channels, m_transformer, m_output_channels);
	}
protected:
	transformer_type				m_transformer;
	vector<output_channel_type*>	m_output_channels;
	vector<input_channel_type*>		m_input_channels;
	strategy_type					m_strategy;
	string							m_name;
};

#endif /* __FLOW_GRAPH_FILTER_H */