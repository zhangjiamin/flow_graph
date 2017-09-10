#ifndef __FLOW_GRAPH_ADAPTER_H
#define __FLOW_GRAPH_ADAPTER_H
#include <queue>
#include <string>
#include <iostream>
using namespace std;

#include <boost/thread.hpp>
using namespace boost;

template <typename AdaptableOperator>
struct LoopOperator:public AdaptableOperator
{
	void start()
	{
	}

	void operate()
	{	
		mutex::scoped_lock lock(m_mu);
		while(!m_cond.timed_wait(lock, posix_time::microseconds(0)))
		{
			AdaptableOperator::operate();
		}

		cout<<m_name<<":exit operate()!"<<endl;
	}

	void stop()
	{
		m_mu.unlock();
	}
protected:
	mutex				m_mu;
	condition_variable	m_cond;
};

template <typename AdaptableOperator>
struct AsyncOperator:public AdaptableOperator
{
	void start()
	{
		thread(&AsyncOperator<AdaptableOperator>::operate, this);
	}
};

template <typename AdaptableChannel>
struct async_channel:public AdaptableChannel
{
	typedef typename AdaptableChannel::input_data_type		input_data_type;
	typedef typename AdaptableChannel::output_data_type		output_data_type;

	void write(const input_data_type& data)
	{
		mutex::scoped_lock lock(m_mu);
		AdaptableChannel::write(data);
	}

	bool read(output_data_type& data)
	{
		mutex::scoped_lock lock(m_mu);
		return AdaptableChannel::read(data);
	}
protected:
	mutex				m_mu;
};


#endif /* __FLOW_GRAPH_ADAPTER_H */