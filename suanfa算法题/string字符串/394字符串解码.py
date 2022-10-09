class Solution:
    def decodeString(self, s: str) -> str:
        def fun(s):
            temp = ''
            pre = 0
            while pre < len(s):
                if s[pre].isalpha():
                    temp+=s[pre]
                    pre+=1
                elif s[pre].isdigit():
                    num = ''
                    while s[pre].isdigit():
                        num+=s[pre]
                        pre+=1
                    num = int(num)  #数字要特殊处理
                    stack = [1]
                    st = ''
                    pre+=1
                    while stack:
                        i = s[pre]
                        if i == '[':
                            stack.append(1)
                            st+=i
                        elif i == ']':
                            stack.pop()
                            if stack:
                                st+=i
                        else:
                            st+=i
                        pre+=1
                    temp+=num*fun(st)
            return temp
        return fun(s)
