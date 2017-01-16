#ifndef _NIMA_KEYFRAMEPOSX_HPP_
#define _NIMA_KEYFRAMEPOSX_HPP_

#include "KeyFrameNumeric.hpp"

namespace nima
{
	class ActorNode;

	class KeyFramePosX : public KeyFrameNumeric
	{
		protected:
			void setValue(ActorNode* node, float value, float mix) override;
	};
}

#endif