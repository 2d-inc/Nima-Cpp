#ifndef _NIMA_PROPERTYANIMATION_HPP_
#define _NIMA_PROPERTYANIMATION_HPP_

#include <string>

namespace nima
{
	class BlockReader;
	class ActorNode;

	class PropertyAnimation
	{
		private:
			enum PropertyTypes
			{
				Unknown = 0,
				PosX = 1,
				PosY = 2,
				ScaleX = 3,
				ScaleY = 4,
				Rotation = 5,
				Opacity = 6,
				DrawOrder = 7,
				Length = 8,
				VertexDeform = 9,
				IKStrength = 10
			};

			PropertyTypes m_Type;
			// KeyFrame** m_KeyFrames;
			// int m_KeyFramesCount;

		public:

			PropertyAnimation();
			~PropertyAnimation();
			void read(BlockReader* reader, ActorNode* node);

	};
}
#endif