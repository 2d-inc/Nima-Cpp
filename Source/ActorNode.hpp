#ifndef _NIMA_ACTORNODE_HPP_
#define _NIMA_ACTORNODE_HPP_

#include <string>
#include <vector>
#include <nima/Mat2D.hpp>

namespace nima
{
	class ActorNode
	{
		protected:
			std::string m_Name;
			ActorNode* m_Parent;
			Actor* m_Actor;
			std::vector<ActorNode*> m_Children;
			std::vector<ActorNode*> m_Dependents;
			Mat2D m_Transform;
			Mat2D m_WorldTransform;
	};
}
#endif