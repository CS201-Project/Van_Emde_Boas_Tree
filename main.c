//Name: Swapnil Saurav, Entry Number: 2019EEB1204
//Name: Tanishk Gupta, Entry Number: 2019EEB1205
//Name: Yash Jain, Entry Number: 2019EEB1208

#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<stdbool.h>

struct VEB_Node
{
    int U_size;
    int Minimum;
    int Maximum;
    struct VEB_Node *Summary;
    struct VEB_Node **Clusters;
};

typedef struct VEB_Node VEB_Node;

int Cluster_Index(int key,int U_Size)
{
    int divi = ceil(sqrt(U_Size));
    return key / divi;
}

int Pos_In_Cluster(int key,int U_Size)
{
    int mod = ceil(sqrt(U_Size));
    return key % mod;
}

int Gen_Index(int a, int b, int U_Size)
{
    int mul = ceil(sqrt(U_Size));
    return a*mul + b;
}

VEB_Node *Initialize_Tree(int Node_Size)
{
    VEB_Node *ptr=(VEB_Node *)malloc(sizeof(VEB_Node));
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

        ptr->Clusters = (VEB_Node **)malloc(Cluster_Size*sizeof(VEB_Node *));

        for (int i = 0; i < Cluster_Size; i++)
        {
            ptr->Clusters[i]=NULL;
        }

        for (int i = 0; i < Cluster_Size; i++)
        {
            ptr->Clusters[i] = Initialize_Tree(ceil(sqrt(Node_Size)));
        }
    }
    return ptr;
}

int main()
{
    VEB_Node* akp = Initialize_Tree(4);
    printf("%d\n",Cluster_Index(2,akp->U_size));
    printf("%d\n",Pos_In_Cluster(2,akp->U_size));
    return 0;
}





