//Name: Swapnil Saurav, Entry Number: 2019EEB1204
//Name: Tanishk Gupta, Entry Number: 2019EEB1205
//Name: Yash Jain, Entry Number: 2019EEB1208

#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<stdbool.h>

void Swap(int *a, int* b){
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


//insert function 
VEB_Node* Insert_In_Empty(VEB_Node* root, int x){

    root->Minimum  =  x;
    root->Maximum  =  x;
    return root;

}

VEB_Node* Insert(VEB_Node* root, int x){
    
    if(root->Minimum  ==  -1){
        root = Insert_In_Empty(root,x);
    }
    else{
        if(x < root->Minimum){
            Swap(&x, &(root->Minimum));
        }
        if(root->U_size > 2){
            int k = ceil(sqrt(root->U_size));
            if((root->Clusters[x/k])->Minimum == -1){
                root->Summary = Insert(root->Summary, x/k);
                root->Clusters[x/k] = Insert_In_Empty(root->Clusters[x/k], x%k);
            }
            else{
               root->Clusters[x/k] =  Insert(root->Clusters[x/k], x%k);
            }
        }
        if(x > root->Maximum){
            root->Maximum = x;
        }
    }
    return root;
}

bool IsPresent(VEB_Node *root, int x){
    
    if(root->Maximum == x || root->Minimum == x){
        return true;
    }
    if(root->U_size == 2){
        return false;
    }
    int k = ceil(sqrt(root->U_size));
    return IsPresent(root->Clusters[x/k], x%k);

}

int main()
{
    VEB_Node* akp = Initialize_Tree(4);
    printf("%d\n",Cluster_Index(2,akp->U_size));
    printf("%d\n",Pos_In_Cluster(2,akp->U_size));
    return 0;
}






