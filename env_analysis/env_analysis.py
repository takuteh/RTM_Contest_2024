#!/usr/bin/env python
# -*- coding: utf-8 -*-
# -*- Python -*-

# <rtc-template block="description">
"""
 @file env_analysis.py
 @brief ModuleDescription
 @date $Date$


"""
# </rtc-template>

import sys
import time
sys.path.append(".")

# Import RTM module
import RTC
import OpenRTM_aist

import joblib #識別用
import numpy as np
import pandas as pd
import time
from time import sleep
from concurrent.futures import ThreadPoolExecutor
from concurrent.futures import ProcessPoolExecutor
import csv
from sklearn.decomposition import PCA
from sklearn.svm import SVC
from sklearn.pipeline import make_pipeline
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler
import random
# Import Service implementation class
# <rtc-template block="service_impl">

# </rtc-template>

# Import Service stub modules
# <rtc-template block="consumer_import">
# </rtc-template>


# This module's spesification
# <rtc-template block="module_spec">
env_analysis_spec = ["implementation_id", "env_analysis", 
         "type_name",         "env_analysis", 
         "description",       "ModuleDescription", 
         "version",           "1.0.0", 
         "vendor",            "VenderName", 
         "category",          "Category", 
         "activity_type",     "STATIC", 
         "max_instance",      "1", 
         "language",          "Python", 
         "lang_type",         "SCRIPT",
         ""]
# </rtc-template>

