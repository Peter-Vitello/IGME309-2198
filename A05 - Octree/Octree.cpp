#include "Octree.h"
//using namespace Simplex;
//Octree()
//Simplex

Simplex::OctreeNode::OctreeNode(uint a_nMaxLevel, uint a_nIdealEntityCount) // the root Octree
{
	m_pEntityMngr = MyEntityManager::GetInstance();
	for (int i = 0; i < m_pEntityMngr->GetEntityCount(); i++)
	{
		MyRigidBody* entity = m_pEntityMngr->GetEntity(i)->GetRigidBody();
		m_EntityList.push_back(i);
		vector3 maxGlobal = entity->GetMaxGlobal();
		vector3 minGlobal = entity->GetMinGlobal();
		
		//checks for the max xyz of all the entities 
		if (maxGlobal.x> m_v3Max.x){
			m_v3Max.x = maxGlobal.x;
		}
		if (maxGlobal.y > m_v3Max.y) {
			m_v3Max.y = maxGlobal.y;
		}
		if (maxGlobal.z > m_v3Max.z) {
			m_v3Max.z = maxGlobal.z;
		}
		
		// checks for the min of all the entities
		if (minGlobal.x < m_v3Min.x) {
			m_v3Min.x = minGlobal.x;
		}
		if (minGlobal.y < m_v3Min.y) {
			m_v3Min.y = minGlobal.y;
		}
		if (minGlobal.z < m_v3Min.z) {
			m_v3Min.z = minGlobal.z;
		}
	}
	m_v3Center = (m_v3Max - m_v3Min) / 2;

	m_uMaxLevel = a_nMaxLevel;
	m_uIdealEntityCount = a_nIdealEntityCount;
	m_uOctreeNodeCount = 1;
	m_pRoot = this;

	// time to set stuff up for the children 

	SplitOctreeNode();

}

Simplex::OctreeNode::OctreeNode(vector3 a_v3Center, vector3 a_v3Min, vector3 a_v3Max , OctreeNode* parentNode) // children constuctor
{
	// need to update my level and attach to parent 
	m_pParent = parentNode;
	level = m_pParent->level + 1;
	m_v3Center = a_v3Center;
	m_v3Max = a_v3Max;
	m_v3Min = a_v3Min;
	SplitOctreeNode();
}

void Simplex::OctreeNode::SplitOctreeNode()
{
	if (level != m_uMaxLevel && m_EntityList.size() > m_uIdealEntityCount)// this tells us if we can split 
	{
		m_uChildren = 8; 

		vector3 midpoints = (m_v3Max + m_v3Min) / 2;

		// front top right octant DONE
		vector3 newMax = vector3(m_v3Max.x, m_v3Max.y, midpoints.z);
		vector3 newMin = vector3(midpoints.x, midpoints.y, m_v3Min.z); 
		m_pChild[0] = new OctreeNode((newMax + newMin) / 2, newMin, newMax, this); 

		// back top right octant DONE
		//newMax = vector3(m_v3Max.x, m_v3Max.y, midpoints.z);
		//newMin = vector3(midpoints, midpoints, m_v3Min.z);
		m_pChild[1] = new OctreeNode((m_v3Max + midpoints) / 2, midpoints, m_v3Max, this);
		
		// back top left octant DONE
		newMax = vector3(midpoints.x, m_v3Max.y, m_v3Max.z);
		newMin = vector3(m_v3Min.x, midpoints.y, midpoints.z);
		m_pChild[2] = new OctreeNode((newMax + newMin) / 2, newMin, newMax, this);

		// front top left octant DONE
		newMax = vector3(midpoints.x, m_v3Max.y, midpoints.z);
		newMin = vector3(m_v3Min.x, midpoints.y, m_v3Min.z);
		m_pChild[3] = new OctreeNode((newMax + newMin) / 2, newMin, newMax, this);
		
		// front bottom right octant DONE
		newMax = vector3(m_v3Max.x, midpoints.y, midpoints.z);
		newMin = vector3(midpoints.x, m_v3Min.y, m_v3Min.z);
		m_pChild[4] = new OctreeNode((newMax + newMin) / 2, newMin, newMax, this);

		// front bottm left octant DONE
		//newMax = vector3(midpoints.x, midpoints.y, midpoints.z);
		//newMin = vector3(m_v3Min.x, m_v3Min.y, m_v3Min.z);
		m_pChild[5] = new OctreeNode((midpoints + m_v3Min) / 2, m_v3Min, midpoints, this);

		// back bottom right octant DONE
		newMax = vector3(m_v3Max.x, midpoints.y, m_v3Max.z);
		newMin = vector3(midpoints.x, m_v3Min.y, midpoints.z);
		m_pChild[6] = new OctreeNode((newMax + newMin) / 2, newMin, newMax, this);

		// back bottom left octant 
		newMax = vector3(midpoints.x, midpoints.y, m_v3Max.z);
		newMin = vector3(m_v3Min.x, m_v3Min.y, midpoints.z);
		m_pChild[7] = new OctreeNode((newMax + newMin) / 2, newMin, newMax, this);
	}
}
