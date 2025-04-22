#include "iBrickState.h"
#include "Brick.h"

namespace ArkanoidGame
{
	void NormalBrickState::ApplySingleHitBuff(Brick& brick)
	{
		brick.SetHitCount(singleHitCount);
		brick.SetState(std::make_unique<SingleHitBrickState>(singleHitCount));
	}
	void NormalBrickState::RevertSingleHitBuff(Brick& brick)
	{
		// Normal State should not revert anything
	}
	//-----------------------------------------------------------------------------
	void SingleHitBrickState::ApplySingleHitBuff(Brick& brick)
	{
		// Buff State should not apply anything
	}
	void SingleHitBrickState::RevertSingleHitBuff(Brick& brick)
	{
		brick.SetHitCount(brick.GetOriginalHitCount());
		brick.SetState(std::make_unique<NormalBrickState>(brick.GetOriginalHitCount()));
	}
}