class env_orig:
    def __init__(self):
        self.mpu_data_array=[0.0]*8
        self.arr=[]
        self.fft_data=np.array([])

        # FFT処理の関数を定義
    def perform_fft(self,signal, fs):
        # 窓関数の選択 (ハニング窓)
        window = np.hanning(len(signal))
        # 窓関数を信号に適用
        windowed_signal = signal * window

        # FFTを計算
        fft_result = np.fft.fft(windowed_signal)

        # 振幅スペクトルを取得
        amplitude_spectrum = np.abs(fft_result)

        # 周波数軸を生成
        freqs = np.fft.fftfreq(len(signal), 1.0/fs)

        # 振幅スペクトルと対応する周波数を半分に切り取る
        half_spectrum = amplitude_spectrum[:len(signal)//2]
        half_freqs = freqs[:len(signal)//2]

        # 0Hz成分を除外
        nonzero_indices = half_freqs > 2
        half_freqs = half_freqs[nonzero_indices]
        half_spectrum = half_spectrum[nonzero_indices]

        return half_freqs, half_spectrum
    
    def GetIMU(self):  
        for i in range(256):
            self.arr.append([self.mpu_data_array[0],self.mpu_data_array[1],self.mpu_data_array[2],self.mpu_data_array[3],self.mpu_data_array[4],self.mpu_data_array[5],self.mpu_data_array[6],self.mpu_data_array[7],self.mpu_data_array[8]])
    
    def exec_fft(self):
        # リストをDataFrameに変換
        IMU_df = pd.DataFrame(self.arr, columns=['mpu_temp', 'acc_x', 'acc_y', 'acc_z', 'gyro_x', 'gyro_y', 'gyro_z','time'])
        
        # 時間と加速度データを取得
        time_vals = IMU_df['time'].values
        acc_x = IMU_df['acc_x'].values
        acc_y = IMU_df['acc_y'].values
        acc_z = IMU_df['acc_z'].values
        gyro_x = IMU_df['gyro_x'].values
        gyro_y = IMU_df['gyro_y'].values
        gyro_z = IMU_df['gyro_z'].values

        # サンプリング周波数を計算 Tsの平均値から算出
        fs = 1 / (sum(IMU_df["time"]/len(IMU_df["time"])))
        
        # 各軸に対してFFTを行い結果を取得
        freqs_ax, spectrum_ax = self.perform_fft(acc_x, fs)
        freqs_ay, spectrum_ay = self.perform_fft(acc_y, fs)
        freqs_az, spectrum_az = self.perform_fft(acc_z, fs)
        freqs_gx, spectrum_gx = self.perform_fft(gyro_x, fs)
        freqs_gy, spectrum_gy = self.perform_fft(gyro_y, fs)
        freqs_gz, spectrum_gz = self.perform_fft(gyro_z, fs)

        fft_ax_predict = np.array(spectrum_ax).reshape(1, -1)
        fft_ay_predict = np.array(spectrum_ay).reshape(1, -1)
        fft_az_predict = np.array(spectrum_az).reshape(1, -1)
        fft_gx_predict = np.array(spectrum_gx).reshape(1, -1)
        fft_gy_predict = np.array(spectrum_gy).reshape(1, -1)
        fft_gz_predict = np.array(spectrum_gz).reshape(1, -1)

        self.fft_data = np.concatenate((spectrum_ax, spectrum_az))
    def exec_main(self):
        # 1. CSVファイルの読み込み(学習データ)
        # CSVファイルのパスを指定（例: "data.csv"）
        data = pd.read_csv("/home/takumi/RTComponent/corba_comp/env_analysis/dataset_by_fft_xz_include_stack_3.csv")

        # 2. 特徴量とラベルに分割
        # 例として、最後の列をラベル（y）として、それ以外を特徴量（X）に指定します
        X = data.iloc[:, :-1].values  # 全ての行と、最後の列を除く全ての列が特徴量
        y = data.iloc[:, -1].values   # 最後の列がラベル

        # 3. データを訓練セットとテストセットに分割
        X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)

        # 4. PCAの実行とSVMのモデルを作成
        pipeline = make_pipeline(StandardScaler(), PCA(n_components=2), SVC(kernel='rbf', gamma='scale', C=1.0))
        # 5. モデルの訓練
        pipeline.fit(X_train, y_train)

        # 6. テストデータの識別
        predictions = pipeline.predict(X_test)

        # 7. 任意のデータの識別
        # ここで新しいデータを指定（例: CSVと同じ形式のデータ）
        self.fft_data = np.array(self.fft_data).reshape(1, -1)

        # self.fft_data の次元を確認
        print(f"self.fft_data shape: {self.fft_data.shape}")
        # 訓練データ X_train の次元を確認
        print(f"X_train shape: {X_train.shape}")

        # 特徴量数が異なる場合の処理
        if self.fft_data.shape[1] != X_train.shape[1]:
            print(f"Feature mismatch: self.fft_data has {self.fft_data.shape[1]} features, but the model expects {X_train.shape[1]} features.")
            # 必要に応じて、self.fft_dataの次元を修正するコードをここに追加できます
            # 例えば、ゼロパディングや特徴量の削減などを行う場合があります
        # 特徴量数の調整（ゼロパディングまたは削減）
        if self.fft_data.shape[1] < X_train.shape[1]:
            # ゼロパディング
            padding_size = X_train.shape[1] - self.fft_data.shape[1]
            self.fft_data = np.pad(self.fft_data, ((0, 0), (0, padding_size)), 'constant')
            print(f"Zero-padded self.fft_data to match feature size: {self.fft_data.shape}")
        elif self.fft_data.shape[1] > X_train.shape[1]:
            # 特徴量の削減
            self.fft_data = self.fft_data[:, :X_train.shape[1]]
        print(f"Reduced self.fft_data to match feature size: {self.fft_data.shape}")
        # 新しいデータを識別
        new_predictions = pipeline.predict(self.fft_data)
        # 8. 結果の表示 (0:走行(道路) 1:走行(土) 2:スタック)
        print("now_time:",time.time())
        print("Predictions for new data:", new_predictions)
        return new_predictions.item() 
# <rtc-template block="component_description">
##
# @class env_analysis
# @brief ModuleDescription
# 
# 
# </rtc-template>
class env_analysis(OpenRTM_aist.DataFlowComponentBase):
	
    ##
    # @brief constructor
    # @param manager Maneger Object
    # 
    def __init__(self, manager):
        OpenRTM_aist.DataFlowComponentBase.__init__(self, manager)

        self._d_mpu_data = OpenRTM_aist.instantiateDataType(RTC.TimedDoubleSeq)
        """
        """
        self._mpu_dataIn = OpenRTM_aist.InPort("mpu_data", self._d_mpu_data)
        self._d_env = OpenRTM_aist.instantiateDataType(RTC.TimedLong)
        """
        """
        self._envOut = OpenRTM_aist.OutPort("env", self._d_env)
        #インスタンス化
        self.env=env_orig()
        self.i=0
		


        # initialize of configuration-data.
        # <rtc-template block="init_conf_param">
		
        # </rtc-template>


		 
    ##
    #
    # The initialize action (on CREATED->ALIVE transition)
    # 
    # @return RTC::ReturnCode_t
    # 
    #
    def onInitialize(self):
        # Bind variables and configuration variable
		
        # Set InPort buffers
        self.addInPort("mpu_data",self._mpu_dataIn)
		
        # Set OutPort buffers
        self.addOutPort("env",self._envOut)
		
        # Set service provider to Ports
		
        # Set service consumers to Ports
		
        # Set CORBA Service Ports
		
        return RTC.RTC_OK
	
    ###
    ## 
    ## The finalize action (on ALIVE->END transition)
    ## 
    ## @return RTC::ReturnCode_t
    #
    ## 
    #def onFinalize(self):
    #

    #    return RTC.RTC_OK
	
    ###
    ##
    ## The startup action when ExecutionContext startup
    ## 
    ## @param ec_id target ExecutionContext Id
    ##
    ## @return RTC::ReturnCode_t
    ##
    ##
    #def onStartup(self, ec_id):
    #
    #    return RTC.RTC_OK
	
    ###
    ##
    ## The shutdown action when ExecutionContext stop
    ##
    ## @param ec_id target ExecutionContext Id
    ##
    ## @return RTC::ReturnCode_t
    ##
    ##
    #def onShutdown(self, ec_id):
    #
    #    return RTC.RTC_OK
	
    ##
    #
    # The activated action (Active state entry action)
    #
    # @param ec_id target ExecutionContext Id
    # 
    # @return RTC::ReturnCode_t
    #
    #
    def onActivated(self, ec_id):
        self.i=0
        return RTC.RTC_OK
	
    ##
    #
    # The deactivated action (Active state exit action)
    #
    # @param ec_id target ExecutionContext Id
    #
    # @return RTC::ReturnCode_t
    #
    #
    def onDeactivated(self, ec_id):
    
        return RTC.RTC_OK
	
    ##
    #
    # The execution action that is invoked periodically
    #
    # @param ec_id target ExecutionContext Id
    #
    # @return RTC::ReturnCode_t
    #
    #
    def onExecute(self, ec_id):
        if self._mpu_dataIn.isNew():
            if self.i<256:
            # 新しいデータが来ているか確認
                data=self._mpu_dataIn.read()
                
                #mpuから取得したデータを格納
                self.env.arr.append(data.data)
                self.i=self.i+1
            elif self.i==256:
                self.env.exec_fft()
                now_env=self.env.exec_main()
                print("now_env:",now_env)
                self._d_env.data=now_env
                self._envOut.write()
                self.i=0;  
                self.env.arr=[]
        return RTC.RTC_OK
	
    ###
    ##
    ## The aborting action when main logic error occurred.
    ##
    ## @param ec_id target ExecutionContext Id
    ##
    ## @return RTC::ReturnCode_t
    ##
    ##
    #def onAborting(self, ec_id):
    #
    #    return RTC.RTC_OK
	
    ###
    ##
    ## The error action in ERROR state
    ##
    ## @param ec_id target ExecutionContext Id
    ##
    ## @return RTC::ReturnCode_t
    ##
    ##
    #def onError(self, ec_id):
    #
    #    return RTC.RTC_OK
	
    ###
    ##
    ## The reset action that is invoked resetting
    ##
    ## @param ec_id target ExecutionContext Id
    ##
    ## @return RTC::ReturnCode_t
    ##
    ##
    #def onReset(self, ec_id):
    #
    #    return RTC.RTC_OK
	
    ###
    ##
    ## The state update action that is invoked after onExecute() action
    ##
    ## @param ec_id target ExecutionContext Id
    ##
    ## @return RTC::ReturnCode_t
    ##

    ##
    #def onStateUpdate(self, ec_id):
    #
    #    return RTC.RTC_OK
	
    ###
    ##
    ## The action that is invoked when execution context's rate is changed
    ##
    ## @param ec_id target ExecutionContext Id
    ##
    ## @return RTC::ReturnCode_t
    ##
    ##
    #def onRateChanged(self, ec_id):
    #
    #    return RTC.RTC_OK
	



def env_analysisInit(manager):
    profile = OpenRTM_aist.Properties(defaults_str=env_analysis_spec)
    manager.registerFactory(profile,
                            env_analysis,
                            OpenRTM_aist.Delete)

def MyModuleInit(manager):
    env_analysisInit(manager)

    # create instance_name option for createComponent()
    instance_name = [i for i in sys.argv if "--instance_name=" in i]
    if instance_name:
        args = instance_name[0].replace("--", "?")
    else:
        args = ""
  
    # Create a component
    comp = manager.createComponent("env_analysis" + args)

def main():
    # remove --instance_name= option
    argv = [i for i in sys.argv if not "--instance_name=" in i]
    # Initialize manager
    mgr = OpenRTM_aist.Manager.init(sys.argv)
    mgr.setModuleInitProc(MyModuleInit)
    mgr.activateManager()
    mgr.runManager()

if __name__ == "__main__":
    main()

