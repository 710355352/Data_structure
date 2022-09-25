from config import config
import json
from remote_model import Baidu_ner
import requests
import pandas as pd
config = config()
from tqdm import tqdm
import matplotlib.pyplot as plt 
# with open(config.processed_news, mode = 'r', encoding = 'utf8') as f:
#     for line in f:
#         line = json.loads(line)
#         print(line)
#         break
# test_results_writer = open(config.test_results, mode = 'w+', encoding = 'utf8')
def predict():
    with open(config.test_data, mode = 'r', encoding = 'utf8') as f:
        baidu_api = Baidu_ner(config=config, mode = 'test')
        for id,data in enumerate(f):
            # data = {'text':'平安银行和深圳银行都是银行'}
            data = json.loads(data)
            url = list(data.keys())[0]
            if 'content' in data[url][0]:
                data = data[url][0]
                print(data)

            data = {'text': data['content']}
            baidu_api.predict(data)
        baidu_api.predict_over()
# predict()
# with open(config.data_dic_json, 'r', encoding = 'utf8') as f:
#     dic = {}
#     max_content_len = 0
#     length = []
#     for idx,line in enumerate(tqdm(f)):
#         line = json.loads(line)
#         news_url = list(line.keys())[0]
#         # print(news_url)
#         dic[idx] = len(line[news_url][0]['content'])
#         if dic[idx]<=1000:
#             length.append(dic[idx])
#         # print(line[news_url][0], type(line[news_url][0]))
#         # break
#         max_content_len = max(max_content_len, dic[idx])
#     pd.to_pickle(dic, 'data/news_len.pkl')
#     print('news_len:', '\t', idx,'\n','max_content_len:','\t',max_content_len, '<1000:','\t', len(length))
#     plt.hist(x = length, bins = 50 ,edgecolor = 'k')
#     plt.savefig('data/content_hist.png')

with open('data/baidu_ner_result/results0.json','r', encoding = 'utf8') as f:
    print(len(f.readlines()))




# headers = config.ph_ner_headers

# data = {'text':'平安银行和深圳银行都是银行'}
# url = config.ph_ner_url
# print(url)
# response = requests.get(url = url, params= data)
# print(response)
# print(response.json())
