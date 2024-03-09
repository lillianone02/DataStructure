#include <iostream>
#include <vector>
#include <cstdlib>  // for std::swap

using namespace std;

int partition(vector<int>& arr, int left, int right) {
    int pivot = arr[right];
    int i = left;

    for (int j = left; j < right; j++) {
        if (arr[j] > pivot) { // Change to '<' for K-th smallest
            swap(arr[i], arr[j]);
            i++;
        }
    }

    swap(arr[i], arr[right]);
    return i;
}

int quickSelect(vector<int>& arr, int left, int right, int K) {
    if (left == right) return arr[left];

    int pivotIndex = partition(arr, left, right);

    if (K == pivotIndex)
        return arr[K];
    else if (K < pivotIndex)
        return quickSelect(arr, left, pivotIndex - 1, K);
    else
        return quickSelect(arr, pivotIndex + 1, right, K);
}

int main() {
    int N, K;
    cin >> N >> K;
    vector<int> scores(N);
    for (int i = 0; i < N; i++) {
        cin >> scores[i];
    }

    cout << quickSelect(scores, 0, N - 1, K - 1) << endl; // K - 1 because of zero-based indexing

    return 0;
}
