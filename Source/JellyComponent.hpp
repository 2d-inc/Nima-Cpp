#ifndef _NIMA_JELLYCOMPONENT_HPP_
#define _NIMA_JELLYCOMPONENT_HPP_

#include "ActorComponent.hpp"
#include "nima/Vec2D.hpp"
#include <vector>
#include <cmath>

namespace nima
{
	class Actor;
	class BlockReader;
    class ActorJellyBone;

	class JellyComponent : public ActorComponent
	{
		typedef ActorComponent Base;

        public:
            static constexpr int JellyMax = 16;
            static const float OptimalDistance;
            static const float CurveConstant;

        private:
            float m_EaseIn;
            float m_EaseOut;
            float m_ScaleIn;
            float m_ScaleOut;
            unsigned short m_InTargetIdx;
            unsigned short m_OutTargetIdx;
            ActorNode* m_InTarget;
            ActorNode* m_OutTarget;
            std::vector<ActorJellyBone*> m_Bones;
            Vec2D m_InPoint;
            Vec2D m_InDirection;
            Vec2D m_OutPoint;
            Vec2D m_OutDirection;

            Vec2D m_CachedTip;
            Vec2D m_CachedOut;
            Vec2D m_CachedIn;
            float m_CachedScaleIn;
            float m_CachedScaleOut;

            Vec2D m_JellyPoints[JellyMax+1];
            std::vector<Vec2D> m_NormalizedCurvePoints;

		public:
			JellyComponent();
			ActorComponent* makeInstance(Actor* resetActor) override;
			void copy(JellyComponent* node, Actor* resetActor);
			static JellyComponent* read(Actor* actor, BlockReader* reader, JellyComponent* node = nullptr);
			void resolveComponentIndices(ActorComponent** components) override;
			void completeResolve() override;
			void updateJellies();
            void update(unsigned char dirt) override;
	};
}
#endif