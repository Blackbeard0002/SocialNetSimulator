#include "AVLTree.h"
#include <algorithm> // For std::max
#include <iostream>  

static long long globalPostTimestamp = 0;

Post::Post(const std::string& c) : content(c) {
    timestamp = globalPostTimestamp++;
}

AVLNode::AVLNode(const Post& p) : post(p), left(nullptr), right(nullptr), height(1) {}

AVLTree::AVLTree() : root(nullptr) {}

AVLTree::~AVLTree() {
    clear(root);
}

void AVLTree::clear(AVLNode* node) {
    if(node != nullptr) {
        clear(node->left);
        clear(node->right);
        delete node;
    }
}

int AVLTree::getHeight(AVLNode* node) {
    if (node == nullptr) return 0;
    return node->height;
}

int AVLTree::getBalance(AVLNode* node) {
    if (node == nullptr) return 0;
    return getHeight(node->left) - getHeight(node->right);
}

void AVLTree::updateHeight(AVLNode* node) {
    if (node != nullptr) {
        node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
    }
}

AVLNode* AVLTree::rightRotate(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;
    x->right = y;
    y->left = T2;
    updateHeight(y);
    updateHeight(x);
    return x;
}

AVLNode* AVLTree::leftRotate(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;
    y->left = x;
    x->right = T2;
    updateHeight(x);
    updateHeight(y);
    return y;
}

AVLNode* AVLTree::insertNode(AVLNode* node, const Post& post) {
    if (node == nullptr) {
        return new AVLNode(post);
    }

    if (post.timestamp < node->post.timestamp) {
        node->left = insertNode(node->left, post);
    } else {
        node->right = insertNode(node->right, post);
    }

    updateHeight(node);
    int balance = getBalance(node);

    if (balance > 1 && post.timestamp < node->left->post.timestamp) {
        return rightRotate(node);
    }
    if (balance < -1 && post.timestamp > node->right->post.timestamp) {
        return leftRotate(node);
    }
    if (balance > 1 && post.timestamp > node->left->post.timestamp) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    if (balance < -1 && post.timestamp < node->right->post.timestamp) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    return node;
}

void AVLTree::addPost(const std::string& content) {
    Post newPost(content);
    root = insertNode(root, newPost);
}

void AVLTree::getPostsReverseInOrder(AVLNode* node, int& N, std::vector<std::string>& posts) {
    if (node == nullptr) {
        return;
    }

    getPostsReverseInOrder(node->right, N, posts);

    if (N == -1) {
        posts.push_back(node->post.content);
    } else if (N > 0) {
        posts.push_back(node->post.content);
        N--;
    } else {
        return;
    }

    if (N == -1 || N > 0) {
        getPostsReverseInOrder(node->left, N, posts);
    }
}

std::vector<std::string> AVLTree::getRecentPosts(int N) {
    std::vector<std::string> posts;
    int count = N;
    getPostsReverseInOrder(root, count, posts);
    return posts;
}
