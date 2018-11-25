#include <stdio.h>
#include <malloc.h>

void bucketsort(int *arr, int size, int numOfbucket);

int main() {
    int a[] = {1, 2, 22, 1, 11, 55, 6, 77, 4, 66, 45, 199, 1101, 1111, 1121, 1, 12, 23, 34, 543, 45};
    int size = sizeof(a) / sizeof(int), i;
    bucketsort(a, size, 13);
	for(i = 0; i < size; ++i) {
		printf("%d\n", a[i]);
	}
    return 0;
}

typedef struct bucket {
    int key;
    struct bucket *next;
}bucket_table;

void bucketsort(int *arr, int size, int numOfbucket) {
    bucket_table **bucketTable = (bucket_table**)malloc(numOfbucket * sizeof(bucket_table*)); 
    int i;
    //init bucketTable
    for(i = 0; i < numOfbucket; ++i) {
        bucket_table *tmp = (bucket_table*)malloc(sizeof(bucket_table*));
        tmp->key = 0;
        tmp->next = NULL;
        bucketTable[i] = tmp;
    }

    // get divider key
    int ma = arr[0];
    for(i = 1; i < size; ++i) {
        if(arr[i] > ma) ma = arr[i];
    }
    int divider = (ma + numOfbucket) / numOfbucket;
    //printf("divider = %d\n", divider);

    //push and sort
    for(i = 0; i < size; ++i) {
        
        bucket_table *tmp = (bucket_table*)malloc(sizeof(bucket_table*));
        int index = arr[i] / divider;
        tmp->key = arr[i];
        tmp->next = NULL;

        if(bucketTable[index]->next == NULL) {
            bucketTable[index]->next = tmp;
        } else {
            bucket_table *tmpBucket = bucketTable[index];
            while(tmpBucket->next != NULL && tmpBucket->next->key <= arr[i]) {
                tmpBucket = tmpBucket -> next;
            }
            tmp -> next = tmpBucket->next;
            tmpBucket -> next = tmp;
        }
        bucketTable[index]->key ++;
    }

    //print or save
    int count = 0;
    bucket_table *del;
    for(i = 0; i < numOfbucket; ++i) {
        bucket_table *tmp = bucketTable[i] -> next;
        free(bucketTable[i]);
        bucketTable[i] = NULL;
        while(tmp) {
            //printf("%d\n", tmp -> key);
            del = tmp;
            arr[count++] = tmp -> key;
            tmp = tmp -> next;
            free(del);
            del = NULL;
        }
    }
}