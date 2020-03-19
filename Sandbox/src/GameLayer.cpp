#include "GameLayer.h"

GameLayer::GameLayer()
{
	player = new Player();

	for (int i = 0; i < 10; i++)
	{
		player->Inventory().Add(ItemFactory::Instance().GetItem(2));
		player->Inventory().Add(ItemFactory::Instance().GetItem(4));
	}

	player->Inventory().Remove(2);
	player->Inventory().Remove(7);
	player->Inventory().Remove(17);

	playerUI = new PlayerInterface(*player);
}

GameLayer::~GameLayer()
{
	delete player;
	delete playerUI;
}

void GameLayer::HandlePathing()
{
	static std::list<Point> path;
	static PathFinder pathFinder(map);

	if (Square::InputHandler::Instance().MouseButtonPressed(Square::InputHandler::left))
	{
		Point target;
		target.x = (Square::InputHandler::Instance().MousePos().x + Square::Graphics::Instance().Camera().x) / 32.0f;
		target.y = (Square::InputHandler::Instance().MousePos().y + Square::Graphics::Instance().Camera().y) / 32.0f;

		std::cout << target.x << ", " << target.y << std::endl;

		path.clear();
		path = pathFinder.GeneratePath(player->MapPosition(), target);
	}

	if (!path.empty() && !player->Moving())
	{
		player->MoveTo(path.front());
		path.pop_front();
	}


}

void GameLayer::OnUpdate()
{
	player->Update();
	playerUI->Update();
	map.Update(0);

	HandlePathing();
}

void GameLayer::OnRender()
{
	map.Render(0);
	player->Render();
	playerUI->Render();
}