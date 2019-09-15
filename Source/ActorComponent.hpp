#ifndef _NIMA_ACTORCOMPONENT_HPP_
#define _NIMA_ACTORCOMPONENT_HPP_

#include <Mat2D.hpp>
#include <Vec2D.hpp>

#include <string>
#include <vector>

namespace nima
{
	class Actor;
	class ActorNode;
	class BlockReader;
	class CustomIntProperty;
	class CustomFloatProperty;
	class CustomStringProperty;
	class CustomBooleanProperty;

	enum class ComponentType
	{
		ActorNode = 2,
		ActorBone = 3,
		ActorRootBone = 4,
		ActorImage = 5,
		ActorIKTarget = 11,
		ActorEvent = 12,
		CustomIntProperty = 13,
		CustomFloatProperty = 14,
		CustomStringProperty = 15,
		CustomBooleanProperty = 16,
		ColliderRectangle = 17, // TODO
		ColliderTriangle = 18, // TODO
		ColliderCircle = 19, // TODO
		ColliderPolygon = 20, // TODO
		ColliderLine = 21, // TODO
		ActorNodeSolo = 23,
		NestedActorNode = 24,
		ActorStaticMesh = 27,
		JellyComponent = 28,
		ActorJellyBone = 29,
		ActorIKConstraint = 30,
		ActorDistanceConstraint = 31,
		ActorTranslationConstraint = 32,
		ActorRotationConstraint = 33,
		ActorScaleConstraint = 34,
		ActorTransformConstraint = 35
	};


	class ActorComponent
	{
		protected:
			ComponentType m_Type;
			std::string m_Name;
			ActorNode* m_Parent;
			Actor* m_Actor;
			std::vector<CustomIntProperty*> m_CustomIntProperties;
			std::vector<CustomFloatProperty*> m_CustomFloatProperties;
			std::vector<CustomStringProperty*> m_CustomStringProperties;
			std::vector<CustomBooleanProperty*> m_CustomBooleanProperties;
			std::vector<ActorComponent*> m_Dependents;

		public:
			// Used by the DAG in Actor.
			unsigned int m_GraphOrder;
			unsigned char m_DirtMask;

		private:
			unsigned short m_ParentIdx;
			unsigned short m_Idx;
			
		protected:
			ActorComponent(ComponentType type);
			ActorComponent(Actor* actor, ComponentType type);

		public:
			virtual ~ActorComponent();
			Actor* actor() const;
			const std::string& name() const;
			ComponentType type() const;

			ActorNode* parent() const;
			unsigned short parentIdx() const;
			unsigned short idx() const;
			virtual void resolveComponentIndices(ActorComponent** components);
			virtual void completeResolve();
			virtual ActorComponent* makeInstance(Actor* resetActor) = 0;
			void copy(ActorComponent* node, Actor* resetActor);
			virtual bool isNode() { return false; }

			static ActorComponent* read(Actor* actor, BlockReader* reader, ActorComponent* component = NULL);

			void addCustomIntProperty(CustomIntProperty* property);
			void addCustomFloatProperty(CustomFloatProperty* property);
			void addCustomStringProperty(CustomStringProperty* property);
			void addCustomBooleanProperty(CustomBooleanProperty* property);

			CustomIntProperty* getCustomIntProperty(const std::string& name);
			CustomFloatProperty* getCustomFloatProperty(const std::string& name);
			CustomStringProperty* getCustomStringProperty(const std::string& name);
			CustomBooleanProperty* getCustomBooleanProperty(const std::string& name);
			std::vector<ActorComponent*>& dependents() { return m_Dependents; }

			virtual void onDirty(unsigned char dirt){}
			virtual void update(unsigned char dirt){}
	};
}
#endif