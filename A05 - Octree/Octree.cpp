#include "Octree.h"
//using namespace Simplex;
//Octree()
//Simplex


Simplex::uint Simplex::OctreeNode::m_uOctreeNodeCount = 0; 
Simplex::uint Simplex::OctreeNode::m_uMaxLevel = 0;
Simplex::uint Simplex::OctreeNode::m_uIdealEntityCount = 0;

Simplex::OctreeNode::OctreeNode(uint a_nMaxLevel, uint a_nIdealEntityCount) // the root Octree
{
	// get the instance for both of the singletons 
	m_pEntityMngr = MyEntityManager::GetInstance();
	m_pMeshMngr = MeshManager::GetInstance();
	m_nodeID = 0;
	
	for (int i = 0; i < m_pEntityMngr->GetEntityCount(); i++)
	{
		MyRigidBody* entity = m_pEntityMngr->GetEntity(i)->GetRigidBody();
		m_EntityList.push_back(i);
		vector3 maxGlobal = entity->GetMaxGlobal();
		vector3 minGlobal = entity->GetMinGlobal();
		
		//checks for the max xyz of all the entities 
		if (maxGlobal.x> m_v3Max.x){
			m_v3Max = vector3(maxGlobal.x);

		}
		if (maxGlobal.y > m_v3Max.y) {
			m_v3Max = vector3(maxGlobal.y);
			
		}
		if (maxGlobal.z > m_v3Max.z) {
			m_v3Max = vector3(maxGlobal.z);
		}
		
		// checks for the min of all the entities
		if (minGlobal.x < m_v3Min.x) {
			m_v3Min = vector3(minGlobal.x);
		}
		if (minGlobal.y < m_v3Min.y) {
			m_v3Min = vector3(minGlobal.y);
		}
		if (minGlobal.z < m_v3Min.z) {
			m_v3Min = vector3(minGlobal.z);
		}
	}
	// the size of my cube for display use
	meshSize = (m_v3Max.x - m_v3Min.x);

	m_v3Center = (m_v3Max + m_v3Min) / 2.0f;

	m_uMaxLevel = a_nMaxLevel;
	m_uIdealEntityCount = a_nIdealEntityCount;
	m_uOctreeNodeCount = 1;
	m_pRoot = this;
	m_pEntityMngr->ClearDimensionSetAll();

	m_nodes.push_back(this);
	// time to set stuff up for the children 
	SplitOctreeNode();

}

//child constructor 
Simplex::OctreeNode::OctreeNode(vector3 a_v3Center, vector3 a_v3Min, vector3 a_v3Max , OctreeNode* parentNode) // children constuctor
{
	// SET the node id 
	m_nodeID = m_uOctreeNodeCount;
	m_uOctreeNodeCount += 1;

	// singletons instances 
	m_pEntityMngr = MyEntityManager::GetInstance();
	m_pMeshMngr = MeshManager::GetInstance();

	m_pParent = parentNode;
	// need to update my level and attach to parent 
	level = m_pParent->level + 1;

	m_v3Center = a_v3Center;
	m_v3Max = a_v3Max;
	m_v3Min = a_v3Min;
	m_pRoot = m_pParent->m_pRoot;

	// has to happe after the previous line 
	m_pRoot->m_nodes.push_back(this);

	// the size of my cube for display use
	meshSize = (m_v3Max.x - m_v3Min.x);

	PopEntityList(m_pParent->m_EntityList);
	SplitOctreeNode();
}

Simplex::OctreeNode::~OctreeNode(void)
{
	for (size_t i = 0; i < 8; i++)
	{
		delete m_pChild[i];
		m_pChild[i] = nullptr;
	}
	m_pEntityMngr = nullptr;
	m_pMeshMngr = nullptr;
}

