#ifndef __FLOW_GRAPH_SINK_H
#define __FLOW_GRAPH_SINK_H

template <typename _InputDataType, typename _Consumer, typename _InputChannel>
struct base_sink
{
	typedef _InputDataType	input_data_type;
	typedef _Consumer		generator_type;
	typedef _InputChannel	input_channel_type;
};



#endif /* __FLOW_GRAPH_SOURCE_H */