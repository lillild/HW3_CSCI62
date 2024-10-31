#include "network.h"
#include <iostream>
#include <string>


//Defalt constructor 
//pre:
//post: create default values for each
Network::Network(){}

//Destructor 
Network::~Network(){
	for(size_t i = 0; i < users_.size(); i++){
		if(users_[i] != nullptr){
			delete users_[i];
			users_[i] = nullptr;
		}
	}
}


//pre: takes in an ID
//post: returns a pointer to the corresponding User
//		if user not found return nullptr
User* Network::getUser(int id){ 
	for (auto user : users_) { 
        if (user->getId() == id) {         //call whats pointed to
            return user;                   //return the pointer
        }
   	}
    return nullptr;  
}


//pre: takes a string into the [firstname][lastname]
//post:return the id for that user
//	   return -1 if no user exists
int Network::getId(std::string name){ 
	for (auto user : users_) { 
        if (user->getName() == name) {         //call whats pointed to
            return user->getId();                      //user
        }
   	}
    return -1;  
}




//pre: takes in a pinter to a new User object
//post: adds the User to Network database
void Network::addUser(User* newUser){ 
	users_.push_back(newUser);
}



//pre: takes two strings [firstname] [lastname] 
//post: add a connection (addfriend in user??) if it doesnt exist
//      return -1 if either user is invalid
//      and 0 otherwise(else)
int Network::addConnection(std::string s1, std::string s2){ 
	int id1 = getId(s1);                      // Get the ID of users
    int id2 = getId(s2);

    User* user1 = getUser(id1);
    User* user2 = getUser(id2);

	if (user1 && user2) {
    	if (user1->getFriends().find(id2) == user1->getFriends().end()) {  // They are not friends, so add the connection
            user1->addFriend(id2);
            user2->addFriend(id1);
        	return 0;  
		}    
	}
	else{
		return -1;     //either user is invalid
	}
	return 0;          //otherwise
}




//pre: takes two strings [firstname] [lastname]
//post:delete the friend connection if it exists.
//	   Return -1 if either user is invalid 
//	   and 0 otherwise(else)
int Network::deleteConnection(std::string s1, std::string s2){ 
	int id1 = getId(s1);                      // Get the ID of users
    int id2 = getId(s2);

    User* user1 = getUser(id1);
    User* user2 = getUser(id2);

   if (user1 && user2) {     // Check if they are already friends
        if (user1->getFriends().find(id2) != user1->getFriends().end()) {  // They are friends, so delete the connection
            user1->deleteFriend(id2);
            user2->deleteFriend(id1);
            return 0;
        }
    }
    else{ 
 		return -1;		//either user is invalid
    }
    return 0;          //otherwise
}



//pre:
//post:returns the number of Users in the Network
int Network::numUsers(){ 
	return users_.size();
}



//File I/O

//pre: readin a file 
//post:initialized all the liness into user and network
void Network::readUsers(const char* filename){ 
	
	std::ifstream fileIn(filename);
	if(fileIn.fail()){ 
		std::cerr << "Unable To Open " << filename << std::endl;
		return;
	}

	//the first line is how many users 
	std::string myLine;
	int numUsers;

	fileIn >> numUsers;
	fileIn.ignore();

	for(int i = 0; i < numUsers; i++){ 

		int id = 0, year = 0, zip = 0;
		std::string name;
		std::string line;

		std::set<int> friends;

		fileIn >>id;
		fileIn.ignore();

		std::getline(fileIn, name);   
        fileIn.ignore();  

		fileIn >>year;
		fileIn.ignore();


		fileIn >>zip;
		fileIn.ignore();

	    
	    // Read friends' IDs from the line loop throught it 
	    //get the full line first then use filein to seperate each id
        std::getline(fileIn, line);
        std::stringstream each_id(line);
        int friendId;
        while (each_id>> friendId) {
            friends.insert(friendId);
        }

        //  add the user to the network
        User* user = new User(id, name, year, zip, friends);
        addUser(user); 
    }

    fileIn.close();

}


