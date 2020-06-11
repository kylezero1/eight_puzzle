#include <iostream>
#include <stdlib.h>
#include <string>
#include <queue>
#include <algorithm>
#include <math.h>

using namespace std;

int num_nodes = 0;

struct node {
    int puzzle[3][3];
    int g_n;
    int h_n;
};

bool goal_test(int puzzle[3][3]) {
    if (puzzle[0][0] == 1 && puzzle[0][1] == 2 && puzzle[0][2] == 3 &&
        puzzle[1][0] == 4 && puzzle[1][1] == 5 && puzzle[1][2] == 6 &&
        puzzle[2][0] == 7 && puzzle[2][1] == 8 && puzzle[2][2] == 0) {
            return true;
    } else {
        return false;
    }
}

int misplacedHeuristic(int puzzle[3][3]) {
    int misplaced = 0;

    if (puzzle[0][0] != 1) {
        misplaced++;
    }
    if (puzzle[0][1] != 2) {
        misplaced++;
    }
    if (puzzle[0][2] != 3) {
        misplaced++;
    }
    if (puzzle[1][0] != 4) {
        misplaced++;
    }
    if (puzzle[1][1] != 5) {
        misplaced++;
    }
    if (puzzle[1][2] != 6) {
        misplaced++;
    }
    if (puzzle[2][0] != 7) {
        misplaced++;
    }
    if (puzzle[2][1] != 8) {
        misplaced++;
    }

    return misplaced;

}

int manhattanHeuristic(int puzzle[3][3]) {
    int manhattan = 0;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (puzzle[i][j] == 1) {
                manhattan += abs(i - 0) + abs(j - 0);
            }
            if (puzzle[i][j] == 2) {
                manhattan += abs(i - 0) + abs(j - 1);
            }
            if (puzzle[i][j] == 3) {
                manhattan += abs(i - 0) + abs(j - 2);
            }
            if (puzzle[i][j] == 4) {
                manhattan += abs(i - 1) + abs(j - 0);
            }
            if (puzzle[i][j] == 5) {
                manhattan += abs(i - 1) + abs(j - 1);
            }
            if (puzzle[i][j] == 6) {
                manhattan += abs(i - 1) + abs(j - 2);
            }
            if (puzzle[i][j] == 7) {
                manhattan += abs(i - 2) + abs(j - 0);
            }
            if (puzzle[i][j] == 8) {
                manhattan += abs(i - 2) + abs(j - 1);
            }
        }
    }
    return manhattan;
}

