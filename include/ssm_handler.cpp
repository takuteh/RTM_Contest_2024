#include <iostream>
#include <fstream>
#include <string>
#include "intSsm.h"

#include "ssm_handler.h"

#define READ_FILE "file.json"

using namespace std;
using json = nlohmann::json;

SSMHANDLE::SSMHANDLE(string comp_name, string mode, int id)
{
        this->gShutOff = false;
        this->intSsm = nullptr;
        this->comp_name = comp_name;
        this->ssm_id = id;
        this->ssm_con_flag = false;
        cout << id << endl;
        if (mode == "read" || mode == "write")
        {
                this->ssm_mode = mode;
                if (ssm_id != -1) // ssm_idがnullptrの場合接続しない
                        this->connect_ssm();
        }
        else if (mode == "create")
        {
                this->ssm_mode = "create";
                if (ssm_id != -1)
                        this->create_ssm();
        }
        else
        {
                cerr << mode << " is invalid mode!" << endl;
        }

        cout << "Setting mode is " << this->ssm_mode << endl;
}

void SSMHANDLE::ctrlC(int aStatus)
{
        signal(SIGINT, NULL);
        this->gShutOff = true;
}

int SSMHANDLE::change_ssm(int id)
{ // 接続するssm_idを受け取る
        cout << "change!" << endl;
        // それぞれの処理でエラーが出たら関数を抜ける
        if (this->close_ssm())
                return 1; // 現在アクセスしてるssmからぬける
        this->ssm_id = id;
        if (this->ssm_mode == "read" || "write")
        {
                if (this->connect_ssm())
                        return 1; // あらたなSSMに接続
        }
        else if (this->ssm_mode == "create")
        {
                if (this->create_ssm())
                        return 1; // あらたなSSMを作成
        }
        return 0;
}

int SSMHANDLE::set_ssm_id()
{
        if (read_file())
                return 1; // jsonファイルを読み込む
        if (parse_json())
                return 1; // パースして自分のIDを判別

        return 0;
}

int SSMHANDLE::read_file()
{ // jsonstrにファイルの内容をすべて読み込む
        string buf;

        ifstream inputFile(READ_FILE);
        if (!inputFile)
        {
                cerr << "Error opening file" << endl;
                return 1;
        }

        while (!inputFile.eof())
        {
                getline(inputFile, buf);
                this->jsonstr += buf;
        }

        return 0;
}

int SSMHANDLE::parse_json()
{ // jsonデータをパース
        auto jobj = json::parse(this->jsonstr);

        // コンポーネントに対応したSSMIDの記載があれば設定を行う
        if (jobj[this->comp_name]["id"].empty())
        {
                cerr << "ssm id is empty" << endl;
                return 1;
        }

        this->ssm_id = jobj[this->comp_name]["id"];

        cout << "ssm id is " << this->ssm_id << endl;

        this->jsonstr = "";
        return 0;
}

int SSMHANDLE::connect_ssm()
{ // すでにあるSSMに接続
        if (this->intSsm != nullptr)
        { // オブジェクトが初期化されているか
                cout << "object has memory!" << endl;
                return 1;
        }

        this->intSsm = new SSMApi<intSsm_k, intSsm_p>(SNAME_INT, this->ssm_id); // オブジェクトの作成

        // ssm関連の初期化
        if (!initSSM())
        { // @suppress("Invalid arguments")
                cerr << "error init ssm" << endl;
                return 1;
        }

        if (this->ssm_mode == "read")
        { // 読み込みモードに設定
                this->open_mode = SSM_READ;
        }
        else if (this->ssm_mode == "write")
        { // 書き込みモードに設定
                this->open_mode = SSM_WRITE;
        }

        // 共有メモリにすでにある領域を開く
        // open 失敗するとfalseを返す
        if (!(this->intSsm->open(this->open_mode)))
        {
                endSSM();
                cout << "open false" << endl;
                this->ssm_con_flag = false;
                return 1;
        } // @suppress("Invalid arguments")
        this->ssm_con_flag = true;
        return 0;
}

int SSMHANDLE::create_ssm()
{                                                                               // SSMを作成
        this->intSsm = new SSMApi<intSsm_k, intSsm_p>(SNAME_INT, this->ssm_id); // オブジェクトの作成
        if (!initSSM())
                return 0;
        if (!this->intSsm->create(5.0, 1.0))
        {
                this->ssm_con_flag = false;
                return 1;
        }
        this->intSsm->setProperty();
        this->ssm_con_flag = true;
        return 0;
}

int SSMHANDLE::close_ssm()
{
        if (this->ssm_mode == "read" || this->ssm_mode == "write")
        {
                // openしたらclose
                this->intSsm->close();
        }
        else if (this->ssm_mode == "create")
        {
                // create したら必ず最後にrelease
                this->intSsm->release();
        }

        // SSMからの切断
        endSSM();
        delete this->intSsm;
        this->intSsm = nullptr;

        return 0;
}
