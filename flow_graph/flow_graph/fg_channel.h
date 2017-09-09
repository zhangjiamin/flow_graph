#ifndef __FLOW_GRAPH_CHANNEL_H
#define __FLOW_GRAPH_CHANNEL_H
#include <queue>
#include <string>
using namespace std;

template <typename _DataType>
struct base_channel
{
	typedef _DataType		input_data_type;
	typedef _DataType		output_data_type;
};

template <typename _DataType>
struct sync_queue_channel:public base_channel<_DataType>
{
public:
	sync_queue_channel()
	{

	}

	sync_queue_channel(string name)
	{
		m_name = name;
	}

public:
	void write(const _DataType& data)
	{
		m_queue.push(data);
	}

	bool read(_DataType& data)
	{
		if (m_queue.empty())
		{
			return false;
		} 
		else
		{
			data = m_queue.front();
			m_queue.pop();
			return true;
		}
	}
protected:
	string				m_name;
	queue<_DataType>	m_queue;
};


#endif /* __FLOW_GRAPH_CHANNEL_H */