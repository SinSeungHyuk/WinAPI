#include "pch.h"
#include "TimerTrapCondition.h"

#include "CTimeMgr.h"
#include "CTrap.h"
#include "CLogMgr.h"

void TimerTrapCondition::ActiveTrap()
{
	timer += DT;

	if (timer > 2.f) {
		timer = 0.f;
		owner->IsTrapActive(isActive);
		isActive = !isActive;
	}
}
