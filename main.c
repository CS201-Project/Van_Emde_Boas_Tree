//Name: Swapnil Saurav, Entry Number: 2019EEB1204
//Name: Tanishk Gupta, Entry Number: 2019EEB1205
//Name: Yash Jain, Entry Number: 2019EEB1208

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

void Swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

struct VEB_Node
{
    int U_size;
    int Minimum;
    int Maximum;
    struct VEB_Node *Summary;
    struct VEB_Node **Clusters;
};

typedef struct VEB_Node VEB_Node;

// Initialize an empty array
VEB_Node *Initialize_Tree(int Node_Size)
{
    VEB_Node *ptr = (VEB_Node *)malloc(sizeof(VEB_Node));
    ptr->U_size = Node_Size;
    ptr->Minimum = -1;
    ptr->Maximum = -1;

    if (Node_Size <= 2)
    {
        ptr->Clusters = NULL;
        ptr->Summary = NULL;
    }
    else
    {
        int Cluster_Size = ceil(sqrt(Node_Size));

        ptr->Summary = Initialize_Tree(Cluster_Size);

        ptr->Clusters = (VEB_Node **)malloc(Cluster_Size * sizeof(VEB_Node *));

        for (int i = 0; i < Cluster_Size; i++)
        {
            ptr->Clusters[i] = NULL;
        }

        for (int i = 0; i < Cluster_Size; i++)
        {
            ptr->Clusters[i] = Initialize_Tree(ceil(sqrt(Node_Size)));
        }
    }
    return ptr;
}

// Insert helper function
VEB_Node *Insert_In_Empty(VEB_Node *root, int x)
{
    root->Minimum = x;
    root->Maximum = x;
    return root;
}

// Insert Function
VEB_Node *Insert(VEB_Node *root, int x)
{
    if(x<0 || x>=root->U_size)
    {
        printf("Query out of bounds!!!\n");
        return root;
    }
    if (root->Minimum == -1)
    {
        root = Insert_In_Empty(root, x);
    }
    else
    {
        if (x < root->Minimum)
        {
            Swap(&x, &(root->Minimum));
        }
        if (root->U_size > 2)
        {
            int k = ceil(sqrt(root->U_size));
            if ((root->Clusters[x / k])->Minimum == -1)
            {
                root->Summary = Insert(root->Summary, x / k);
                root->Clusters[x / k] = Insert_In_Empty(root->Clusters[x / k], x % k);
            }
            else
            {
                root->Clusters[x / k] = Insert(root->Clusters[x / k], x % k);
            }
        }
        if (x > root->Maximum)
        {
            root->Maximum = x;
        }
    }
    return root;
}

// Ispresent function
bool IsPresent(VEB_Node *root, int x)
{
    if (x >= root->U_size || x < 0)
    {
        printf("Query is Out of Bounds\n");
        return false;
    }
    if (root->Maximum == x || root->Minimum == x)
    {
        return true;
    }
    if (root->U_size == 2)
    {
        return false;
    }
    int k = ceil(sqrt(root->U_size));
    return IsPresent(root->Clusters[x / k], x % k);
}

// Print
void Print_Tree(VEB_Node *root, int t)
{
    if (root)
    {
        printf("|");
        for(int i=0;i<root->U_size;i++)
        {
            printf(" %d -> %d |",i,IsPresent(root,i));
        }
        printf("\n");
    }
    else printf("Tree is empty.\n");
}

// Successor
int Successor(VEB_Node *root, int x)
{
    int k = ceil(sqrt(root->U_size));
    if (root->U_size == 2)
    {
        if (x == 0 && root->Maximum == 1)
        {
            return 1;
        }
        else
        {
            return -1;
        }
    }
    else if (root->Minimum != -1 && x < root->Minimum)
    {
        return root->Minimum;
    }
    else
    {
        int max_cluster = (root->Clusters[x / k])->Maximum;
        if (max_cluster != -1 && x % k < max_cluster)
        {
            int temp = Successor(root->Clusters[x / k], x % k);
            return (temp + (x / k) * k);
        }
        else
        {
            int successor_cluster = Successor(root->Summary, x / k);
            if (successor_cluster != -1)
            {
                int temp = (root->Clusters[successor_cluster])->Minimum;
                return (temp + successor_cluster * k);
            }
            else
            {
                return -1;
            }
        }
    }
}

