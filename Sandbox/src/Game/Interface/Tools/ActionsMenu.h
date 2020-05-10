#pragma once

#include <Square.h>

#include <vector>

#include "Game/Utility.h"
#include "Game/GridObject.h"

class ActionsMenu : public Square::GameObject
{
private:
	static const std::string FONT_PATH;
	static const int PADDING = 6;

	Square::Vector2 mTopLeft;
	int mWidth;
	int mHeight;

	Square::Text* mTitle;

	std::vector<std::string> mActions;
	std::vector<Square::Text*> mActionsText;
	std::vector<Square::Text*> mHighlightedText;

	std::vector<Square::GameObject*> mObjects;

	int mSelectedAction;

	void Init(std::string title, std::vector<std::string> actions, Square::Vector2 pos);

public:
	ActionsMenu(std::string title, std::vector<std::string> actions, Square::Vector2 pos);
	ActionsMenu(std::string title, std::vector<GridObject*> gridObjects, Square::Vector2 pos);
	~ActionsMenu();

	bool ContainsMouse() const;
	std::string Action();
	Square::GameObject* Object();

	void Update();
	void Render();
};