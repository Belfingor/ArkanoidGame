#pragma once
#include <memory>

namespace ArkanoidGame
{
	class Brick;

	class iBrickState
	{
	public:
		virtual ~iBrickState() = default;
		virtual void ApplySingleHitBuff(Brick& brick) = 0;
		virtual void RevertSingleHitBuff(Brick& brick) = 0;
	};

	class NormalBrickState : public iBrickState
	{
	private:
		int singleHitCount = 1;
	public:
		NormalBrickState(int hitCount) {}
		void ApplySingleHitBuff(Brick& brick) override;
		void RevertSingleHitBuff(Brick& brick) override;
	};

	class SingleHitBrickState : public iBrickState
	{
	public:
		SingleHitBrickState(int hitCount) {}
		void ApplySingleHitBuff(Brick& brick) override;
		void RevertSingleHitBuff(Brick& brick) override;
	};
}