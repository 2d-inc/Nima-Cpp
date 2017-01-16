#ifndef _NIMA_KEYFRAME_HPP_
#define _NIMA_KEYFRAME_HPP_

namespace nima
{
	class BlockReader;
	class ActorNode;

	enum class InterpolationType
	{
		Hold = 0,
		Linear = 1,
		Mirrored = 2,
		Asymmetric = 3,
		Disconnected = 4,
		Progression = 5,
		Max
	};

	class KeyFrame
	{
		public:

		protected:
			float m_Time;

		public:
			KeyFrame();
			virtual ~KeyFrame();
			
			float time() const;

			virtual bool read(BlockReader* reader, ActorNode* node);
			virtual void setNext(KeyFrame* frame) = 0;
			virtual void apply(ActorNode* node, float mix) = 0;
			virtual void applyInterpolation(ActorNode* node, float time, KeyFrame* toFrame, float mix) = 0;
	};
}

#endif