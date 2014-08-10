#ifndef WIN32_PROCESSMESSAGEDELEGATE_H
#define WIN32_PROCESSMESSAGEDELEGATE_H

# include <windows.h>

template<typename T>
class ProcessMessageDelegate
{
	typedef LRESULT (T::*ProcessFunction)(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
public:
	ProcessMessageDelegate(T* object, ProcessFunction procFunc)
	{
		mObject = object;
		mProcessFunction = procFunc;
	}

	LRESULT Invoke(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM	lParam)
	{
		return (mObject->*mProcessFunction)(hWnd, uMsg, wParam, lParam);
	}

private:
	ProcessFunction mProcessFunction;
	T* mObject;

};
#endif // WIN32_PROCESSMESSAGEDELEGATE_H