1.排序 + 双指针

// 快排函数(升序)。
int compare(const void* a, const void* b) {
    return (*(int*)a)-(*(int*)b);
}

int** threeSum(int* nums, int numsSize, int* returnSize) {
    int** result = malloc(sizeof(int*)*numsSize*numsSize);
    *returnSize = 0;
    
    qsort(nums, numsSize, sizeof(int), compare);   

    for (int i = 0; i < numsSize-2; i++) {
        int pos1 = i+1, pos2 = numsSize-1;
        
        // 去除重复值。
        if (i > 0 && nums[i] == nums[i-1])
            continue;
        // 双指针首尾碰撞。
        while (pos1 < pos2) {
            // 如果前两个数的和大于0，break。
            if (nums[i]+nums[pos1] > 0)
                break;
            if (nums[pos1]+nums[pos2] < -nums[i])
                pos1++;
            else if (nums[pos1]+nums[pos2] > -nums[i])
                pos2--;
            else {
                result[*returnSize] = malloc(sizeof(int)*3);    
                result[*returnSize][0] = nums[i];
                result[*returnSize][1] = nums[pos1];
                result[*returnSize][2] = nums[pos2]; 
                (*returnSize)++;     
                pos1++;
                pos2--;
                
                // 去除重复值。
                while (pos1 < numsSize && nums[pos1] == nums[pos1-1])
                    pos1++;
                while (pos2 >= i+1 && nums[pos2] == nums[pos2+1])
                    pos2--;
            }
        }
        // 如果为三个非负数，break。
        if (nums[i] >= 0)
            break;
    }
    
    return result;
}

    
2.排序 + 哈希表(uthash)

// uthash是一个用c语言编写的开源库，使用宏实现了哈希表的增删改查等功能。
// 快排函数(升序)。
int compare(const void* a, const void* b) {
    return (*(int*)a)-(*(int*)b);
}

int** threeSum(int* nums, int numsSize, int* returnSize) {
    struct hash {
        int value;
        UT_hash_handle hh; 
    };
    
    int** result = malloc(sizeof(int*)*numsSize*numsSize);
    *returnSize = 0;
    qsort(nums, numsSize, sizeof(int), compare);      

    // 可以转化成 1.两数之和，即a+b=-c。
    for (int i = 0; i < numsSize-2; i++) {
        struct hash *hashTable = NULL;
        
        // 去除重复值。
        if (i > 0 && nums[i] == nums[i-1])
            continue;
        // 寻找两个数，使其和等于-nums[i]。    
        for (int j = i+1; j < numsSize; j++) {
            struct hash *h;
            // 边将nums[j]添加到哈希表中，边检查每个元素所对应的目标元素(-nums[i]-nums[j])是否存在于表中。
            int diff = -nums[i]-nums[j];
            HASH_FIND_INT(hashTable, &diff, h);
            
            if (!h) {
                if (nums[i]+nums[j] <= 0) {
                    h = malloc(sizeof(struct hash));
                    h->value = nums[j];
                    HASH_ADD_INT(hashTable, value, h);
                }
            }
            else {
                result[*returnSize] = malloc(sizeof(int)*3);
                result[*returnSize][0] = h->value;
                result[*returnSize][1] = -nums[i]-h->value;
                result[*returnSize][2] = nums[i]; 
                (*returnSize)++;
                
                // 去除重复值。
                while (j+1 < numsSize && nums[j+1] == nums[j])
                    j++;
            }
        }
        // 如果为三个非负数，break。
        if (nums[i] >= 0)
            break;
    }
    
    return result;
}