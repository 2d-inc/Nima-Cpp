#ifndef _NIMA_KEYFRAMEIKSTRENGTH_HPP_
#define _NIMA_KEYFRAMEIKSTRENGTH_HPP_

#include "KeyFrameNumeric.hpp"

namespace nima
{
	class ActorNode;

	class KeyFrameIKStrength : public KeyFrameNumeric
	{
		protected:
			void setValue(ActorNode* node, float value, float mix) override;
	};
}

#endif