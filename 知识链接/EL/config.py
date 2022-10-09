# 集合所有的EL项目超参数以及文件软路径等

import os
from get_baidu_access import GetAcess

class config:
    def __init__(self):
        self.test_data_dir = os.getcwd() + '/test_data/'
        if not os.path.exists(self.test_data_dir):
            os.makedirs(self.test_data_dir)
        self.test_data = self.test_data_dir + 'test_data.json'
        
        self.test_data_nums = 10
        self.test_results_dir = self.test_data+'baidu_ner_result/'
        if not os.path.exists(self.test_data_dir):
            os.makedirs(self.test_data_dir)
        self.test_results = self.test_data_dir +  'results.json'
        self.data_path = os.getcwd() + '/data/'
        self.data_dic = self.data_path + 'data_dic.pkl'
        self.stock2id = self.data_path + 'stock2id.pkl'
        self.data_alis_stock_id = self.data_path + 'alis_stock_id.pkl'
        self.data_dic_json = self.data_path + 'data_dic.json'
        self.data_stock2id_json = self.data_path + 'stock2id.json'
        self.data_alis_stock_id_json = self.data_path + 'alis_stock_id.json'
        self.origin_news = self.data_path + 'original_news.json'
        self.processed_news = self.data_path + 'processed_news.json'
        self.baidu_ner_headers = {'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/102.0.0.0 Safari/537.36',\
                                "sec-ch-ua-platform": "Windows",'Content-Type':'json'}
        self.ph_ner_headers = {'User-Agent': 'Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/58.0.3029.81 Safari/537.36',\
                                "sec-ch-ua-platform": "Windows",'Content-Type':'json'}
        # self.baidu_ner_pa = {'access_token':'24.31c9a8d65d650282f7329e1667c22ebc.2592000.1659580852.282335-26626025'}
        self.baidu_ner_pa = {'charset':'UTF-8', 'access_token': GetAcess().get_acc()}
        self.baidu_get_acc_headers = {'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/102.0.0.0 Safari/537.36',\
                    "sec-ch-ua-platform": "Windows"}
        self.baidu_oauth_host = 'https://aip.baidubce.com/oauth/2.0/token'
        # host = 'https://aip.baidubce.com/oauth/2.0/token?grant_type=client_credentials&client_id=oQZGPUuoUcPiAWSd7eyQyB4K&client_secret=sxbpXpYYpUG7EgbVjQszSB0M7G3d5Ep0'
        self.baidu_nlp_api_host = 'https://aip.baidubce.com/rpc/2.0/nlp/v1/lexer'
        # self.ph_ner_host = 'https://ai.phfund.com.cn/nlu/api/query'
        self.baidu_ner_results = os.getcwd()+'/data/baidu_ner_result/results.json'
        self.ph_ner_results = os.getcwd()+'/data/ph_ner_result/results.json'
        self.baidu_ner_url = 'https://aip.baidubce.com/rpc/2.0/nlp/v1/lexer'
        self.ph_ner_url = 'http://172.22.17.90:8320/query'
        self.company_stock_name = os.getcwd() + '/data/company_stock_name.txt'
        self.company_abstract = os.getcwd() + '/data/company_abstract.json'
        self.company_abstract_dic = os.getcwd() + '/data/company_abstract.pkl'
        