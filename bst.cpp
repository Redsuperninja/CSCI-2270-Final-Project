#include "bst.hpp"

BST::BST() {
	//initalize the bst
	root = nullptr;
	size = 0;
}

void destroy(XPost* curr){
	//a recursive function called to destruct the BST
    if(curr != nullptr){
		//goes through the left tree, then right tree, then finally deletes root node
        destroy(curr->left);
        destroy(curr->right);
        delete curr;
    }
}

BST::~BST() {
	//uses above recussive function to traverse the tree to destruct it
	destroy(root);
    root = nullptr;
}

XPost* BST::createPost(float time, string content, int likes) 
{
	//initializes a new XPost struct and returns the XPost 
	XPost* temp = new XPost;
	temp->postedTime = time;
	temp->xContents = content;
	temp->likes = likes;
	temp->left = nullptr;
	temp->right = nullptr;
	return temp;
}

void BST::insertPost(float time, string content, int likes) 
{
	//assigns a new Post by using the create Post function;
	XPost* new_pst = createPost(time,content,likes);
	//calls the insertHelper and returns the modified tree to the root
	root = insertHelper(root, new_pst);
}

XPost* BST::insertHelper(XPost* rt, XPost* pst) 
{
	//if the tree is empty point the root to the new post
	if(!rt){
		return pst;
	}
	//else check if the new post is less or greater than the root posted time and if so go left or right to maintain the bst
	if(rt->postedTime > pst->postedTime){
		rt->left = insertHelper(rt->left, pst);
	}
	else if(rt->postedTime < pst->postedTime){
		rt->right = insertHelper(rt->right, pst);
	}
	return rt;
}

void BST::displayPosts() 
{
	//call the dispplay post recursive helper
	displayHelper(root);
}

void BST::displayHelper(XPost* rt) // Inorder Traversal
{
	//if the root exists call the helper on the left side of the tree, return the post info, and call recurisevly on the right side
	if(rt){
		displayHelper(rt->left);
		cout << rt->postedTime << ":" << endl;
		cout << "__| likes: " << rt->likes << endl;
		cout << "__| " << rt->xContents << endl;
		displayHelper(rt->right);
	}
}

XPost* BST::mostPopular() 
{
	//set the most popular to root, call the most Popular Helper revusive and return the modified most popular XPost pointer
	XPost* most_popular = root;
	mostPopularHelper(root, most_popular);
	return most_popular;
}

void BST::mostPopularHelper(XPost* rt, XPost*& mostLiked) 
{
	//if the root exists
	if(rt){
		//check if the root has more like and if so reassign the mostliked post to the current root
		if(rt->likes > mostLiked->likes){
			mostLiked = rt;
		}
		//traverse throught the tree using the most popular helper
		mostPopularHelper(rt->left, mostLiked);
		mostPopularHelper(rt->right, mostLiked);
	}
}
