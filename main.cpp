#include <iostream>
#include <stack>
#include <climits>

struct Node{
	int key;
	int npl;
	Node* left;
	Node* right;
	Node(int val) : key(val), npl(0), left(nullptr), right(nullptr) {}
};

class LeftistHeap{
	private:
		Node* root;
		Node* merge(Node* h1, Node* h2){
			if(!h1) return h2;
			if(!h2) return h1;
			std::stack<Node*> mergeStack;
			if (h1->key > h2->key) std::swap(h1, h2);
			Node* mergedRoot = h1;
			mergeStack.push(h1);
			mergeStack.push(h2);
			while(!mergeStack.empty()){
				Node* n2 = mergeStack.top(); mergeStack.pop();
				Node* n1 = mergeStack.top(); mergeStack.pop();
				if(!n1->right){
					n1->right = n2;
				}else{
					if(n1->right->key > n2->key) std::swap(n1->right, n2);
					mergeStack.push(n1->right);
					mergeStack.push(n2);
				}
				if(!n1->left || n1->left->npl < n1->right->npl){
					std::swap(n1->left, n1->right);
				}
				n1->npl = (n1->right ? n1->right->npl : -1) + 1;
			}
			return mergedRoot;
		}
		void deleteHeap(Node* node){
			if(!node) return;
			deleteHeap(node->left);
			deleteHeap(node->right);
			delete node;
		}
		void currentLevel(Node* root, int level){
			if(root == nullptr)
				return;
			if(level == 1)
				std::cout << root->key << " ";
			else if (level > 1){
				currentLevel(root->left, level-1);
				currentLevel(root->right, level-1);
			}
		}
		int height(Node* node){
			if(node == nullptr)
				return 0;
			else{
				int lheight = height(node->left);
				int rheight = height(node->right);
				return (lheight > rheight) ? (lheight + 1) : (rheight + 1);
			}
		}
		void levelOrder(Node* root){
			int h = height(root);
			for(int i = 1; i <= h; i++)
				currentLevel(root, i);
		}
	public:
		LeftistHeap() : root(nullptr) {}
		~LeftistHeap() {
			deleteHeap(root);
		}
		void insert(int key){
			Node* newNode = new Node(key);
			root = merge(root, newNode);
		}
		void mergeWith(LeftistHeap& other){
			root = merge(root, other.root);
			other.root = nullptr;
		}
		void print() {
			levelOrder(root);
			std::cout << std::endl;
		}
};

int main(){
	int heap1[] = {4, 19, 8, 27, 20, 12, 43, 15, 25};
	int heap2[] = {6, 8, 7, 14};
	LeftistHeap h1;
	LeftistHeap h2;
	for(int i=0; i<9; i++){
		h1.insert(heap1[i]);
	}
	for(int i=0; i<4; i++){
		h2.insert(heap2[i]);
	}
	std::cout << "Heap 1: " << std::endl;
	h1.print();
	std::cout << "Heap 2: " << std::endl;
	h2.print();
	h1.mergeWith(h2);
	std::cout << "Merged Heap(level order traversal): " << std::endl;
	h1.print();
	return 0;
}
