#ifndef __FLOW_GRAPH_CONNECTOR_H
#define __FLOW_GRAPH_CONNECTOR_H
#include <queue>
#include <string>
using namespace std;

template <typename _Source, typename _Sink>
struct base_connector
{
	typedef _Source			source_type;
	typedef _Sink			sink_type;
};


template <typename _Source, typename _Sink>
struct connector:public base_connector<_Source, _Sink>
{
	void operator()(source_type source, sink_type sink)
	{
		sink_type::input_channel_type* input_channel;
		source_type::output_channel_type* output_channel;
		output_channel = source.output_channel();
		cout<<"source:"<<output_channel<<endl;
		input_channel = static_cast<sink_type::input_channel_type*>(output_channel);
		sink.input_channel(input_channel);
	}
};

template <typename _Source, typename _Sink>
void connect_source_to_sink(_Source _source, _Sink _sink)
{
	_sink.input_channel(_source.output_channel());
}

#endif /* __FLOW_GRAPH_CONNECTOR_H */