// Predecessor function
int Predecessor(VEB_Node *root, int x)
{

    int k = ceil(sqrt(root->U_size));

    if (root->U_size == 2)
    {
        if (x == 1 && root->Minimum == 0)
        {
            return 0;
        }
        else
        {
            return -1;
        }
    }
    else if (root->Maximum != -1 && x > root->Maximum)
    {
        return root->Maximum;
    }

    else
    {
        int min_cluster = (root->Clusters[x/k])->Minimum;
        if (min_cluster != -1 && x%k > min_cluster)
        {
            int temp = Predecessor(root->Clusters[x/k], x%k);
            return (temp + (x / k) * k);
        }
        else
        {
            int pr_cluster = Predecessor(root->Summary, x/k);
            if (pr_cluster == -1)
            {
                if(root->Minimum != -1 && x > root->Minimum){
                    return root->Minimum;
                }
                else{
                    return -1;
                }
            }
            else
            {
                int temp = (root->Clusters[pr_cluster])->Maximum;
                return (temp + (pr_cluster * k));
            }
        }
    }
}

// Delete function
VEB_Node *Delete_Element(VEB_Node *root, int x)
{
    int k = ceil(sqrt(root->U_size));
    if (root->Minimum == root->Maximum)
    {
        root->Minimum = -1;
        root->Maximum = -1;
    }
    else if (root->U_size == 2)
    {
        if (x == 0)
            root->Minimum = 1;
        else
            root->Minimum = 0;

        root->Maximum = root->Minimum;
    }
    else
    {
        if (x == root->Minimum)
        {
            int Cluster_One = (root->Summary)->Minimum;
            x = Cluster_One * k + (root->Clusters[Cluster_One])->Minimum;
            root->Minimum = x;
        }
        root->Clusters[x / k] = Delete_Element(root->Clusters[x / k], x % k);
        if ((root->Clusters[x / k])->Minimum == -1)
        {
            root->Summary = Delete_Element(root->Summary, x / k);
            if (x == root->Maximum)
            {
                int temp = (root->Summary)->Maximum;
                if (temp == -1)
                    root->Maximum = root->Minimum;
                else
                    root->Maximum = temp * k + +(root->Clusters[temp])->Maximum;
            }
        }
        else if (x == root->Maximum)
            root->Maximum = (x / k) * k + (root->Clusters[x / k])->Maximum;
    }
    return root;
}

int main()
{
    int n;
    printf("Enter the size of array: ");
    scanf("%d", &n);
    VEB_Node *tree = Initialize_Tree(n);
    int nn;
    printf("How many integers are present? ");
    scanf("%d", &nn);
    printf("Enter %d values:", nn);
    for (int i = 0; i < nn; i++)
    {
        int node_val;
        scanf("%d", &node_val);
        tree = Insert(tree, node_val);
    }
    while (1)
    {
        int query;
        printf("Enter 1 to Insert an element\nEnter 2 to search an element\nEnter 3 to find predesessor of element\nEnter 4 to find successor of element\nEnter 5 to delete an element\nEnter 6 to display the tree\nEnter 7 to get minimum\nEnter 8 to get maximum\nEnter 9 to exit\n");
        scanf("%d", &query);
        if(query == 1)
        {
            int val;
            printf("Enter number to insert: ");
            scanf("%d",&val);
            Insert(tree,val);
        }
        else if (query == 2)
        {
            int val;
            printf("Enter number to search: ");
            scanf("%d", &val);
            if (IsPresent(tree, val))
            {
                printf("Present\n");
            }
            else
            {
                printf("Not Present\n");
            }
        }
        else if (query == 3)
        {
            int val;
            printf("Enter number to find the predecessor: ");
            scanf("%d", &val);
            if (Predecessor(tree, val) != -1)
            {
                int pred = Predecessor(tree, val);
                printf("Predecessor of %d is %d\n", val, pred);
            }
            else
            {
                printf("No predecessor\n");
            }
        }
        else if (query == 4)
        {
            int val;
            printf("Enter number to find the successor: ");
            scanf("%d", &val);
            if (Successor(tree, val) != -1)
            {
                int succ = Successor(tree, val);
                printf("Successor of %d is %d\n", val, succ);
            }
            else
            {
                printf("No successor\n");
            }
        }
        else if (query == 5)
        {
            int val;
            printf("Enter number to delete: ");
            scanf("%d", &val);
            tree = Delete_Element(tree, val);
        }
        else if (query == 6)
        {
            Print_Tree(tree, 0);
        }
        else if(query == 7){
             printf("Minimum element is %d\n",tree->Minimum);
        }
        else if(query == 8){
            printf("Maximum element is %d\n",tree->Maximum);
        }
        else
        {
            break;
        }
    }
}
