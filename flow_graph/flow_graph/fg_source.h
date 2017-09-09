#ifndef __FLOW_GRAPH_SOURCE_H
#define __FLOW_GRAPH_SOURCE_H
#include "fg_channel.h"
#include <string>
#include <iostream>
using namespace std;

#include <boost/thread.hpp>
using namespace boost;

template <typename _OutputDataType, typename _Generator, typename _OutputChannel>
struct base_source
{
	typedef _OutputDataType	output_data_type;
	typedef _Generator		generator_type;
	typedef _OutputChannel	output_channel_type;
};

template <typename _OutputDataType, typename _Generator, typename _OutputChannel>
struct base_sync_source:public base_source<_OutputDataType, _Generator, _OutputChannel >
{
public:
	base_sync_source()
	{
		m_name      = "source";
	}

	base_sync_source(string name)
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


template <typename _OutputDataType, typename _Generator>
struct sync_queue_channel_source:public base_sync_source<_OutputDataType, _Generator, sync_queue_channel<_OutputDataType> >
{
public:
	sync_queue_channel_source()
	{
		m_name      = "source";
	}
	sync_queue_channel_source(string name)
	{
		m_name      = name;
	}
};


template <typename _OutputDataType, typename _Generator, typename _OutputChannel>
struct base_async_source:public base_sync_source<_OutputDataType, _Generator, _OutputChannel >
{
public:
	base_async_source()
	{
		m_name      = "source";
	}

	base_async_source(string name)
	{
		m_name      = name;
	}

public:
	void start()
	{
		thread(&base_async_source<_OutputDataType, _Generator, _OutputChannel>::loop_operate, this);
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


template <typename _OutputDataType, typename _Generator>
struct async_queue_channel_source:public base_async_source<_OutputDataType, _Generator, async_queue_channel<_OutputDataType> >
{
public:
	async_queue_channel_source()
	{
		m_name      = "source";
	}
	async_queue_channel_source(string name)
	{
		m_name      = name;
	}
};

#endif /* __FLOW_GRAPH_SOURCE_H */