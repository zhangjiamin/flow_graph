#ifndef __FLOW_GRAPH_SINK_H
#define __FLOW_GRAPH_SINK_H
#include <string>
#include <iostream>
using namespace std;

#include <boost/thread.hpp>
using namespace boost;

template <typename _Consumer, typename _InputChannel, typename _Strategy>
struct sink
{
	typedef _Consumer		consumer_type;
	typedef _InputChannel	input_channel_type;
	typedef _Strategy		strategy_type;
};

template <typename _Consumer, typename _InputChannel, typename _Strategy>
struct base_sink:public sink<_Consumer, _InputChannel, _Strategy>
{
public:
	base_sink():m_input_channel(NULL){m_name = "sink";}
	base_sink(string name):m_input_channel(NULL){m_name = name;}
public:
	void input_channel(input_channel_type* channel)
	{
		m_input_channel = channel;
		cout<<"sink:"<<m_input_channel<<endl;
	}
public:
	void operate()
	{
		m_strategy(m_consumer, m_input_channel);
	}
protected:
	consumer_type					m_consumer;
	strategy_type					m_strategy;
	input_channel_type*				m_input_channel;
	string							m_name;
};

template <typename _InputDataType, typename _Consumer, typename _Strategy>
struct base_sync_queue_channel_sink:public base_sink<_Consumer, base_queue_channel<_InputDataType>,  _Strategy>
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