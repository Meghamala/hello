#include<stdio.h>
#include<stdlib.h>
struct node
{
	int offset;
	unsigned int a[4];
	struct node *link;
};
typedef struct node* NODE;
NODE unionn(NODE [],NODE,int);
NODE insertrear(NODE,NODE);
NODE copynode(NODE);
NODE getNode()
{
	NODE a=(NODE)malloc(sizeof(struct node));
	a->link=NULL;
	a->offset=0;
	int i;
	for(i=0;i<4;i++)
		a->a[i]=0;
	return a;
}

NODE copynode(NODE temp1)
{
	int i;
	NODE nn=getNode();
	//nn=temp;
	nn->offset=temp1->offset;
	for(i=0;i<4;i++)
		nn->a[i]=temp1->a[i];
	nn->link=NULL;
	return nn;
}

NODE unionn(NODE heads[],NODE un,int n)
{	
	int i,j,flag=1;
	NODE temp,temp1=heads[0],temp2;
	//NODE un=getnode();
	while(temp1!=NULL)
	{
		temp=copynode(temp1);
		un=insertrear(un,temp);
		temp1=temp1->link;
	}
	for(i=1;i<n;i++)
	{
		temp1=heads[i];
		while(temp1!=NULL)
		{
			flag=1;
			temp2=un;
			while(temp2!=NULL)
			{
				if(temp2->offset==temp1->offset)
				{
					for(j=0;j<4;j++)
					{
					//	printf("%d   ",temp2->a[j]);
						temp2->a[j]=temp2->a[j]|temp1->a[j];
					}
					flag=0;
				//	printf("\n");
					
				}
				temp2=temp2->link;
			}
			if(flag)
			{
				temp=copynode(temp1);
				un=insertrear(un,temp);
			//	printf("%d  ",temp->a[i]);

			}
			temp1=temp1->link;
		}
	}
	return un;
}

NODE intersec(NODE heads[],NODE in,int n)
{	
	int i,j,flag=1;
	NODE temp,temp1=heads[0],temp2;
	//NODE un=getnode();
	while(temp1!=NULL)
	{
		temp=copynode(temp1);
		in=insertrear(in,temp);
		temp1=temp1->link;
	}
	for(i=1;i<n;i++)
	{
		temp1=heads[i];
		while(temp1!=NULL)
		{
			flag=1;
			temp2=in;
			while(temp2!=NULL)
			{
				if(temp2->offset==temp1->offset)
				{
					for(j=0;j<4;j++)
					{
					//	printf("%d   ",temp2->a[j]);
						temp2->a[j]=temp2->a[j]&temp1->a[j];
					}
					flag=0;
				//	printf("\n");
					
				}
				temp2=temp2->link;
			}
			if(flag)
			{
				temp=copynode(temp1);
				in=insertrear(in,temp);
			//	printf("%d  ",temp->a[i]);

			}
			temp1=temp1->link;
		}
	}
	return in;
}
void bitset(NODE node,int item)
{
	int pos,n;
	n=((item-node->offset))/32;
	pos=item%32;
	node->a[n]=node->a[n]|(1<<(pos));
	printf("%d %d %u\n",n,pos,node->a[n]);
}

NODE search(NODE head,int item)
{
	if(head==NULL)
	{
		return NULL;
	}
	do
	{
		if(head->offset==(item/128)*128)
		{
			return head;
		}
		head=head->link;
	}while(head!=NULL);
	return NULL;
}

NODE insertrear(NODE head,NODE temp)
{
	NODE temp3=head;
	if(temp3==NULL)
	{
		return NULL;
	}
	while(temp3->link!=NULL)
	{
		temp3=temp3->link;
	}
	temp3->link=temp;
	return head;
}

NODE insert(NODE head,int item)
{
	int o,pos,n;
	NODE temp;
	if(head==NULL)
	{
		head=getNode();
		head->offset=(item/128)*128;
		bitset(head,item);
		return head;
	}
	else
	{
		o=item/128;
		o=o*128;
		temp=search(head,o);
		if(temp!=NULL)
		{
			bitset(temp,item);
			return head;
		}
		else
		{
			temp=getNode();
			temp->offset=(item/128)*128;
			bitset(temp,item);
			head=insertrear(head,temp);
			return head;
		}
	}
}

void disp(NODE n)
{
	int i;
	//FILE *op=fopen("output","w");
	while(n!=NULL)
	{
		for(i=0;i<4;i++)
			printf("%d  ",n->a[i]);
	//		fprintf(op,"%d ",n->a[i]);
	//		fprintf(op," ");
			

		printf("\n");
		n=n->link;
	}
}

void main()
{
	int n,m;
	FILE *fp;
	fp=fopen("input","a");
	scanf("%d",&n);
	fprintf(fp,"%d\n",n);
	NODE heads[n];
       NODE un=getNode();
	NODE in=getNode();
//	NODE union(NODE [],NODE,int);
	int b[100],i,j;
	
	//printf("Enter the number of customers\n");
	//scanf("%d",&n);
	
	
	for(i=0;i<n;i++)
		heads[i]=getNode();
	for(i=0;i<n;i++)
	{

	printf("Enter the number of items purchased\n");
		scanf("%d",&m);
		fprintf(fp,"%d\n",m);
		for(j=0;j<m;j++)
		{
			scanf("%d",&b[j]);
			fprintf(fp,"%d\n",b[j]);
			heads[i]=insert(heads[i],b[j]);
		}
	}
	
	fclose(fp);
	un=unionn(heads,un,n);
	in=intersec(heads,in,n);
	printf("\n");
	disp(un);
	printf("\n");
	disp(in);
}
