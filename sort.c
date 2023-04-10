#include <time.h>
#include <stdlib.h>
#include <stdio.h>

int extraMemoryAllocated;

// implements heap sort
// extraMemoryAllocated counts bytes of memory allocated
void heapify(int pData[], int n, int x)
{
	int largest = x;
	int left = 2 * x + 1;
	int right = 2 * x + 2;
	int temp;

	if(left < n && pData[left] > pData[largest])
	{
		largest = left;
	}
	if (right < n && pData[right] > pData[largest])
	{
		largest = right;
	}
	if (largest != x)
	{
		temp = pData[x];
		pData[x] = pData[largest];
		pData[largest] = temp;

		heapify(pData, n, largest);
	}
}
void heapSort(int pData[], int n)
{
	int temp;
	for(int x = n / 2 - 1; x >= 0; x--)
	{
		heapify(pData, n,x);
	}
	for(int i = n - 1; i >= 0; i--)
	{
		temp = pData[0];
		pData[0] = pData[i];
		pData[i] = temp;

		heapify(pData, i,0);

	}
}


// implement merge sort
// extraMemoryAllocated counts bytes of extra memory allocated
void merge( int pData[], int l , int m, int r)
{
	int x = 0;
	int y = 0;
	int k = 0;
	int n1 = m - l + 1;
	int n2 = r - m;

	extraMemoryAllocated = (n1 * sizeof(int)) + (n2 * sizeof(int));

	int *Left = (int *) malloc(n1 * sizeof(int));
	int *Right = (int *) malloc(n2 * sizeof(int));

	for (x = 0; x < n1; x++)
	{
		Left[x]= pData[l + x];
	}
	for (int y = 0; y < n2; y++)
	{
		Right[y]= pData[m + 1 + y];
	}
	x = 0;
	y = 0;
	k = l;
	while( x<n1 && y <n2)
	{
		if(Left[x] <= Right[y])
		{
			pData[k] = Left[x];
			x++;
		}
		else
		{
			pData[k] = Right[y];
			y++;
		}
		k++;
	}
	while(x<n1)
	{
		pData[k] = Left[x];
		x++;
		k++;
	}
	while(y < n2)
	{
		pData[k] = Right[y];
		y++;
		k++;
	}
	free(Right);
	free(Left);
}
void mergeSort(int pData[], int l, int r)
{
	if(l < r)
	{
		int m = (l + r) / 2; //This is the mid index
		mergeSort(pData, l, m);
		mergeSort(pData, m + 1, r);
		merge(pData, l, m, r);
	}
}

// parses input file to an integer array
int parseData(char *inputFileName, int **ppData)
{
	FILE* inFile = fopen(inputFileName,"r");
	int dataSz = 0;
	int i, n, *data;
	*ppData = NULL;
	
	if (inFile)
	{
		fscanf(inFile,"%d\n",&dataSz);
		*ppData = (int *)malloc(sizeof(int) * dataSz);
		// Implement parse data block
		if (*ppData == NULL)
		{
			printf("Cannot allocate memory\n");
			exit(-1);
		}
		for (i=0;i<dataSz;++i)
		{
			fscanf(inFile, "%d ",&n);
			data = *ppData + i;
			*data = n;
		}

		fclose(inFile);
	}
	
	return dataSz;
}

// prints first and last 100 items in the data array
void printArray(int pData[], int dataSz)
{
	int i, sz = dataSz - 100;
	printf("\tData:\n\t");
	for (i=0;i<100;++i)
	{
		if(i >= dataSz)
		{
			printf("\n\n");
			return;
		}
		printf("%d ",pData[i]);
	}
	printf("\n\t");
	
	for (i=sz;i<dataSz;++i)
	{
		printf("%d ",pData[i]);
	}
	printf("\n\n");
}

int main(void)
{
	clock_t start, end;
	int i;
    double cpu_time_used;
	char* fileNames[] = { "input1.txt", "input2.txt", "input3.txt", "input4.txt" };
	
	for (i=0;i<4;++i)
	{
		int *pDataSrc, *pDataCopy;
		int dataSz = parseData(fileNames[i], &pDataSrc);
		
		if (dataSz <= 0)
			continue;
		
		pDataCopy = (int *)malloc(sizeof(int)*dataSz);
	
		printf("---------------------------\n");
		printf("Dataset Size : %d\n",dataSz);
		printf("---------------------------\n");
		
		printf("Heap Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		heapSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		printf("Merge Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		mergeSort(pDataCopy, 0, dataSz - 1);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		free(pDataCopy);
		free(pDataSrc);
	}
	
}