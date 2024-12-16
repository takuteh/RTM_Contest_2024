#ifndef SSM_HANDLER_H
#define SSM_HANDLER_H

// c++系
#include <iomanip>
// c系
#include <unistd.h>
#include <signal.h>
// その他
#include <ssm.hpp>
#include "intSsm.h"
#include <string>
#include "nlohmann/json.hpp"

class SSMHANDLE
{
public:
	SSMHANDLE(std::string co_name, std::string mode, int id);
	void ctrlC(int aStatus);
	int change_ssm(int id); // SIGUSRを受け取ったら実行
	int close_ssm();		// SSMを閉じる
	bool gShutOff;
	bool ssm_con_flag; // ssm接続フラグ
	SSMApi<intSsm_k, intSsm_p> *intSsm;

	// private:
	std::string jsonstr;
	int connect_ssm(); // 読み込むためのSSMの接続と初期化
	int create_ssm();
	int read_file();  // jsonfileの読み込み
	int parse_json(); // jsonパース
	int set_ssm_id();
	int ssm_id; // 接続先のSSMのID

	std::string comp_name; // コンポーネント起動時に設定する
	std::string ssm_mode;
	SSM_open_mode open_mode;
};

#endif
