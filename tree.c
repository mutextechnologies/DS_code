
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
typedef struct QNode
{
    void *data;
    struct QNode *next;
} QNode;

typedef struct Queue
{
    struct QNode *front;
    struct QNode *rear;
} Queue;

QNode *getQNode(void *data)
{
    QNode *q = (QNode *)malloc(sizeof(QNode));
    q->data = data;
    q->next = NULL;
    return q;
}
void enQueue(Queue *q, void *data)
{
    QNode *newNode = getQNode(data);
    if (q->front == NULL)
    {
        q->front = newNode;
        q->rear = newNode;
        return;
    }
    q->rear->next = newNode;
    q->rear = newNode;
}
void *dQueue(Queue *q)
{
    QNode *temp;
    void *d;
    if (q->front == NULL)
    {
        return NULL;
    }
    temp = q->front;
    d = q->front->data;
    q->front = q->front->next;
    free(temp);
    if (q->front == NULL)
    {
        q->rear = NULL;
    }
    return d;
}

int isEmpty(Queue *q)
{
    return q->front == NULL;
}

typedef struct TNode
{
    struct TNode *left;
    int data;
    struct TNode *right;
} TNode;

TNode *newTNode(int data)
{
    TNode *newNode = (TNode *)malloc(sizeof(TNode));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}
void insertBTree(TNode **root, int data)
{
    Queue *q = NULL;
    TNode *newNode = newTNode(data);
    q = (Queue *)malloc(sizeof(Queue));
    q->front = NULL;
    q->rear = NULL;
    if (*root == NULL)
    {
        *root = newNode;
        return;
    }
    enQueue(q, *root);
    while (1)
    {
        TNode *n = NULL;
        void *node = dQueue(q);
        n = (TNode *)node;
        if (n->left == NULL)
        {
            n->left = newNode;
            return;
        }
        enQueue(q, n->left);
        if (n->right == NULL)
        {
            n->right = newNode;
            return;
        }
        enQueue(q, n->right);
    }
}

void preOrderR(TNode *root)
{
    if (root == NULL)
    {
        return;
    }
    printf("%d\t", root->data);
    preOrderR(root->left);
    preOrderR(root->right);
}

void inOrderR(TNode *root)
{
    if (root == NULL)
    {
        return;
    }
    inOrderR(root->left);
    printf("%d\t", root->data);
    inOrderR(root->right);
}

void postOrderR(TNode *root)
{
    if (root == NULL)
    {
        return;
    }
    postOrderR(root->left);
    postOrderR(root->right);
    printf("%d\t", root->data);
}

int max(int num1, int num2)
{
    return num1 > num2 ? num1 : num2;
}

int height(TNode *root)
{
    int lh, rh, maxH;
    if (root == NULL)
    {
        return 0;
    }
    lh = height(root->left);
    rh = height(root->right);
    maxH = max(lh, rh);
    return maxH + 1;
}

int sumR(TNode *root)
{
    if (root == NULL)
    {
        return 0;
    }
    return root->data + sumR(root->left) + sumR(root->right);
}

Queue *createNewQueue()
{
    Queue *q = (Queue *)malloc(sizeof(Queue));
    q->front = NULL;
    q->rear = NULL;
    return q;
}

void levelOrderBTree(TNode *root)
{
    Queue *q = createNewQueue();
    TNode *n = NULL;
    void *node = NULL;
    if (root == NULL)
    {
        printf("Empty Tree..");
        return;
    }
    n = root;
    do
    {
        printf("%d\t", n->data);
        if (n->left != NULL)
        {
            enQueue(q, n->left);
        }
        if (n->right != NULL)
        {
            enQueue(q, n->right);
        }
        node = dQueue(q);
        n = (TNode *)node;

    } while (!isEmpty(q));
    printf("%d\n", n->data);
}

int main()
{
    TNode *root = NULL;

    insertBTree(&root, 10);
    insertBTree(&root, 20);

    insertBTree(&root, 30);
    insertBTree(&root, 40);
    insertBTree(&root, 50);
    insertBTree(&root, 60);
    insertBTree(&root, 70);
    printf("%d\t", height(root));

    // printf("%d\t", sumR(root));

    // levelOrderBTree(root);
    // preOrderR(root);
    // inOrderR(root);
    // postOrderR(root);
}