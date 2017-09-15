#ifndef __FLOW_GRAPH_STRATEGY_H
#define __FLOW_GRAPH_STRATEGY_H

template <typename _Generator, typename _OutputChannel>
struct base_source_strategy
{
	typedef _Generator		generator_type;
	typedef _OutputChannel	output_channel_type;
};

template <typename _Generator, typename _OutputChannel>
struct normal_source_strategy: public base_source_strategy<_Generator, _OutputChannel>
{
public:
	void operator()(generator_type& generator, output_channel_type& channel)
	{
		channel.write(generator());
	}
};

#endif /* __FLOW_GRAPH_STRATEGY_H */