// Binary Tree Template

#ifndef BINARYTREE_H
#define BINARYTREE_H
#include <iostream>
using namespace std;

template <class T>
class BinaryTree
{
private:
	struct TreeNode
	{
		T value;
		TreeNode *left;
		TreeNode *right;
	};

	int leafCount;

	TreeNode *root;
	void insert(TreeNode *&, TreeNode *&);
	void destroySubTree(TreeNode *);
	void deleteNode(T, TreeNode *&);
	void makeDeletion(TreeNode *&);
	void displayInOrder(TreeNode *);
	void displayPreOrder(TreeNode *);
	void displayPostOrder(TreeNode *);
	int countNodes(TreeNode *&);
    void countLeaves(TreeNode *);
	int getTreeHeight(TreeNode *);
	int numAtLevel(TreeNode *, int);

public:
	BinaryTree()							// Constructor
		{ root = NULL; }
	~BinaryTree()							// Destructor
		{ destroySubTree(root); }
	void insertNode(T);
	// searchNode has been modified.
	T *searchNode(T);
	void remove(T);
	void displayInOrder()
		{	displayInOrder(root); }
	void displayPreOrder()
		{	displayPreOrder(root); }
	void displayPostOrder()
		{	displayPostOrder(root); }

	int numNodes();
	int numLeafNodes();
	int treeHeight();
	int getWidth();
};

//*************************************************************
// insert accepts a TreeNode pointer and a pointer to a node. *
// The function inserts the node into the tree pointed to by  *
// the TreeNode pointer. This function is called recursively. *
//*************************************************************

template <class T>
void BinaryTree<T>::insert(TreeNode *&nodePtr, TreeNode *&newNode)
{
	if (nodePtr == NULL)
		nodePtr = newNode;						// Insert the node.
	else if (newNode->value < nodePtr->value)
		insert(nodePtr->left, newNode);			// Search the left branch
	else 
		insert(nodePtr->right, newNode);		// Search the right branch
}

//**********************************************************
// insertNode creates a new node to hold num as its value, *
// and passes it to the insert function.                   *
//**********************************************************

template <class T>
void BinaryTree<T>::insertNode(T num)
{
	TreeNode *newNode;		// Pointer to a new node.

	// Create a new node and store num in it.
	newNode = new TreeNode;
	newNode->value = num;
	newNode->left = newNode->right = NULL;
	// Insert the node.
	insert(root, newNode);
}

//***************************************************
// destroySubTree is called by the destructor. It   *
// deletes all nodes in the tree.                   *
//***************************************************

template <class T>
void BinaryTree<T>::destroySubTree(TreeNode *nodePtr)
{
	if (nodePtr)
	{
		if (nodePtr->left)
			destroySubTree(nodePtr->left);
		if (nodePtr->right)
			destroySubTree(nodePtr->right);
		delete nodePtr;
	}
}
	
//***************************************************
// searchNode determines if a value is present in   *
// the tree. If so, the function returns a pointer  *
// to the value member of the node.                 *
// Otherwise, it returns false.                     *
// THIS FUNCTION HAS BEEN MODIFIED FROM THE         *
// PREVIOUS VERSION.                                *
//***************************************************

template <class T>
T *BinaryTree<T>::searchNode(T num)
{
	TreeNode *nodePtr = root;

	while (nodePtr)
	{
		if (nodePtr->value == num)
			return &nodePtr->value;
		else if (num < nodePtr->value)
			nodePtr = nodePtr->left;
		else
			nodePtr = nodePtr->right;
	}
	return NULL;
}

//**********************************************
// remove calls deleteNode to delete the       *
// node whose value member is the same as num. *
//**********************************************

template <class T>
void BinaryTree<T>::remove(T num)
{
	deleteNode(num, root);
}


//********************************************
// deleteNode deletes the node whose value   *
// member is the same as num.                *
//********************************************

template <class T>
void BinaryTree<T>::deleteNode(T num, TreeNode *&nodePtr)
{
	if (num < nodePtr->value)
		deleteNode(num, nodePtr->left);
	else if (num > nodePtr->value)
		deleteNode(num, nodePtr->right);
	else
		makeDeletion(nodePtr);
}


//***********************************************************
// makeDeletion takes a reference to a pointer to the node  *
// that is to be deleted. The node is removed and the       *
// branches of the tree below the node are reattached.      *
//***********************************************************

template <class T>
void BinaryTree<T>::makeDeletion(TreeNode *&nodePtr)
{
	TreeNode *tempNodePtr;	// Temporary pointer, used in reattaching the
	                        // left subtree.

	if (nodePtr == NULL)
		cout << "Cannot delete empty node.\n";
	else if (nodePtr->right == NULL)
	{
		tempNodePtr = nodePtr;
		nodePtr = nodePtr->left;	// Reattach the left child
		delete tempNodePtr;
	}
	else if (nodePtr->left == NULL)
	{
		tempNodePtr = nodePtr;
		nodePtr = nodePtr->right;	// Reattach the right child
		delete tempNodePtr;
	}
	// If the node has two children.
	else
	{
		// Move one node the right.
		tempNodePtr = nodePtr->right;
		// Go to the end left node.
		while (tempNodePtr->left)
			tempNodePtr = tempNodePtr->left;
		// Reattach the left subtree.
		tempNodePtr->left = nodePtr->left;
		tempNodePtr = nodePtr;
		// Reattach the right subtree.
		nodePtr = nodePtr->right;
		delete tempNodePtr;
	}
}

