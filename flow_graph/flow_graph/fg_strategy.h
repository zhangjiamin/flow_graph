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
	void operator()(generator_type& generator, vector<output_channel_type*>& channels)
	{
		typename generator_type::output_data_type data;
		data = generator();
		for(int i=0;i<channels.size();++i)
		{
			channels[i]->write(data);
		}
		
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

template <typename _InputChannel, typename _Transformer, typename _OutputChannel>
struct base_filter_strategy
{
	typedef _InputChannel	input_channel_type;
	typedef _Transformer	transformer_type;
	typedef _OutputChannel	output_channel_type;
};

template <typename _InputChannel, typename _Transformer, typename _OutputChannel>
struct normal_filter_strategy: public base_filter_strategy<_InputChannel, _Transformer, _OutputChannel>
{
public:
	void operator()(input_channel_type* input_channel, transformer_type& transformer, vector<output_channel_type*>& output_channels)
	{
		bool result = false;
		typename input_channel_type::data_type input_data;
		typename output_channel_type::data_type output_data;
		result = input_channel->read(input_data);
		if(result)
		{
			output_data = transformer(input_data);
			for(int i=0;i<output_channels.size();++i)
			{
				output_channels[i]->write(output_data);
			}
			
		}
	}
};

#endif /* __FLOW_GRAPH_STRATEGY_H */