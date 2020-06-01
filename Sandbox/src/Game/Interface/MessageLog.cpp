#include "Game/Interface/MessageLog.h"

MessageLog::MessageLog(int width, int height, std::string fontPath, int fontSize, Square::Vector2 offset)
	: mWidth(width), mHeight(height), mFontPath(fontPath), mFontSize(fontSize)
{
	Pos(offset);

	mBackground = new Square::Sprite("Interface/panelInset_beigeLight.png");
	mBackground->Parent(this);
	mBackground->Scale(Square::Vector2(width * (fontSize - 1) / 150.0f, height * fontSize / 75.0f));
	mBackground->Pos(Square::Vector2(mBackground->ScaledDimensions().x * 0.5f - offset.x, (-mBackground->ScaledDimensions().y * 0.5f + 1.0f) - offset.y));
}

MessageLog::~MessageLog()
{
	delete mBackground;

	for (auto text : mText)
		delete text;
}

bool MessageLog::ContainsClick() const
{
	Square::Vector2 pos = Square::InputHandler::Instance().MousePos();

	if (Active())
	{
		if (pos.x >= mBackground->Pos().x - mBackground->ScaledDimensions().x * 0.5f &&
			pos.x <= mBackground->Pos().x + mBackground->ScaledDimensions().x * 0.5f &&
			pos.y >= mBackground->Pos().y - mBackground->ScaledDimensions().y * 0.5f &&
			pos.y <= mBackground->Pos().y + mBackground->ScaledDimensions().y * 0.5f)
			return true;
	}

	return false;
}

void MessageLog::AddMessage(Square::Text* message)
{
	mText.push_back(message);
	mText.back()->Parent(this);

	if (mText.size() > mHeight)
	{
		std::vector<Square::Text*>::iterator i = mText.begin();
		delete (*i);
		mText.erase(i);
	}

	int lines = 0;
	for (auto it = mText.rbegin(); it != mText.rend(); ++it)
	{
		(*it)->Pos(Square::Vector2(0 + (*it)->ScaledDimensions().x * 0.5f, lines * (*it)->ScaledDimensions().y * -2.0f));
		lines++;
	}
}

void MessageLog::AddMessage(std::string text, SDL_Color color)
{
	std::string message = "";
	std::istringstream iss(text);
	std::vector<std::string> result{ std::istream_iterator<std::string>(iss), {} };

	int currentLineLength = 0;
	for (int i = 0; i < result.size(); i++)
	{
		if (currentLineLength + result[i].size() <= mWidth)
		{
			message += result[i];
			currentLineLength += result[i].size();

			if (i != result.size() - 1)
			{
				message += " ";
				currentLineLength++;
			}
		}
		else
		{
			while (result[i].size() > mWidth)
			{
				AddMessage(new Square::Text(message, mFontPath, mFontSize, color));
				message.clear();
				message += result[i].substr(0, mWidth);

				result[i].erase(0, mWidth);
				currentLineLength = 0;
			}

			if (result[i].size())
			{
				AddMessage(new Square::Text(message, mFontPath, mFontSize, color));
				message.clear();
				currentLineLength = 0;
				i--;
			}
		}

		if (i > -1 && result[i].size() && i == result.size() - 1)
			AddMessage(new Square::Text(message, mFontPath, mFontSize, color));
	}
}

void MessageLog::Render()
{
	mBackground->Render(true);
	for (const auto& text : mText)
		text->Render(true);
}
