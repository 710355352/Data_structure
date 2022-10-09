'''
森林中有未知数量的兔子。提问其中若干只兔子 "还有多少只兔子与你（指被提问的兔子）颜色相同?" ，将答案收集到一个整数数组 answers 中，其中 answers[i] 是第 i 只兔子的回答。

来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/rabbits-in-forest
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
'''
class Solution:
    def numRabbits(self, answers: List[int]) -> int:
        dic = {}
        ans = 0
        for i in answers:
            if i in dic:
                dic[i]+=1
            else:
                dic[i] = 1
        for i in dic:
            group = (dic[i]-1)//(i+1) + 1 
            ans += group*(i+1)
        return ans