//pre: provided network
//post:export a file
void Network::writeUsers(const char* filename){   
	
	std::ofstream outfile(filename);
    if (!outfile){
     std::cout << "Unable to write to file" << filename << std::endl;
        return;
    }

    outfile << users_.size() << std::endl;  // Write the number of users
    										// in the first line

    for (auto user : users_) {
        outfile << user->getId() << std::endl;
        outfile << user->getName() << std::endl;
        outfile << user->getYear() << std::endl;
        outfile << user->getZip() << std::endl;

        const std::set<int>& friends = user->getFriends();  // Get the user's friends
        if (!friends.empty()) {
            for (auto friendId : friends) {
                outfile << friendId << " ";  // Write each friend ID, separated by space
            }
        } else {
            outfile << "None";  // If the user has no friends, write "None"
        }

        outfile << std::endl;  
    }
    

    outfile.close();
}





//HW2
//pre: take in from(which is the friend to start BFS) and to
//post: return the shortest path to to (the ending friend )
std::vector<int> Network::shortestPath(int from, int to) {
	//first check if the users are valid 
    assert(getUser(from) != nullptr && "Invalid 'from' user ID.");
    assert(getUser(to) != nullptr && "Invalid 'to' user ID.");

    //if it is the same user we return just the from 
    if (from == to) {
        return std::vector<int>{from};
    }

    std::queue<int> q;
    std::vector<bool> visited(users_.size(), false);
    std::vector<int> dist(users_.size(), -1);  // save all distance 
    std::vector<std::vector<int>> paths(users_.size());  // Vector of paths for each user

    dist[from] = 0;
    visited[from] = true;
    q.push(from);

    // Initialize the path from `from`
    paths[from].push_back(from);

    while (!q.empty()) {
        int cur = q.front();
        q.pop();

        const std::set<int>& friends = users_[cur]->getFriends();  //get the friends of the current 

        //loop though all the friends of the current user
        for (int friend_id : friends) {
            if (!visited[friend_id]) {
                dist[friend_id] = dist[cur] + 1;  //if not visited we set the distance to be one more
                visited[friend_id] = true;

                paths[friend_id] = paths[cur]; 
                paths[friend_id].push_back(friend_id);  //adds the friend's id to path

                q.push(friend_id);

                // check if we can end 
                if (friend_id == to) {
                    return paths[friend_id];
                }
            }
        }
    }

    // No path found, return empty vector
    return {};
}



//pre: take in from, to, and distance
//post: if a user exist with the exact distance from from, returns the shortest path to that user 
//		and sets to to the user’s ID. If no such user exists, returns an empty vector and sets 
//		to to -1.
std::vector<int> Network::distanceUser(int from, int& to, int distance){
	//first check if the users are valid 
    assert(getUser(from) != nullptr && "Invalid 'from' user ID.");
	

	std::queue<int> q;
    std::vector<bool> visited(users_.size(), false);
    std::vector<int> dist(users_.size(), -1);  // save all distance 
    std::vector<std::vector<int>> paths(users_.size());  // Vector of paths for each user
    std::vector<int> prev(users_.size(), -1);  //new


    dist[from] = 0;
    visited[from] = true;
    q.push(from);

   // Initialize the path from `from`
    paths[from].push_back(from);

    while (!q.empty()) {
        int cur = q.front();
        q.pop();


		const std::set<int>& friends = users_[cur]->getFriends();  //get the friends of the current 

		//loop though all the friends of the current user
		 for (int friend_id : friends) {
	            if (!visited[friend_id]) {
	                dist[friend_id] = dist[cur] + 1;	//if not visited we set the distance to be one more
	                visited[friend_id] = true;

	                paths[friend_id] = paths[cur];
	                paths[friend_id].push_back(friend_id);	//adds the friend's id to path

	                //new!! If we have found a user with the exact distance
	                if (dist[friend_id] == distance) {
	                    to = friend_id;
	                    return paths[friend_id];  // Return the path directly without reversing
	                }

	                q.push(friend_id);
	            }
	        }
	}
    // If no user was found at the exact distance, return an empty vector and set `to = -1`
	to = -1;
    return {};
}




