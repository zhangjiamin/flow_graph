#ifndef __FLOW_GRAPH_SINK_H
#define __FLOW_GRAPH_SINK_H
#include <string>
#include <iostream>
#include <vector>
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
	base_sink(){m_name = "sink";}
	base_sink(string name){m_name = name;}
	~base_sink(){}
public:
	void setup(int number_input, int number_output)
	{
		for(int i=0;i<number_input;++i)
		{
			m_input_channels.push_back(0);
		}
	}
	void input_channel(int index, input_channel_type* channel)
	{
		m_input_channels[index] = channel;
	}
	void operate()
	{
		m_strategy(m_consumer, m_input_channels);
	}
protected:
	consumer_type					m_consumer;
	strategy_type					m_strategy;
	vector<input_channel_type*>		m_input_channels;
	string							m_name;
};

template <typename _InputDataType, typename _Consumer, typename _Strategy>
struct base_sync_queue_channel_sink:public base_sink<_Consumer, base_queue_channel<_InputDataType>,  _Strategy>
{
public:
	base_sync_queue_channel_sink(){	m_name = "sink";}
	base_sync_queue_channel_sink(string name){m_name = name;}
};

#endif /* __FLOW_GRAPH_SINK_H */