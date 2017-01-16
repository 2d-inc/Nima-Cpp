#ifndef _NIMA_KEYFRAMENUMERIC_HPP_
#define _NIMA_KEYFRAMENUMERIC_HPP_

#include "KeyFrameWithInterpolation.hpp"

namespace nima
{
	class BlockReader;
	class ActorNode;

	class KeyFrameNumeric : public KeyFrameWithInterpolation
	{
		private:
			float m_Value;

		public:
			KeyFrameNumeric();
			float value() const;

			bool read(BlockReader* reader) override;
			void apply(ActorNode* node, float mix) override;
			virtual void setValue(ActorNode* node, float value, float mix) = 0;
			void applyInterpolation(ActorNode* node, float time, KeyFrame* toFrame, float mix) override;
	};
}

#endif