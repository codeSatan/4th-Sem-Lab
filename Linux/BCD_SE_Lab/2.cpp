/*
* Name: Suman Mondal
* Roll no: 001911001014
* BEIT UG-2
* Software Engineering Assignment 
* Question 2
*/

//to run enter in the terminal: g++ 2.cpp 

// Program to solve Job Assignment problem using Branch and Bound

//header files
#include <bits/stdc++.h>

using namespace std;
#define N 4
  
// state space tree node
struct Node
{
    //Node variables
    Node* parent;
    int pathCost;
    int cost;
    int workerID;
    int jobID;
    bool assigned[N];
};
  
// Function to allocate a new search tree node
// Here Person x is assigned to job y
Node* newNode(int x, int y, bool assigned[], Node* parent)
{
    Node* node = new Node;
  
    for (int j = 0; j < N; j++)
        node->assigned[j] = assigned[j];
    node->assigned[y] = true;
  
    node->parent = parent;
    node->workerID = x;
    node->jobID = y;
  
    return node;
}
  
// to calculate the least promising cost
int calculateCost(int costMatrix[N][N], int x, int y, bool assigned[])
{
    int cost = 0;
    bool available[N] = {true};
    for (int i = x + 1; i < N; i++)
    {
        int min = INT_MAX, minIndex = -1;
        for (int j = 0; j < N; j++)
        {
            if (!assigned[j] && available[j] && costMatrix[i][j] < min)
            {
                minIndex = j;
                min = costMatrix[i][j];
            }
        }
        cost += min;
        available[minIndex] = false;
    }
   return cost;
}
  
// Comparison object to be used to order the heap
struct comp
{
    bool operator()(const Node* lhs, const Node* rhs) const
    {
        return lhs->cost > rhs->cost;
    }
};
  
// print Assignments
void printAssignments(Node *min)
{
    if(min->parent==NULL)
        return;
    printAssignments(min->parent);
    cout << "Assign Worker " << char(min->workerID + 'A')<< " to Job " << min->jobID << endl;
}
 
// Finds minimum cost using Branch and Bound.
int findMinCost(int costMatrix[N][N])
{
    // Create a priority queue to store live nodes
    priority_queue<Node*, std::vector<Node*>, comp> pq;
  
    // initailize heap to dummy node with cost 0
    bool assigned[N] = {false};
    Node* root = newNode(-1, -1, assigned, NULL);
    root->pathCost = root->cost = 0;
    root->workerID = -1;
  
    // Add dummy node to list of live nodes;
    pq.push(root);
    while (!pq.empty())
    {
      Node* min = pq.top();
  
      pq.pop();
  
      int i = min->workerID + 1;

      if (i == N)
      {
          printAssignments(min);
          return min->cost;
      }
  
      for (int j = 0; j < N; j++)
      {
        // If unassigned
        if (!min->assigned[j])
        {
          Node* child = newNode(i, j, min->assigned, min);
          child->pathCost = min->pathCost + costMatrix[i][j];

          child->cost = child->pathCost + calculateCost(costMatrix, i, j, child->assigned);
          pq.push(child);
        }
      }
    }
}
  
// Driver code
int main()
{
    // x-cordinate represents a Worker
    // y-cordinate represents a Job
    int costMatrix[N][N] =
    {
        {9, 2, 7, 8},
        {6, 4, 3, 7},
        {5, 8, 1, 8},
        {7, 6, 9, 4}
    };

    cout << "Optimal Cost is \n"<< findMinCost(costMatrix)<<"\n";
  
    return 0;
}