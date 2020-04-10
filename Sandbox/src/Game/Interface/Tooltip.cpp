#include "Tooltip.h"

const std::string Tooltip::FONT_PATH = "Font/VeraMono.ttf";

Tooltip::Tooltip(std::vector<std::string> infoText, Square::Vector2 pos)
{
	mWidth = PADDING * 2.0f;
	mHeight = PADDING * 2.5f;

	for (const auto& info : infoText)
	{
		mInfoText.push_back(new Square::Text(info, FONT_PATH, 12, { 0, 0, 0, 255 }));
		mInfoText.back()->Parent(this);
		mInfoText.back()->Translate(-Square::VEC2_UP * ((mInfoText.back()->ScaledDimensions().y + PADDING) * mInfoText.size()));

		mHeight += mInfoText.back()->ScaledDimensions().y + PADDING;

		if (mWidth < mInfoText.back()->ScaledDimensions().x)
			mWidth = mInfoText.back()->ScaledDimensions().x;
	}

	mWidth += PADDING;

	if (pos.x + mWidth * 0.5f > Square::Graphics::Instance().Camera().x + Square::Graphics::Instance().Camera().w)
		pos.x = Square::Graphics::Instance().Camera().x + Square::Graphics::Instance().Camera().w - mWidth * 0.5f;

	if (pos.y + mHeight * 0.5f > Square::Graphics::Instance().Camera().y + Square::Graphics::Instance().Camera().h)
		pos.y = Square::Graphics::Instance().Camera().y + Square::Graphics::Instance().Camera().h - mHeight * 0.5f;

	Pos(pos);
	mTopLeft = mInfoText.front()->Pos() - Square::Vector2(mWidth + PADDING * 0.5f, mInfoText.front()->ScaledDimensions().y + PADDING * 2.0f) * 0.5f;
}

Tooltip::~Tooltip()
{
	for (auto infoText : mInfoText)
		delete infoText;
}

void Tooltip::Update()
{
	
}

void Tooltip::Render()
{
	Square::Graphics::Instance().DrawRectangle(mTopLeft, mWidth, mHeight, { 255, 255, 160, 255 });

	for (const auto& infoText : mInfoText)
		infoText->Render();
}
