#pragma once

class MovementConfig
{
public:
	inline static FString IdleMovementStateName = FString("IdleMovementState");
	inline static FString PullUpStateName = FString("PullUpState");
	inline static FString DashStateName = FString("DashState");
	inline static FString ClimbStateName = FString("ClimbState");

	
	inline static FString ClimbableSurfaceTag = FString("Climbable");
};
