#ifndef __FLOW_GRAPH_FILTER_H
#define __FLOW_GRAPH_FILTER_H
#include "fg_channel.h"

template <typename _InputDataType, typename _InputChannel, typename _Transformer, typename _OutputDataType, typename _OutputChannel>
struct base_filter
{
	typedef _InputDataType	input_data_type;
	typedef _InputChannel	input_channel_type;
	typedef _Transformer	transformer_type;
	typedef _OutputDataType	output_data_type;
	typedef _OutputChannel	output_channel_type;
};

template <typename _InputDataType, typename _InputChannel, typename _Transformer, typename _OutputDataType, typename _OutputChannel>
struct base_sync_filter:public base_filter<_InputDataType, _InputChannel, _Transformer, _OutputDataType, _OutputChannel>
{
public:
	base_sync_filter()
	{
		m_name      = "filter";
	}

	base_sync_filter(string name)
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
		input_data_type data, t_data;
		result = m_input_channel->read(data);
		if(result)
		{
			t_data = m_transformer(data);
			m_output_channel.write(t_data);
		}
	}
protected:
	transformer_type				m_transformer;
	output_channel_type				m_output_channel;
	input_channel_type*				m_input_channel;
	string							m_name;
};

template <typename _InputDataType, typename _Transformer, typename _OutputDataType>
struct sync_queue_channel_filter:public base_sync_filter<_InputDataType, sync_queue_channel<_InputDataType>, _Transformer, _OutputDataType, sync_queue_channel<_OutputDataType> >
{
public:
	sync_queue_channel_filter()
	{
		m_name      = "filter";
	}
	sync_queue_channel_filter(string name)
	{
		m_name      = name;
	}
};


#endif /* __FLOW_GRAPH_SOURCE_H */