#include "Game/Interface/Message.h"

MessageLog::MessageLog(int width, int height)
	: mWidth(width), mHeight(height)
{
}

MessageLog::~MessageLog()
{
	for (auto& text : mText)
		delete text;
}

void MessageLog::AddMessage(Square::Text* message)
{
	mText.push_back(message);
	mText.back()->Parent(this);

	if (mText.size() > mHeight)
		mText.erase(mText.begin());

	int lines = 0;
	for (auto it = mText.rbegin(); it != mText.rend(); ++it)
	{
		(*it)->Pos(Square::Vector2(0 + (*it)->ScaledDimensions().x * 0.5f, lines * (*it)->ScaledDimensions().y * -2.0f));
		lines++;
	}
}

void MessageLog::AddMessage(std::string text, SDL_Color color)
{
	std::string message;
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
				AddMessage(new Square::Text(message, "UI/VeraMono.ttf", 16, color));
				message.clear();
				message += result[i].substr(0, mWidth);

				result[i].erase(0, mWidth);
				currentLineLength = 0;
			}

			if (result[i].size())
			{
				AddMessage(new Square::Text(message, "UI/VeraMono.ttf", 16, color));
				message.clear();
				currentLineLength = 0;
				i--;
			}
		}

		if (result[i].size() && i == result.size() - 1)
			AddMessage(new Square::Text(message, "UI/VeraMono.ttf", 16, color));
	}
}

void MessageLog::Render()
{
	for (const auto& text : mText)
		text->Render();
}
