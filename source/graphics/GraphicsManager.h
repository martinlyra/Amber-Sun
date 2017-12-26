#pragma once

class GraphicsManager
{
public:
	GraphicsManager();
	~GraphicsManager();

	void Initialize();

	void DrawFrame(); // alias for calling the three methods below at once

	void BeginDraw();
	void Draw();
	void EndDraw();
};

