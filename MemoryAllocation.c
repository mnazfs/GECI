#include<stdio.h>
#include<stdlib.h>

int partitions[10];

void firstFit(int processSize,int p)
{
	int flag=0;
	for(int i=0;i<p;++i) {
		if(partitions[i]>=processSize) {
			partitions[i]=processSize;
			printf("Process of size %d allocated to partition %d\n",processSize,i+1);
			flag=1;
			break;
		} else
			continue;
	}
	if(flag==0)
		printf("Unable to allocate memory\n");
}

void bestFit(int processSize,int p)
{
	int flag=0;
	for(int i=0;i<p;++i)
		for(int j=0;j<p-i-1;++j)
			if(partitions[j]>partitions[j+1]) {
				int p=partitions[j];
				partitions[j]=partitions[j+1];
				partitions[j+1]=p;
			}
	for(int i=0;i<p;++i) {
		if(partitions[i]>=processSize) {
			partitions[i]=processSize;
			printf("Process of size %d allocated to partition %d\n",processSize,i);
			flag=1;
			break;
		} else
			continue;
	}
	if(flag==0)
		printf("Process can't be allocated\n");
}

void worstFit(int processSize,int p)
{
	int flag=0;
	for(int i=0;i<p;++i)
		for(int j=0;j<p-i-1;++j)
			if(partitions[j]<partitions[j+1]) {
				int p=partitions[j];
				partitions[j]=partitions[j+1];
				partitions[j+1]=p;
			}
	for(int i=0;i<p;++i) {
		if(partitions[i]>=processSize) {
			partitions[i]-=processSize;
			printf("Process of size %d allocated to partition %d\n",processSize,i);
			flag=1;
			break;
		} else 
			continue;
	}
	if(flag==0) 
		printf("Process allocation failed\n");
}

int main()
{
	int n,p,c,choice;
	printf("Enter number of partitions: ");
	scanf("%d",&n);
	printf("Enter the partitions: ");
	for(int i=0;i<n;++i)
		scanf("%d",&partitions[i]);
	printf("Enter the number of processes: ");
	scanf("%d",&p);
	printf("First Fit:1  Best Fit:2  Worst Fit:3  Enter choice: ");
	scanf("%d",&choice);
	switch(choice) {
		case 1:
			for(int i=1;i<=p;++i) {
				printf("Enter size of process %d: ",i);
				scanf("%d",&c);
				firstFit(c,p);
			}
			break;
		case 2:
			for(int i=1;i<=p;++i) {
				printf("Enter size of process %d: ",i);
				scanf("%d",&c);
				bestFit(c,p);
			}
			break;
		case 3:
			for(int i=1;i<=p;++i) {
				printf("Enter size of process %d: ",i);
				scanf("%d",&c);
				worstFit(c,p);
			}
			break;
		default:
			printf("Wrong input!\n");
	}
}
