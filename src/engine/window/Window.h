#include <Windows.h>
#include "WindowSettings.h"

class Window
{
public:
	virtual void init() = 0;
	virtual void createWindow() = 0;
	virtual void showWindow() = 0;
	virtual void killWinodw() = 0;

	inline WindowSettings& getSettings() { return settings; }

protected:
	WindowSettings settings;
};