#pragma once

#include "ChocoGL/Core/Core.h"
#include "ChocoGL/Core/Timestep.h"

#include <string>

#include "ChocoGL/Scene/Components.h"
#include "ChocoGL/Scene/Entity.h"

extern "C" {
	typedef struct _MonoObject MonoObject;
	typedef struct _MonoClassField MonoClassField;
}

namespace ChocoGL {

	enum class FieldType
	{
		None = 0, Float, Int, UnsignedInt, String, Vec2, Vec3, Vec4
	};

	struct EntityInstance;

	struct PublicField
	{
		std::string Name;
		FieldType Type;

		PublicField(const std::string& name, FieldType type)
			: Name(name), Type(type) {}

		template<typename T> 
		T GetValue() const
		{
			T value;
			GetValue_Internal(&value);
			return value;
		}

		template<typename T>
		void SetValue(T value) const
		{
			SetValue_Internal(&value);
		}
	private:
		EntityInstance* m_EntityInstance;
		MonoClassField* m_MonoClassField;

		void SetValue_Internal(void* value) const;
		void GetValue_Internal(void* outValue) const;

		friend class ScriptEngine;
	};

	using ScriptModuleFieldMap = std::unordered_map<std::string, std::vector<PublicField>>;

	class ScriptEngine
	{
	public:
		static void Init(const std::string& assemblyPath);
		static void Shutdown();

		static void OnCreateEntity(Entity entity);
		static void OnUpdateEntity(uint32_t entityID, Timestep ts);

		static void OnInitEntity(ScriptComponent& script, uint32_t entityID, uint32_t sceneID);

		static const ScriptModuleFieldMap& GetFieldMap();
	};

}