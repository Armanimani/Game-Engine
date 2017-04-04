#pragma once

#include "Viewport.h"
#include <vector>
#include "layout\ViewportLayout.h"
#include "../window/WindowSettings.h"
#include "../camera/Camera.h"

class ViewportManager
{
public:
	ViewportManager() {}

	void prepare();
	inline void updateLayout() {layout->updateLayout(map); }

	inline void addViewport (const std::shared_ptr<Viewport> viewport) { map.push_back(viewport); }
	inline const std::shared_ptr<Viewport> getViewport(const GLuint& ID) { return map[static_cast<std::size_t>(ID)]; }

	inline void setLayout(const std::shared_ptr<ViewportLayout> value, const std::vector<std::shared_ptr<Camera>> cams)
	{
		layout = value;
		layout->initLayout(map, cams);
	}
	inline const std::shared_ptr<ViewportLayout> getLayout() { return layout; }

	inline const std::size_t getSize() { return map.size(); }

	inline void cleanUp() { map.clear(); }
	std::shared_ptr<Camera> findCamera(const GLuint& x, const GLuint& y);
protected:
	GLuint ID = 0;
	std::shared_ptr<ViewportLayout> layout;
	std::vector<std::shared_ptr<Viewport>> map;
};