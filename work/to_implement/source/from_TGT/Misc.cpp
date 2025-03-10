ncp_call(0x0211B91C, 10)
void goalFadeOutHook(Player* player)
{
	if (Game::getPlayerCount() > 1)
	{
		u32 playerID = player->playerID;
		u32 otherID = playerID ^ 1;

		Fader& fader = Game::fader;
		//fader.fadingType = Fader::FadingType::FadeOnly;
		fader.fadingState[otherID] |= 0x28;
	}

	player->goalBeginPoleSlide(); // Keep replaced instruction
}

ncp_call(0x0211B960, 10)
void goalFadeInHook(Player* player)
{
	if (player->transitionTimer == 0)
	{
		if (Game::getPlayerCount() > 1)
		{
			u32 playerID = player->playerID;
			u32 otherID = playerID ^ 1;

			Game::fader.fadingState[otherID] |= 5;

			PlayerSpectate::setTarget(otherID, playerID);
		}
		player->transitionTimer = -1;
	}
	player->goalPoleTurn(); // Keep replaced instruction
}