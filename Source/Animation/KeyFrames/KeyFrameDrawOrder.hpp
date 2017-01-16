#ifndef _NIMA_KEYFRAMEDRAWORDER_HPP_
#define _NIMA_KEYFRAMEDRAWORDER_HPP_

#include "KeyFrame.hpp"

namespace nima
{
	class ActorNode;

	class KeyFrameDrawOrder : public KeyFrame
	{
		typedef KeyFrame Base;
		private:
			struct DrawOrderIndex
			{
				unsigned short nodeIdx;
				unsigned short order;
			};
			DrawOrderIndex* m_OrderedNodes;
			int m_OrderedNodesCount;

		public:	
			KeyFrameDrawOrder();
			virtual ~KeyFrameDrawOrder();

			bool read(BlockReader* reader, ActorNode* node) override;
			void setNext(KeyFrame* frame) override;
			void apply(ActorNode* node, float mix) override;
			void applyInterpolation(ActorNode* node, float time, KeyFrame* toFrame, float mix) override;
	};
}

#endif