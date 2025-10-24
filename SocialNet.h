#ifndef SOCIALNET_H
#define SOCIALNET_H

#include <string>
#include <vector>
#include <unordered_map>
#include <map>
#include "Graph.h"
#include "AVLTree.h"

/**
 * Main class to manage the social network simulation.
 */
class SocialNet {
private:
    Graph friendshipGraph;
    
    std::unordered_map<std::string, int> userToId; // normalized_name -> id
    std::vector<std::string> idToUsername;         // id -> original_case_name
    
    std::vector<AVLTree> userPosts; // Index is user ID
    int nextUserId;

    // Helper to get a user's ID from their username.
    int getUserId(const std::string& username);
    // Helper to get a user's original-case name from their ID.
    std::string getUsername(int id);

    // Struct for sorting friend suggestions
    struct FriendSuggestion {
        int id;
        int mutualFriends;
        std::string username;

        bool operator>(const FriendSuggestion& other) const {
            if (mutualFriends != other.mutualFriends) {
                return mutualFriends > other.mutualFriends;
            }
            return username < other.username;
        }
    };

public:
    SocialNet();

    void addUser(const std::string& username);
    void addFriend(const std::string& user1, const std::string& user2);
    void listFriends(const std::string& username);
    void suggestFriends(const std::string& username, int N);
    void degreesOfSeparation(const std::string& user1, const std::string& user2);
    void addPost(const std::string& username, const std::string& content);
    void outputPosts(const std::string& username, int N);
    
    void run();
};

#endif 
