# 计算文本字面相似度

# haming距离，即计算文本的hash值的按位异或，对非0求和。
# yakebi距离
import jieba as jb

class TextScore():
    '''

    '''
    def __init__(self):
        # self.word_dic = set()
        self.jb = jb
        pass

    def Cal_Jieba_Dis(self,t1,t2):
        self.jb.add_word(t1)
        self.jb.add_word(t2)
        self.params = 2*len(t1)*len(t2)/(len(t1)**2 + len(t2)**2)
        # print('Pa:','\t',self.params)
        text_cut1, text_cut2 = list(self.jb.cut(t1)), list(self.jb.cut(t2))
        text_cut1, text_cut2 = list(self.jb.lcut_for_search(t1)), list(self.jb.lcut_for_search(t2))
        # print(text_cut1, text_cut2)
        Set = set(text_cut1) | set(text_cut2)
        List = list(Set)
        Map = {token:i for i,token in enumerate(List)}
        t1_map = [0]*len(Set)
        t2_map = [0]*len(Set)
        for token in text_cut1:
            t1_map[Map[token]]+= 1
        for token in text_cut2:
            t2_map[Map[token]] += 1
        # score = self.dot_mut(t1_map,t2_map)/(self.dot_mut(self.list_sum(t1_map, t2_map), self.list_sum(t1_map, t2_map)))
        score = self.dot_mut(t1_map,t2_map)/(self.dot_mut(t1_map, t1_map)**0.5 * self.dot_mut(t2_map, t2_map)**0.5 )
        return score
    def dot_mut(self,list1,list2):
        # 点积
        # 输入两个一维矩阵
        return sum([i*j for i,j in zip(list1,list2)])
    def list_sum(self,list1,list2):
        return [i+j for i ,j in zip(list1,list2)]

    def Cal_Word_Dis(self, t1, t2):
        self.params = 2*len(t1)*len(t2)/(len(t1)**2 + len(t2)**2)
        text_cut1 , text_cut2 = set(t1), set(t2)
        Set = set(text_cut1) | set(text_cut2)
        List = list(Set)
        Map = {token:i for i,token in enumerate(List)}
        # print(Map)
        t1_map = [0]*len(Set)
        t2_map = [0]*len(Set)
        for token in text_cut1:
            t1_map[Map[token]]+= 1
        for token in text_cut2:
            t2_map[Map[token]] += 1
        # print(t1_map, '\n', t2_map)
        # score = self.dot_mut(t1_map,t2_map)/(self.dot_mut(self.list_sum(t1_map, t2_map), self.list_sum(t1_map, t2_map)))
        score = self.dot_mut(t1_map,t2_map)/(self.dot_mut(t1_map, t1_map)**0.5 * self.dot_mut(t2_map, t2_map)**0.5 )
        return score

    def Abbreviation_expander(self, t1, t2):
        self.params = 2*len(t1)*len(t2)/(len(t1)**2 + len(t2)**2)
        text_cut1 , text_cut2 = set(t1), set(t2)
        min_len = min(len(t1), len(t2))
        max_len = max(len(t1), len(t2))
        copy_word = len(text_cut1 & text_cut2)
        return (copy_word/len(t2))
    
    def Score(self,t1,t2):
        self.params += 1e-6
        return (0.1*self.Cal_Jieba_Dis(t1,t2) + 0.6*self.Cal_Word_Dis(t1,t2) + 0.3*self.Abbreviation_expander(t1,t2))/self.params
# def HamingDis(text1,text2):
#     hs1,hs2 = hash(text1), hash(text2)
#     HasmingDis = bin(hs1^hs2).count('1')
#     return HasmingDis   2* 6 *2 / 36 + 4 2*6*4/36+16
    
if __name__ == '__main__':
    ts = TextScore()
    t1 = '中国建设银行'
    t2 = '中国银行'
    t3 = '中国'
    print(ts.Cal_Jieba_Dis(t1,t2),\
    ts.Cal_Jieba_Dis(t1,t3))
    print(ts.Cal_Word_Dis(t1,t2),\
    ts.Cal_Word_Dis(t1,t3))
    print(ts.Abbreviation_expander(t1,t2),\
    ts.Abbreviation_expander(t1,t3))
    print(ts.Score(t1,t2),\
    ts.Score(t1,t3))
    
    