#include <iostream>
#include<vector>
#include<algorithm>
#include <cmath>    // For pow function

using namespace std;

struct TreeNode {
    int value;
    TreeNode *left;
    TreeNode *right;

    TreeNode(int x) : value(x), left(nullptr), right(nullptr) {}
};

TreeNode* constructTree(const int* arr, int len) {
    if (len <= 0) return nullptr;
    
    TreeNode** nodes = new TreeNode*[len];
    for (int i = 0; i < len; ++i) {
        nodes[i] = new TreeNode(arr[i]);
    }

    for (int i = 0; i < len; ++i) {
        if (2 * i + 1 < len) {
            nodes[i]->left = nodes[2 * i + 1];
        }
        if (2 * i + 2 < len) {
            nodes[i]->right = nodes[2 * i + 2];
        }
    }

    TreeNode* root = nodes[0];
    delete[] nodes;
    return root;
}

int findMaxPathSum(TreeNode* node) {
    if (node == nullptr) return 0;
    if (node->left == nullptr && node->right == nullptr) return node->value;
    int leftMax = findMaxPathSum(node->left);
    int rightMax = findMaxPathSum(node->right);
    return node->value + max(leftMax, rightMax);
}

void deleteTree(TreeNode* node) {
    if (node == nullptr) return;
    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}

void collectLeaves(TreeNode* node, vector<int>& leaves) {
    if (!node) return;
    if (!node->left && !node->right) {
        leaves.push_back(node->value);
        return;
    }
    collectLeaves(node->left, leaves);
    collectLeaves(node->right, leaves);
}

bool mergeSubTrees(vector<int>& a, int low, int mid, int high) {
    if (a[mid] < a[mid + 1]) return false;
    
    for (int i = low; i <= mid; i++) {
        swap(a[i], a[i + (high - low + 1) / 2]);
    }
    return true;
}

void minSwapsRequired(vector<int>& a, int low, int high, int& result) {
    if (low < high) {
        int mid = low + (high - low) / 2;
        minSwapsRequired(a, low, mid, result);
        minSwapsRequired(a, mid + 1, high, result);
        if (mergeSubTrees(a, low, mid, high)) result++;
    }
}

int main() {
    // cin level
    int L;
    cin >> L;
    // cin key
    int numberOfElements = static_cast<int>(pow(2, L) - 1);
    int* arr = new int[numberOfElements];

    for (int i = 0; i < numberOfElements; ++i) {
        cin >> arr[i];
    }
    //建立樹
    TreeNode* root = constructTree(arr, numberOfElements);
    //把leaves裝起來   
    vector<int> leaves;
    collectLeaves(root, leaves);
    //先計算最常路徑
    int maxPathSum = findMaxPathSum(root);
    //再計算leaves排序所需要的最小swaps數量
    int result = 0;
    minSwapsRequired(leaves, 0, leaves.size() - 1, result);
    //若能排序就印出swap數量 若不行就印出-1
    if(is_sorted(leaves.begin(), leaves.end()))
        cout << result << endl;
    else
        cout << -1 << endl;
    //印出最長路徑
    cout << maxPathSum;
    
    deleteTree(root);
    delete[] arr;

    return 0;
}
