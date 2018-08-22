#ifndef _NIMA_ACTORNODE_HPP_
#define _NIMA_ACTORNODE_HPP_

#include <vector>
#include <nima/Mat2D.hpp>
#include <nima/Vec2D.hpp>
#include "ActorComponent.hpp"
#include "ActorConstraint.hpp"

namespace nima
{
	class Actor;
	class BlockReader;

	class ActorNode : public ActorComponent
	{
		typedef ActorComponent Base;
		protected:
			std::vector<ActorNode*> m_Children;
			std::vector<ActorConstraint*> m_Constraints;
			Mat2D m_Transform;
			Mat2D m_WorldTransform;
			Vec2D m_Translation;
			float m_Rotation;
			Vec2D m_Scale;
			float m_Opacity;
			float m_RenderOpacity;

		protected:
			bool m_OverrideWorldTransform;
			bool m_IsCollapsedVisibility;
			bool m_RenderCollapsed;

		protected:
			ActorNode(ComponentType type);
		private:
			ActorNode(Actor* actor, ComponentType type);
		public:
			ActorNode(Actor* actor);
			ActorNode();
			virtual ~ActorNode();
			const Mat2D& transform();
			const Mat2D& worldTransform();
			Mat2D& mutableTransform();
			Mat2D& mutableWorldTransform();
			void overrideWorldTransform(const Mat2D& transform);
			void clearWorldTransformOverride();

			static const unsigned char TransformDirty = 1<<0;
			static const unsigned char WorldTransformDirty = 1<<1;

			const Vec2D& translation() const;
			void translation(const Vec2D& v);
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
			bool collapsedVisibility() const;
			void collapsedVisibility(bool v);
			bool renderCollapsed() const;
			void markTransformDirty();
			void worldTranslation(Vec2D& result);
			Vec2D worldTranslation();
			void updateTransform();
			virtual void updateWorldTransform();
			void addChild(ActorNode* node);
			void removeChild(ActorNode* node);
			void resolveComponentIndices(ActorComponent** components) override;
			ActorComponent* makeInstance(Actor* resetActor) override;
			void copy(ActorNode* node, Actor* resetActor);
			bool isNode() override { return true; }

			static ActorNode* read(Actor* actor, BlockReader* reader, ActorNode* node = nullptr);

			bool addConstraint(ActorConstraint* constraint);
			void update(unsigned char dirt) override;

			const std::vector<ActorNode*>& children() const { return m_Children; }
	};
}
#endif