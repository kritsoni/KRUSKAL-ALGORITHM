#include<iostream>
#include<malloc.h>
using namespace std;
int edge = 0;
struct heap{          
int weight;
struct heap*left;
struct heap*right;
}*head,*temp,*h,*item,*max,*c,*v;
heap* create_node();
struct edge{
int src;
int dest;
int weight;
};
struct graph{
int t;
struct edge e;
}*g;
struct set{
int v;
struct set *parent; 
}*s[100];
void print_heap(struct heap *,int,int);
heap* create_heap(struct graph *g,heap* t, int,int);
 void locator(heap* t,int ,int );
int heapsort(int n);
void kruskal(int n,int m);
heap* extract_min(int);
void makeset(int);
int check_cycle(struct graph,int );
int findset(int,int);
set* findparent(struct set*);
void unionn(struct graph,int);
void kruskal_result(int);
int main(){
int no_edge,ch=1,no_ver,i=1,src,dest,weight,last_weight,last_dest,last_src,last_t;
cout<<"GRAPH INPUT"<<endl;
cout<<"enter no of edges in graph"<<endl;
cin>>no_edge;
cout<<"enter no of vertex in graph";
cin>>no_ver;
g=(struct graph*)malloc(sizeof(graph)*no_edge);
while(ch<=no_edge){
cout<<"enter source vertex of an edge";
cin>>src;
cout<<"enter destination vertex of an edge";
cin>>dest;
cout<<"enter weight of edge";
cin>>weight;
g[i].e.src=src;
g[i].e.dest=dest;
g[i].e.weight=weight;
g[i].t=0;
i++;
ch++;
}
last_weight = g[no_edge].e.weight;  //last one was causing trouble so explicit assignment
last_src = g[no_edge].e.src;
last_dest = g[no_edge].e.dest;
last_t = g[no_edge].t;
create_heap(g,head,1,no_edge);
g[no_edge].e.weight=last_weight;
g[no_edge].e.src=last_src;
g[no_edge].e.dest=last_dest;
g[no_edge].t=last_t;
locator(head,no_edge,1);
item->weight = last_weight;
if(no_edge%2==0){              //avoiding null comparison by adding dummy node if no. of edge is even
locator(head,no_edge/2,1);
temp=create_node();
temp->weight = 9999;
item->right=temp;
heapsort(no_edge+1); 
}
else
 heapsort(no_edge);
kruskal(no_ver,no_edge);
kruskal_result(no_edge);
return 0;
}


heap* create_node(){
h=(struct heap*)malloc(sizeof(struct heap));
h->left=NULL;
h->right=NULL;
return h;
}
heap* create_heap(struct graph *g,heap* t,int i,int size){
int x,y;
if(i<=size){
temp =create_node();
temp->weight=g[i].e.weight;
if(i==1)
   head=temp;
t=temp;
x=2*i;
y=2*i+1;
t->left = create_heap(g,t->left,x,size);
t->right = create_heap(g,t->right,y,size);
}
}

void print_heap(struct heap* h,int i,int size){

if(i<=size){
cout<<h->weight<<endl;
print_heap(h->left,2*i,size);
print_heap(h->right,2*i+1,size);}

}
int heapsort(int n){
int temp;
int swap=0;
for(int i=n/2;i>0;i--){
         locator(head,i,1);
           if(item->weight>item->left->weight){
             swap=1;
             temp=item->weight;
             item->weight=item->left->weight;
              item->left->weight=temp;}
            if(item->weight>item->right->weight){
              swap=1;
             temp=item->weight;
             item->weight=item->right->weight;
              item->right->weight=temp;}
               }    

if(swap==1)
 heapsort(n);
}


 void locator(heap* t,int i,int x){  //function to locate ith element of the heap 
  if(x<=i){
  locator(t->left,i,2*x);
   locator(t->right,i,2*x+1);
   if(x==i){
      item=t;
      }
      return;
}

}

void kruskal(int n,int m){
int count;
int is_cycle;
struct graph check;
heap *extracted;
for(int i=1;i<=n;i++)
    makeset(i);
while(edge<n-1){
       extracted=extract_min(m);
     for(count=1;count<=m;count++){
       if(extracted->weight == g[count].e.weight && g[count].t==0){     
          check=g[count];      
       break;
            }
}
is_cycle = check_cycle(check,n);

if(is_cycle == 0)
     g[count].t=1;
extracted->weight=9999;  
heapsort(n);

}
}

heap* extract_min(int m){  //function to extract the min edge of the edge set 
int temp;
locator(head,m,1);
temp=item->weight;
item->weight=head->weight;
head->weight=temp;

return item;
}

/*functions check_cycle,makeset,findset,findparent,unionn performs 
  UNION_FIND to detect cycles in graph by making set for each vertex
  */  
  
 int check_cycle(struct graph check,int n){  
   int x,y;
   x=findset(check.e.src,n);
   y=findset(check.e.dest,n);
   unionn(check,n);
  if(x==y)
    return 1;
  else{
     edge++;
    return 0;
}  
 }
void makeset(int i){
s[i] = (struct set *)malloc(sizeof(struct set));
s[i]->v=i;
s[i]->parent = s[i];
}

int findset(int f,int n){
struct set *z,*z1;
for(int i=1;i<=n;i++){
   if(s[i]->v == f){
      z=s[i];
       break;}
}

z1=findparent(z);
return z1->v;
}


set* findparent(struct set *z){

if(z->parent == z)
return z;
else{
z = z->parent;
return findparent(z);
}
}

void unionn(struct graph z,int n){
struct set *z1,*z2;
for(int i=1;i<=n;i++){
   if(s[i]->v == z.e.src)
      z1=s[i];
   if(s[i]->v == z.e.dest)
      z2=s[i];
}
z1=findparent(z1);
z2=findparent(z2);
z1->parent=z2;
}
void kruskal_result(int n){
cout<<endl<<endl<<"AFTER KRUSKAL ALGORITHM ON THE GRAPH:-"<<endl;
cout<<"edges taken are"<<endl;
for(int i=1;i<=n;i++){

if(g[i].t == 1){
cout<<"source_vertex"<<g[i].e.src<<endl;
cout<<"destination_vertex"<<g[i].e.dest<<endl;
cout<<"weight of edge is"<<g[i].e.weight<<endl;
}

}
}
			
