#include "SocialNet.h"
#include "utility.h" // For normalize()
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <vector>
#include <algorithm> // For std::sort

SocialNet::SocialNet() : nextUserId(0) {}

int SocialNet::getUserId(const std::string& username) {
    std::string normUser = normalize(username);
    if (userToId.find(normUser) != userToId.end()) {
        return userToId[normUser];
    }
    return -1;
}

std::string SocialNet::getUsername(int id) {
    if (id >= 0 && (size_t)id < idToUsername.size()) {
        return idToUsername[id];
    }
    return "";
}

void SocialNet::addUser(const std::string& username) {
    std::string normUser = normalize(username);
    if (userToId.find(normUser) != userToId.end()) {
        std::cout << "Error: User '" << username << "' already exists." << std::endl;
        return;
    }

    int newId = nextUserId++;
    userToId[normUser] = newId;
    idToUsername.push_back(username);
    
    friendshipGraph.addVertex(newId);
    userPosts.push_back(AVLTree());

    std::cout << "User '" << username << "' added." << std::endl;
}

void SocialNet::addFriend(const std::string& user1, const std::string& user2) {
    int id1 = getUserId(user1);
    int id2 = getUserId(user2);

    if (id1 == -1) {
        std::cout << "Error: User '" << user1 << "' not found." << std::endl;
        return;
    }
    if (id2 == -1) {
        std::cout << "Error: User '" << user2 << "' not found." << std::endl;
        return;
    }
    if (id1 == id2) {
         std::cout << "Error: Cannot add self as friend." << std::endl;
         return;
    }

    friendshipGraph.addEdge(id1, id2);
    std::cout << "Friendship established between '" << getUsername(id1) << "' and '" << getUsername(id2) << "'." << std::endl;
}

void SocialNet::listFriends(const std::string& username) {
    int id = getUserId(username);
    if (id == -1) {
        std::cout << "Error: User '" << username << "' not found." << std::endl;
        return;
    }

    std::vector<int> friendIds = friendshipGraph.getFriends(id);
    if (friendIds.empty()) {
        std::cout << "User '" << getUsername(id) << "' has no friends." << std::endl;
        return;
    }

    std::vector<std::string> friendNames;
    for (int friendId : friendIds) {
        friendNames.push_back(getUsername(friendId));
    }
    sort(friendNames.begin(), friendNames.end());

    std::cout << "Friends of '" << getUsername(id) << "':" << std::endl;
    for (const std::string& name : friendNames) {
        std::cout << "- " << name << std::endl;
    }
}

void SocialNet::suggestFriends(const std::string& username, int N) {
    if (N <= 0) return;

    int userId = getUserId(username);
    if (userId == -1) {
        std::cout << "Error: User '" << username << "' not found." << std::endl;
        return;
    }

    std::vector<int> myFriends = friendshipGraph.getFriends(userId);
    std::unordered_map<int, int> suggestions;

    for (int friendId : myFriends) {
        std::vector<int> fofIds = friendshipGraph.getFriends(friendId);
        for (int fofId : fofIds) {
            bool isMe = (fofId == userId);
            bool isFriend = (std::find(myFriends.begin(),myFriends.end(),fofId) != myFriends.end());
            if (!isMe && !isFriend) {
                suggestions[fofId]++;
            }
        }
    }

    if (suggestions.empty()) {
        std::cout << "No friend suggestions for '" << getUsername(userId) << "'." << std::endl;
        return;
    }

    std::vector<FriendSuggestion> rankedSuggestions;
    for (auto const& [id, count] : suggestions) {
        rankedSuggestions.push_back({id, count, getUsername(id)});
    }

    std::sort(rankedSuggestions.begin(), rankedSuggestions.end(), std::greater<FriendSuggestion>());

    std::cout << "Friend suggestions for '" << getUsername(userId) << "':" << std::endl;
    int count = 0;
    for (const auto& s : rankedSuggestions) {
        if (count >= N) break;
        std::cout << "- " << s.username << " (" << s.mutualFriends << " mutual friend" << (s.mutualFriends > 1 ? "s" : "") << ")" << std::endl;
        count++;
    }
}

