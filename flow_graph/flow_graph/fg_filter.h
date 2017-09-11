#ifndef __FLOW_GRAPH_FILTER_H
#define __FLOW_GRAPH_FILTER_H
#include <boost/thread.hpp>
using namespace boost;

template <typename _InputChannel, typename _Transformer, typename _OutputChannel>
struct filter
{
	typedef _InputChannel	input_channel_type;
	typedef _Transformer	transformer_type;
	typedef _OutputChannel	output_channel_type;
};

template <typename _InputChannel, typename _Transformer, typename _OutputChannel>
struct base_filter:public filter<_InputChannel, _Transformer, _OutputChannel>
{
public:
	base_filter()
	{
		m_name      = "filter";
	}

	base_filter(string name)
	{
		m_name      = name;
	}

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
		bool result = false;
		typename input_channel_type::data_type input_data;
		typename output_channel_type::data_type output_data;
		result = m_input_channel->read(input_data);
		if(result)
		{
			output_data = m_transformer(input_data);
			m_output_channel.write(output_data);
		}
	}
protected:
	transformer_type				m_transformer;
	output_channel_type				m_output_channel;
	input_channel_type*				m_input_channel;
	string							m_name;
};


#endif /* __FLOW_GRAPH_FILTER_H */