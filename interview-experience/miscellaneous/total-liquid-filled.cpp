#include <iostream>
#include <map>
#include <vector>
using namespace std;

int totalLiquidFilled(vector<vector<int>> matrix) {
    int m = matrix.size();
    int n = matrix[0].size();
    vector<vector<int>> left(m, vector<int>(n, 0));
    vector<vector<int>> right(m, vector<int>(n, 0));
    vector<vector<int>> top(m, vector<int>(n, 0));
    vector<vector<int>> bottom(m, vector<int>(n, 0));

    for(int i=0; i<m; i++){
        for(int j=0; j<n; j++){
            if(i==0) top[i][j] = matrix[i][j];
            else top[i][j] = max(top[i-1][j], matrix[i][j]);

            if(j==0) left[i][j] = matrix[i][j];
            else left[i][j] = max(left[i][j-1], matrix[i][j]);
        }
    }

    for(int i=m-1; i>=0; i--){
        for(int j=n-1; j>=0; j--){
            if(i==m-1) bottom[i][j] = matrix[i][j];
            else bottom[i][j] = max(bottom[i+1][j], matrix[i][j]);

            if(j==n-1) right[i][j] = matrix[i][j];
            else right[i][j] = max(right[i][j+1], matrix[i][j]);
        }
    }

    int total = 0;
    for(int i=0; i<m; i++){
        for(int j=0; j<n; j++){
            total += min({top[i][j], bottom[i][j], left[i][j], right[i][j]}) - matrix[i][j];
        }
    }
    return total;
}

int main() {
    int m, n;
    cin >> m >> n;
    vector<vector<int>> matrix(m, vector<int>(n));
    for(int i=0; i<m; i++){
        for(int j=0; j<n; j++){
            cin >> matrix[i][j];
        }
    }
    cout << totalLiquidFilled(matrix) << endl;
    return 0;
}

void Multiply(node *p, node *q, node *result) {
    map<pair<int, int>, int> resultMap;
    node *pRow = p->down;
    while (pRow != NULL) {
        node *qCol = q->right;
        while (qCol != NULL) {
            node *pTemp = pRow->right, *qTemp = qCol->down;
            int sum = 0;
            while (pTemp != NULL && qTemp != NULL) {
                if (pTemp->colno < qTemp->rowno) {
                    pTemp = pTemp->right;
                } else if (pTemp->colno > qTemp->rowno) {
                    qTemp = qTemp->down;
                } else {
                    sum += pTemp->value * qTemp->value;
                    pTemp = pTemp->right;
                    qTemp = qTemp->down;
                }
            }
            if (sum != 0) {
                resultMap[{pRow->rowno, qCol->colno}] = sum;
            }
            qCol = qCol->right;
        }
        pRow = pRow->down;
    }

    for (auto it : resultMap) {
        int i = it.first.first, j = it.first.second, val = it.second;
        node *dwn = result, *rgt = result;
        while (dwn->down != NULL && dwn->down->rowno < i)
            dwn = dwn->down;
        while (rgt->right != NULL && rgt->right->colno < j)
            rgt = rgt->right;
        node *newnode = new node(i, j, rgt->right, dwn->down, val);
        dwn->down = newnode;
        rgt->right = newnode;
    }
}
