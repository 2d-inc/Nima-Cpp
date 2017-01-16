#ifndef _NIMA_KEYFRAMEVERTEXDEFORM_HPP_
#define _NIMA_KEYFRAMEVERTEXDEFORM_HPP_

#include "KeyFrameWithInterpolation.hpp"

namespace nima
{
	class ActorNode;

	class KeyFrameVertexDeform : public KeyFrameWithInterpolation
	{
		typedef KeyFrameWithInterpolation Base;
		private:
			float* m_Vertices;
			unsigned int m_VerticesCount;

		public:	
			KeyFrameVertexDeform();
			virtual ~KeyFrameVertexDeform();

			bool read(BlockReader* reader, ActorNode* node) override;
			void apply(ActorNode* node, float mix) override;
			void applyInterpolation(ActorNode* node, float time, KeyFrame* toFrame, float mix) override;
	};
}

#endif