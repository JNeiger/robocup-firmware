#include "Kickoff.hpp"

Gameplay::Behaviors::Kickoff::Kickoff(GameplayModule *gameplay):
    Behavior(gameplay)
{
}

bool Gameplay::Behaviors::Kickoff::run()
{
	if (!allVisible())
	{
		return false;
	}
	
	// Use the real ball position if we have it.  Otherwise, assum the middle of the field.
    Geometry2d::Point ballPos(0, Constants::Field::Length / 2);
    if (ball().valid)
    {
		ballPos = ball().pos;
    }

	switch (gameState().state)
    {
        case GameState::Setup:
            robot()->move(Geometry2d::Point(0,Constants::Field::Length / 2 - 0.3));
			robot()->face(ballPos);
            break;

        case GameState::Ready:
			robot()->move(ballPos + Geometry2d::Point(0, 0.1));
            robot()->face(ballPos);
			robot()->kick(255);
            break;

        default:
            break;
    }
	
	return gameState().state != GameState::Playing;
}
