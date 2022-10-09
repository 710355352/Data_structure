'''
给定一个整数数组 temperatures ，表示每天的温度，返回一个数组 answer ，其中 answer[i] 是指对于第 i 天，下一个更高温度出现在几天后。如果气温在这之后都不会升高，请在该位置用 0 来代替。
'''

class Solution:
    def dailyTemperatures(self, temperatures: List[int]) -> List[int]:
        ans = [0 for _ in range(len(temperatures))]
        for i in range(len(temperatures)-2,-1,-1):
            cur = i+1
            while temperatures[i] >= temperatures[cur]:
                if ans[cur] == 0:
                    ans[i]=0
                    break
                else:
                    cur += ans[cur]
            else: ans[i] = cur-i
        return ans
