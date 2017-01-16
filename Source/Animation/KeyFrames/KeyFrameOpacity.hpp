#ifndef _NIMA_KEYFRAMEOPACITY_HPP_
#define _NIMA_KEYFRAMEOPACITY_HPP_

#include "KeyFrameNumeric.hpp"

namespace nima
{
	class ActorNode;

	class KeyFrameOpacity : public KeyFrameNumeric
	{
		protected:
			void setValue(ActorNode* node, float value, float mix) override;
	};
}

#endif