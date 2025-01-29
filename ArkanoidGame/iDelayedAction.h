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

		virtual void UpdateTimer(float timeDelta)
		{
			if(!isTimerStarted_) return;
			currentTime_ -= timeDelta;
			EachTickAction(timeDelta);
			if(currentTime_ <= 0.f)
			{
				FinalAction();
				currentTime_ = 0.f;
			}
		}

		virtual void EachTickAction(float timeDelta) = 0;
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