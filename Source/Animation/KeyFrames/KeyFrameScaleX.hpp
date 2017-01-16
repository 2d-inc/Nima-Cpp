#ifndef _NIMA_KEYFRAMESCALEX_HPP_
#define _NIMA_KEYFRAMESCALEX_HPP_

#include "KeyFrameNumeric.hpp"

namespace nima
{
	class ActorNode;

	class KeyFrameScaleX : public KeyFrameNumeric
	{
		protected:
			void setValue(ActorNode* node, float value, float mix) override;
	};
}

#endif