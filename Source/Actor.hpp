#ifndef _NIMA_ACTOR_HPP_
#define _NIMA_ACTOR_HPP_

#include "ActorNode.hpp"
#include "ActorImage.hpp"
#include "BlockReader.hpp"
#include "Solver.hpp"
#include "Animation/ActorAnimation.hpp"

namespace nima
{
	enum class BlockType
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

	class Actor
	{
		public:
			Actor();
			virtual ~Actor();

		private:
			int m_NodeCount;
			ActorNode** m_Nodes;
			ActorNode* m_Root;
			void readNodesBlock(BlockReader* block);
			void readAnimationsBlock(BlockReader* block);

		protected:
			int m_MaxTextureIndex;
			int m_ImageNodeCount;
			int m_SolverNodeCount;
			int m_AnimationsCount;

			ActorImage** m_ImageNodes;
			Solver** m_Solvers;
			ActorAnimation* m_Animations;


		public:
			static Actor* fromBytes(unsigned char* bytes, unsigned int length);
			static Actor* fromFile(const char* filename);

			ActorNode* getNode(unsigned int index) const;
			ActorNode* getNode(unsigned short index) const;
			ActorAnimation* getAnimation(const std::string& name) const;

			void copy(const Actor& actor);
	};
}
#endif