#ifndef _TRAI_H_
#define _TRAI_H_
#include <unordered_map>
using namespace std;

template <class T>
class trai {
    class Node {
    public:
        unordered_map<T, Node*> sub_nodes;
        ~Node() {
            for (auto &i : sub_nodes) {
                delete i.second;
            }
        }
    };
    Node root;
public:
    void insert(vector<T>& dic) {
        Node* node = &root;
        for (auto &i : dic) {
            auto iter = node->sub_nodes.find(i);
            if (node->sub_nodes.end() == iter) {
                Node* new_node = new Node;
                node->sub_nodes.emplace(i, new_node);
                node = new_node;
            }
            else {
                node = iter->second;
            }
        }
	}
	void erase(vector<T>& dic) {
        Node* node = &root;
        size_t i;
        for (i = 0; i < dic.size() - 1; ++i) {
            auto iter = node->sub_nodes.find(dic[i]);
            if (node->sub_nodes.end() != iter) {
                node = iter->second;
            }
            else {
                return;
            }
        }
        auto iter = node->sub_nodes.find(dic[i]);
        if (node->sub_nodes.end() != iter) {
            delete iter->second;
            node->sub_nodes.erase(iter);
        }
	}
	vector<T> ls(vector<T>& dic) {
		Node* node = &root;
        size_t i;
        for (i = 0; i < dic.size() - 1; ++i) {
            auto iter = node->sub_nodes.find(dic[i]);
            if (node->sub_nodes.end() != iter) {
                node = iter->second;
            }
            else {
                return vector<T>();
            }
        }
        auto iter = node->sub_nodes.find(dic[i]);
        if (node->sub_nodes.end() != iter) {
            if (iter->second->sub_nodes.size() == 0) {
                return vector<T>({iter->first});
            }
            else {
                vector<T> ret;
                for (auto &i : iter->second->sub_nodes) {
                    ret.emplace_back(i.first);
                }
                return ret;
            }
        }
        else {
            return vector<T>();
        }
	}
};
#endif // _TRAI_H_
