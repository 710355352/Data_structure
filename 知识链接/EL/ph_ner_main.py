from config import config
from remote_model import PhNER
from tqdm import tqdm
import json

config = config()
ph_api = PhNER(config=config)

if __name__ == "__main__":
    data_dic_reader = open(config.data_dic_json, mode='r', encoding = 'utf8')
    for idx,data in enumerate(tqdm(data_dic_reader)):
        if idx <= 45e5:
            data = json.loads(data)
            assert type(data)== type(dict())
            ph_api.predict(data)
    ph_api.predict_over()