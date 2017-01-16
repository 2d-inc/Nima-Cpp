#ifndef _NIMA_KEYFRAMEROTATION_HPP_
#define _NIMA_KEYFRAMEROTATION_HPP_

#include "KeyFrameNumeric.hpp"

namespace nima
{
	class ActorNode;

	class KeyFrameRotation : public KeyFrameNumeric
	{
		protected:
			void setValue(ActorNode* node, float value, float mix) override;
	};
}

#endif