#ifndef __FLOW_GRAPH_CONSUMER_H
#define __FLOW_GRAPH_CONSUMER_H
#include <iostream>
using namespace std;

template <typename _InputDataType>
struct base_consumer
{
	typedef _InputDataType	input_data_type;
};

struct int_consumer: public base_consumer<int>
{
public:
	int_consumer()
	{
	}

	void operator()(input_data_type& data)
	{
		cout<<data<<endl;
	}
protected:
	
};

#endif /* __FLOW_GRAPH_CONSUMER_H */