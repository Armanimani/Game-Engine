#pragma once
#include "../text/Font.h"
#include <memory>


class FontFileController
{
public:
	static std::shared_ptr<Font> readFile(const std::string& path);
};