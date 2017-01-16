#ifndef _NIMA_KEYFRAMEPOSY_HPP_
#define _NIMA_KEYFRAMEPOSY_HPP_

#include "KeyFrameNumeric.hpp"

namespace nima
{
	class ActorNode;

	class KeyFramePosY : public KeyFrameNumeric
	{
		protected:
			void setValue(ActorNode* node, float value, float mix) override;
	};
}

#endif