queue<node> uniformCostSearch(queue<node> nodes, node node_removed) {
    //Operators -> Move 0 left, right, up, down

    int blankPOSi, blankPOSj;

    queue<node> returnNodes = nodes;

    node child0, child1, child2, child3;

    for (int i = 0; i < 3; i++) { //Get the position of the 0 (blank)
        for (int j = 0; j < 3; j++) {
            if (node_removed.puzzle[i][j] == 0) {
                blankPOSi = i;
                blankPOSj = j;
            }
        }
    }

    if (blankPOSj != 0) { //Operator: Move blank left
        for (int i = 0; i < 3; i++) { //copy node_removed.puzzle into child0.puzzle
            for (int j = 0; j < 3; j++) {
                child0.puzzle[i][j] = node_removed.puzzle[i][j];
            }
        }

        child0.puzzle[blankPOSi][blankPOSj] = node_removed.puzzle[blankPOSi][blankPOSj-1]; //Swap
        child0.puzzle[blankPOSi][blankPOSj-1] = 0;

        child0.g_n = node_removed.g_n + 1;
        child0.h_n = 0;
    }

    if (blankPOSj != 2) { //Operator: Move blank right
        for (int i = 0; i < 3; i++) { //copy node_removed.puzzle into child1.puzzle
            for (int j = 0; j < 3; j++) {
                child1.puzzle[i][j] = node_removed.puzzle[i][j];
            }
        }

        child1.puzzle[blankPOSi][blankPOSj] = node_removed.puzzle[blankPOSi][blankPOSj+1]; //Swap
        child1.puzzle[blankPOSi][blankPOSj+1] = 0;
        
        child1.g_n = node_removed.g_n + 1;
        child1.h_n = 0;
    }

    if (blankPOSi != 0) { //Operator: Move blank up
        for (int i = 0; i < 3; i++) { //copy node_removed.puzzle into child2.puzzle
            for (int j = 0; j < 3; j++) {
                child2.puzzle[i][j] = node_removed.puzzle[i][j];
            }
        }

        child2.puzzle[blankPOSi][blankPOSj] = node_removed.puzzle[blankPOSi-1][blankPOSj]; //Swap
        child2.puzzle[blankPOSi-1][blankPOSj] = 0;

        child2.g_n = node_removed.g_n + 1;
        child2.h_n = 0;
    }

    if (blankPOSi != 2) { //Operator: Move blank down
        for (int i = 0; i < 3; i++) { //copy node_removed.puzzle into child3.puzzle
            for (int j = 0; j < 3; j++) {
                child3.puzzle[i][j] = node_removed.puzzle[i][j];
            }
        }

        child3.puzzle[blankPOSi][blankPOSj] = node_removed.puzzle[blankPOSi+1][blankPOSj]; //Swap
        child3.puzzle[blankPOSi+1][blankPOSj] = 0;

        child3.g_n = node_removed.g_n + 1;
        child3.h_n = 0;
    }

    int total0 = child0.g_n + child0.h_n;
    int total1 = child1.g_n + child1.h_n;
    int total2 = child2.g_n + child2.h_n;
    int total3 = child3.g_n + child3.h_n;

    if ((total0 <= total1 && total0 <= total2 && total0 <= total3)) {
        returnNodes.push(child0);
        if (child1.h_n <= node_removed.h_n) returnNodes.push(child1);
        if (child2.h_n <= node_removed.h_n) returnNodes.push(child2);
        if (child3.h_n <= node_removed.h_n) returnNodes.push(child3);
        num_nodes++;
    } else if ((total1 <= total0 && total1 <= total2 && total1 <= total3)) {
        returnNodes.push(child1);
        if (child0.h_n <= node_removed.h_n) returnNodes.push(child0);
        if (child2.h_n <= node_removed.h_n) returnNodes.push(child2);
        if (child3.h_n <= node_removed.h_n) returnNodes.push(child3);
        num_nodes++;
    } else if ((total2 <= total0 && total2 <= total1 && total2 <= total3)) {
        returnNodes.push(child2);
        if (child0.h_n <= node_removed.h_n) returnNodes.push(child0);
        if (child1.h_n <= node_removed.h_n) returnNodes.push(child1);
        if (child3.h_n <= node_removed.h_n) returnNodes.push(child3);
        num_nodes++;
    } else if ((total3 <= total0 && total3 <= total1 && total3 <= total2)) {
        returnNodes.push(child3);
        if (child0.h_n <= node_removed.h_n) returnNodes.push(child0);
        if (child1.h_n <= node_removed.h_n) returnNodes.push(child1);
        if (child2.h_n <= node_removed.h_n) returnNodes.push(child2);
        num_nodes++;
    }
    return returnNodes;
}

