#ifndef __FLOW_GRAPH_SINK_H
#define __FLOW_GRAPH_SINK_H
#include "fg_channel.h"
#include <string>
#include <iostream>
using namespace std;

#include <boost/thread.hpp>
using namespace boost;

template <typename _InputDataType, typename _Consumer, typename _InputChannel>
struct base_sink
{
	typedef _InputDataType	input_data_type;
	typedef _Consumer		consumer_type;
	typedef _InputChannel	input_channel_type;
};

template <typename _InputDataType, typename _Consumer, typename _InputChannel>
struct base_sync_sink:public base_sink<_InputDataType, _Consumer, _InputChannel >
{
public:
	base_sync_sink()
	{
		m_name          = "sink";
		m_input_channel = NULL;
	}

	base_sync_sink(string name)
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
		input_data_type data;
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

template <typename _InputDataType, typename _Consumer, typename _InputChannel>
struct base_async_sink:public base_sync_sink<_InputDataType, _Consumer, _InputChannel >
{
public:
	base_async_sink()
	{
		m_name      = "sink";
	}

	base_async_sink(string name)
	{
		m_name      = name;
	}

public:
	void start()
	{
		thread(&base_async_sink<_InputDataType, _Consumer, _InputChannel>::loop_operate, this);
	}
	void stop(){}
protected:
	void loop_operate()
	{
		while(true)
		{
			operate();
			this_thread::sleep(posix_time::milliseconds(1));
		}
	}
};


template <typename _InputDataType, typename _Consumer>
struct sync_queue_channel_sink:public base_sync_sink<_InputDataType, _Consumer, sync_queue_channel<_InputDataType> >
{
public:
	sync_queue_channel_sink()
	{
		m_name          = "sink";
		m_input_channel = NULL;
	}
	sync_queue_channel_sink(string name)
	{
		m_name = name;
		m_input_channel = NULL;
	}
};

template <typename _InputDataType, typename _Consumer>
struct async_queue_channel_sink:public base_async_sink<_InputDataType, _Consumer, async_queue_channel<_InputDataType> >
{
public:
	async_queue_channel_sink()
	{
		m_name          = "sink";
		m_input_channel = NULL;
	}
	async_queue_channel_sink(string name)
	{
		m_name = name;
		m_input_channel = NULL;
	}
};



#endif /* __FLOW_GRAPH_SOURCE_H */