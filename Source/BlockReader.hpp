#ifndef _NIMA_BLOCKREADER_HPP_
#define _NIMA_BLOCKREADER_HPP_

#include <string>
#include "BinaryReader.hpp"

namespace nima
{

	class BlockReader : public BinaryReader
	{
		public:
			enum BlockTypes
			{
				Unknown = 0,
				Nodes = 1,
				ActorNode = 2,
				ActorBone = 3,
				ActorRootBone = 4,
				ActorImage = 5,
				View = 6,
				Animation = 7,
				Animations = 8,
				Atlases = 9,
				Atlas = 10,
				ActorIKTarget = 11
			};
		private:
			BlockTypes m_BlockType;

		public:
			BlockReader(unsigned char* data, unsigned int length);
			BlockReader(BlockTypes type, unsigned char* data, unsigned int length);
			BlockReader* readNextBlock();

			BlockTypes blockType() { return m_BlockType; }
	};
}
#endif