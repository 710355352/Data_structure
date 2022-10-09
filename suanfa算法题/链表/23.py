# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
'''
合并K个链表
分治、优先队列、暴力破解
'''
class Solution:
    def mergeKLists(self, lists: List[Optional[ListNode]]) -> Optional[ListNode]:
        '''
        self.li = []
        def lists_li(lists):
            root = lists
            while root:
                self.li.append(root)
                root= root.next
        for i in lists:
            lists_li(i)
        self.li.sort(key=lambda x:x.val)
        if self.li:
            root = cur = self.li[0]
            for i in self.li[1:]:
                cur.next = i
                cur = cur.next
            return root
        else:
            return None
        '''
        if not lists:
            return None
        root = ListNode(-1*10**4)
        cur = root
        lists = [i for i in lists if i != None]
        while True:
            # print(lists)
            # while None in lists:
            #     lists.remove(None)
            # print(lists)
            if lists:
                lists.sort(key = lambda x:x.val)
                cur.next = lists[0]
                lists[0] = lists[0].next
                if not lists[0]:
                    lists.pop(0)
                cur = cur.next
            else:
                break
        return root.next