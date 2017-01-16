#ifndef _NIMA_KEYFRAMELENGTH_HPP_
#define _NIMA_KEYFRAMELENGTH_HPP_

#include "KeyFrameNumeric.hpp"

namespace nima
{
	class ActorNode;

	class KeyFrameLength : public KeyFrameNumeric
	{
		protected:
			void setValue(ActorNode* node, float value, float mix) override;
	};
}

#endif