/**
给你一个整数数组 nums 和一个整数 target 。

向数组中的每个整数前添加 '+' 或 '-' ，然后串联起所有整数，可以构造一个 表达式 ：

例如，nums = [2, 1] ，可以在 2 之前添加 '+' ，在 1 之前添加 '-' ，然后串联起来得到表达式 "+2-1" 。
返回可以通过上述方法构造的、运算结果等于 target 的不同 表达式 的数目。

 

示例 1：

输入：nums = [1,1,1,1,1], target = 3
输出：5
解释：一共有 5 种方法让最终目标和为 3 。
-1 + 1 + 1 + 1 + 1 = 3
+1 - 1 + 1 + 1 + 1 = 3
+1 + 1 - 1 + 1 + 1 = 3
+1 + 1 + 1 - 1 + 1 = 3
+1 + 1 + 1 + 1 - 1 = 3
示例 2：

输入：nums = [1], target = 1
输出：1
 

提示：

1 <= nums.length <= 20
0 <= nums[i] <= 1000
0 <= sum(nums[i]) <= 1000
-1000 <= target <= 100

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/target-sum
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/
#include <stdio.h>
#include <math.h>

// 思路：把+和-认为是一个分支，每个分支点就是一个迭代，如果迭代到最后一个时，刚好target匹配目标值，即可返回
int findTargetSumWays(int* nums, int numsSize, int target){
  // 总共有2^numsSize个分支的可能
  int pathsSize = (int)pow(2, numsSize);
  printf("nums size: %d, total paths size: %d\n", numsSize, pathsSize);

  int paths[pathsSize];
  for (int i=0; i<pathsSize; i++) {
    paths[i] = 0;
  }

  int j = 0;
  // 每个分支点就是一个迭代
  for (int i=0; i<numsSize; i++) {
    j = (int)pow(2, i);

    printf("fetch %d, j=%d\n", i, j);
    
    for (int k=0; k<j; k++) {
      // 复制一份新的，成双倍
      paths[j+k] = paths[k];

      // 一部分使用增加
      paths[k] += nums[i];
      // 一部分使用减少
      paths[j+k] -= nums[i];

      printf("paths[k=%d]=%d\n", k, paths[k]);
      printf("paths[j+k=%d]=%d\n", j+k, paths[j+k]);
    }
  }

  // 检查最后一个的分支，是否满足要求
  int ways = 0;
  for (int i=0; i<pathsSize; i++) {
    if (paths[i] == target) {
      ways += 1;
    }
  }
  return ways;
}

int main(int argc, char const *argv[])
{
  int numsSize = 5;
  int nums[] = {1,1,1,1,1};
  int target = 3;
  int output = findTargetSumWays(nums, numsSize, target);
  printf("target ways: %d\n", output);
  return 0;
}
