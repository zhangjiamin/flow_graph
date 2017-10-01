#ifndef __FLOW_GRAPH_CONNECTOR_H
#define __FLOW_GRAPH_CONNECTOR_H
#include <queue>
#include <string>
using namespace std;

template <typename _Source, typename _Sink>
void connect_source_to_sink(_Source& _source, int source_port_index, _Sink& _sink, int sink_port_index)
{
	_sink.input_channel(source_port_index,_source.output_channel(sink_port_index));
}

#endif /* __FLOW_GRAPH_CONNECTOR_H */