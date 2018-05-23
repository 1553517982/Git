#include "AppDelegate.h"

#include <windows.h>
#include <process.h>
#include <stdio.h>

#include "CCLuaEngine.h"

USING_NS_CC;


#define BUFFER_MAX 1024

char g_nbstdin_buffer[2][BUFFER_MAX];
HANDLE g_input[2];
HANDLE g_process[2];

DWORD WINAPI console_input(LPVOID lpParameter)
{
	for (;;) {
		int i;
		for (i=0;i<2;i++) {
			fgets(g_nbstdin_buffer[i],BUFFER_MAX,stdin);
			SetEvent(g_input[i]);
			WaitForSingleObject(g_process[i],INFINITE);
		}
	}
	return 0;
}

void create_nbstdin()
{
	int i;
	DWORD tid;
	CreateThread(NULL,1024,&console_input,0,0,&tid);
	for (i=0;i<2;i++) {
		g_input[i]=CreateEvent(NULL,FALSE,FALSE,NULL);
		g_process[i]=CreateEvent(NULL,FALSE,FALSE,NULL);
		g_nbstdin_buffer[i][0]='\0';
	}
}

const char* nbstdin()
{
	DWORD n=WaitForMultipleObjects(2,g_input,FALSE,0);
	if (n==WAIT_OBJECT_0 || n==WAIT_OBJECT_0+1) {
		n=n-WAIT_OBJECT_0;
		SetEvent(g_process[n]);
		return g_nbstdin_buffer[n];
	}
	else {
		return 0;
	}
}

class ConsoleNode : public CCNode
{
public:
	static ConsoleNode* instance(){
		static ConsoleNode* inst = nullptr;
		if (!inst)
		{
			inst = new ConsoleNode();
		}
		
		return inst;
	}

	virtual void update(float delta){
		//²¶×½¼üÅÌÏûÏ¢
		const char *line = nbstdin();
		if (line && strlen(line)>0) 
		{
			printf(">%s",line);
			if (LuaEngine::defaultEngine())
			{
				std::string text = line;
				int pos = text.find("\n");
				if (pos != -1)
				{
					text = text.substr(0, pos);
				}

				char stext[1024]  = {0};
				sprintf_s(stext, "ChatCC:SendMsg(\"%s\")", text.c_str());
			
				LuaEngine::defaultEngine()->executeString(stext);
			}

		}
	}

	void startCatchConsole(){
		this->scheduleUpdate();
		this->resumeSchedulerAndActions();
	}

private:
	ConsoleNode(){
		create_nbstdin();
	}
};

