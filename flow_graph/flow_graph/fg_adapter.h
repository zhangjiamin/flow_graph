#ifndef __FLOW_GRAPH_OPERATOR_H
#define __FLOW_GRAPH_OPERATOR_H
#include <queue>
#include <string>
using namespace std;

#include <boost/thread.hpp>
using namespace boost;

template <typename AdaptableOperator>
struct LoopOperator:public AdaptableOperator
{
	void operate()
	{
		while(true)
		{
			AdaptableOperator::operate();
		}
	}
};

template <typename AdaptableOperator>
struct AsyncOperator:public AdaptableOperator
{
	void start()
	{
		thread(&AsyncOperator<AdaptableOperator>::operate, this);
	}
	void stop(){}
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


#endif /* __FLOW_GRAPH_OPERATOR_H */