#include "InputMapper.h"
#include "../../debug/Debug.h"

void InputMapper::registerScene(Scene& scene)
{
	scenes.push_back(&scene);
}

const int InputMapper::registerEvent(const InputEvent& event, const InputHandlerCode& code)
{
	for (auto i = scenes.cbegin(); i != scenes.cend(); ++i)
	{
		
		if ((*i)->getWindowHandle() == event.hwnd)
		{
			(*i)->handleInputEvent(event, code);
		}
	}
	return 0; // TODO for now!
}
