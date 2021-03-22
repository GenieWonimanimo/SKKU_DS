#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>


//트리노드가 하위 노드의 합을 가지고 있다. 이경우에는 delete이 노드를 할당해제하지 않는다.

typedef struct _node
{
   int grade;
   int q_val;
   int sub_sum;
   struct _node* left;
   struct _node* right;
} node;

typedef struct _tree
{
   node * root;
} tree;

void insert_node(tree* inv, int grade, int qt);
void delete_node(tree* inv, int grade, int qt);
int getSubsumleft(node* n, int l);
int getSubsumright(node* n, int r);
int count(tree* inv, int grade);
int range(tree* inv, int l, int r);
int top(tree* inv, int r);
int getGrade(node* n, int m);

enum { INSERT = 'I', DELETE = 'D', COUNT = 'C', RANGECOUNT = 'R', TOP = 'T' };

int main() {
    tree* inventory = (tree * )malloc(sizeof(node)); // Initial state of tree
    inventory->root = NULL;
    int N;
    scanf(" %d", &N);
    for (int i = 0; i < N; i++)
    {
        char option;
        int n, m;
        int temp;
        scanf(" %c", &option);
        switch (option)
        {
        case INSERT:
            scanf(" %d %d", &n, &m);
            insert_node(inventory, n, m);
            break;
        case DELETE:
            scanf(" %d %d", &n, &m);
            delete_node(inventory, n, m);
            break;
        case COUNT:
            scanf(" %d", &n);
            temp = count(inventory, n);
            printf("%d\n", (temp == -1)? 0:temp);
            break;
        case RANGECOUNT:
            scanf(" %d %d", &n, &m);
            printf("%d\n", range(inventory, n, m));
            break;
        case TOP:
            scanf(" %d", &n);
            printf("%d\n", top(inventory, n));
            break;
        default:
            exit(1);
        }
    }
    return 0;
}

void insert_node(tree* inv, int grade, int qt)
{
    if (inv->root == NULL) {
        //노드가 없을경우 새 노드로 헤드에 추가한다.
        node* temp_node = (node*)malloc(sizeof(node)); // sizeof(node) byte 의 메모리 할당
        temp_node->grade = grade; // 새로운 노드에 값 저장
        temp_node->sub_sum = qt; // 새 노드의 새 노드를 포함한 서브트리의 양의 합은 qt이다.
        temp_node->q_val = qt;
        temp_node->left = NULL; // 첫 노드이기 때문에 왼쪽 자식과 오른쪽 자식이 없기 때문에 NULL 로 초기화한다.
        temp_node->right = NULL;
        inv->root = temp_node; // 할당한 노드를 루트포인터가 가리키게 한다.
        return; // 첫 노드를 만들었다면 종료한다
    }
    // 첫 노드가 아니라면
    node* p_cursor = NULL; // 부모를 가리키는 커서를 NULL로 초기화한다
    node* cursor = inv->root; // 최초 커서포인터를 루트노드를 가리키게 한다
    //커서 루프. 만약 커서가 널일 경우 루프를 종료한다.
    while (cursor != NULL) {
        //메모이제이션 사용시: 커서의 수량에 qt를 더한다.
        cursor->sub_sum += qt;
        //커서의 등급이 grade일경우 qt에 합한다.
        if (cursor->grade == grade) {
            cursor->q_val += qt;
            return;
        //이경우엔 리턴하여 함수를 종료한다.
        }
        //아닐경우 grade 와 비교하여 자식의 노드로 향한다.
        if (cursor->grade > grade) { // 커서의 등급이 인자로 grade 보다 크다면 커서를 왼쪽 자식으로 이동시킨다.
            p_cursor = cursor; // 커서가 자식으로 이동하기 전에 부모를 가리키는 포인터에 커서의 주소 값을 저장해둔다.
            cursor = cursor->left;
        }
        else { // 커서의 등급이 grade보다 작다면 커서를 오른쪽 자식으로 이동시킨다.
            p_cursor = cursor; // 커서가 자식으로 이동하기 전에 부모를 가리키는 포인터에 커서의 주소 값을 저장해둔다.
            cursor = cursor->right;
        }
    }
    //루프에서 빠져나왔다면 커서에 새 노드를 만들고 부모 노드에 잇는다.
    cursor = (node*)malloc(sizeof(node));
    cursor->grade = grade;
    cursor->q_val = qt;
    cursor->sub_sum = qt;
    cursor->left = NULL;
    cursor->right = NULL;
    
    if (p_cursor->grade > grade) { // 부모 노드의 등급이 grade 보다 크다면 새로 만든 노드를 왼쪽 자식으로 만든다.
        p_cursor->left = cursor;
    }
    else { // 부모 노드의 등급이 grade 보다 작다면 새로 만든 노드를 오른쪽 자식으로 만든다.
        p_cursor->right = cursor;
    }
}

