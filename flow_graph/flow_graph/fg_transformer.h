#ifndef __FLOW_GRAPH_TRANSFORMER_H
#define __FLOW_GRAPH_TRANSFORMER_H

template <typename _InputDataType, typename _OutputDataType>
struct base_transformer
{
	typedef _InputDataType	input_data_type;
	typedef _OutputDataType	output_data_type;
};

struct int_transformer: public base_transformer<int, int>
{
public:
	int_transformer()
	{
		//m_val = output_data_type();
	}

	output_data_type& operator()(const input_data_type& data)
	{
		m_val = data * 2;
		return m_val;
	}
protected:
	output_data_type m_val;

};

#endif /* __FLOW_GRAPH_TRANSFORMER_H */