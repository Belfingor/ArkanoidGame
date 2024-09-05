#pragma once
#include <SFML/Graphics.hpp>
#include <memory>

namespace ArkanoidGame
{
	class iDelayedAction
	{
	protected:
		bool isTimerStarted_ = false;
		float destroyTime_ = 0.f;
		float currentTime_ = 0.f;

		virtual void UpdateTimer(float deltaTime)
		{
			if(!isTimerStarted_)
				return;
			currentTime_ -= deltaTime;
			EachTickAction(deltaTime);
			if(currentTime_ <= 0.f)
			{
				FinalAction();
				currentTime_ = 0.f;
			}
		}

		virtual void EachTickAction(float deltaTime) = 0;
		virtual void FinalAction() = 0;
	public:
		void StartTimer(float destroyTime)
		{
			destroyTime_ = destroyTime;
			currentTime_ = destroyTime;
			isTimerStarted_ = true;
		}
	
	};
}