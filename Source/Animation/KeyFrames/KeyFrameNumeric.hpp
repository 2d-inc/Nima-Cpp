#ifndef _NIMA_KEYFRAMENUMERIC_HPP_
#define _NIMA_KEYFRAMENUMERIC_HPP_

#include "KeyFrameWithInterpolation.hpp"

namespace nima
{
	class BlockReader;
	class ActorNode;

	class KeyFrameNumeric : public KeyFrameWithInterpolation
	{
		typedef KeyFrameWithInterpolation Base;
		private:
			float m_Value;

		public:
			KeyFrameNumeric();
			float value() const;

			bool read(BlockReader* reader, ActorComponent* component) override;
			void apply(ActorComponent* component, float mix) override;
			void applyInterpolation(ActorComponent* component, float time, KeyFrame* toFrame, float mix) override;
			
		protected:
			virtual void setValue(ActorComponent* component, float value, float mix) = 0;
	};
}

#endif