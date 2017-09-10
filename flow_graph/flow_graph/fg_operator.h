#ifndef __FLOW_GRAPH_OPERATOR_H 
#define __FLOW_GRAPH_OPERATOR_H 
#include <queue>
#include <string>
#include <iostream>
using namespace std;

#include <boost/thread.hpp>
using namespace boost;


struct Operator
{
	void operate(){}
};

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


#endif /* __FLOW_GRAPH_OPERATOR_H */