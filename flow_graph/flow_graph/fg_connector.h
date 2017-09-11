#ifndef __FLOW_GRAPH_CONNECTOR_H
#define __FLOW_GRAPH_CONNECTOR_H
#include <queue>
#include <string>
using namespace std;

template <typename _Source, typename _Sink>
void connect_source_to_sink(_Source& _source, _Sink& _sink)
{
	_sink.input_channel(_source.output_channel());
}

#endif /* __FLOW_GRAPH_CONNECTOR_H */