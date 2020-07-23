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

		OctreeNode* m_pParent = nullptr;// Will store the parent of current OctreeNode
		OctreeNode* m_pChild[8];//Will store the children of the current OctreeNode
		MyEntityManager* m_pEntityMngr = nullptr; //Entity Manager Singleton

		std::vector<uint> m_EntityList; //List of Entities under this OctreeNode (Index in Entity Manager)

		OctreeNode* m_pRoot = nullptr;//Root OctreeNode
		std::vector<OctreeNode*> m_lChild; //list of nodes that contain objects (this will be applied to root only)

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

		// split function 

		// find the cube of all the entities first //DONE\\

		// split into 8 Octants based on the cube //DONE\\

		// if collision is happening then split into 8 more children based on if there was entity collision //DONE\\

		// If there is a collision against the parents collidied entities 

		// stores the collisions that are in your area in a new list of collisions 

		// make it a recursive function so the same code runs over and over but the coords should change based on world position //DONE\\

		// determine if there is more than 3 entities in that octant then repeat until there is 3 or less entities in the octant //DONE\\

		// If there is no entities in the branch at all then kill the octant 
		
		// after about 4 splits is the max fps I should be getting 
	};
}


//sing namespace Simplex;
//System Class

//class OctreeNode
//{
	//typedef unsigned int uint;
	//static uint m_uOctreeNodeCount; //will store the number of OctreeNodes instantiated
	//static uint m_uMaxLevel;//will store the maximum level an OctreeNode can go to
	//static uint m_uIdealEntityCount; //will tell how many ideal Entities this object will contain
	//
	//uint m_uID = 0; //Will store the current ID for this OctreeNode
	//uint m_uLevel = 0; //Will store the current level of the OctreeNode
	//uint m_uChildren = 0;// Number of children on the OctreeNode (either 0 or 8)

	//vector3 m_v3Center = vector3(0.0f); //stores the center point of the OctreeNode
	//vector3 m_v3Min = vector3(0.0f); //stores the minimum vector of the OctreeNode
	//vector3 m_v3Max = vector3(0.0f); //stores the maximum vector of the OctreeNode
	//
	//float m_fSize = 0.0f; //Size of the OctreeNode
	//
	//OctreeNode* m_pParent = nullptr;// Will store the parent of current OctreeNode
	//OctreeNode* m_pChild[8];//Will store the children of the current OctreeNode
	//MyEntityManager* m_pEntityMngr = nullptr; //Entity Manager Singleton

	//MeshManager* m_pMeshMngr = nullptr;//Mesh Manager singleton


	//vector3 m_v3Center = vector3(0.0f); //stores the center point of the OctreeNode
	//vector3 m_v3Min = vector3(0.0f); //stores the minimum vector of the OctreeNode
	//vector3 m_v3Max = vector3(0.0f); //stores the maximum vector of the OctreeNode



	//std::vector<uint> m_EntityList; //List of Entities under this OctreeNode (Index in Entity Manager)
	//
	//OctreeNode* m_pRoot = nullptr;//Root OctreeNode
	//std::vector<OctreeNode*> m_lChild; //list of nodes that contain objects (this will be applied to root only)

