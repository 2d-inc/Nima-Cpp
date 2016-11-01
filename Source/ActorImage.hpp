#ifndef _NIMA_ACTORIMAGE_HPP_
#define _NIMA_ACTORIMAGE_HPP_

#include "ActorNode.hpp"

namespace nima
{
	class Actor;
	class BlockReader;
	class ActorNode;

	enum BlendModes
	{
		Normal = 0,
		Multiply = 1,
		Screen = 2,
		Additive = 3
	};

	class ActorImage : public ActorNode
	{
		private:
			int m_DrawOrder;
			BlendModes m_BlendMode;
			int m_TextureIndex;
			float* m_Vertices;
			unsigned short* m_Triangles;
			int m_VertexCount;
			int m_TriangleCount;
			float* m_AnimationDeformedVertices;
			bool m_IsVertexDeformDirty;

			struct BoneConnection
			{
				unsigned short boneIndex;
				ActorNode* node;
				Mat2D bind;
				Mat2D ibind;
			};

			BoneConnection* m_BoneConnections;

		public:
			ActorImage();
			ActorNode* makeInstance(Actor* resetActor);
			void copy(ActorImage* node, Actor* resetActor);

			static ActorImage* read(Actor* actor, BlockReader* reader, ActorImage* node = NULL);
	};
}
#endif