void delete_node(tree* inv, int grade, int qt) {
    //루트가 널이면 아무것도 하지 않는다.
    if (inv->root == NULL) {
        return;
    }
    //
    int temp = count(inv, grade); // count 함수는 등급이 grade 인 노드를 찾았다면 해당 노드의 다이아 수를, 찾지 못했다면 -1을 반환한다.
    if (temp == -1) { // 찾지 못했다면,
        return; // 지울 노드가 없으므로 함수를 종료한다.
    }
    int havingqt = temp < qt ? temp : qt; // qt 만큼의 다이아를 줄인다고 할 때,  다이아의 수가 음수일 수는 없기 때문에 
                                         //해당 grade 의 다이아 수가 qt보다 작다면 가지고 있는 다이아의 수를 줄일 다이아 수로 정한다.
    node* cursor = inv->root; // 커서는 루트를 가리킨다.
    while (cursor != NULL) { // 커서 루프, 다이아 양을 줄일 노드를 찾는다.
        cursor->sub_sum -= havingqt; // 루프를 돌 때마다 찾으러 가는 길의 노드의 서브트리의 다이아 수를 줄인다.
        assert(cursor->sub_sum >= 0);  
        if (cursor->grade == grade) { // 대상 노드를 찾았다면,
            cursor->q_val -= havingqt; // 다이아 수를 줄인다.
            return; // 다이아 수를 줄이는 데에 성공하였으므로 함수를 종료한다.
        }
        if (cursor->grade > grade) { // 커서가 가리키는 노드의 등급이 grade보다 크다면
            cursor = cursor->left; // 커서를 왼쪽으로 이동시킨다.
        }
        else { // 커서가 가리키는 노드의 등급이 grade보다 작다면
            cursor = cursor->right; // 커서를 오른쪽으로 이동시킨다.
        }
    }
}

int count(tree* inv, int grade) {
    if (inv->root == NULL) { // 트리가 비어있다면
        return -1; // 원하는 노드를 찾을 수 없으므로 -1을 반환한다.
    }
    node* cursor = inv->root; // 커서를 root로 초기화한다.
    while (cursor != NULL) { // 커서 루프, 커서가 널이면 루프를 빠져나간다.
        if (cursor->grade == grade) { // 등급이 grade 인 노드를 찾았다면,
            return cursor->q_val; // 해당 노드의 다이아 수를 반환한다.
        }
        if (cursor->grade > grade) { // 커서의 등급이 grade보다 크다면,
            cursor = cursor->left; // 커서를 왼쪽으로 이동시킨다.
        }
        else { // 커서의 등급이 grade보다 작다면,
            cursor = cursor->right; // 커서를 오른쪽으로 이동시킨다.
        }
    }
    return -1; // 루프를 빠져나왔다면 찾지 못했다는 뜻이므로 -1을 반환한다.
}

int range(tree* inv, int l, int r) // l <= grade <= r 인 다이아 수를 반환한다.
{
    if (l == r) { // l과 r이 같다면,
        return count(inv, l); // 등급이 l 인 다이아 수를 반환한다.
    }
    else { // l과 r이 다르다면, (l < r)
        return inv->root->sub_sum - getSubsumleft(inv->root, l) - getSubsumright(inv->root, r); 
        // 모든 다이아의 수에서 l보다 등급이 낮은 다이아의 수, r보다 등급이 높은 다이아의 수를 뺀 값을 반환한다.
    }
    return 0;
}

int top(tree* inv, int n)
{
    if (inv->root == NULL) return -1; // 트리가 비어있다면, -1을 반환한다.
    return getGrade(inv->root, n);
}

int getGrade(node* n, int m)
{
    int result = 0;
    // node null 제외
    if (n == NULL) return -1;
    // m 0 보다 커야함
    // subsum 0보다 커야함
    if (m < 1 || n->sub_sum < 1) return -1;
    if (n->sub_sum < m) return -1;

    int lss = 0;
    if (n->left != NULL && n->left->sub_sum) lss = n->left->sub_sum;
    if (lss != 0 && m <= lss) { // n의 왼쪽 서브트리의 합이 0이 아니고 그 합보다 m이 작을 때
        return getGrade(n->left,m);
    }else if(m <= lss + n->q_val){
        return n->grade;
    }
    else {
        assert((m - lss + n->q_val) > 0);
        return getGrade(n->right, m - lss - n->q_val);
    }
    return -1;
}

int getSubsumleft(node* n, int l) {
    int result = 0;
    if (n == NULL) return 0; // 전달된 노드가 없다면, 0을 반환한다.
    if (n->grade == l) { // 노드의 등급이 l과 같다면,
        if (n->left != NULL) result = n->left->sub_sum; // 왼쪽 서브트리의 합을 result에 저장한다.
//        return result += n->q_val;
        return result; // result 를 반환한다.
    }
    if (n->grade < l) { // 노드의 등급이 l보다 작다면,
        if (n->left != NULL) result = n->left->sub_sum; // 왼쪽 서브트리의 합을 result에 저장한다.
        result += n->q_val; // 노드의 다이아 수도 더한다.
        return result + getSubsumleft(n->right, l); // 노드의 오른쪽 자식노드에 대해 반복한다.
    }
    else { // 노드의 등급이 l보다 크다면,
        return getSubsumleft(n->left, l); // 왼쪽 자식노드에 대해 반복한다. 
    }
}


int getSubsumright(node* n, int r) {
    int result = 0;
    if (n == NULL) return 0; // 전달된 노드가 없다면, 0을 반환한다.
    if (n->grade == r) { // 노드의 등급이 r과 같다면,
        if (n->right != NULL) result = n->right->sub_sum;
//        return result += n->q_val;
        return result; // 오른쪽 서브트리의 합을 반환한다.
    }
    if (n->grade > r) { // 노드의 등급이 r보다 크다면,
        if (n->right != NULL) result = n->right->sub_sum;
        result += n->q_val;
        return result + getSubsumright(n->left, r); // 오른쪽 서브트리의 합과 노드의 다이아 양 + 노드의 왼쪽 자식에 대해 반복한 값을 반환한다.
    }
    else { // 노드의 등급이 r보다 작다면, 
        return getSubsumright(n->right, r); // 오른쪽 자식노드에 대해 반복한다.
    }
}