//pre: take in a who, user id must be valid in network
//post:Returns a list of friend suggestions for the user with the given ID who, 
//		and sets score to the highest number of mutual friends found. 
std::vector<int> Network::suggestFriends(int who, int& score) {
    
    std::vector<int> potentialFriends;  // List of suggested friends
    score = 0;  // Initialize the score to 0

    // Get the user's direct friends
    User* user = getUser(who);
    if (!user) {  //check if valid
        return {};
    }

    const std::set<int>& friends = user->getFriends();  //get the friends of the User


    // Vector to store the mutual friend count for each potential friend
    std::vector<int> mutualFriend(users_.size(), 0);  // Initialize to 0 for all users


    // Loop through the user's direct friends
    for (int friend_id : friends) {
        User* friendUser = getUser(friend_id);
		if (!friendUser) {
    	return {};  
}

        // Get the friends of the friend (i.e., potential friends)
        const std::set<int>& friendsoffriend = friendUser->getFriends();

        // Iterate through the friends of the user's friend (potential friends)
        for (int potentialFriend_id : friendsoffriend) {
            // Check that the potential friend is not the original user and is not already a direct friend
            if (potentialFriend_id != who && friends.find(potentialFriend_id) == friends.end()) {
                // if not score goes up
                mutualFriend[potentialFriend_id]++;

                // switch out current friend if potential friend has more mutual friends 
                if (mutualFriend[potentialFriend_id] > score) {
                    score = mutualFriend[potentialFriend_id];
                }
            }
        }
    }

    // Collect all potential friends who have the highest number of mutual friends
    for (int i = 0; i < users_.size(); i++) {
        if (mutualFriend[i] == score && score > 0) {
            potentialFriends.push_back(i);  // Add potential friends with the highest mutual friend count
        }
    }

    return potentialFriends;  // Return the list of suggested friends
}




//DFS functions 
//pre: cur is a user ID, vector called group, visited
//post: recursion helper
void Network::dfsHelper(int cur, std::vector<int>& group, std::vector<bool>& visited) {
    visited[cur] = true;  // Mark the current user as visited
    group.push_back(cur);  // Add the user to the current group

    const std::set<int>& friends = users_[cur]->getFriends();  // Get the user's friends

    // Recursively visit all unvisited friends
    for (int friend_id : friends) {
        if (!visited[friend_id]) {
            dfsHelper(friend_id, group, visited);
        }
    }
}


// Entry point for DFS, calls disHelper to actually perform the search
	//pre: startuser is a user ID, group, visited
	//post: fill group with all users connecter to 'startUser' mark visited 
void Network::dfs(int startUser, std::vector<int>& group, std::vector<bool>& visited) {
    dfsHelper(startUser, group, visited);  // Call the helper to perform the DFS
}



//pre:
//post:Returns a vector of vectors,  each inner vector who all have paths to one another 
//		but have no edges to all other uses.
std::vector<std::vector<int>> Network::groups() {
    std::vector<std::vector<int>> allConnectedComponents;  // Stores all groups of connected users
    std::vector<bool> visited(users_.size(), false);  

    // Iterate over each user in the network
    for (size_t i = 0; i < users_.size(); i++){
        if (!visited[i]) {  // If the user hasn't been visited yet
            std::vector<int> group;  // Stores the current connected component (group)
            dfs(i, group, visited);  // DFS to find all connected users in this group
            allConnectedComponents.push_back(group);  // Add the group list of all groups
        }
    }

    return allConnectedComponents; 
}





