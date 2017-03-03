#include "Debug.h"

bool Debug::initialized = false;
std::unordered_map<KeyCode, std::string> Debug::keyMap;
std::unordered_map<InputEventType, std::string> Debug::eventTypeMap;
std::unordered_map<ShaderType, std::string> Debug::shaderTypeMap;

void Debug::init()
{
	if (initialized)
	{
		return;
	}

	initialized = true;

	createKeyMap();
	createInputEventTypeMap();
	createShaderTypeMap();

	std::cout << "========== Debug Mode ==========" << std::endl;
}

void Debug::print(const std::string& msg)
{
	std::cout << msg << std::endl;
}

void Debug::print(const InputEvent & event)
{
	std::cout << "- InputEvent \n";
	std::cout << "     Event Type:   " << inputEventType_toString(event.type) << "\n";
	std::cout << "     Key Code:     " << keyCode_toString(event.key) << "\n";

	std::cout << "     Alt Down:     " << event.altDown << "\n";
	std::cout << "     Ctrl Down:    " << event.ctrlDown << "\n";
	std::cout << "     Shift Down:   " << event.shiftDown << "\n";

	std::cout << "     LMouse Down:  " << event.mouseLDown << "\n";
	std::cout << "     RMouse Down:  " << event.mouseRDown << "\n";
	std::cout << "     MMouse Down:  " << event.mouseMDown << "\n";

	std::cout << "     MMouse PosX:  " << event.posX << "\n";
	std::cout << "     MMouse PosX:  " << event.posY << "\n";

	std::cout << std::endl;
}

void Debug::print(const USIVec2& vec)
{
	std::cout << "X = " << vec.x << "     " << "Y = " << vec.y << std::endl;
}

void Debug::print(const std::shared_ptr<USIVec2>& vec)
{
	std::cout << "X = " << vec->x << "     " << "Y = " << vec->y << std::endl;
}

void Debug::print(const FVec2& vec)
{
	std::cout << "X = " << vec.x << "     " << "Y = " << vec.y << std::endl;
}

void Debug::print(const std::shared_ptr<FVec2>& vec)
{
	std::cout << "X = " << vec->x << "     " << "Y = " << vec->y << std::endl;
}

void Debug::print(const ShaderType & type)
{
	std::cout << shaderType_toString(type) << std::endl;
}

