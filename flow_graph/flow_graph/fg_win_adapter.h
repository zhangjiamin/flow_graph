#ifndef __FLOW_GRAPH_WIN_ADAPTER_H
#define __FLOW_GRAPH_WIN_ADAPTER_H
#include <queue>
#include <string>
#include <iostream>
using namespace std;

#include "windows.h"

template <typename AdaptableOperator>
struct WinLoopOperator:public AdaptableOperator
{
	void start()
	{
	}

	void operate()
	{	
		m_hEvent = CreateEvent(NULL,TRUE,FALSE,NULL); 
		while(WAIT_OBJECT_0 != WaitForSingleObject(m_hEvent,0))
		{
			AdaptableOperator::operate();
		}

		cout<<m_name<<":exit operate()!"<<endl;
	}

	void stop()
	{
		SetEvent(m_hEvent);
	}
protected:
	HANDLE				m_hEvent;

};


#endif /* __FLOW_GRAPH_WIN_ADAPTER_H */