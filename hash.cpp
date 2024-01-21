// CPP program to implement hashing with chaining
#include<iostream>
#include<sstream>
#include "hash.hpp"
using namespace std;

HashTable::HashTable()
{
	//initalize the hash table size to M which is a global variable, numCollision to zero and a new table of XUser with nullptr
	tableSize = M;
	numCollision = 0;

	table = new XUser*[tableSize];
	for(int i = 0; i < tableSize; i++){
		table[i] = nullptr;
	}
}

XUser* HashTable::createUser(string username, string userBio)
{
	//intializer for the create users intialzing a BST to contain the potential posts
	XUser *temp = new XUser;
	temp->username = username;
	temp->userBio = userBio;
	temp->postCount = 0;
	temp->next = nullptr;
	temp->bst = new BST();
	return temp;
}

unsigned int HashTable::hashFunction(string username)
{
	unsigned int hash_value = 0;
	//add up the values of the string and set it to the hash value
	for(int i = 0; i < username.size(); i++){
		hash_value += username[i];
	}
	//take the hash_value and mod it by table size
	hash_value = hash_value%tableSize;
	//return the new hash value
	return hash_value;
}


//function to insert a new user into hash table (posts inserted separately)
XUser* HashTable::insertUser(string username, string userBio)
{
	unsigned int hash_val = 0;
	XUser* temp = nullptr;
	//call searchUser and as long as it nullptr the User doesn't exist in the hash table yet
	if(searchUser(username) == nullptr){
		//use createUser to initalize an XUSER with given value and find the hashvalue assoicated to it
		temp = createUser(username, userBio);
		hash_val = hashFunction(username);
		//insert the new XUSER to the front of the linkedlisted of the table to resolve the collision and iterate the numCOllisions
		temp->next = table[hash_val];
		table[hash_val] = temp;
		numCollision++;
		return temp;
	}
	else{
		//if the user exists return nullptr
		return nullptr;
	}
}

XUser* HashTable::searchUser(string username)
{
	//find where the username should be in the has table
	unsigned int hash_val = hashFunction(username);
	XUser* curr = table[hash_val];
	//if there are values at the location in the hash table traverse the linked list at that table index
	if(curr != nullptr){
		while(curr != nullptr){
			//if the given username equals the username in the hashtable return the pointer, otherwise itterate till it is found or you have traversed the linked list at the index
			if(curr->username == username){
				return curr;
			}
			else{
				curr = curr->next;
			}
		}
	}
	//otherwise return nullptr
	return nullptr;
}

void HashTable::printUsers()
{
	XUser *curr = nullptr;
	//traverse the whole has table
	for(int i = 0; i < tableSize; i++){
		cout << i << "|";
		curr = table[i];
		//if there is a linkedlist at a given index traverse the linked list
		while(curr != nullptr){
			cout << curr->username << "-->";
			curr = curr->next;
		}
		cout << "NULL" << endl;
	}
}

void HashTable::printAllPostByUser(string username) 
{
	//get the table index associated with the username and set a new XUSER to the pointer to the index at that point in the table
	XUser *curr = table[hashFunction(username)];
	//if there are no users at the index return the user doesn't exist
	if(curr == nullptr){
		cout << "User does not exit, try again..." << endl;
		return;
	}
	//traverse the linked list till the username is found or it is fully travered
	while(curr->username != username){
		//if the linkedlist is fully traversed return the user wasn't found
		if(curr->next == nullptr){
			cout << "User does not exit, try again..." << endl;
			return;
		}
		else{
			curr = curr->next;
		}
	}
	//output all the posts by the given user in the format given
	cout << curr->username << ":" << endl;
	cout << "| userBio: " << curr->userBio << endl;
	cout << "| postCount: " << curr->postCount << endl;
	cout << "| Posts:" << endl; 
	curr->bst->displayPosts();
}

void HashTable::printMostLikedPost() 
{
	XUser *curr = nullptr;
	XUser *most_liked_user = nullptr;
	XPost *most_liked_post = new XPost;
	most_liked_post->likes = 0;
	//traverse the entire table
	for(int i = 0; i < tableSize; i++){
		curr = table[i];
		while(curr != nullptr){
			//call the mostPopular function on the bst and compare the likes of the current to the likes of the stored most liked post
			if(curr->bst->mostPopular()->likes > most_liked_post->likes){
				//if the current has most likes set the most_liked post to the current_mostpopular XPost and most_liked user to the current user pointer
				most_liked_post = curr->bst->mostPopular();
				most_liked_user = curr;
			}
			curr = curr->next;
		}
	}
	//output the information of the most liked user and most
	cout << most_liked_user->username << ":" << endl;
	cout << "| userBio: " << most_liked_user->userBio << endl;
	cout << "| postCount: " << most_liked_user->postCount << endl;
	cout << "| Posts:" << endl; 
	cout << most_liked_post->postedTime << ":" << endl;
	cout << "__| likes: " << most_liked_post->likes << endl;
	cout << "__| " << most_liked_post->xContents << endl;
}

int HashTable::longestChain() 
{
	int longest = 0;
	int temp = 0;
	XUser *curr = nullptr;
	//traverse the entire tree
	for(int i = 0; i < tableSize; i++){
		//reinitalize temp variable very time you go to a new table index
		curr = table[i];
		temp = 0;
		//if there is a linked list traverse the linked list and every look iterate the temp variable
		while(curr != nullptr){
			curr = curr->next;
			temp++;
		}
		//compare the temp to the longest and if it is longer set longest equal to temp
		if(temp > longest){
			longest = temp;
		}
	}
	return longest;
}
    
