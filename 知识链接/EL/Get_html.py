'''
爬取Baidu网页的类。
主要爬取对象是摘要，以及其他格式化数据，正文不爬取。
每个公司默认都是百度百科的唯一主题条，如果有重名的，做一个标注，以备人工判断。
'''
import requests
import re
import json
from config import config
import pandas as pd
from tqdm import tqdm

class get_baike_data():
    def __init__(self,config = config()):
        self.main_herf = 'https://baike.baidu.com/item/'
        self.company = self.get_company_list( config.company_stock_name)
        self.obj_abs = re.compile(r'<meta name="description" content="(?P<abstract>.*?)">', re.S)
        self.headers = config.baidu_ner_headers
        self.writer = open(file = config.company_abstract, mode = 'w+', encoding = 'utf8')
    def get_company_list(self, address):
        company = []
        with open(file = address, mode = 'r', encoding = 'utf8') as f:
            for line in f:
                line = line.split('\t')
                line = line[0][1:-1]
                company.append(line)
            f.close()     
        return company[1:]
    
    def get_html(self,herf):
        url = herf
        resp = requests.get(url = url, headers = self.headers)
        text = resp.text
        resp.close()
        return text

    def get_abs(self):
        dic = dict()
        bad_case = []
        for idx,company_name in enumerate(tqdm( self.company)):
            url = self.main_herf+company_name
            text = self.get_html(url)
            result = self.obj_abs.search(text)
            if result:
                dic[company_name] = result.group('abstract')
                line = json.dumps({company_name:dic[company_name]}, ensure_ascii = False)
                self.writer.write(line+'\n')
            else:
                bad_case.append(company_name)
        print(bad_case)    
        pd.to_pickle(dic, config.company_abstract_dic)




if __name__ == '__main__':
    config = config()
    get_baike_data = get_baike_data(config = config)
    print('\n'.join(get_baike_data.company[:10]))
    print('\n\n\n')
    get_baike_data.get_abs()
