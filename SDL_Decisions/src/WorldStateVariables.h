#pragma once

enum WorldStateVariables {
	AgentAlive = 1,
	AgentArmed = 2,
	WeaponCharged = 4,
	AgentHasBomb = 8,
	EnemyVisible = 16,
	EnemyAligned = 32,
	EnemyNear = 64,
	EnemyAlive = 128,
	BombNearEnemy = 256,
};