//****************************************************************
// The displayInOrder member function displays the values        *
// in the subtree pointed to by nodePtr, via inorder traversal.  *
//****************************************************************

template <class T>
void BinaryTree<T>::displayInOrder(TreeNode *nodePtr)
{
	if (nodePtr)
	{
		displayInOrder(nodePtr->left);
		cout << nodePtr->value << endl;
		displayInOrder(nodePtr->right);
	}
}

//****************************************************************
// The displayPreOrder member function displays the values       *
// in the subtree pointed to by nodePtr, via preorder traversal. *
//****************************************************************

template <class T>
void BinaryTree<T>::displayPreOrder(TreeNode *nodePtr)
{
	if (nodePtr)
	{
		cout << nodePtr->value << endl;
		displayPreOrder(nodePtr->left);		
		displayPreOrder(nodePtr->right);
	}
}

//****************************************************************
// The displayPostOrder member function displays the values      *
// in the subtree pointed to by nodePtr, via postorder traversal.*
//****************************************************************

template <class T>
void BinaryTree<T>::displayPostOrder(TreeNode *nodePtr)
{
	if (nodePtr)
	{
		displayPostOrder(nodePtr->left);		
		displayPostOrder(nodePtr->right);
		cout << nodePtr->value << endl;
	}
}

//****************************************************************
// The numNodes function returns the number of nodes in the tree.*
//****************************************************************

template <class T>
int BinaryTree<T>::numNodes()
{
	return countNodes(root);
}

//****************************************************************
// The countNodes function uses recursion to count the nodes in  *
// the tree. This function is called by the public member        *
// function numNodes.                                            *
//****************************************************************

template <class T>
int  BinaryTree<T>::countNodes(TreeNode *&nodePtr)
{
	if (nodePtr == NULL)
		return 0;
	else
		return 1 + countNodes(nodePtr->left) + countNodes(nodePtr->right);
}

//******************************************************************
// Function numLeafNodes                                           *
// Calls countLeaves() and displays number of leaf nodes in tree   *
//******************************************************************

template <class T>
int BinaryTree<T>::numLeafNodes()
{
        leafCount = 0;    // reset to 0 each time a count is made
        countLeaves(root);
        return leafCount;
}

//*********************************************************
// Function countLeaves                                   *
// Performs postorder traversal and counts leaf nodes     *
//*********************************************************

template <class T>
void BinaryTree<T>::countLeaves(TreeNode* nodePtr)
{
	if (nodePtr)
	{
		countLeaves(nodePtr->left);                                                             
		countLeaves(nodePtr->right);
		if (nodePtr->left == NULL && nodePtr->right == NULL)
		{
			leafCount++;
		}
	}

}

//*************************************************************
// Function getTreeHeight                                     *
// This function uses recursion to count the height of        *
// the tree.                                                  *
//*************************************************************

template <class T>
int BinaryTree<T>::getTreeHeight(TreeNode* nodePtr)
{
	int leftHeight, rightHeight;

	if (nodePtr)
	{
		leftHeight = getTreeHeight(nodePtr->left);								
		rightHeight = getTreeHeight(nodePtr->right);
		if (leftHeight > rightHeight)
			return leftHeight + 1;
		else
			return rightHeight + 1;
	}
	else
	{
		return 0;
	}
}

//*************************************************************
// Function TreeHeight                                        *
// Calls getTreeHeight and displays height of tree.           *     
//*************************************************************

template <class T>
int BinaryTree<T>::treeHeight()
{
	return getTreeHeight(root);
}

//*********************************************************************
// numAtLevel is a private recursive function that counts the         *
// number of nodes at a specific level in the tree. The value         *
// passed into the level parameter indicates the level of the         *
// tree the function is to count the number of nodes in.              *
//*********************************************************************

template <class T>
int BinaryTree<T>::numAtLevel(TreeNode *nodePtr, int level)
{
	level--;

	// Have we reached the desired level?
	if (level == 0)
	{
		if (nodePtr)	// Is this a node?
			return 1;
		else
			return 0;
	}

	// Have we run out of nodes before reaching
	// the desired level?
	else if (!nodePtr)
	{
		return 0;
	}
	
	// If we haven't reached the desired level, and we
	// haven't run out of nodes yet, keep going down in
	// the tree. Keep a sum of the number of nodes found
	// at the desired level in both the left and right branches.
	else
	{
		return numAtLevel(nodePtr->left, level) + numAtLevel(nodePtr->right, level);
	}
}

//*********************************************************************
// getWidth calls the private function numAtLevel to determine        *
// the width of each level in the tree. The width of the tree is      *
// the number of nodes in the level with the most nodes. This value   *
// is returned.                                                       *
//*********************************************************************

template <class T>
int BinaryTree<T>::getWidth()
{
	int height = treeHeight();
	int nodes, largest =0;

	// Call numAtLevel for each level in the tree
	// and keep track of the largest number of nodes found.
	for (int x = 1; x <= height; x++)
	{
		nodes = numAtLevel(root, x);
		largest = nodes > largest ? nodes : largest; 
	}
	// Return the largest number of nodes found at any level.
	return largest;
}

#endif