#ifndef _NIMA_ACTOR_HPP_
#define _NIMA_ACTOR_HPP_

#include "ActorNode.hpp"
#include "BlockReader.hpp"

namespace nima
{
	class Actor
	{
		public:
			Actor();
			~Actor();

		private:
			int m_NodeCount;
			ActorNode** m_Nodes;
			ActorNode* m_Root;
			void readNodesBlock(BlockReader* block);

		public:
			static Actor* fromBytes(unsigned char* bytes, unsigned int length);
			static Actor* fromFile(const char* filename);
	};
}
#endif