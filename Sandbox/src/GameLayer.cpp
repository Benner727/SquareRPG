#include "GameLayer.h"

GameLayer::GameLayer()
{
	mText = new Square::Text("SquareRPG", "StrVar.ttf", 64, { 245, 245, 245, 255 });
	mText->Pos(Square::Vector2(Square::Graphics::SCREEN_WIDTH * 0.5f, Square::Graphics::SCREEN_HEIGHT * 0.5f));
}

GameLayer::~GameLayer()
{
	delete mText;
}


void GameLayer::OnUpdate()
{

}

void GameLayer::OnRender()
{
	mText->Render();
}