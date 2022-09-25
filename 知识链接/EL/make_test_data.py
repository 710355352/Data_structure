import json
from config import config

config=config()
writer = open(config.test_data,'w+',encoding='utf8')
with open(config.data_dic_json,mode='r',encoding='utf8') as f:
    for id, line in enumerate(f):
        if id != config.test_data_nums:
            line = json.loads(line)
            line = json.dumps(line, ensure_ascii=False)
            writer.write(line+'\n')
        else:
            break

writer.close()
print('Write successfully！\n',f'dir is {config.test_data} \n',f'write nums is {config.test_data_nums}')

    

