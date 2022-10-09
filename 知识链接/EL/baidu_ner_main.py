from config import config
from remote_model import Baidu_ner
from tqdm import tqdm
import json
import time

config = config()
baidu_api = Baidu_ner(config=config)

if __name__ == "__main__":
    data_dic_reader = open(config.data_dic_json, mode='r', encoding = 'utf8')
    for idx,data in enumerate(tqdm(data_dic_reader)):
        if idx >= 45e4 and idx <= 90e4:
            data = json.loads(data)
            assert type(data)== type(dict())
            baidu_api.predict(data)
            time.sleep(1)
    baidu_api.predict_over()