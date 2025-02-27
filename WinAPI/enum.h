#pragma once


enum class PEN_TYPE
{
	RED,
	GREEN,
	BLUE,
	YELLOW,
	MAGENTA,	
	END,
};


enum class BRUSH_TYPE
{
	RED,
	BLUE,
	GREEN,
	GRAY,
	TURQUOISE,
	HOLLOW,	
	END,
};

enum class LEVEL_TYPE
{
	START,
	STAGE_01,
	STAGE_02,
	STAGE_03,
	EDITOR,
	END,
};


enum class LAYER_TYPE
{
	DEFAULT,
	BACKGROUND,
	TILE,
	PLATFORM,
	PLAYER,
	PLAYER_PROJECTILE,
	TRAP,
	MONSTER,
	MONSTER_PROJECTILE,
	ITEM,


	UI = 31,
	END = 32,
};


enum class TASK_TYPE
{
	CREATE_OBJECT, // Param0 : Object Adress, Param1 : LayerType
	DELETE_OBJECT, // Param0 : Object Adress
	CHANGE_LEVEL,  // Param0 : LEVEL_TYPE
};


enum class COMPONENT_TYPE
{
	COLLIDER,
	ANIMATOR,
	RIGIDBODY,
	TILEMAP,
	STATE_MACHINE,
};

enum class DEBUG_SHAPE
{
	RECT,
	CIRCLE,
	CROSS,
	LINE,
};

enum class LOG_LEVEL
{
	LOG,
	WARNING,
	BUG,
};

enum class OVERLAP_TYPE {
	IS_COLLISION_UP,
	IS_COLLISION_DOWN,
	IS_COLLISION_LEFT,
	IS_COLLISION_RIGHT
};

enum class ANIMATION_TYPE {
	IDLE,
	MOVEMENT,
	ATTACK,
	DEAD,
};

enum class StateMachineLayer {
	MovementLayer,
	DetectLayer,
	AttackLayer,
};