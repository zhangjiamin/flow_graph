// flow_graph.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "fg_generator.h"
#include "fg_channel.h"
#include "fg_source.h"
#include "fg_transformer.h"
#include "fg_consumer.h"
#include "fg_sink.h"
#include "fg_filter.h"
//#include "fg_connector.h"

#include <iostream>
using namespace std;


int _tmain(int argc, _TCHAR* argv[])
{
	async_queue_channel_source<int,int_generator> bsource("source");
	async_queue_channel_filter<int,int_transformer,int> bfilter("filter");
	async_queue_channel_sink<int,int_consumer>bsink("sink");
	
	bfilter.input_channel(bsource.output_channel());
	bsink.input_channel(bfilter.output_channel());

	bool r;
	int a;

	for(int i=0;i<100;++i)
	{
		//bsource.operate();
		//bfilter.operate();
		//bsink.operate();
	}

	bsource.start();
	bfilter.start();
	bsink.start();

	::system("pause");
	return 0;
}

