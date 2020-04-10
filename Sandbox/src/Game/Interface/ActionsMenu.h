#pragma once

#include <Square.h>

#include <vector>

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

	int mSelectedAction;

public:
	ActionsMenu(std::string title, std::vector<std::string> actions, Square::Vector2 pos);
	~ActionsMenu();

	bool ContainsMouse() const;
	std::string Action();

	void Update();
	void Render();
};