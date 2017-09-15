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


template <typename _Consumer, typename _InputChannel>
struct base_sink_strategy
{
	typedef _Consumer		consumer_type;
	typedef _InputChannel	input_channel_type;
};

template <typename _Consumer, typename _InputChannel>
struct normal_sink_strategy: public base_sink_strategy<_Consumer, _InputChannel>
{
public:
	void operator()(consumer_type& consumer, input_channel_type* channel)
	{
		bool result = false;
		input_channel_type::data_type data;
		result = channel->read(data);
		if(result)
		{
			consumer(data);
		}
	}
};

#endif /* __FLOW_GRAPH_STRATEGY_H */