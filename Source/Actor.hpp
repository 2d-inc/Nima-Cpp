#ifndef _NIMA_ACTOR_HPP_
#define _NIMA_ACTOR_HPP_

#include "ActorNode.hpp"
#include "ActorImage.hpp"
#include "ActorStaticMesh.hpp"
#include "BlockReader.hpp"
#include "Solver.hpp"
#include "Animation/ActorAnimation.hpp"
#include "Animation/ActorAnimationInstance.hpp"

namespace nima
{
	enum class BlockType
	{
		Unknown = 0,
		Components = 1,
		ActorNode = 2,
		ActorBone = 3,
		ActorRootBone = 4,
		ActorImage = 5,
		View = 6,
		Animation = 7,
		Animations = 8,
		Atlases = 9,
		Atlas = 10,
		ActorIKTarget = 11,
		ActorEvent = 12,
		CustomIntProperty = 13,
		CustomFloatProperty = 14,
		CustomStringProperty = 15,
		ActorStaticMesh = 22
	};

	class Actor
	{
		friend class ActorAnimationInstance;
		public:
			Actor();
			virtual ~Actor();

			enum Flags
			{
				IsDrawOrderDirty = 1<<0,
				IsVertexDeformDirty = 1<<1,
				IsInstance = 1<<2
			};
		private:
			unsigned short m_Flags;
			int m_ComponentCount;
			int m_NodeCount;
			ActorComponent** m_Components;
			ActorNode** m_Nodes;
			ActorNode* m_Root;
			void* m_EventCallbackUserData;
			ActorAnimationEvent::Callback m_EventCallback;
			void readComponentsBlock(BlockReader* block);
			void readAnimationsBlock(BlockReader* block);
			
		protected:
			int m_MaxTextureIndex;
			int m_ImageNodeCount;
			int m_RenderNodeCount;
			int m_SolverNodeCount;
			int m_AnimationsCount;
			std::string m_BaseFilename;

			ActorImage** m_ImageNodes;
			ActorRenderNode** m_RenderNodes;
			Solver** m_Solvers;
			ActorAnimation* m_Animations;

			virtual ActorImage* makeImageNode();
			virtual ActorStaticMesh* makeStaticMeshNode();
			virtual void dispose();
			virtual void updateVertexDeform(ActorImage* image) {};

		public:
			void load(unsigned char* bytes, unsigned int length);
			void load(const std::string& filename);
			void setFilename(const std::string& filename);

			ActorComponent* component(unsigned int index) const;
			ActorComponent* component(unsigned short index) const;
			ActorComponent* component(const std::string& name) const;

			void eventCallback(ActorAnimationEvent::Callback callback, void* userdata = nullptr);
			
			template<typename T>
			T component(const std::string& name) const
			{
				return dynamic_cast<T>(component(name));
			}

			ActorNode* root() const;
			ActorAnimation* animation(const std::string& name) const;
			ActorAnimationInstance* animationInstance(const std::string& name);

			void copy(const Actor& actor);
			const int textureCount() const;
			const std::string& baseFilename() const;
			virtual void advance(float elapsedSeconds);
			void markDrawOrderDirty();
	};
}
#endif