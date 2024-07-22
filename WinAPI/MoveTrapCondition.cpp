#include "pch.h"
#include "MoveTrapCondition.h"

#include "CTimeMgr.h"
#include "CTrap.h"

MoveTrapCondition::MoveTrapCondition(float distance, float speed)
	: moveDistance(distance) , speed(speed)
{
}

void MoveTrapCondition::ActiveTrap()
{
	currentMoveDistance += speed * DT;

	Vec2 pos = owner->GetPos();

	if (isUp) {
		pos.y -= speed * DT;
	}
	else {
		pos.y += speed * DT;
	}

	if (currentMoveDistance >= moveDistance) {
		isUp = !isUp;
		currentMoveDistance = 0.f;
	}

	owner->SetPos(pos);
}
