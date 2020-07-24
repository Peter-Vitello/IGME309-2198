#pragma once

#include <vector>
#include "MyEntityManager.h"

namespace Simplex
{
	class OctreeNode
	{
		static uint m_uOctreeNodeCount; //will store the number of OctreeNodes instantiated
		static uint m_uMaxLevel;//will store the maximum level an OctreeNode can go to
		static uint m_uIdealEntityCount; //will tell how many ideal Entities this object will contain
		
		vector3 m_v3Center = vector3(0.0f); //stores the center point of the OctreeNode
		vector3 m_v3Min = vector3(2000000000000000000000000000.0f); //stores the minimum vector of the OctreeNode
		vector3 m_v3Max = vector3(-2000000000000000000000000000.0f); //stores the maximum vector of the OctreeNode
		
		uint m_uChildren = 0;// Number of children on the OctreeNode (either 0 or 8)

		int level = 0; // level of octants present

		uint m_nodeID; 

		OctreeNode* m_pParent = nullptr;// Will store the parent of current OctreeNode
		OctreeNode* m_pChild[8];//Will store the children of the current OctreeNode

		// singletons 
		MyEntityManager* m_pEntityMngr = nullptr; //Entity Manager Singleton
		MeshManager* m_pMeshMngr = nullptr;//Mesh Manager singleton
		float meshSize;

		std::vector<uint> m_EntityList; //List of Entities under this OctreeNode (Index in Entity Manager)

		OctreeNode* m_pRoot = nullptr;//Root OctreeNode
		std::vector<OctreeNode*> m_lChild; //list of nodes that contain objects (this will be applied to root only)

		std::vector<OctreeNode*> m_nodes; //list of nodes that contain objects (this will be applied to root only)

	private:


	public:
		OctreeNode(uint a_nMaxLevel = 2, uint a_nIdealEntityCount = 5);
		/*
		USAGE: Constructor
		ARGUMENTS:
		- vector3 a_v3Center -> Center of the OctreeNode in global space
		- float a_fSize -> size of each side of the OctreeNode volume
		OUTPUT: class object
		*/
		OctreeNode(vector3 a_v3Center, vector3 a_v3Min, vector3 a_v3Max, OctreeNode* parentNode);
		/*
		USAGE: Copy Constructor
		ARGUMENTS: class object to copy
		OUTPUT: class object instance
		*/
		OctreeNode(OctreeNode const& other);
		/*
		USAGE: Copy Assignment Operator
		ARGUMENTS: class object to copy
		OUTPUT: ---
		*/
		OctreeNode& operator=(OctreeNode const& other);
		/*
		USAGE: Destructor
		ARGUMENTS: ---
		OUTPUT: ---
		*/
		~OctreeNode(void);
		/*
		USAGE: Asks if there is a collision with the Entity specified by index from the Bounding Object Manager
		ARGUMENTS:
		- int a_uRBIndex -> Index of the Entity in the Entity Manager
		OUTPUT: check of the collision
		*/
		bool IsColliding(uint a_uRBIndex);
		//Octree(uint OctreeNodeLevels, uint maxSub); //construct octree
		//Model* model;
		//void Display(uint octreeID); //display octree


		//||||||||||||||||STUFF ADDED AFTER PSUDO CODE||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||

		/*
		USAGE: Gets the center of the OctreeNode in global scape
		ARGUMENTS: ---
		OUTPUT: Center of the OctreeNode in global space
		*/
		vector3 GetCenterGlobal(void);
		/*
		USAGE: Gets the min corner of the OctreeNode in global space
		ARGUMENTS: ---
		OUTPUT: Minimum in global space
		*/
		vector3 GetMinGlobal(void);
		/*
		USAGE: Gets the max corner of the OctreeNode in global space
		ARGUMENTS: ---
		OUTPUT: Maximum in global space
		*/
		vector3 GetMaxGlobal(void);

		/*
		USAGE: Displays the OctreeNode volume specified by index including the objects underneath
		ARGUMENTS:
		- uint a_nIndex -> OctreeNode to be displayed.
		- vector3 a_v3Color = REYELLOW -> Color of the volume to display.
		OUTPUT: ---
		*/
		void Display(uint a_nIndex, vector3 a_v3Color = C_YELLOW);
		/*
		USAGE: Displays the OctreeNode volume in the color specified
		ARGUMENTS:
		- vector3 a_v3Color = REYELLOW -> Color of the volume to display.
		OUTPUT: ---
		*/
		void Display(vector3 a_v3Color = C_YELLOW);

		/*
		USAGE: Displays the non empty leafs in the octree
		ARGUMENTS:
		- vector3 a_v3Color = REYELLOW -> Color of the volume to display.
		OUTPUT: ---
		*/
		void DisplayLeafs(vector3 a_v3Color = C_YELLOW);


		void SplitOctreeNode();
		
		void PopEntityList(std::vector<uint> a_Entities);

		uint GetOctantCount();

		std::vector<OctreeNode*> GetLeaves();
		std::vector<uint> GetEntityList();

		void CollisionCheck();

		
		//bool IsLeaf(void);

		// split function 

		// find the cube of all the entities first //DONE\\

		// split into 8 Octants based on the cube //DONE\\

		// if collision is happening then split into 8 more children based on if there was entity collision //DONE\\

		// If there is a collision against the parents collidied entities ??DONE??

		// stores the collisions that are in your area in a new list of collisions //DONE\\ 

		// make it a recursive function so the same code runs over and over but the coords should change based on world position //DONE\\

		// determine if there is more than 3 entities in that octant then repeat until there is 3 or less entities in the octant //DONE\\

		// If there is no entities in the branch at all then kill the octant 

		// draw the octants to the screen and 
		
		// after about 4 splits is the max fps I should be getting 
	};
}