void Debug::createKeyMap()
{
	keyMap.insert(std::make_pair(KeyCode::NO_CODE, "NO_CODE"));
	keyMap.insert(std::make_pair(KeyCode::MOUSE_L, "MOUSE_L"));
	keyMap.insert(std::make_pair(KeyCode::MOUSE_R, "MOUSE_R"));
	keyMap.insert(std::make_pair(KeyCode::MOUSE_M, "MOUSE_M"));
	keyMap.insert(std::make_pair(KeyCode::MOUSE_N1, "MOUSE_N1"));
	keyMap.insert(std::make_pair(KeyCode::MOUSE_N2, "MOUSE_N2"));

	keyMap.insert(std::make_pair(KeyCode::BACKSPACE, "BACKSPACE"));
	keyMap.insert(std::make_pair(KeyCode::TAB, "TAB"));

	keyMap.insert(std::make_pair(KeyCode::ENTER, "ENTER"));
	keyMap.insert(std::make_pair(KeyCode::SHIFT, "SHIFT"));
	keyMap.insert(std::make_pair(KeyCode::CTRL, "CTRL"));
	keyMap.insert(std::make_pair(KeyCode::ALT, "ALT"));

	keyMap.insert(std::make_pair(KeyCode::PAUSE, "PAUSE"));
	keyMap.insert(std::make_pair(KeyCode::CAPSLOCK, "CAPSLOCK"));
	keyMap.insert(std::make_pair(KeyCode::ESC, "ESC"));
	keyMap.insert(std::make_pair(KeyCode::SPACE, "SPACE"));

	keyMap.insert(std::make_pair(KeyCode::PAGEUP, "PAGEUP"));
	keyMap.insert(std::make_pair(KeyCode::PAGEDOWN, "PAGEDOWN"));
	keyMap.insert(std::make_pair(KeyCode::END, "END"));
	keyMap.insert(std::make_pair(KeyCode::HOME, "HOME"));

	keyMap.insert(std::make_pair(KeyCode::LEFT, "LEFT"));
	keyMap.insert(std::make_pair(KeyCode::UP, "UP"));
	keyMap.insert(std::make_pair(KeyCode::RIGHT, "RIGHT"));
	keyMap.insert(std::make_pair(KeyCode::DOWN, "DOWN"));

	keyMap.insert(std::make_pair(KeyCode::SELECT, "SELECT"));
	keyMap.insert(std::make_pair(KeyCode::PRINT, "PRINT"));
	keyMap.insert(std::make_pair(KeyCode::EXECUTE, "EXECUTE"));
	keyMap.insert(std::make_pair(KeyCode::PRINTSCREEN, "PRINTSCREEN"));
	keyMap.insert(std::make_pair(KeyCode::INSERT, "INSERT"));
	keyMap.insert(std::make_pair(KeyCode::DEL, "DELETE"));
	keyMap.insert(std::make_pair(KeyCode::HELP, "HELP"));

	keyMap.insert(std::make_pair(KeyCode::KEY0, "KEY0"));
	keyMap.insert(std::make_pair(KeyCode::KEY1, "KEY1"));
	keyMap.insert(std::make_pair(KeyCode::KEY2, "KEY2"));
	keyMap.insert(std::make_pair(KeyCode::KEY3, "KEY3"));
	keyMap.insert(std::make_pair(KeyCode::KEY4, "KEY4"));
	keyMap.insert(std::make_pair(KeyCode::KEY5, "KEY5"));
	keyMap.insert(std::make_pair(KeyCode::KEY6, "KEY6"));
	keyMap.insert(std::make_pair(KeyCode::KEY7, "KEY7"));
	keyMap.insert(std::make_pair(KeyCode::KEY8, "KEY8"));
	keyMap.insert(std::make_pair(KeyCode::KEY9, "KEY9"));

	keyMap.insert(std::make_pair(KeyCode::A, "A"));
	keyMap.insert(std::make_pair(KeyCode::B, "B"));
	keyMap.insert(std::make_pair(KeyCode::C, "C"));
	keyMap.insert(std::make_pair(KeyCode::D, "D"));
	keyMap.insert(std::make_pair(KeyCode::E, "E"));
	keyMap.insert(std::make_pair(KeyCode::F, "F"));
	keyMap.insert(std::make_pair(KeyCode::G, "G"));
	keyMap.insert(std::make_pair(KeyCode::H, "H"));
	keyMap.insert(std::make_pair(KeyCode::I, "I"));
	keyMap.insert(std::make_pair(KeyCode::J, "J"));
	keyMap.insert(std::make_pair(KeyCode::K, "K"));
	keyMap.insert(std::make_pair(KeyCode::L, "L"));
	keyMap.insert(std::make_pair(KeyCode::M, "M"));
	keyMap.insert(std::make_pair(KeyCode::N, "N"));
	keyMap.insert(std::make_pair(KeyCode::O, "O"));
	keyMap.insert(std::make_pair(KeyCode::P, "P"));
	keyMap.insert(std::make_pair(KeyCode::Q, "Q"));
	keyMap.insert(std::make_pair(KeyCode::R, "R"));
	keyMap.insert(std::make_pair(KeyCode::S, "S"));
	keyMap.insert(std::make_pair(KeyCode::T, "T"));
	keyMap.insert(std::make_pair(KeyCode::U, "U"));
	keyMap.insert(std::make_pair(KeyCode::V, "V"));
	keyMap.insert(std::make_pair(KeyCode::W, "W"));
	keyMap.insert(std::make_pair(KeyCode::X, "X"));
	keyMap.insert(std::make_pair(KeyCode::Y, "Y"));
	keyMap.insert(std::make_pair(KeyCode::Z, "Z"));

	keyMap.insert(std::make_pair(KeyCode::WIDNOWS_L, "WINDOWS_L"));
	keyMap.insert(std::make_pair(KeyCode::WINDOWS_R, "WINDOWS_R"));
	keyMap.insert(std::make_pair(KeyCode::APPLICATION, "APPLICATION"));
	keyMap.insert(std::make_pair(KeyCode::SLEEP, "SLEEP"));

	keyMap.insert(std::make_pair(KeyCode::NUM0, "NUM0"));
	keyMap.insert(std::make_pair(KeyCode::NUM1, "NUM1"));
	keyMap.insert(std::make_pair(KeyCode::NUM2, "NUM2"));
	keyMap.insert(std::make_pair(KeyCode::NUM3, "NUM3"));
	keyMap.insert(std::make_pair(KeyCode::NUM4, "NUM4"));
	keyMap.insert(std::make_pair(KeyCode::NUM5, "NUM5"));
	keyMap.insert(std::make_pair(KeyCode::NUM6, "NUM6"));
	keyMap.insert(std::make_pair(KeyCode::NUM7, "NUM7"));
	keyMap.insert(std::make_pair(KeyCode::NUM8, "NUM8"));
	keyMap.insert(std::make_pair(KeyCode::NUM9, "NUM9"));

	keyMap.insert(std::make_pair(KeyCode::MULTIPLY, "MULTIPLY"));
	keyMap.insert(std::make_pair(KeyCode::ADD, "ADD"));
	keyMap.insert(std::make_pair(KeyCode::SEPERATOR, "SEPERATOR"));
	keyMap.insert(std::make_pair(KeyCode::SUBTRACT, "SUBTRACT"));
	keyMap.insert(std::make_pair(KeyCode::DECIMAL, "DECIMAL"));
	keyMap.insert(std::make_pair(KeyCode::DIVIDE, "DIVIDE"));

	keyMap.insert(std::make_pair(KeyCode::F1, "F1"));
	keyMap.insert(std::make_pair(KeyCode::F2, "F2"));
	keyMap.insert(std::make_pair(KeyCode::F3, "F3"));
	keyMap.insert(std::make_pair(KeyCode::F4, "F4"));
	keyMap.insert(std::make_pair(KeyCode::F5, "F5"));
	keyMap.insert(std::make_pair(KeyCode::F6, "F6"));
	keyMap.insert(std::make_pair(KeyCode::F7, "F7"));
	keyMap.insert(std::make_pair(KeyCode::F8, "F8"));
	keyMap.insert(std::make_pair(KeyCode::F9, "F9"));
	keyMap.insert(std::make_pair(KeyCode::F10, "F10"));
	keyMap.insert(std::make_pair(KeyCode::F11, "F11"));
	keyMap.insert(std::make_pair(KeyCode::F12, "F12"));

	keyMap.insert(std::make_pair(KeyCode::NUMLOCK, "NUMLOCK"));
	keyMap.insert(std::make_pair(KeyCode::SCROLLLOCK, "SCROLLLOCK"));

	keyMap.insert(std::make_pair(KeyCode::SHIFT_L, "SHIFT_L"));
	keyMap.insert(std::make_pair(KeyCode::SHIFT_R, "SHIFT_R"));
	keyMap.insert(std::make_pair(KeyCode::CTRL_L, "CTRL_L"));
	keyMap.insert(std::make_pair(KeyCode::CTRL_R, "CTRL_R"));
	keyMap.insert(std::make_pair(KeyCode::ALT_L, "ALT_L"));
	keyMap.insert(std::make_pair(KeyCode::ALT_R, "ALT_R"));
}

