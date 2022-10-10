'''
给定一个长度为 n 的整数数组 height 。有 n 条垂线，第 i 条线的两个端点是 (i, 0) 和 (i, height[i]) 。

找出其中的两条线，使得它们与 x 轴共同构成的容器可以容纳最多的水。

返回容器可以储存的最大水量。

说明：你不能倾斜容器。

来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/container-with-most-water
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
'''

class Solution:
    def maxArea(self, height) -> int:
        ans = 0
        pre,end = 0,len(height)-1
        while pre < end:
            ans = max(ans,(end-pre)*min(height[pre],height[end]))
            if height[pre]>height[end]:
                end-=1
            else:
                pre+=1
        return ans