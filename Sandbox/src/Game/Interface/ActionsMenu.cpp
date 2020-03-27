#include "ActionsMenu.h"

const std::string ActionsMenu::FONT_PATH = "Font/VeraMono.ttf";

ActionsMenu::ActionsMenu(std::string title, std::vector<std::string> actions, Square::Vector2 pos)
	: mSelectedAction(-1)
{
	mTitle = new Square::Text(title, FONT_PATH, 18, { 255, 140, 0, 255 });
	mTitle->Parent(this);

	mWidth = mTitle->ScaledDimensions().x + PADDING * 2.0f;
	mHeight = mTitle->ScaledDimensions().y + PADDING * 2.5f;

	for (const auto& action : actions)
	{
		mActions.push_back(action);

		mActionsText.push_back(new Square::Text(action, FONT_PATH, 16, { 255, 255, 255, 255 }));
		mActionsText.back()->Parent(this);
		mActionsText.back()->Translate(-Square::VEC2_UP * ((mActionsText.back()->ScaledDimensions().y + PADDING) * mActions.size()));

		mHighlightedText.push_back(new Square::Text(action, FONT_PATH, 16, { 255, 215, 0, 255 }));
		mHighlightedText.back()->Parent(this);
		mHighlightedText.back()->Translate(-Square::VEC2_UP * ((mActionsText.back()->ScaledDimensions().y + PADDING) * mActions.size()));

		mHeight += mActionsText.back()->ScaledDimensions().y + PADDING;

		if (mWidth < mActionsText.back()->ScaledDimensions().x)
			mWidth = mActionsText.back()->ScaledDimensions().x;
	}

	if (pos.x + mWidth * 0.5f > Square::Graphics::Instance().Camera().x + Square::Graphics::Instance().Camera().w)
		pos.x = Square::Graphics::Instance().Camera().x + Square::Graphics::Instance().Camera().w - mWidth * 0.5f;

	if (pos.y + mHeight * 0.5f > Square::Graphics::Instance().Camera().y + Square::Graphics::Instance().Camera().h)
		pos.y = Square::Graphics::Instance().Camera().y + Square::Graphics::Instance().Camera().h - mHeight * 0.5f;

	Pos(pos);
	mTopLeft = mTitle->Pos() - mTitle->ScaledDimensions() * 0.5f - PADDING;
}

ActionsMenu::~ActionsMenu()
{
	delete mTitle;

	for (auto text : mActionsText)
		delete text;

	for (auto highlighted : mHighlightedText)
		delete highlighted;
}

bool ActionsMenu::ContainsMouse() const
{
	Square::Vector2 pos = Square::InputHandler::Instance().MousePos();

	if (pos.x >= mTopLeft.x && pos.y >= mTopLeft.y &&
		pos.x <= mTopLeft.x + mWidth && pos.y <= mTopLeft.y + mHeight)
		return true;

	return false;
}

std::string ActionsMenu::Action()
{
	std::string action = "";

	if (mSelectedAction != -1)
		action = mActions[mSelectedAction];

	return action;
}

void ActionsMenu::Update()
{
	mSelectedAction = -1;

	if (ContainsMouse())
	{
		Square::Vector2 pos = Square::InputHandler::Instance().MousePos();
		int slot = 0;
		for (const auto& action : mActionsText)
		{
			if (pos.x >= action->Pos().x - action->ScaledDimensions().x * 0.5f &&
				pos.x <= action->Pos().x + action->ScaledDimensions().x * 0.5f &&
				pos.y >= action->Pos().y - action->ScaledDimensions().y * 0.5f &&
				pos.y <= action->Pos().y + action->ScaledDimensions().y * 0.5f)
			{
				mSelectedAction = slot;
				break;
			}

			slot++;
		}
	}
	else
		Active(false);
}

void ActionsMenu::Render()
{
	Square::Graphics::Instance().DrawRectangle(mTopLeft, mWidth, mHeight, { 93, 84, 71, 255 });

	mTitle->Render();

	for (int i = 0; i < mActionsText.size(); i++)
	{
		if (mSelectedAction != i)
			mActionsText[i]->Render();
		else
			mHighlightedText[i]->Render();
	}
}
