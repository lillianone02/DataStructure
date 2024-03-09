#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <climits>

using namespace std;

// Define a custom structure for airline information
struct AirlineInfo {
    int airline;
    int cost;

    AirlineInfo(int airline, int cost) : airline(airline), cost(cost) {}
};

// Define a custom structure for elements in the priority queue
struct QueueNode {
    int cost;
    int city;
    int lastAirline;

    QueueNode(int cost, int city, int lastAirline) : cost(cost), city(city), lastAirline(lastAirline) {}

    // Operator to compare QueueNodes. Lower cost has higher priority.
    bool operator>(const QueueNode& other) const {
        return cost > other.cost;
    }
};

// Graph structure to hold flight information
class Graph {
    int C; // Number of cities
    vector<vector<vector<AirlineInfo>>> adj; // 3D vector for flight information

public:
    Graph(int C) : C(C), adj(C, vector<vector<AirlineInfo>>(C)) {}

    void addOrUpdateFlight(int U, int V, int P, int A) {
        bool found = false;
        for (auto &route : adj[U][V]) {
            if (route.airline == A) {
                route.cost = P;
                found = true;
                break;
            }
        }
        if (!found) {
            adj[U][V].push_back(AirlineInfo(A, P));
        }
    }

    void deleteFlight(int U, int V, int A) {
        for (auto it = adj[U][V].begin(); it != adj[U][V].end(); ++it) {
            if (it->airline == A) {
                adj[U][V].erase(it);
                break;
            }
        }
    }

    int requestCheapestFlight(int SRC, int DST, int W) {
        priority_queue<QueueNode, vector<QueueNode>, greater<QueueNode>> pq;
        vector<vector<int>> minCost(C, vector<int>(C, INT_MAX));

        pq.push(QueueNode(0, SRC, -1));
        minCost[SRC][SRC] = 0;

        while (!pq.empty()) {
            QueueNode node = pq.top();
            pq.pop();

            if (node.city == DST) {
                return node.cost;
            }

            for (auto& info : adj[node.city]) {
                for (auto& flight : info) {
                    int nextCity = &info - &adj[node.city][0];
                    int airline = flight.airline;
                    int flightCost = flight.cost;
                    int totalCost = node.cost + flightCost;
                    if (node.lastAirline != -1 && node.lastAirline != airline) {
                        totalCost += 5; // Additional cost for changing airlines
                    }

                    if (totalCost <= W && totalCost < minCost[nextCity][airline]) {
                        pq.push(QueueNode(totalCost, nextCity, airline));
                        minCost[nextCity][airline] = totalCost;
                    }
                }
            }
        }

        return -1;
    }
};

int main() {
    int C, N;
    cin >> C >> N;

    Graph graph(C);

    for (int i = 0; i < N; ++i) {
        string instruction;
        cin >> instruction;

        if (instruction == "Add") {
            int U, V, P, A;
            cin >> U >> V >> P >> A;
            graph.addOrUpdateFlight(U, V, P, A);
        } else if (instruction == "Delete") {
            int U, V, A;
            cin >> U >> V >> A;
            graph.deleteFlight(U, V, A);
        } else if (instruction == "Request") {
            int SRC, DST, W;
            cin >> SRC >> DST >> W;
            int cost = graph.requestCheapestFlight(SRC, DST, W);
            cout << cost << endl;
        }
    }

    return 0;
}