void SocialNet::degreesOfSeparation(const std::string& user1, const std::string& user2) {
    int id1 = getUserId(user1);
    int id2 = getUserId(user2);

    if (id1 == -1) {
        std::cout << "Error: User '" << user1 << "' not found." << std::endl;
        return;
    }
    if (id2 == -1) {
        std::cout << "Error: User '" << user2 << "' not found." << std::endl;
        return;
    }

    int degrees = friendshipGraph.bfs(id1, id2);
    std::cout << "Degrees of separation between '" << getUsername(id1) << "' and '" << getUsername(id2) << "': " << degrees << std::endl;
}

void SocialNet::addPost(const std::string& username, const std::string& content) {
    int id = getUserId(username);
    if (id == -1) {
        std::cout << "Error: User '" << username << "' not found." << std::endl;
        return;
    }
    userPosts[id].addPost(content);
    std::cout << "Post added for '" << getUsername(id) << "'." << std::endl;
}

void SocialNet::outputPosts(const std::string& username, int N) {
    int id = getUserId(username);
    if (id == -1) {
        std::cout << "Error: User '" << username << "' not found." << std::endl;
        return;
    }

    std::vector<std::string> posts = userPosts[id].getRecentPosts(N);

    if (posts.empty()) {
        std::cout << "User '" << getUsername(id) << "' has no posts." << std::endl;
        return;
    }

    std::cout << "Posts from '" << getUsername(id) << "':" << std::endl;
    for (const std::string& post : posts) {
        std::cout << "- " << post << std::endl;
    }
}

void SocialNet::run() {
    std::string line;
    while (std::getline(std::cin, line)) {
        if (line.empty()) continue;

        std::stringstream ss(line);
        std::string command;
        ss >> command;

        try {
            if (command == "ADD_USER") {
                std::string username;
                ss >> username;
                if (username.empty()) throw std::runtime_error("Missing username.");
                addUser(username);
            } 
            else if (command == "ADD_FRIEND") {
                std::string u1, u2;
                ss >> u1 >> u2;
                if (u1.empty() || u2.empty()) throw std::runtime_error("Missing usernames.");
                addFriend(u1, u2);
            } 
            else if (command == "LIST_FRIENDS") {
                std::string username;
                ss >> username;
                if (username.empty()) throw std::runtime_error("Missing username.");
                listFriends(username);
            } 
            else if (command == "SUGGEST_FRIENDS") {
                std::string username;
                int N;
                ss >> username >> N;
                if (username.empty()) throw std::runtime_error("Missing username or N.");
                if (ss.fail()) throw std::runtime_error("Invalid N value.");
                suggestFriends(username, N);
            } 
            else if (command == "DEGREES_OF_SEPARATION") {
                std::string u1, u2;
                ss >> u1 >> u2;
                if (u1.empty() || u2.empty()) throw std::runtime_error("Missing usernames.");
                degreesOfSeparation(u1, u2);
            } 
            else if (command == "ADD_POST") {
                std::string username;
                ss >> username;
                
                std::string content;
                size_t firstQuote = line.find('"');
                size_t lastQuote = line.rfind('"');

                if (firstQuote == std::string::npos || lastQuote == std::string::npos || firstQuote == lastQuote) {
                    throw std::runtime_error("Invalid post format. Use: ADD_POST <user> \"<content>\"");
                }
                
                content = line.substr(firstQuote + 1, lastQuote - firstQuote - 1);
                
                if (username.empty()) throw std::runtime_error("Missing username.");
                addPost(username, content);
            } 
            else if (command == "OUTPUT_POSTS") {
                std::string username;
                int N;
                ss >> username >> N;
                if (username.empty()) throw std::runtime_error("Missing username or N.");
                if (ss.fail()) throw std::runtime_error("Invalid N value.");
                outputPosts(username, N);
            } 
            else if (command == "EXIT") {
                std::cout << "Exiting SocialNet. Goodbye!" << std::endl;
                break;
            }
            else {
                std::cout << "Error: Unknown command '" << command << "'" << std::endl;
            }
        } catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << std::endl;
        }
        std::cout << std::endl;
    }
}
