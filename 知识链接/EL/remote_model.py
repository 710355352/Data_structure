# 用于请求ai.phfund.com.cn
# 得到ORG的机构信息，重新构建数据集

from email import header
import requests
import re
import json
from get_baidu_access import GetAcess
from config import config


config = config()
class PhNER():
    def __init__(self,config=config, mode = None):
        self.config = config
        # self.headers = config.ph_ner_headers
        # self.pa = config.ph_ner_pa
        self.url = config.ph_ner_url
        self.write_dir = config.ph_ner_results if mode == None else config.test_results
        self.writer = open(self.write_dir, 'w+', encoding='utf8')
    def predict(self,data):
        if type(data)!=type(dict()):
            raise f'type data is not dict, the data type is {type(data)}'
        else:
            url = list(data.keys())[0]
            if 'content' in data[url][0]:
                data = data[url][0]
                self.data = json.dumps({'text':data['content'][:500]})
                self.data = json.loads(self.data)
                assert type(self.data)  ==  type(dict())
                assert 'text' in self.data
            else:
                self.data = data
            # print('data',self.data)
            self.pa = self.data
            self.response = requests.get(self.url, params=self.pa)
            # print(self.response)
            self.response_json = self.response.json()
            self.response_json['url'] = url

            self.line = json.dumps(self.response_json, ensure_ascii=False )
            self.writer.write(self.line + '\n')
            self.response.close()

    def predict_over(self):
        # 用于结束预测
        self.writer.close()
        print('All data write successfully!')
        pass
        

class Baidu_ner():
    def __init__(self,config=config, mode = None):
        self.config = config
        self.headers = config.baidu_ner_headers
        self.pa = config.baidu_ner_pa
        self.url = config.baidu_ner_url
        self.write_dir = config.baidu_ner_results if mode == None else config.test_results
        self.writer = open(self.write_dir, 'w+', encoding='utf8')
    
    def predict(self,data):
        # 预测的主函数
        if type(data)!=type(dict()):
            raise f'type data is not dict, the data type is {type(data)}'
        else:
            url = list(data.keys())[0]
            if 'content' in data[url][0]:
                data = data[url][0]
                data['content'] = data['content'][:1000]
                self.data = json.dumps({'text':data['content']})
            else:
                self.data = json.dumps(data)
            self.response = requests.post(self.url, headers=self.headers, params=self.pa, data = self.data)
            self.response_json = self.response.json()
            self.response_json['url'] = url
            self.line = json.dumps(self.response_json, ensure_ascii=False )
            self.writer.write(self.line + '\n')
            self.response.close()

    def predict_over(self):
        # 用于结束预测
        self.writer.close()
        print('All data write successfully!')

    



if __name__=="__main__":
    data = {'text':'平安银行和深圳银行都是银行'}
    f = open(config.test_data, mode='r', encoding = 'utf8')
    data = f.readline().strip()
    # print(type(data))
    data = json.loads(data)
    # print(data)
    # print(type(data))
    baidu_api = Baidu_ner(config=config)
    # ph_api = PhNER(config=config, mode = 'test')
    # ph_api.predict(data)
    # print(ph_api.data)
    # ph_api.predict(data)
    baidu_api.predict(data)
    baidu_api.predict(data)
    print(type(baidu_api.response.json()))
    baidu_api.predict_over()
    # ph_api.predict_over()