queue<node> aWithMisplaced(queue<node> nodes, node node_removed) {
//Operators -> Move 0 left, right, up, down

    int blankPOSi, blankPOSj;

    queue<node> returnNodes = nodes;

    node child0, child1, child2, child3;

    for (int i = 0; i < 3; i++) { //Get the position of the 0 (blank)
        for (int j = 0; j < 3; j++) {
            if (node_removed.puzzle[i][j] == 0) {
                blankPOSi = i;
                blankPOSj = j;
            }
        }
    }

    if (blankPOSj != 0) { //Operator: Move blank left
        for (int i = 0; i < 3; i++) { //copy node_removed.puzzle into child0.puzzle
            for (int j = 0; j < 3; j++) {
                child0.puzzle[i][j] = node_removed.puzzle[i][j];
            }
        }

        child0.puzzle[blankPOSi][blankPOSj] = node_removed.puzzle[blankPOSi][blankPOSj-1]; //Swap
        child0.puzzle[blankPOSi][blankPOSj-1] = 0;

        child0.g_n = node_removed.g_n + 1;
        child0.h_n = misplacedHeuristic(child0.puzzle);
    }

    if (blankPOSj != 2) { //Operator: Move blank right
        for (int i = 0; i < 3; i++) { //copy node_removed.puzzle into child1.puzzle
            for (int j = 0; j < 3; j++) {
                child1.puzzle[i][j] = node_removed.puzzle[i][j];
            }
        }

        child1.puzzle[blankPOSi][blankPOSj] = node_removed.puzzle[blankPOSi][blankPOSj+1]; //Swap
        child1.puzzle[blankPOSi][blankPOSj+1] = 0;
        
        child1.g_n = node_removed.g_n + 1;
        child1.h_n = misplacedHeuristic(child1.puzzle);
    }

    if (blankPOSi != 0) { //Operator: Move blank up
        for (int i = 0; i < 3; i++) { //copy node_removed.puzzle into child2.puzzle
            for (int j = 0; j < 3; j++) {
                child2.puzzle[i][j] = node_removed.puzzle[i][j];
            }
        }

        child2.puzzle[blankPOSi][blankPOSj] = node_removed.puzzle[blankPOSi-1][blankPOSj]; //Swap
        child2.puzzle[blankPOSi-1][blankPOSj] = 0;

        child2.g_n = node_removed.g_n + 1;
        child2.h_n = misplacedHeuristic(child2.puzzle);
    }

    if (blankPOSi != 2) { //Operator: Move blank down
        for (int i = 0; i < 3; i++) { //copy node_removed.puzzle into child3.puzzle
            for (int j = 0; j < 3; j++) {
                child3.puzzle[i][j] = node_removed.puzzle[i][j];
            }
        }

        child3.puzzle[blankPOSi][blankPOSj] = node_removed.puzzle[blankPOSi+1][blankPOSj]; //Swap
        child3.puzzle[blankPOSi+1][blankPOSj] = 0;

        child3.g_n = node_removed.g_n + 1;
        child3.h_n = misplacedHeuristic(child3.puzzle);
    }

    int total0 = child0.g_n + child0.h_n;
    int total1 = child1.g_n + child1.h_n;
    int total2 = child2.g_n + child2.h_n;
    int total3 = child3.g_n + child3.h_n;

    if ((total0 <= total1 && total0 <= total2 && total0 <= total3)) {
        returnNodes.push(child0);
        if (child1.h_n <= node_removed.h_n) returnNodes.push(child1);
        if (child2.h_n <= node_removed.h_n) returnNodes.push(child2);
        if (child3.h_n <= node_removed.h_n) returnNodes.push(child3);
        num_nodes++;
    } else if ((total1 <= total0 && total1 <= total2 && total1 <= total3)) {
        returnNodes.push(child1);
        if (child0.h_n <= node_removed.h_n) returnNodes.push(child0);
        if (child2.h_n <= node_removed.h_n) returnNodes.push(child2);
        if (child3.h_n <= node_removed.h_n) returnNodes.push(child3);
        num_nodes++;
    } else if ((total2 <= total0 && total2 <= total1 && total2 <= total3)) {
        returnNodes.push(child2);
        if (child0.h_n <= node_removed.h_n) returnNodes.push(child0);
        if (child1.h_n <= node_removed.h_n) returnNodes.push(child1);
        if (child3.h_n <= node_removed.h_n) returnNodes.push(child3);
        num_nodes++;
    } else if ((total3 <= total0 && total3 <= total1 && total3 <= total2)) {
        returnNodes.push(child3);
        if (child0.h_n <= node_removed.h_n) returnNodes.push(child0);
        if (child1.h_n <= node_removed.h_n) returnNodes.push(child1);
        if (child2.h_n <= node_removed.h_n) returnNodes.push(child2);
        num_nodes++;
    }
    return returnNodes;
}

