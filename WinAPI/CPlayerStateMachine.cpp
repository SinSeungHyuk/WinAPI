#include "pch.h"
#include "CPlayerStateMachine.h"

#include "CPlayerIdleState.h"
#include "CPlayerMoveState.h"


CPlayerStateMachine::CPlayerStateMachine()
	: CStateMachine()
{
	AddStates();
	//SetLayer();
}

CPlayerStateMachine::~CPlayerStateMachine()
{
}

void CPlayerStateMachine::AddStates()
{
	AddState(L"IdleState", new CPlayerIdleState, (int)StateMachineLayer::MovementLayer);
	AddState(L"MoveState", new CPlayerMoveState, (int)StateMachineLayer::MovementLayer);
}
