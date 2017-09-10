#ifndef __FLOW_GRAPH_SINK_H
#define __FLOW_GRAPH_SINK_H
#include "fg_channel.h"
#include "fg_operator.h"
#include <string>
#include <iostream>
using namespace std;

#include <boost/thread.hpp>
using namespace boost;

template <typename _Consumer, typename _InputChannel>
struct sink
{
	typedef _Consumer		consumer_type;
	typedef _InputChannel	input_channel_type;
};

template <typename _Consumer, typename _InputChannel>
struct base_sink:public sink<_Consumer, _InputChannel >, public Operator
{
public:
	base_sink()
	{
		m_name          = "sink";
		m_input_channel = NULL;
	}

	base_sink(string name)
	{
		m_name = name;
		m_input_channel = NULL;
	}

public:
	void input_channel(input_channel_type* channel)
	{
		m_input_channel = channel;
		cout<<"sink:"<<m_input_channel<<endl;
	}
public:
	void operate()
	{
		bool result = false;
		input_channel_type::data_type data;
		result = m_input_channel->read(data);
		if(result)
		{
			m_consumer(data);
		}
	}
protected:
	consumer_type					m_consumer;
	input_channel_type*				m_input_channel;
	string							m_name;
};

template <typename _InputDataType, typename _Consumer>
struct base_sync_queue_channel_sink:public base_sink<_Consumer, base_queue_channel<_InputDataType> >
{
public:
	base_sync_queue_channel_sink()
	{
		m_name          = "sink";
		m_input_channel = NULL;
	}
	base_sync_queue_channel_sink(string name)
	{
		m_name = name;
		m_input_channel = NULL;
	}
};

#endif /* __FLOW_GRAPH_SINK_H */