queue<node> aWithManhattan(queue<node> nodes, node node_removed) {
//Operators -> Move 0 left, right, up, down

    int blankPOSi, blankPOSj;

    queue<node> returnNodes = nodes;

    node child0, child1, child2, child3;

    for (int i = 0; i < 3; i++) { //Get the position of the 0 (blank)
        for (int j = 0; j < 3; j++) {
            if (node_removed.puzzle[i][j] == 0) {
                blankPOSi = i;
                blankPOSj = j;
            }
        }
    }

    if (blankPOSj != 0) { //Operator: Move blank left
        for (int i = 0; i < 3; i++) { //copy node_removed.puzzle into child0.puzzle
            for (int j = 0; j < 3; j++) {
                child0.puzzle[i][j] = node_removed.puzzle[i][j];
            }
        }

        child0.puzzle[blankPOSi][blankPOSj] = node_removed.puzzle[blankPOSi][blankPOSj-1]; //Swap
        child0.puzzle[blankPOSi][blankPOSj-1] = 0;

        child0.g_n = node_removed.g_n + 1;
        child0.h_n = manhattanHeuristic(child0.puzzle);
    }

    if (blankPOSj != 2) { //Operator: Move blank right
        for (int i = 0; i < 3; i++) { //copy node_removed.puzzle into child1.puzzle
            for (int j = 0; j < 3; j++) {
                child1.puzzle[i][j] = node_removed.puzzle[i][j];
            }
        }

        child1.puzzle[blankPOSi][blankPOSj] = node_removed.puzzle[blankPOSi][blankPOSj+1]; //Swap
        child1.puzzle[blankPOSi][blankPOSj+1] = 0;
        
        child1.g_n = node_removed.g_n + 1;
        child1.h_n = manhattanHeuristic(child1.puzzle);
    }

    if (blankPOSi != 0) { //Operator: Move blank up
        for (int i = 0; i < 3; i++) { //copy node_removed.puzzle into child2.puzzle
            for (int j = 0; j < 3; j++) {
                child2.puzzle[i][j] = node_removed.puzzle[i][j];
            }
        }

        child2.puzzle[blankPOSi][blankPOSj] = node_removed.puzzle[blankPOSi-1][blankPOSj]; //Swap
        child2.puzzle[blankPOSi-1][blankPOSj] = 0;

        child2.g_n = node_removed.g_n + 1;
        child2.h_n = manhattanHeuristic(child2.puzzle);
    }

    if (blankPOSi != 2) { //Operator: Move blank down
        for (int i = 0; i < 3; i++) { //copy node_removed.puzzle into child3.puzzle
            for (int j = 0; j < 3; j++) {
                child3.puzzle[i][j] = node_removed.puzzle[i][j];
            }
        }

        child3.puzzle[blankPOSi][blankPOSj] = node_removed.puzzle[blankPOSi+1][blankPOSj]; //Swap
        child3.puzzle[blankPOSi+1][blankPOSj] = 0;

        child3.g_n = node_removed.g_n + 1;
        child3.h_n = manhattanHeuristic(child3.puzzle);
    }

    int total0 = child0.g_n + child0.h_n;
    int total1 = child1.g_n + child1.h_n;
    int total2 = child2.g_n + child2.h_n;
    int total3 = child3.g_n + child3.h_n;

    if ((total0 <= total1 && total0 <= total2 && total0 <= total3)) {
        returnNodes.push(child0);
        if (child1.h_n <= node_removed.h_n) returnNodes.push(child1);
        if (child2.h_n <= node_removed.h_n) returnNodes.push(child2);
        if (child3.h_n <= node_removed.h_n) returnNodes.push(child3);
        num_nodes++;
    } else if ((total1 <= total0 && total1 <= total2 && total1 <= total3)) {
        returnNodes.push(child1);
        if (child0.h_n <= node_removed.h_n) returnNodes.push(child0);
        if (child2.h_n <= node_removed.h_n) returnNodes.push(child2);
        if (child3.h_n <= node_removed.h_n) returnNodes.push(child3);
        num_nodes++;
    } else if ((total2 <= total0 && total2 <= total1 && total2 <= total3)) {
        returnNodes.push(child2);
        if (child0.h_n <= node_removed.h_n) returnNodes.push(child0);
        if (child1.h_n <= node_removed.h_n) returnNodes.push(child1);
        if (child3.h_n <= node_removed.h_n) returnNodes.push(child3);
        num_nodes++;
    } else if ((total3 <= total0 && total3 <= total1 && total3 <= total2)) {
        returnNodes.push(child3);
        if (child0.h_n <= node_removed.h_n) returnNodes.push(child0);
        if (child1.h_n <= node_removed.h_n) returnNodes.push(child1);
        if (child2.h_n <= node_removed.h_n) returnNodes.push(child2);
        num_nodes++;
    }
    return returnNodes;
}

