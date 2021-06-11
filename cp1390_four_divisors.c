/*
给你一个整数数组 nums，请你返回该数组中恰有四个因数的这些整数的各因数之和。

如果数组中不存在满足题意的整数，则返回 0 。

 

示例：

输入：nums = [21,4,7]
输出：32
解释：
21 有 4 个因数：1, 3, 7, 21
4 有 3 个因数：1, 2, 4
7 有 2 个因数：1, 7
答案仅为 21 的所有因数的和。
 

提示：

1 <= nums.length <= 10^4
1 <= nums[i] <= 10^5

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/four-divisors
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/
#include <stdio.h>
#include <stdlib.h>
#define DEBUG printf

// 分析，任意两个不同素数的乘积，即可满足条件；
// 需要准备所有因子，但只需要考虑到数组中最大数的一半
int sumFourDivisors(int* nums, int numsSize){
  int sum = 0;

  // 找到最大数
  int maxNum = 0;
  for (int i=0; i<numsSize; i++) {
    if (maxNum < nums[i]) {
      maxNum = nums[i];
    }
  }
  
  
  // 找到最大数一半的区间内的素数表
  int maxFactor = (int)(maxNum/2);
  DEBUG("maxNum is %d, maxFactor is %d\n", maxNum, maxFactor);

  // 素数表
  int *factorTable[100];
  factorTable[0] = (int*)malloc(sizeof(int)*1024);
  int factorSize = 0;

  // 组装素数表
  for (int i=2; i<=maxFactor; i++) {
    int isFactor = 1;
    for (int j=2; j<i; j++) {
      if (i % j == 0) {
        isFactor = 0;
        break;
      }
    }
    if (isFactor) {
      DEBUG("%d is factor\n", i);
      
      int row = factorSize/1024;
      factorTable[row][factorSize%1024] = i;
      factorSize += 1;
      // 动态扩充
      if (factorSize/1024 > row) {
        //printf("add a row\n");
        factorTable[row+1] = (int*)malloc(sizeof(int)*1024);
      }
    }
  }

  DEBUG("factorSize:%d\n", factorSize);

  int factor = 0;
  for (int i=0; i<numsSize; i++) {
    DEBUG("test num %d \n", nums[i]);

    // 检验每个数是否能被素数表里的数整除
    for (int j=0; j<factorSize; j++) {
      factor = factorTable[j/1024][j%1024];

      if (factor > nums[i]/2) {
        DEBUG("test %d finish at:%d\n", nums[i], factor);
        break;
      }

      // 如果可以被整除，检测另外一个因子是否在素数表里
      if (nums[i] % factor == 0) {
        int key = nums[i] / factor;
        DEBUG("%d, got a facotr:%d, test another:%d\n", nums[i], factor, key);

        // 二分搜索
        int start = j+1;
        int end = factorSize;
        int mid = 0;
        int midVal = 0;
        while (start <= end) {
          mid = start + ((end-start)/2>>1);
          midVal = factorTable[mid/1024][mid%1024];
          DEBUG("%d, %d, %d, %d\n", start, end, mid, midVal);

          if (key == midVal) {
            break;
          }
          if (key > midVal) {
            start = mid+1;
          } else {
            end = mid-1;
          }
        }

        // 找到的因子
        if (key == midVal) {
          DEBUG("match %d*%d for %d\n", factor, key, nums[i]);
          // 符合即输出到结果里
          sum += 1 + nums[i] + factor + key;
          break;
        }
      }
    }
  }

  return sum;
}

// 尝试暴力破解了
int sumFourDivisors2(int* nums, int numsSize){
  int sum = 0;
  int factorNum;
  int start, end, iterSum;
  for (int i=0; i<numsSize; i++) {
    DEBUG("test:%d\n", nums[i]);

    // 1和本身
    iterSum = 1 + nums[i];
    factorNum = 2;
    // 在2和自己一半的区间内找因子（最小因子、最大因子之间找）
    start = 2;
    end = nums[i]/2;
    // 如果找到4个以上，快速退出
    while (start <= end && factorNum < 5) {
      DEBUG("start:%d, end:%d, factorNum:%d\n", start, end, factorNum);

      // 找到因子，还需要判断除数是不是因子
      if (nums[i] % start == 0) {
        iterSum += start;
        factorNum ++;
        
        // 除数不是被除数，也是因子
        if (nums[i] / start != start) {
          iterSum += nums[i] / start;
          factorNum ++;
        }
      }

      // 判断下一个条件
      start += 1;
      // 缩小判断范围
      end = nums[i] / start;
    }
    
    DEBUG("num:%d, start:%d, end:%d, factorNum:%d, iterSum:%d\n", nums[i], start, end, factorNum, iterSum);

    // 恰好是4因子
    if (factorNum == 4) {
      sum += iterSum;
    }
  }
  return sum;
}

int main(int argc, char const *argv[])
{
  int numsSize = 10;
  int nums[] = {7286,18704,70773,8224,91675};
  int output = sumFourDivisors2(nums, numsSize);
  DEBUG("sum: %d\n", output);
  return 0;
}

// 1,2,3,4,5,6,7,8,9,10=>45
// 6 = 2*3 => 12
// 8 = 2*4 => 15
// 10 = 2*5 => 18

// [7286,18704,70773,8224,91675] => 