void Debug::createInputEventTypeMap()
{
	eventTypeMap.insert(std::make_pair(InputEventType::NO_EVENT, "NO_EVENT"));
	
	eventTypeMap.insert(std::make_pair(InputEventType::KEY_DOWN, "KEY_DOWN"));
	eventTypeMap.insert(std::make_pair(InputEventType::KEY_UP, "KEY_UP"));

	eventTypeMap.insert(std::make_pair(InputEventType::MOUSE_DOWN, "MOUSE_DOWN"));
	eventTypeMap.insert(std::make_pair(InputEventType::MOUSE_UP, "MOUSE_UP"));
}

void Debug::createShaderTypeMap()
{
	shaderTypeMap.insert(std::make_pair(ShaderType::BasicShader, "BasicShader"));
	shaderTypeMap.insert(std::make_pair(ShaderType::SimplePositionShader, "SimplePositionShader"));
	shaderTypeMap.insert(std::make_pair(ShaderType::SimpleColorShader, "SimpleColorShader"));
}

std::string Debug::keyCode_toString(const KeyCode& c)
{
	auto it = keyMap.find(c);
	
	if (it != keyMap.end())
	{
		return it->second;
	}
	return "No Key";
}

std::string Debug::inputEventType_toString(const InputEventType& e)
{
	auto it = eventTypeMap.find(e);

	if (it != eventTypeMap.end())
	{
		return it->second;
	}
	return "No Event";
}

std::string Debug::shaderType_toString(const ShaderType & type)
{
	auto it = shaderTypeMap.find(type);

	if (it != shaderTypeMap.end())
	{
		return it->second;
	}
	return "No Shader Type";
}
