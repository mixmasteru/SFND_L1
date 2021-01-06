/* \author Aaron Brown */
// Quiz on implementing kd tree

#include "../../render/render.h"


// Structure to represent node of kd tree
struct Node {
    std::vector<float> point;
    int id;
    Node *left;
    Node *right;

    Node(std::vector<float> arr, int setId)
            : point(arr), id(setId), left(NULL), right(NULL) {}
};

struct KdTree {
    Node *root;

    KdTree()
            : root(NULL) {}

    void insertP(Node **node, uint depth, std::vector<float> point, uint id) {
        if (*node == NULL)
            *node = new Node(point, id);
        else {
            uint cd = depth % 2;

            if (point[cd] < ((*node)->point[cd]))
                insertP(&((*node)->left), depth + 1, point, id);
            else
                insertP(&((*node)->right), depth + 1, point, id);
        }
    }

    void insert(std::vector<float> point, int id) {
        insertP(&root, 0, point, id);
    }

    void searchP(std::vector<float> target, Node *node, int depth, float distanceTol, std::vector<int> &ids) {
        if (node != NULL) {
            if (node->point[0] >= (target[0] - distanceTol) && node->point[0] <= (target[0] + distanceTol) &&
                node->point[1] >= (target[1] - distanceTol) && node->point[1] <= (target[1] + distanceTol)) {
                float dist = sqrt((node->point[0] - target[0]) * (node->point[0] - target[0]) +
                                  (node->point[1] - target[1]) * (node->point[1] - target[1]));
                if (dist <= distanceTol)
                    ids.push_back(node->id);
            }

            if ((target[depth % 2] - distanceTol) < node->point[depth % 2])
                searchP(target, node->left, depth + 1, distanceTol, ids);
            if ((target[depth % 2] + distanceTol) > node->point[depth % 2])
                searchP(target, node->right, depth + 1, distanceTol, ids);
        }
    }

    // return a list of point ids in the tree that are within distance of target
    std::vector<int> search(std::vector<float> target, float distanceTol) {
        std::vector<int> ids;
        searchP(target, root, 0, distanceTol, ids);
        return ids;
    }


};




