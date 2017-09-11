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
#include "fg_operator.h"
#include "fg_win_operator.h"
//#include "fg_connector.h"


#include <iostream>
using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	typedef base_source<int_generator, base_async_queue_channel<int> > base_async_queue_source;
	typedef WinLoopOperator<base_async_queue_source> loop_base_async_queue_source;
	typedef AsyncOperator<loop_base_async_queue_source> async_loop_base_async_queue_source;

	typedef base_filter<base_async_queue_channel<int>, int_transformer, base_async_queue_channel<int> > base_async_queue_filter;
	typedef WinLoopOperator<base_async_queue_filter> loop_base_async_queue_filter;
	typedef AsyncOperator<loop_base_async_queue_filter> async_loop_base_async_queue_filter;

	typedef base_sink<int_consumer, base_async_queue_channel<int> > base_async_queue_sink;
	typedef WinLoopOperator<base_async_queue_sink> loop_base_async_queue_sink;
	typedef AsyncOperator<loop_base_async_queue_sink> async_loop_base_async_queue_sink;

	async_loop_base_async_queue_source bsource;
	async_loop_base_async_queue_filter bfilter;
	async_loop_base_async_queue_sink bsink;

	bfilter.input_channel(bsource.output_channel());
	bsink.input_channel(bfilter.output_channel());

	//connect_source_to_sink(bsource,bfilter);
	//connect_source_to_sink(bfilter,bsink);

	bsource.start();
	bfilter.start();
	bsink.start();

	this_thread::sleep(posix_time::seconds(5));
	bsource.stop();

	this_thread::sleep(posix_time::seconds(5));
	bfilter.stop();

	this_thread::sleep(posix_time::seconds(5));
	bsink.stop();

	::system("pause");
	return 0;
}

