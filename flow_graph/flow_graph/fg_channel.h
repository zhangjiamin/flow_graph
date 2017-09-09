#ifndef __FLOW_GRAPH_CHANNEL_H
#define __FLOW_GRAPH_CHANNEL_H
#include <queue>
#include <string>
using namespace std;

#include <boost/thread.hpp>
using namespace boost;

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
		m_name = "channel";
	}

	sync_queue_channel(string name)
	{
		m_name = name;
	}

public:
	void write(const input_data_type& data)
	{
		m_queue.push(data);
	}

	bool read(output_data_type& data)
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


template <typename _DataType>
struct async_queue_channel:public base_channel<_DataType>
{
public:
	async_queue_channel(){}

	async_queue_channel(string name)
	{
		m_name = name;
	}

public:
	void write(const input_data_type& data)
	{
		mutex::scoped_lock lock(m_mu);
		m_queue.push(data);
	}

	bool read(output_data_type& data)
	{
		mutex::scoped_lock lock(m_mu);
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
	mutex				m_mu;
};


#endif /* __FLOW_GRAPH_CHANNEL_H */