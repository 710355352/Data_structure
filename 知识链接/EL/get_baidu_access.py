# 获取百度NLP api的access_token

import requests

class GetAcess:
    __dic =  {'refresh_token': '25.0b3169eff4dce3e07efb7ba61145dfe9.315360000.1972348852.282335-26626025', \
            'expires_in': 2592000, 'session_key': '9mzdCPWJCeKJH2c3UuHELw4i+7/ZAn3EzVVTlS0JxG+UdMTqxtyvfv5RNrLtj9vWsWF4OneN00BufftqiQu8YGTCW00auQ==', \
            'access_token': '24.31c9a8d65d650282f7329e1667c22ebc.2592000.1659580852.282335-26626025',\
            'scope': 'public nlp_simnet nlp_wordemb nlp_comtag nlp_dnnlm_cn brain_nlp_lexer brain_all_scope brain_nlp_comment_tag \
                brain_nlp_dnnlm_cn brain_nlp_word_emb_vec brain_nlp_word_emb_sim brain_nlp_sentiment_classify brain_nlp_simnet brain_nlp_depparser brain_nlp_wordembedding \
                brain_nlp_dnnlm_cn_legacy brain_nlp_simnet_legacy brain_nlp_comment_tag_legacy brain_nlp_lexer_custom brain_nlp_keyword brain_nlp_topic brain_nlp_ecnet\
                brain_nlp_emotion brain_nlp_comment_tag_custom brain_nlp_news_summary brain_nlp_sentiment_classify_custom brain_creation_couplets brain_creation_poem\
                brain_nlp_address brain_nlp_titlepredictor wise_adapt lebo_resource_base lightservice_public hetu_basic lightcms_map_poi kaidian_kaidian ApsMisTest_Test权限\
                vis-classify_flower lpq_开放 cop_helloScope ApsMis_fangdi_permission smartapp_snsapi_base smartapp_mapp_dev_manage iop_autocar oauth_tp_app smartapp_smart_game_openapi\
                oauth_sessionkey smartapp_swanid_verify smartapp_opensource_openapi smartapp_opensource_recapi fake_face_detect_开放Scope vis-ocr_虚拟人物助理 idl-video_虚拟人物助理\
                smartapp_component smartapp_search_plugin avatar_video_test b2b_tp_openapi b2b_tp_openapi_online smartapp_gov_aladin_to_xcx',\
                'session_secret': '815c62acd25421f46d92b3e03a10826b'}
    __dic = {"refresh_token": "25.edb3785695f58c8e9f807281c79eb1d4.315360000.1972517425.282335-26644577","expires_in": 2592000,"session_key": "9mzdDoClEY5w8AMFgJato1o58L5aB5xBmRfhrE9s8UgV+lPwVlkGJPly6qdIOIFdfd1fI9qIOUYGgKEjtTtGtKvymSx1bA==","access_token": "24.5245652286984cb4c76c1bce54e7657a.2592000.1659749425.282335-26644577","scope": "public nlp_simnet nlp_wordemb nlp_comtag nlp_dnnlm_cn brain_nlp_lexer brain_all_scope brain_nlp_comment_tag brain_nlp_dnnlm_cn brain_nlp_word_emb_vec brain_nlp_word_emb_sim brain_nlp_sentiment_classify brain_nlp_simnet brain_nlp_depparser brain_nlp_wordembedding brain_nlp_dnnlm_cn_legacy brain_nlp_simnet_legacy brain_nlp_comment_tag_legacy brain_nlp_lexer_custom brain_nlp_keyword brain_nlp_topic brain_nlp_ecnet brain_nlp_emotion brain_nlp_comment_tag_custom brain_nlp_news_summary brain_nlp_sentiment_classify_custom brain_creation_couplets brain_creation_poem brain_nlp_address brain_nlp_titlepredictor wise_adapt lebo_resource_base lightservice_public hetu_basic lightcms_map_poi kaidian_kaidian ApsMisTest_Test\u6743\u9650 vis-classify_flower lpq_\u5f00\u653e cop_helloScope ApsMis_fangdi_permission smartapp_snsapi_base smartapp_mapp_dev_manage iop_autocar oauth_tp_app smartapp_smart_game_openapi oauth_sessionkey smartapp_swanid_verify smartapp_opensource_openapi smartapp_opensource_recapi fake_face_detect_\u5f00\u653eScope vis-ocr_\u865a\u62df\u4eba\u7269\u52a9\u7406 idl-video_\u865a\u62df\u4eba\u7269\u52a9\u7406 smartapp_component smartapp_search_plugin avatar_video_test b2b_tp_openapi b2b_tp_openapi_online smartapp_gov_aladin_to_xcx","session_secret": "0db3d7aba6eb1685ff1e6a8d896a2728"}
    def __init__(self, reget_access = False):
        if not reget_access:
            self.__access_token = GetAcess.__dic['access_token']
        else:
            self.__access_token = self.__re_get_acc()
    
    def __re_get_acc(self):
        self.host = 'https://aip.baidubce.com/oauth/2.0/token'
        self.headers = {'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/102.0.0.0 Safari/537.36',\
                    "sec-ch-ua-platform": "Windows"}
        pa = {"grant_type":"client_credentials", "client_id":"oQZGPUuoUcPiAWSd7eyQyB4K","client_secret":"sxbpXpYYpUG7EgbVjQszSB0M7G3d5Ep0"}
        self.__response = requests.post(self.host, headers=headers,params = pa)
        access_token = self.__response['access_token']
        return access_token
    
    def get_acc(self):
        return self.__access_token
        

if __name__=='__main__':
    acc = GetAcess().get_acc()
    print(acc)
    print(type(acc))
