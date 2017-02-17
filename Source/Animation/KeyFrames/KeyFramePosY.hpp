#ifndef _NIMA_KEYFRAMEPOSY_HPP_
#define _NIMA_KEYFRAMEPOSY_HPP_

#include "KeyFrameNumeric.hpp"

namespace nima
{
	class ActorComponent;

	class KeyFramePosY : public KeyFrameNumeric
	{
		protected:
			void setValue(ActorComponent* component, float value, float mix) override;
	};
}

#endif