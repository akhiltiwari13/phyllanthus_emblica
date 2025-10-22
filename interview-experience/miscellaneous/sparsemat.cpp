#include <cstddef>
#include <iostream>
using namespace std;

// The struct contains its column number, row number, a right and a down pointer,
// and its value. The actual matrix nodes are one indexed while the margin ones
// have either coordinate equal to zero. In c++, nodes can also have a constructor
// as used below
typedef struct node {
    int colno;
    int rowno;
    node *right;
    node *down;
    int value;
    node(int row, int col, node *r, node *d, int val) {
        colno = col;
        rowno = row;
        right = r;
        down = d;
        value = val;
    }
    node() {
        colno = rowno = 0;
        right = down = NULL;
        value = -1;
    }
} node;

// Multiplication function takes in two head pointers and stores the result in
// node *result



void insertIntoResultMatrix(node* result, int row, int col, int value) {
    // Navigate to the correct row
    node* rowPtr = result;
    while (rowPtr->down != NULL && rowPtr->down->rowno < row)
        rowPtr = rowPtr->down;

    // Navigate to the correct column
    node* colPtr = result;
    while (colPtr->right != NULL && colPtr->right->colno < col)
        colPtr = colPtr->right;

    // Check if the node already exists
    node* current = rowPtr->right;
    while (current != NULL && current->colno < col)
        current = current->right;

    if (current != NULL && current->colno == col) {
        // Node exists, update value
        current->value += value;
    } else {
        // Create new node
        node* newNode = new node(row, col, current, rowPtr->down, value);
        rowPtr->down = newNode;
        colPtr->right = newNode;
    }
}


void Multiply(node *p, node *q, node *result) {

    node *rowP = p->down; // Starting from the first row of p

    while (rowP != NULL) {
        node *colQ = q->right; // Starting from the first column of q

        while (colQ != NULL) {
            int sum = 0;

            node *elementP = rowP->right; // Elements in the current row of p
            node *elementQ = colQ->down;  // Elements in the current column of q

            while (elementP != NULL && elementQ != NULL) {
                if (elementP->colno < elementQ->rowno) {
                    elementP = elementP->right;
                } else if (elementP->colno > elementQ->rowno) {
                    elementQ = elementQ->down;
                } else {
                    sum += elementP->value * elementQ->value;
                    elementP = elementP->right;
                    elementQ = elementQ->down;
                }
            }

            if (sum != 0) {
                // Insert sum into the result matrix
                // You would need a function to insert a new value into the result sparse matrix
                // This function is not implemented here
                insertIntoResultMatrix(result, rowP->rowno, colQ->colno, sum);
            }

            colQ = colQ->right;
        }

        rowP = rowP->down;
    }

}





void Print(node *nd) {
    node *rowsl = nd->down;
    while (rowsl != NULL) {
        node *clsl = rowsl->right;
        while (clsl != NULL) {
            cout << clsl->rowno << " " << clsl->colno << " " << clsl->value << "\n";
            clsl = clsl->right;
        }
        rowsl = rowsl->down;
    }
}

int main() {
    int n;
    scanf("%d", &n);
    node root[3] = {};
    node *prevn[3] = {&root[0], &root[1], &root[2]};
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < 3; j++) {
            prevn[j]->right = new node(0, i, NULL, NULL, -1);
            prevn[j] = prevn[j]->right;
        }
    }
    prevn[0] = &root[0];
    prevn[1] = &root[1];
    prevn[2] = &root[2];
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < 3; j++) {
            prevn[j]->down = new node(i, 0, NULL, NULL, -1);
            prevn[j] = prevn[j]->down;
        }
    }
    node *topsl[2] = {&root[0], &root[1]};
    node *rowsl[2] = {&root[0], &root[1]};

    int matno;
    scanf("%d", &matno);
    matno -= 1;
    while (matno != -1) {
        int i, j, val;
        scanf("%d %d %d", &i, &j, &val);

        if (rowsl[matno]->rowno > i)
            rowsl[matno] = &root[matno];
        if (topsl[matno]->colno > j)
            topsl[matno] = &root[matno];
        while (rowsl[matno]->rowno != i)
            rowsl[matno] = rowsl[matno]->down;
        while (topsl[matno]->colno != j)
            topsl[matno] = topsl[matno]->right;
        node *dwn = topsl[matno], *rgt = rowsl[matno];
        while (dwn->down != NULL && dwn->down->rowno < i)
            dwn = dwn->down;
        while (rgt->right != NULL && rgt->right->colno < j)
            rgt = rgt->right;

        node *newnode = new node(i, j, rgt->right, dwn->down, val);
        dwn->down = newnode;
        rgt->right = newnode;

        scanf("%d", &matno);
        matno -= 1;
    }

    Multiply(&root[0], &root[1], &root[2]);
    Print(&root[2]);
    return 0;
}
