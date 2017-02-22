#pragma once
#include <iostream>
#include <string>
#include <unordered_map>
#include "../userInput/keyCode/KeyCode.h"
#include "../userInput/inputEvent/InputEvent.h"

class Debug
{
public:
	Debug() = delete;
	static void init();
	static void print(const std::string& msg);
	static void print(const InputEvent& event);

private:
	static bool initialized;

	static std::unordered_map<KeyCode, std::string> keyMap;
	static std::unordered_map<InputEventType, std::string> eventTypeMap;

	static void createKeyMap();
	static void createInputEventTypeMap();
	
	static std::string keyCode_toString(KeyCode c);
	static std::string inputEventType_toString(InputEventType e);
};