/*
+addPost(ownerId:int, message:string, likes:int,
         isIncoming:bool, authorName:string, isPublic:bool): void
+getPostsString(ownerId:int, howMany:int, showOnlyPublic:bool): string
*/

// Pre: check ownerId 
// Post: Adds a post to the specific user's messages
void Network::addPost(int ownerId, const std::string& message, int likes, bool isIncoming, const std::string& authorName, bool isPublic){
    int messageId = 0;
    for (const User* user : users_) {
        messageId += user->getPosts().size();  // Sum up posts of each user
    }

    // Find the user 
    for (User* user : users_) {
        if (user->getId() == ownerId) {
            Post* newPost;
            if (isIncoming) {
                newPost = new IncomingPost(messageId, ownerId, message, likes, isPublic, authorName);
            } else {
                newPost = new Post(messageId, ownerId, message, likes);
            }
            user->addPost(newPost);
            return;
        }
    }
}





// Pre: check ownerId 
// Post: Returns a  string of posts for the specific user
std::string Network::getPostsString(int ownerId, int howMany, bool showOnlyPublic) const{
    for (const User* user : users_) {
        if (user->getId() == ownerId) {
            return user->getPostsString(howMany, showOnlyPublic); // Return the posts string
        }
    }

    return "";    // return an empty string cuz no ownerId was found 
}





//Pre:
//Post: Reads posts from a file
int Network::readPosts(const char* fname){
    std::ifstream fileIn(fname);
    if (fileIn.fail()) { 
        return -1; // Return -1 if the file cannot be opened
    }

    int numpost;
    fileIn >> numpost;
    fileIn.ignore(); // Ignore the newline after the post count

    for (int i = 0; i < numpost; ++i) {
        int messageId, ownerId, likes;
        std::string message, privacy, author;

        fileIn >> messageId;
        fileIn.ignore(); // Ignore the newline after messageId

        std::getline(fileIn, message);
        fileIn>> ownerId >> likes;
        fileIn.ignore(); // Ignore newline after likes

        std::getline(fileIn, privacy); 
        std::getline(fileIn, author);  
        bool isIncoming = !author.empty();
        bool isPublic = (privacy == "public");

        addPost(ownerId, message, likes, isIncoming, author, isPublic);
    }

    fileIn.close();
    return 0;
}


//Pre:
//Post: Comparison function 
bool Network::comparePosts(const Post* a, const Post* b){
    return a->getMessageId() < b->getMessageId();
}

//Pre:
//Post: Writes posts to a file
int Network::writePosts(const char* fname) const {
    
    std::ofstream fileIn(fname);
    if (fileIn.fail()) {
        return -1; // Return -1 if the file cannot be opened
    }

    std::vector<Post*> allPosts;

    //Collect all posts from each user and add them to the vector
    for (const User* user : users_) {
        const std::vector<Post*>& userPosts = user->getPosts();
        allPosts.insert(allPosts.end(), userPosts.begin(), userPosts.end());
    }

    std::sort(allPosts.begin(), allPosts.end(), Network::comparePosts); // Sort the collected posts by messageId 

    fileIn << allPosts.size() << "\n";
    for (Post* post : allPosts) {
        fileIn << post->getMessageId() << "\n";
        fileIn << post->getMessage() << "\n";
        fileIn << post->getOwnerId() << "\n";
        fileIn << post->getLikes() << "\n";

        IncomingPost* incomingPost = dynamic_cast<IncomingPost*>(post);
        if (incomingPost) {
            if (incomingPost->getIsPublic()) {
                    fileIn<< "public\n";
                } 
            else {
                    fileIn<< "private\n";
                }
            fileIn << incomingPost->getAuthor() << "\n";
        }
        else {
            fileIn << "\n"; 
            fileIn<< "\n"; 
        }
    }
}


 const std::vector<User*>& Network::GETUSER_GETTER() const {
        return users_;
    }

