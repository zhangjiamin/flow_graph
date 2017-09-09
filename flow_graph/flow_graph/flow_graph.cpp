// flow_graph.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "fg_generator.h"
#include "fg_channel.h"
#include "fg_source.h"
#include "fg_transformer.h"
#include "fg_consumer.h"
#include "fg_sink.h"

#include <iostream>
using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	base_generator<int> bg;
	base_generator<int>::output_data_type a = 0;

	cout<<a<<endl;

	system("pause");
	return 0;
}

