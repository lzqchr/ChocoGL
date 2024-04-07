#pragma once

#include "ChocoGL/Core/Core.h"
#include "ChocoGL/Scene/Components.h"

#include <PhysX/PxPhysicsAPI.h>

namespace ChocoGL {

	enum class ForceMode : uint16_t
	{
		Force = 0,
		Impulse,
		VelocityChange,
		Acceleration
	};

	enum class FilterGroup : uint32_t
	{
		Static = BIT(0),
		Dynamic = BIT(1),
		Kinematic = BIT(2),
		All = Static | Dynamic | Kinematic
	};

	class Physics3D
	{
	public:
		static void Init();
		static void Shutdown();

		static physx::PxSceneDesc CreateSceneDesc();
		static physx::PxScene* CreateScene(const physx::PxSceneDesc& sceneDesc);
		static physx::PxRigidActor* CreateAndAddActor(physx::PxScene* scene, const RigidBodyComponent& rigidbody, const glm::mat4& transform);
		static physx::PxMaterial* CreateMaterial(float staticFriction, float dynamicFriction, float restitution);

		static physx::PxTransform CreatePose(const glm::mat4& transform);

		static void SetCollisionFilters(physx::PxRigidActor* actor, uint32_t filterGroup, uint32_t filterMask);

	private:
		static physx::PxDefaultErrorCallback s_PXErrorCallback;
		static physx::PxDefaultAllocator s_PXAllocator;
		static physx::PxFoundation* s_PXFoundation;
		static physx::PxPhysics* s_PXPhysicsFactory;
		static physx::PxPvd* s_PXPvd;

	};

}