//public:
	/*
	USAGE: Constructor, will create an OctreeNode containing all MagnaEntities Instances in the Mesh
	manager	currently contains
	ARGUMENTS:
	- uint a_nMaxLevel = 2 -> Sets the maximum level of subdivision
	- uint nIdealEntityCount = 5 -> Sets the ideal level of objects per OctreeNode
	OUTPUT: class object
	*/
	//OctreeNode(uint a_nMaxLevel = 2, uint a_nIdealEntityCount = 5);
	/*
	USAGE: Constructor
	ARGUMENTS:
	- vector3 a_v3Center -> Center of the OctreeNode in global space
	- float a_fSize -> size of each side of the OctreeNode volume
	OUTPUT: class object
	*/
	//OctreeNode(vector3 a_v3Center, float a_fSize);
	/*
	USAGE: Copy Constructor
	ARGUMENTS: class object to copy
	OUTPUT: class object instance
	*/
	//OctreeNode(OctreeNode const& other);
	/*
	USAGE: Copy Assignment Operator
	ARGUMENTS: class object to copy
	OUTPUT: ---
	*/
	//OctreeNode& operator=(OctreeNode const& other);
	/*
	USAGE: Destructor
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	//~OctreeNode(void);
	/*
	USAGE: Changes object contents for other object's
	ARGUMENTS:
	- OctreeNode& other -> object to swap content from
	OUTPUT: ---
	*/
	//void Swap(OctreeNode& other);
	/*
	USAGE: Gets this OctreeNode's size
	ARGUMENTS: ---
	OUTPUT: size of OctreeNode
	*/
	//float GetSize(void);
	/*
	USAGE: Gets the center of the OctreeNode in global scape
	ARGUMENTS: ---
	OUTPUT: Center of the OctreeNode in global space
	*/
	//vector3 GetCenterGlobal(void);
	/*
	USAGE: Gets the min corner of the OctreeNode in global space
	ARGUMENTS: ---
	OUTPUT: Minimum in global space
	*/
	//vector3 GetMinGlobal(void);
	/*
	USAGE: Gets the max corner of the OctreeNode in global space
	ARGUMENTS: ---
	OUTPUT: Maximum in global space
	*/
	//vector3 GetMaxGlobal(void);

	/*
	USAGE: Displays the OctreeNode volume specified by index including the objects underneath
	ARGUMENTS:
	- uint a_nIndex -> OctreeNode to be displayed.
	- vector3 a_v3Color = REYELLOW -> Color of the volume to display.
	OUTPUT: ---
	*/
	//void Display(uint a_nIndex, vector3 a_v3Color = C_YELLOW);
	/*
	USAGE: Displays the OctreeNode volume in the color specified
	ARGUMENTS:
	- vector3 a_v3Color = REYELLOW -> Color of the volume to display.
	OUTPUT: ---
	*/
	//void Display(vector3 a_v3Color = C_YELLOW);
	/*
	USAGE: Displays the non empty leafs in the octree
	ARGUMENTS:
	- vector3 a_v3Color = REYELLOW -> Color of the volume to display.
	OUTPUT: ---
	*/
	//void DisplayLeafs(vector3 a_v3Color = C_YELLOW);
	/*
	USAGE: Clears the Entity list for each node
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	//void ClearEntityList(void);
	/*
	USAGE: allocates 8 smaller OctreeNodes in the child pointers
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	//void Subdivide(void);
	/*
	USAGE: returns the child specified in the index
	ARGUMENTS: uint a_nChild -> index of the child (from 0 to 7)
	OUTPUT: OctreeNode object (child in index)
	*/
	//OctreeNode* GetChild(uint a_nChild);
	/*
	USAGE: returns the parent of the OctreeNode
	ARGUMENTS: ---
	OUTPUT: OctreeNode object (parent)
	*/
	//OctreeNode* GetParent(void);
	/*
	USAGE: Asks the OctreeNode if it does not contain any children (its a leaf)
	ARGUMENTS: ---
	OUTPUT: It contains no children
	*/
	//bool IsLeaf(void);
	/*
	USAGE: Asks the OctreeNode if it contains more than this many Bounding Objects
	ARGUMENTS:
	- uint a_nEntities -> Number of Entities to query
	OUTPUT: It contains at least this many Entities
	*/
	//bool ContainsMoreThan(uint a_nEntities);
	/*
	USAGE: Deletes all children and the children of their children (almost sounds apocalyptic)
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	//void KillBranches(void);
	/*
	USAGE: Creates a tree using subdivisions, the max number of objects and levels
	ARGUMENTS:
	- uint a_nMaxLevel = 3 -> Sets the maximum level of the tree while constructing it
	OUTPUT: ---
	*/
	//void ConstructTree(uint a_nMaxLevel = 3);
	/*
	USAGE: Traverse the tree up to the leafs and sets the objects in them to the index
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	//void AssignIDtoEntity(void);

	/*
	USAGE: Gets the total number of OctreeNodes in the world
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	///uint GetOctreeNodeCount(void);

//private:
	/*
	USAGE: Deallocates member fields
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	//void Release(void);
	/*
	USAGE: Allocates member fields
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	//void Init(void);
	/*
	USAGE: creates the list of all leafs that contains objects.
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	//void ConstructList(void);
//};//class

