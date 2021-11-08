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




// print
void Print_Tree(VEB_Node* root , int t=0){
    if (root){
        for(int i=0 ; i<t ; i++){
            printf("\t");
        }
        printf("Summary: %d ( %d , %d )\n",root->U_Size,root->Minimum,root->Maximum);
        if (root->U_Size !=2 ){
            Print_Tree(root->Summary,t+1);
        }
        if (root->U_Size !=2){
            for (int i=0; i<=t ; i++){
                printf("\t");
            }
            printf("Cluster: %d\n",root->U_Size);
            int k = ceil(sqrt(root->U_size));
            for (int i=0;i < k;i++){
                Print_Tree(root->Cluster[i],t+1);
            }
        }
      
    }
}

// successor
int Successor (VEB_Node* root , int x){
    int k = ceil(sqrt(root->U_size));
    int max_cluster = (root->Cluster[x/k])->Maximum;
    if (root->U_Size==2){
        if (x==0 && root->Maximum==1){
            return 1;
        }
        else {
            return -1;
        }
    }
    else if(root->Minimum != -1 && x < root->Minimum){
        return root->Minimum;
    }
    else {
        if (max_cluster != -1 && x%k < max_cluster){
            int temp=Successor(root->Cluster[x/k],x%k);
            return (temp+(x/k)*k);
        }
        else {
            int successor_cluster = Successor(root->Summary,x/k);
            if (successor_cluster != -1){
                int temp=(root->Cluster[x/k])->Minimum;
                return (temp + successor_cluster*k);
            }
            else {
                return -1;
            }
        } 

    }
}

int main()
{
    VEB_Node* akp = Initialize_Tree(4);
    printf("%d\n",Cluster_Index(2,akp->U_size));
    printf("%d\n",Pos_In_Cluster(2,akp->U_size));
    return 0;
}






