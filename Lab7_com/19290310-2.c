#include<stdio.h>
#include<stdlib.h>
 
int parentKey; 
int firstControl=1;
 
 
struct node
{
    int key;
    struct node *left;
    struct node *right;
    int height;
};
 
int extremum(int a, int b);
 
int height(struct node *N)
{
    if (N == NULL)
        return 0;
    return N->height;
}
 
int extremum(int a, int b)
{
    return (a > b)? a : b;
}
 
struct node* newnode(int key)
{
    struct node* node = (struct node*)
                        malloc(sizeof(struct node));
    node->key   = key;
    node->left   = NULL;
    node->right  = NULL;
    node->height = 1;
    return(node);
}
 
struct node *rightRotate(struct node *y)
{
    struct node *x = y->left;
    struct node *lft = x->right;
 

    x->right = y;
    y->left = lft;
 

    y->height = extremum(height(y->left), height(y->right))+1;
    x->height = extremum(height(x->left), height(x->right))+1;
 

    return x;
}

struct node *leftRotate(struct node *x)
{
    struct node *y = x->right;
    struct node *lft = y->left;
 
    y->left = x;
    x->right = lft;
 
    x->height = extremum(height(x->left), height(x->right))+1;
    y->height = extremum(height(y->left), height(y->right))+1;
 
    return y;
}
 
int getBalance(struct node *N)
{
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

struct node* insert(struct node* node, int key)
{
    if (node == NULL)
        return(newnode(key));
 
    if (key < node->key)
        node->left  = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else 
        return node;
 

    node->height = 1 + extremum(height(node->left),
                           height(node->right));
 

    int balance = getBalance(node);
 
 

    if (balance > 1 && key < node->left->key)
        return rightRotate(node);
 

    if (balance < -1 && key > node->right->key)
        return leftRotate(node);
 

    if (balance > 1 && key > node->left->key)
    {
        node->left =  leftRotate(node->left);
        return rightRotate(node);
    }
 

    if (balance < -1 && key < node->right->key)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
 

    return node;
}

void preOrder(struct node *tree)
{
    if(tree != NULL)
    {
        
        preOrder(tree->left);
        printf("%d\n", tree->key);
        preOrder(tree->right);
    }
}
 
int treeLength(struct node *tree)
{
    int extremum;
    if (tree!=NULL)
    {

        int leftSide = treeLength(tree->left);
        int rightSide = treeLength(tree->right);
        if (leftSide > rightSide)
        {
            extremum = leftSide + 1;
            return extremum;
        }
        else
        {
            extremum = rightSide + 1;
            return extremum;
        }
    }
}

void currentlevel(struct node *tree, int level,int isRight)
{
    if (tree != NULL) 
    {
        if (level == 1)
        {
                if(firstControl==1){
                    printf("%d (%d B) ",tree->key,getBalance(tree));
                    firstControl=0;
                }
                else
                    if(isRight==1)
                        printf("%d (%d R) (%d B) ",tree->key,parentKey,getBalance(tree));
                        
                    else 
                        printf("%d (%d L) (%d B) ",tree->key,parentKey,getBalance(tree));
        
          
        }
        else if (level > 1) 
        { 
            parentKey = tree->key;
            currentlevel(tree->left, level-1,0);
            currentlevel(tree->right, level-1,1);
            
        }			
    }
} 
 
 
 
int main()
{
  struct node *tree = NULL;
 
  int key;
  scanf("%d",&key);
  while(key!=-1){
  	tree=insert(tree,key);
  	scanf("%d",&key);
  }
 
    preOrder(tree);
    printf("\n");
    int height = treeLength(tree);
    for(int i = 1; i <= height; i++)      
    {
        currentlevel(tree,i,0);
        printf("\n");
    }
 
  return 0;
}
