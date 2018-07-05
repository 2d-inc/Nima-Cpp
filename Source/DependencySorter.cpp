#include "DependencySorter.hpp"

using namespace nima;


void DependencySorter::sort(ActorComponent* root, std::vector<ActorComponent*>& order)
{
    order.clear();
    visit(root, order);
}

bool DependencySorter::visit(ActorComponent* component, std::vector<ActorComponent*>& order)
{
    if(m_Perm.find(component) != m_Perm.end())
    {
        return true;
    }
    if(m_Temp.find(component) != m_Temp.end())
    {
        fprintf(stderr, "Dependency cycle!\n");
        return false;
    }

    m_Temp.emplace(component);

    // IList<ActorComponent> dependents = n.m_Dependents;
    // if(dependents != null)
    // {
    //     foreach(ActorComponent d in dependents)
    //     {
    //         if(!visit(d, order))
    //         {
    //             return false;
    //         }
    //     }
    // }
    m_Perm.emplace(component);
    order.insert(order.begin(), component);

    return true;
}
