// flow_graph.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "fg_channel.h"
#include "fg_source.h"
#include "fg_filter.h"
#include "fg_sink.h"
#include "fg_operator.h"
#include "fg_win_operator.h"
#include "fg_connector.h"
#include "fg_function.h"


#include <iostream>
using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	typedef base_source<int_generator, base_async_queue_channel<int>, normal_source_strategy<int_generator,base_async_queue_channel<int> > > base_async_queue_source;
	typedef WinLoopOperator<base_async_queue_source> loop_base_async_queue_source;
	typedef AsyncOperator<loop_base_async_queue_source> async_loop_base_async_queue_source;

	typedef base_filter<base_async_queue_channel<int>, int_transformer, base_async_queue_channel<int>, normal_filter_strategy<base_async_queue_channel<int>, int_transformer, base_async_queue_channel<int>> > base_async_queue_filter;
	typedef WinLoopOperator<base_async_queue_filter> loop_base_async_queue_filter;
	typedef AsyncOperator<loop_base_async_queue_filter> async_loop_base_async_queue_filter;

	typedef base_sink<int_consumer, base_async_queue_channel<int>, normal_sink_strategy<int_consumer,base_async_queue_channel<int>> > base_async_queue_sink;
	typedef WinLoopOperator<base_async_queue_sink> loop_base_async_queue_sink;
	typedef AsyncOperator<loop_base_async_queue_sink> async_loop_base_async_queue_sink;

	async_loop_base_async_queue_source bsource;//("source");
	async_loop_base_async_queue_filter bfilter;//("filter");
	async_loop_base_async_queue_sink bsink1;//("sink");
	async_loop_base_async_queue_sink bsink2;//("sink");

	bsource.setup(0,1);
	bfilter.setup(1,2);
	bsink1.setup(1,0);
	bsink2.setup(1,0);

	connect_source_to_sink(bsource,0,bfilter,0);
	connect_source_to_sink(bfilter,0,bsink1,0);
	connect_source_to_sink(bfilter,1,bsink2,0);

	bsource.start();
	bfilter.start();
	bsink1.start();
	bsink2.start();

	this_thread::sleep(posix_time::seconds(5));
	bsource.stop();

	this_thread::sleep(posix_time::seconds(8));
	bfilter.stop();

	this_thread::sleep(posix_time::seconds(8));
	bsink1.stop();

	this_thread::sleep(posix_time::seconds(8));
	bsink2.stop();

	::system("pause");
	return 0;
}

