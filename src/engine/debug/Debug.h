#pragma once
#include <iostream>
#include <string>
#include <unordered_map>
#include "../userInput/keyCode/KeyCode.h"
#include "../userInput/inputEvent/InputEvent.h"
#include "../util/vector/USIVec2.h"
#include "../util/vector/FVec2.h"
#include <memory>

class Debug
{
public:
	Debug() = delete;
	static void init();
	static void print(const std::string& msg);
	static void print(const InputEvent& event);
	static void print(const USIVec2& vec);
	static void print(const FVec2& vec);
	static void print(const std::shared_ptr<USIVec2>& vec);
	static void print(const std::shared_ptr<FVec2>& vec);

private:
	static bool initialized;

	static std::unordered_map<KeyCode, std::string> keyMap;
	static std::unordered_map<InputEventType, std::string> eventTypeMap;

	static void createKeyMap();
	static void createInputEventTypeMap();
	
	static std::string keyCode_toString(KeyCode c);
	static std::string inputEventType_toString(InputEventType e);
};