#ifndef __FLOW_GRAPH_SOURCE_H
#define __FLOW_GRAPH_SOURCE_H

template <typename _OutputDataType, typename _Generator, typename _OutputChannel>
struct base_source
{
	typedef _OutputDataType	output_data_type;
	typedef _Generator		generator_type;
	typedef _OutputChannel	output_channel_type;
};



#endif /* __FLOW_GRAPH_SOURCE_H */