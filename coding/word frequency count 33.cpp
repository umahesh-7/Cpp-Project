#include<stdio.h>
#include<stdlib.h>
#include<string.h> 
struct Node { 
char *s;
 struct Node *left; 
struct Node *right; 
int height; 
int count;
 };
 struct node{
 char *s; 
};
int count(char s[],char word[]) {
 char temp[1000]="";
 int j=0,c=0;
 int i; 
for(i=0;s[i]!='\0';i++) {
 if(s[i]==' '||s[i]=='\0'){
 temp[i]='\0'; 
if(strcmp(word,temp)==0)
 c++; 
j=0;
 }
 else{
 temp[j]=s[i]; 
j++;
 }
 }
 return c;
 }
 
 int height(struct Node *N) {
 if(N==NULL) return 0; 
return N->height;
 }
 int max(int a,int b) { 
return (a>b)?a:b;
 } 
struct Node* newNode(char *s,int count) { 
struct Node*node=(struct Node*)malloc(sizeof(struct Node));
 node->s=s; 
node->count=count; 
node->left= NULL; 
node->right=NULL; 
node->height=1;
 return(node); 
} 
struct Node *rightRotate(struct Node *y) { 
struct Node *x=y->left; 
struct Node *T2=x->right;
 x->right=y; 
y->left=T2;
 y->height=max(height(y->left),height(y->right))+1;
 x->height=max(height(x->left),height(x->right))+1; 
return x; 
} 
struct Node *leftRotate(struct Node *x) {
 struct Node *y=x->right; 
struct Node *T2=y->left; 
y->left=x; x->right=T2;
 x->height=max(height(x->left),height(x->right))+1;
 y->height=max(height(y->left),height(y->right))+1; 
return y;
 }
 int getBalance(struct Node *N) { 
if (N==NULL) return 0;
 return height(N->left)-height(N->right);
 } 
struct Node* insert(struct Node* node, char *s,int count) { 
if (node==NULL)
 return(newNode(s,count));
 if (strcmp(s,node->s)<0) 
node->left=insert(node->left,s,count); 
else if (strcmp(s,node->s)>0) 
node->right=insert(node->right,s,count); 
else return node; 
node->height=1+ max(height(node->left),height(node->right));
 int balance=getBalance(node);
 if(balance>1&&strcmp(s,node->left->s)<0)
 return rightRotate(node);
 if(balance<-1&&strcmp(s,node->right->s)>0) 
return leftRotate(node); 
if(balance>1&&strcmp(s,node->left->s)>0) {
 node->left=leftRotate(node->left);
 return rightRotate(node); 
}
 if(balance<-1&&strcmp(s,node->right->s)<0) {
 node->right=rightRotate(node->right); 
return leftRotate(node);
 }
 return node; 
}
 void inOrder(struct Node *root) {
 if(root != NULL) { 
inOrder(root->left);
 printf("%s : %d\n", root->s,root->count);
 inOrder(root->right); 
}
 }
int main()
{
 struct Node *root=NULL; 
int func,cc=0;
 FILE *fptr;
 char s[1000],word[100]; 
char temp[100][100]; 
while(1){ 
printf("\n------------------------------------------------------\n"); 
printf("1.Reads file and creates AVL tree containing list of all words used in the file with count of the number of times each word is found in the file. \n");
 printf("2.Reads one word from file.\n");
 printf("3.Compares two integers identified by pointers to integers.\n");
 printf("4.Display top element\n");
 printf("5.Prints the list with the count for each word.\n"); 
printf("6:Prints one word from the list with its count.\n"); 
printf("7.Exit function\n"); 
printf("\n------------------------------------------------------\n"); 
printf("Enter function number:"); 
scanf("%d",&func);
 printf("\n"); 
if(func==7) break; 
switch(func){ 
case 1:{ 
fptr=fopen("skills33.txt","r"); 
while(!feof(fptr)){ 
fgets(s,1000,fptr);
 }
 int j=0,ctr=0;
 int i; 
for(i=0;s[i]!='\0';i++) { 
if(s[i]==' ') {
 temp[ctr][j]='\0'; 
ctr++;
 j=0; 
}
 else { 
temp[ctr][j]=s[i];
 j++;
 }
 }
 for(i=0;i<ctr;i++) {
 int c=count(s,temp[i]); 
root=insert(root,temp[i],c); 
}
 printf("Data in file is \"%s\"\n",s);
 printf("AVL tree is created\n");
 printf("Go to function 5 to check whether AVL tree is created or not\n"); 
break; 
}
 case 2:{ 
fptr=fopen("skills33.txt","r"); 
while(!feof(fptr)){ 
fgets(s,1000,fptr);
 }
 printf("Enter the word to find :"); 
scanf("%s",word);
 int j=0,ctr=0; 
cc=count(s,word); 
if(cc==0){ 
printf("Word is present in the FILE \n");
 printf("Go to function 6 to check how many times the word is repeated in the file\n");
 }
 else{ 
printf("Word is not found in the FILE\n");
 printf("If you are not yet satisfied with our project then proceed with another function:\n");
 }
 printf("\n");
  break;
 }
 case 3:
{
 int m=0; 
char w[100]; 
fptr=fopen("skills33.txt","r");
 while(!feof(fptr)){
 fgets(s,1000,fptr);
 } 
int i,j=0,ctr=0;
 for(i=0;s[i]!='\0';i++) {
 if(s[i]==' ')
 {
 temp[ctr][j]='\0'; 
ctr++; 
j=0; 
}
 else 
{ 
temp[ctr][j]=s[i]; 
j++;
 }
 }
 for(i=0;i<ctr;i++) 
{
 int c=count(s,temp[i]);
 if(c>m){
 m=c;
 strcpy(w,temp[i]);
 }
 }
 printf("The most frequent word in the file is \'%s\' and it is repeated \'%d\' times\n\n",w,m);
 printf("If you are not yet satisfied with our project then proceed with another function:\n"); 
break;
 }
 case 4:
{ 
if(root==NULL) 
printf("AVL tree is not constructed\n");
 else 
printf("The top element is: \"%s\" and its count is \'%d\' \n",root->s,root->count);
 printf("\n");
 printf("If you are not yet satisfied with our project then proceed with another function:\n");
 break; 
}
 case 5:
{ 
if(root==NULL)
 printf("AVL tree is not constructed\n"); 
else
{
 printf("Words in the file and their count is :\n");
 inOrder(root);
 } 
printf("\n");
 printf("If you are not yet satisfied with our project then proceed with another function:\n");
 break; 
} 
case 6:
{
 printf("Word \'%s\' is found \'%d\' times in the file\n\n",word,cc); 
printf("If you are not yet satisfied with our project then proceed with another function:\n"); 
break;
}
} 
}
}
