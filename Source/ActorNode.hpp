#ifndef _NIMA_ACTORNODE_HPP_
#define _NIMA_ACTORNODE_HPP_

#include <string>
#include <vector>
#include <nima/Mat2D.hpp>
#include <nima/Vec2D.hpp>

namespace nima
{
	class Actor;
	class BlockReader;

	struct Node
	{
		enum Type
		{
			ActorNode = 2,
			ActorBone = 3,
			ActorRootBone = 4,
			ActorImage = 5,
			ActorIKTarget = 11
		};
	};

	class ActorNode
	{
		public:

		protected:
			Node::Type m_Type;
			std::string m_Name;
			ActorNode* m_Parent;
			Actor* m_Actor;
			std::vector<ActorNode*> m_Children;
			std::vector<ActorNode*> m_Dependents;
			Mat2D m_Transform;
			Mat2D m_WorldTransform;
			Vec2D m_Translation;
			float m_Rotation;
			Vec2D m_Scale;
			float m_Opacity;
			float m_RenderOpacity;

		private:
			unsigned short m_ParentIdx;
			unsigned short m_Idx;
			bool m_IsDirty;
			bool m_IsWorldDirty;
			bool m_SuppressMarkDirty;
			bool m_OverrideWorldTransform;
			bool m_OverrideRotation;
			float m_OverrideRotationValue;

		protected:
			ActorNode(Node::Type type);
		private:
			ActorNode(Actor* actor, Node::Type type);
		public:
			ActorNode(Actor* actor);
			ActorNode();
			virtual ~ActorNode();
			bool suppressMarkDirty() const;
			void suppressMarkDirty(bool suppress); 
			bool isWorldDirty() const;
			bool isDirty() const;
			Actor* actor() const;
			const std::string& name() const;
			const Mat2D& transform();
			const Mat2D& worldTransform();
			void overrideWorldTransform(const Mat2D& transform);
			void clearWorldTransformOverride();
			Node::Type type() const;

			float x() const;
			void x(float v);
			float y() const;
			void y(float v);
			float scaleX() const;
			void scaleX(float v);
			float scaleY() const;
			void scaleY(float v);
			float rotation() const;
			void rotation(float v);
			float opacity() const;
			void opacity(float v);
			float renderOpacity() const;
			ActorNode* parent() const;
			unsigned short parentIdx() const;
			unsigned short idx() const;
			void markDirty();
			void markWorldDirty();
			void addDependent(ActorNode* node);
			void removeDependent(ActorNode* node);
			void worldTranslation(Vec2D& result);
			Vec2D worldTranslation();
			void setRotationOverride(float v);
			void clearRotationOverride();
			float overrideRotationValue() const;
			void updateTransform();
			void updateTransforms();
			void updateWorldTransform();
			void addChild(ActorNode* node);
			void removeChild(ActorNode* node);
			virtual void resolveNodeIndices(ActorNode** nodes);
			virtual ActorNode* makeInstance(Actor* resetActor);
			void copy(ActorNode* node, Actor* resetActor);

			static ActorNode* read(Actor* actor, BlockReader* reader, ActorNode* node = NULL);
	};
}
#endif