void general_search(int puzzle[3][3], string queueing_function) {
    queue<node> nodes;

    node initial_state;

    
    //int h_n = 0;
    int max_nodes = 0;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            initial_state.puzzle[i][j] = puzzle[i][j];
        }
    }

    initial_state.g_n = 1; 

    if (queueing_function == "uniformCostSearch") {
        initial_state.h_n = 0;
    } else if (queueing_function == "aWithMisplaced") {
        initial_state.h_n = misplacedHeuristic(initial_state.puzzle);
    } else if (queueing_function == "aWithManhattan") {
        initial_state.h_n = manhattanHeuristic(initial_state.puzzle);
    }   
    
    nodes.push(initial_state); //make queue with initial state    
    
    num_nodes++;
    max_nodes = 1;

    while (1) {
        if (nodes.empty() == true) { //Check if nodes is empty
            cout << "Failure, no solution to given puzzle \n";
            exit(0);
        }

        node node_removed; //= nodes.front();
        for (int i = 0; i < 3; i++) { //copy front puzzle into node_removed.puzzle
            for (int j = 0; j < 3; j++) {
                node_removed.puzzle[i][j] = nodes.front().puzzle[i][j];
            }
        }

        node_removed.g_n = nodes.front().g_n;
        node_removed.h_n = nodes.front().h_n;

        nodes.pop();

        if (goal_test(node_removed.puzzle) == true) { //Check if removed node is a goal state
            cout << "Found solution with g(n) = " << node_removed.g_n << " and h(n) = " << node_removed.h_n << endl;    
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    cout << node_removed.puzzle[i][j] << " ";                    
                }                
            cout << endl;
            }

            cout << "Goal!! \n";
            cout << "To solve this problem the search algorithm expanded a total of " << num_nodes << " nodes. \n";
            cout << "The maximum number of nodes in the queue at any one time was " << max_nodes << endl;
            cout << "The depth of the goal node was " << node_removed.g_n << endl;

            exit(0);
        }
        cout << "Expanding state with a g(n) = " << node_removed.g_n << " and h(n) = " << node_removed.h_n << endl;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                cout << node_removed.puzzle[i][j] << " ";                    
            }                
            cout << endl;
        }

        if (queueing_function == "uniformCostSearch") {
            nodes = uniformCostSearch(nodes, node_removed); //Operators = move 0 square
        } else if (queueing_function == "aWithMisplaced") {
            nodes = aWithMisplaced(nodes, node_removed);
        } else if (queueing_function == "aWithManhattan") {
            nodes = aWithManhattan(nodes, node_removed);
        }

        max_nodes = max(max_nodes, (int)nodes.size()); //Get the maximum number of nodes in queue at one time
    }
}

