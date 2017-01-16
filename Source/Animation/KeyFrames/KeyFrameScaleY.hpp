#ifndef _NIMA_KEYFRAMESCALEY_HPP_
#define _NIMA_KEYFRAMESCALEY_HPP_

#include "KeyFrameNumeric.hpp"

namespace nima
{
	class ActorNode;

	class KeyFrameScaleY : public KeyFrameNumeric
	{
		protected:
			void setValue(ActorNode* node, float value, float mix) override;
	};
}

#endif