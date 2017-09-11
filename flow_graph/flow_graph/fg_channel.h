#ifndef __FLOW_GRAPH_CHANNEL_H
#define __FLOW_GRAPH_CHANNEL_H

#include <queue>
#include <string>
using namespace std;

#include <boost/thread.hpp>
using namespace boost;

template <typename _DataType>
struct channel
{
	typedef _DataType		data_type;
};

template <typename _DataType>
struct base_queue_channel:public channel<_DataType>
{
public:
	base_queue_channel()
	{
		m_name = "channel";
	}

	base_queue_channel(string name)
	{
		m_name = name;
	}

public:
	void write(const data_type& data)
	{
		m_queue.push(data);
	}

	bool read(data_type& data)
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
	queue<data_type>	m_queue;
};

template <typename AdaptableChannel>
struct async_channel:public AdaptableChannel
{
public:
	typedef typename AdaptableChannel::data_type		data_type;

	async_channel(){}
private:
	async_channel(const async_channel&);
	async_channel& operator=(async_channel const&);
public:

	void write(const data_type& data)
	{
		mutex::scoped_lock lock(m_mu);
		AdaptableChannel::write(data);
	}

	bool read(data_type& data)
	{
		mutex::scoped_lock lock(m_mu);
		return AdaptableChannel::read(data);
	}
protected:
	mutex				m_mu;
};

template<typename _DataType>
struct base_async_queue_channel:public async_channel<base_queue_channel<_DataType> >
{
};

#endif /* __FLOW_GRAPH_CHANNEL_H */