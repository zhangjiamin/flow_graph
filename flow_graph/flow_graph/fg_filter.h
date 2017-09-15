#ifndef __FLOW_GRAPH_FILTER_H
#define __FLOW_GRAPH_FILTER_H
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
	base_filter(string name){m_name = name;}
public:
	output_channel_type* const output_channel()
	{
		return &m_output_channel;
	}
	void input_channel(input_channel_type* channel)
	{
		m_input_channel = channel;
	}
public:
	void operate()
	{
		m_strategy(m_input_channel, m_transformer, m_output_channel);
	}
protected:
	transformer_type				m_transformer;
	output_channel_type				m_output_channel;
	input_channel_type*				m_input_channel;
	strategy_type					m_strategy;
	string							m_name;
};

#endif /* __FLOW_GRAPH_FILTER_H */