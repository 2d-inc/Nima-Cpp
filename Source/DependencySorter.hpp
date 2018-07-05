#ifndef _NIMA_DEPENDENCYSORTER_HPP_
#define _NIMA_DEPENDENCYSORTER_HPP_

#include "ActorComponent.hpp"
#include <unordered_set>
#include <vector>

namespace nima
{
    class DependencySorter
    {
        private:
            std::unordered_set<ActorComponent*> m_Perm;
            std::unordered_set<ActorComponent*> m_Temp;
        public:
            void sort(ActorComponent* root, std::vector<ActorComponent*>& order);
            bool visit(ActorComponent* component, std::vector<ActorComponent*>& order);
    };
}

#endif