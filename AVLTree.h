#ifndef AVLTREE_H
#define AVLTREE_H

#include <string>
#include <vector>


struct Post {
    long long timestamp;
    std::string content;

    Post(const std::string& c);
};

struct AVLNode {
    Post post;
    AVLNode *left;
    AVLNode *right;
    int height;

    AVLNode(const Post& p);
};

class AVLTree {
private:
    AVLNode* root;

    int getHeight(AVLNode* node);
    int getBalance(AVLNode* node);
    void updateHeight(AVLNode* node);
    AVLNode* rightRotate(AVLNode* y);
    AVLNode* leftRotate(AVLNode* x);
    AVLNode* insertNode(AVLNode* node, const Post& post);
    void getPostsReverseInOrder(AVLNode* node, int& N, std::vector<std::string>& posts);
    void clear(AVLNode* node);

public:
    AVLTree();
    ~AVLTree();

    void addPost(const std::string& content);
    std::vector<std::string> getRecentPosts(int N);
};

#endif 