int main() {

    int input;

    int puzzle[3][3] = {{1,2,3},
                        {4,0,6},
                        {7,5,8}};

    cout << "Welcome to Kyle Tran's 8-puzzle solver\n" 
         << "Type 1 to use a default puzzle, or 2 to enter your own puzzle.\n";

    cin >> input;

    switch(input) {
        case 1: //Use default puzzle
            //Prints the default puzzle
            cout << "Using puzzle: (0 is blank space) \n";
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    cout << puzzle[i][j] << " ";                    
                }                
                cout << endl;
            }
            cout << "Enter your choice of algorithm \n" 
                 << "   1. Uniform Cost Search \n"
                 << "   2. A* with the Misplaced Tile heuristic \n"
                 << "   3. A* with the Manhattan distance heuristic \n";

            cin >> input;

            switch(input) {
                case 1: //Uniform cost search
                    cout << "Input : [" << input << "] Solving puzzle with Uniform Cost Search \n";
                    general_search(puzzle, "uniformCostSearch");
                    break;
                case 2: //A* with the Misplaced Tile heuristic
                    cout << "Input : [" << input << "] Solving puzzle with A* with Misplaced Tile heuristic \n";
                    general_search(puzzle, "aWithMisplaced");
                    break;
                case 3: //A* with the Manhattan distance heuristic
                    cout << "Input : [" << input << "] Solving puzzle with A* with Manhattan distance heuristic \n";
                    general_search(puzzle, "aWithManhattan");
                    break;
                default:
                    break;
            }

            break;
        case 2: //Use custom puzzle
            int customPuzzle[3][3];

            cout << "Enter your puzzle, use a zero to represent the blank \n\n";

            cout << "Enter the 1st number of the 1st row \n";
            cin >> customPuzzle[0][0];
            cout << "enter the 2nd number of the 1st row \n";
            cin >> customPuzzle[0][1];
            cout << "enter the 3rd number of the 1st row \n";
            cin >> customPuzzle[0][2];
            cout << "enter the 1nd number of the 2nd row \n";
            cin >> customPuzzle[1][0];
            cout << "enter the 2nd number of the 2nd row \n";
            cin >> customPuzzle[1][1];
            cout << "enter the 3rd number of the 2nd row \n";
            cin >> customPuzzle[1][2];
            cout << "enter the 1st number of the 3rd row \n";
            cin >> customPuzzle[2][0];
            cout << "enter the 2nd number of the 3rd row \n";
            cin >> customPuzzle[2][1];
            cout << "enter the 3rd number of the 3rd row \n";
            cin >> customPuzzle[2][2];

            cout << "Using puzzle: (0 is blank space) \n";
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    cout << customPuzzle[i][j] << " ";                    
                }                
                cout << endl;
            }
            cout << "Enter your choice of algorithm \n" 
                 << "   1. Uniform Cost Search \n"
                 << "   2. A* with the Misplaced Tile heuristic \n"
                 << "   3. A* with the Manhattan distance heuristic \n";

            cin >> input;

            switch(input) {
                case 1: //Uniform cost search
                    cout << "Input : [" << input << "] Solving puzzle with Uniform Cost Search \n";
                    general_search(customPuzzle, "uniformCostSearch");
                    break;
                case 2: //A* with the Misplaced Tile heuristic
                    cout << "Input : [" << input << "] Solving puzzle with A* with Misplaced Tile heuristic \n";
                    general_search(customPuzzle, "aWithMisplaced");
                    break;
                case 3: //A* with the Manhattan distance heuristic
                    cout << "Input : [" << input << "] Solving puzzle with A* with Manhattan distance heuristic \n";
                    general_search(customPuzzle, "aWithManhattan");
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }
    return 0;
}