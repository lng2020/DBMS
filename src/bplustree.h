#ifndef BPLUSTREE_H_
#define BPLUSTREE_H_

#include "basic_lib_header.h"
#include "block.h"

struct Node {
    std::vector<std::shared_ptr<void>> ptrs;     // non-leaf node points to node, leaf node points to vector with shared_ptr of the blocks
    std::vector<std::string> keys;
    bool isLeaf;
    std::uint32_t size;    // max number of keys in the Node
    Node(bool isLeaf, int size) : isLeaf(isLeaf), size(size) {}
};


class BPlusTree {
    std::shared_ptr<Node> root;
    std::uint32_t size;    // max number of keys in a tree node
    int numNodes;    // number of nodes in this tree

 public:
    BPlusTree(){
        size = 10;
        root = nullptr;
        numNodes = 0;
    }

    ~BPlusTree() = default;

    void InsertKey(std::string key, std::shared_ptr<Block> blockPtr);
    void InsertInternal(std::string key, std::shared_ptr<Node> parent, std::shared_ptr<Node> child);
    int DeleteKey(std::string key);
    int RemoveInternal(std::string key, std::shared_ptr<Node> traverseNode, std::shared_ptr<Node> childToDelete);
    std::vector<std::shared_ptr<Block>> Find(std::string key);
    std::vector<std::pair<std::string, std::shared_ptr<std::vector<std::shared_ptr<Block>>>>> FindRange(std::string begin, std::string end);
    void PrintNode(std::shared_ptr<Node> node);
    void PrintNodeWithoutPtr(std::shared_ptr<Node> node);
    void PrintRecordsInNode(std::shared_ptr<Node> node);
    void PrintRecordOfKey(std::shared_ptr<void> ptr, std::string key);
    std::shared_ptr<Node> GetRoot();
    void SetRoot(std::shared_ptr<Node> newRoot);
    std::shared_ptr<Node> FindParent(std::shared_ptr<Node> root, std::shared_ptr<Node> child);
    int GetNumNodes() {
        return numNodes;
    }

    int GetHeight();

    void PrintStats();
};

#endif