bool Simplex::OctreeNode::IsColliding(uint a_uRBIndex)
{
	MyRigidBody* entity = m_pEntityMngr->GetEntity(a_uRBIndex)->GetRigidBody();
	vector3 entityVecMin = entity->GetMinGlobal();
	vector3 entityVecMax = entity->GetMaxGlobal();

	// x axis test 
	if (this->m_v3Max.x < entityVecMin.x) //this to the right of other
		return false;
	if (this->m_v3Min.x > entityVecMax.x) //this to the left of other
		return false;

	// y axis test
	if (this->m_v3Max.y < entityVecMin.y) //this below of other
		return false;
	if (this->m_v3Min.y > entityVecMax.y) //this above of other
		return false;

	// z axis test
	if (this->m_v3Max.z < entityVecMin.z) //this behind of other
		return false;
	if (this->m_v3Min.z > entityVecMax.z) //this in front of other
		return false;

	// the the if statements fail 
	return true;
}

// display of the individual octreenodes
void Simplex::OctreeNode::Display(uint a_nIndex, vector3 a_v3Color)
{
	if (-1== a_nIndex)
	{
		// display only on the root
		m_pRoot->Display(a_v3Color);
	}
	else 
	{
		// uses the node list to display
		m_nodes[a_nIndex]->Display(a_v3Color);
	}
}

// the overall display that displays all 
void Simplex::OctreeNode::Display(vector3 a_v3Color)
{
	m_pMeshMngr->AddWireCubeToRenderList(glm::translate(glm::mat4(), m_v3Center) * glm::scale(vector3(meshSize)), a_v3Color);
	if (m_uChildren > 0) 
	{
		for (size_t i = 0; i < 8; i++)
		{
			m_pChild[i]->Display();
		}
	}
}

void Simplex::OctreeNode::SplitOctreeNode()
{
	if (level != m_uMaxLevel && m_EntityList.size() > m_uIdealEntityCount)// this tells us if we can split 
	{
		m_uChildren = 8; 

		// do all the calculations for the 8 children 
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
		std::vector<std::vector<std::vector<glm::vec3>>> myVariable = vector3(m_v3Max.x, midpoints.y, m_v3Max.z);
		newMax = vector3(m_v3Max.x, midpoints.y, m_v3Max.z);
		newMin = vector3(midpoints.x, m_v3Min.y, midpoints.z);
		m_pChild[6] = new OctreeNode((newMax + newMin) / 2, newMin, newMax, this);

		// back bottom left octant 
		newMax = vector3(midpoints.x, midpoints.y, m_v3Max.z);
		newMin = vector3(m_v3Min.x, m_v3Min.y, midpoints.z);
		m_pChild[7] = new OctreeNode((newMax + newMin) / 2, newMin, newMax, this);
	}
	else 
	{
		if (m_pRoot != nullptr)
		{
			m_pRoot->m_lChild.push_back(this);
		}
	}

}

// add to the entity list based on a collision if that is the case 
void Simplex::OctreeNode::PopEntityList(std::vector<uint> a_Entities)
{

	for (size_t i = 0; i < a_Entities.size(); i++)
	{
		if (IsColliding(a_Entities[i]))
		{
			MyEntity* entity = m_pEntityMngr->GetEntity(a_Entities[i]);
			m_EntityList.push_back(a_Entities[i]);

		}
	}
}

// just return this var for my controls 
Simplex::uint Simplex::OctreeNode::GetOctantCount()
{
	return m_uOctreeNodeCount;
}

std::vector<Simplex::OctreeNode*> Simplex::OctreeNode::GetLeaves()
{
	return m_pRoot->m_lChild;
}

std::vector<Simplex::uint> Simplex::OctreeNode::GetEntityList()
{
	return m_EntityList;
}

// checcks collision based on the entitys of the leave 
void Simplex::OctreeNode::CollisionCheck()
{
	if (this!=m_pRoot)
	{
		return;
	}
	for (uint i = 0; i < m_pEntityMngr->GetEntityCount(); i++)
	{
		m_pEntityMngr->GetEntity(i)->ClearCollisionList();
	}
	for (size_t i = 0; i < m_lChild.size(); i++)
	{
		std::vector<uint> leavesEnts = m_lChild[i]->GetEntityList();
		for (size_t j = 0; j < leavesEnts.size(); j++)
		{
			for (size_t k = 0; k < leavesEnts.size(); k++)
			{
				if (j==k) 
				{
					continue;
				}
				m_pEntityMngr->GetEntity(leavesEnts[j])->IsColliding(m_pEntityMngr->GetEntity(leavesEnts[k])); // checks for collision 
			}
		}
	}
}


