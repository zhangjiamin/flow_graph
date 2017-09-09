#ifndef __FLOW_GRAPH_FILTER_H
#define __FLOW_GRAPH_FILTER_H

template <typename _InputDataType, typename _InputChannel, typename _Transformer, typename _OutputDataType, typename _OutputChannel>
struct base_filter
{
	typedef _InputDataType	input_data_type;
	typedef _InputChannel	input_channel_type;
	typedef _Transformer	transformer_type;
	typedef _OutputDataType	output_data_type;
	typedef _OutputChannel	output_channel_type;
};



#endif /* __FLOW_GRAPH_SOURCE_H */