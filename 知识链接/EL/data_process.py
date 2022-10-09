## 处理news.json的无用部分，截取有用的部分。

from config import config
import json
import os
import numpy as np
from tqdm import tqdm
import pandas as pd



class data_process():
    def __init__(self,config = config()):
        self.config = config
        self.data_pro()
    def data_pro(self):
        writer = open(self.config.processed_news, mode = 'w+', encoding = 'utf8')
        need_keys = {'content', 'stock_name', 'stock_code', 'title', 'url'}
        with open(self.config.origin_news, mode = 'r', encoding = 'utf8') as f:
            for id,line in enumerate(tqdm(f)):
                line = json.loads(line[33:])
                new_json = {key:line[key] for key in line.keys() if key in need_keys}
                if new_json['content'].strip() == '':
                    continue
                new_json = json.dumps(new_json, ensure_ascii=False)
                writer.write(new_json + '\n')
        writer.close()
        print('All data have been processed!')

class data2dict():
    '''
    做一个结构，类似于 
    url_content.pkl : url->content
    url_sotck_name : url-> [stock1,stock2,....]
    或者是
    集合成一个字典
    data_dic:
    url -> {stocks_name->[stock1,stock2,....], content-> str(content)}

    顺道做一个字典，用于查询stock->stock_id

    '''
    def __init__(self, config = config()):
        self.config = config
        self.make_pkl()
        pass

    def make_pkl(self):
        reader = open(config.processed_news, mode = 'r', encoding = 'utf8')
        data_dic_writer = open(config.data_dic_json, mode = 'w+', encoding = 'utf8')
        stock2id_writer = open(config.data_stock2id_json, mode = 'w+', encoding = 'utf8')
        alis_stock_id_writer = open(config.data_alis_stock_id_json, mode = 'w+', encoding = 'utf8')
        dic = dict()
        stock2id = dict()
        alis_stock_id = dict()
        for idx, line in enumerate(tqdm(reader)):
            line = json.loads(line)
            assert type(line) == type(dict())

            # 制作data_dic的字典
            if line['url'] not in dic:
                if line['content']: 
                    dic[line['url']] = [{'content': line['content'], 'stocks_name':[line['stock_name']]}]
            else:
                dic[line['url']][0]['stocks_name'].append(line['stock_name'])
            
            # 制作stock2id的字典，但是途中发现有的股票有两个或者以上的id，
            # 又制作了一个alis_stock_id的json，量比较小就不做dict了
            if line['stock_name'] not in stock2id and line['stock_name'] not in alis_stock_id:
                stock2id[line['stock_name']] = line['stock_code']
            elif line['stock_name'] in alis_stock_id:
                alis_stock_id[line['stock_name']].add(line['stock_code'])
            elif line['stock_name'] in stock2id :
                if stock2id[line['stock_name']] != line['stock_code']:
                    alis_stock_id[line['stock_name']] = set([stock2id[line['stock_name']],line['stock_code']])
                    del stock2id[line['stock_name']]
            # if idx >= 1e5:
            #     break
        # 开始写json
        for key in stock2id:
            line = json.dumps({key:stock2id[key]}, ensure_ascii = False)
            stock2id_writer.write(line+'\n')
        stock2id_writer.close()  
        for key in alis_stock_id:
            print({key:alis_stock_id[key]})
            line = json.dumps({key:list(alis_stock_id[key])}, ensure_ascii = False)  
            alis_stock_id_writer.write(line+'\n')
        alis_stock_id_writer.close()
        for key in dic:
            line = json.dumps({key:dic[key]}, ensure_ascii = False)
            data_dic_writer.write(line+'\n')
        stock2id_writer.close() 
                
        print('Make dic successfully !')
        pd.to_pickle(dic, config.data_dic)
        pd.to_pickle(stock2id, config.stock2id)
        pd.to_pickle(alis_stock_id, config.data_alis_stock_id)
        print(f'The data_dic len is : \t {len(dic)} \nThe alis_stock_id len is \t {len(alis_stock_id)} \nThe stock2id len is \t {len(stock2id)}')
        print('Save successfully !')



def make_news_len():
    with open(config.data_dic_json, 'r', encoding = 'utf8') as f:
    dic = {} #用于储存idx->len(content)
    max_content_len = 0 #记录最大content长度
    length = [] # 记录小于1000的序列长度信息
    for idx,line in enumerate(tqdm(f)):
        line = json.loads(line)
        news_url = list(line.keys())[0]
        # print(news_url)
        dic[idx] = len(line[news_url][0]['content'])
        if dic[idx]<=1000:
            length.append(dic[idx])
        # print(line[news_url][0], type(line[news_url][0]))
        # break
        max_content_len = max(max_content_len, dic[idx])
    pd.to_pickle(dic, 'data/news_len.pkl')
    print('news_len:', '\t', idx,'\n','max_content_len:','\t',max_content_len, '<1000:','\t', len(length))
    plt.hist(x = length, bins = 50 ,edgecolor = 'k')
    plt.savefig('data/content_hist.png')



if __name__ == '__main__':
    config = config()
    # data_process = data_process(config)
    make_pkl = data2dict(config)




        