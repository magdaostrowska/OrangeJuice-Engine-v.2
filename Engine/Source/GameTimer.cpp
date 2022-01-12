#include "GameTimer.h"

#include "SDL\include\SDL.h"


GameTimer::GameTimer() : gameTimer(0.0f), gameStarted(false), deltaTime(0.016f), frameCounter(0), started_at(0.0f), stopped_at(0.0f), lastFrameMs(0.0f), cappedMs(0.0f)
{
	gameTimer = SDL_GetTicks();
}

GameTimer::~GameTimer()
{
}

void GameTimer::Start()
{
	frameCounter++;
	/*deltaTime = (float)GetTime() / 1000.0f;*/
	started_at = SDL_GetTicks();
}

void GameTimer::Stop()
{
	stopped_at = SDL_GetTicks();
}

void GameTimer::FinishUpdate()
{
	lastFrameMs = GetTime();
}

int GameTimer::GetEngineTimeStartup() const
{
	return (SDL_GetTicks() - gameTimer);
}

int GameTimer::GetTime() const
{
	return (SDL_GetTicks() - started_at);
}

void GameTimer::ResetTimer()
{
	gameTimer = SDL_GetTicks();
}

void GameTimer::ReadConfig(JsonParsing& node)
{
	cappedMs = (1 / node.GetJsonNumber("gameFPS")) * 1000;
}

void GameTimer::SaveConfig(JsonParsing& node)
{
	node.SetNewJsonNumber(node.ValueToObject(node.GetRootValue()), "gameFPS", GetFps());
}
