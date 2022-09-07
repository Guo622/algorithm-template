#include<stdio.h>
typedef struct {
	short acc;
	short sta;
} Node;
Node node[100][100];
int x,y,num;
void search(int i,int j)
{
	node[i][j].sta=1;
	if(i==x&&j==y){
		num++;
		printf("%d\n",num);
		for(int i1=1;i1<=x;i1++){
			for(int j1=1;j1<=y;j1++){
                printf("%d",node[i1][j1].sta);
                if(j1<y)printf(" ");
            }
			printf("\n");
		}
	}
	else{
		if(node[i+1][j].acc==1&&node[i+1][j].sta==0)search(i+1,j);
		if(node[i-1][j].acc==1&&node[i-1][j].sta==0)search(i-1,j);
		if(node[i][j+1].acc==1&&node[i][j+1].sta==0)search(i,j+1);
		if(node[i][j-1].acc==1&&node[i][j-1].sta==0)search(i,j-1);
	}
	node[i][j].sta=0;
}
int main()
{
	scanf("%d%d",&x,&y);
	for(int i=1;i<=x;i++){
		for(int j=1;j<=y;j++)
			scanf("%d",&node[i][j].acc);
	}
	search(1,1);
}
