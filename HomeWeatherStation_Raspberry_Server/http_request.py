import requests
import time, datetime
import mysql.connector
import LogsWriter

class HTTP_REQUEST:
    header = {"Content-type": "application/x-www-form-urlencoded"}
    url = "http://alexgorlov99.ru/post-esp-data.php"
    url_clean_table = "http://alexgorlov99.ru/remove_table.php"
    previous_id = 0
    def clean_public_table(self):
        logs = LogsWriter.Logs()
        try:
            #Очистка таблицы публичного сервера
            payload = {'api_key': 'tPmAT5Ab3j7F9'}
            response_decoded_json = requests.post(HTTP_REQUEST.url_clean_table, data=payload, headers=HTTP_REQUEST.header,timeout=1)
            logs.write_log(datetime.datetime.now().strftime("%d-%b-%Y_%H:%M:%S")+" Публичная база данных очищена! ")
            #print(datetime.datetime.now().strftime("%d-%b-%Y_%H:%M:%S")+ " Публичная база данных очищена! ")
        except:
            logs.write_log(datetime.datetime.now().strftime("%d-%b-%Y_%H:%M:%S")+" Публичную базу данных не удалось очистить! ")
            #print(datetime.datetime.now().strftime("%d-%b-%Y_%H:%M:%S")+" Публичную базу данных не удалось очистить! ")
    def send_data_from_local_to_public_server(self):
        logs = LogsWriter.Logs()
        myconn = mysql.connector.connect(host="localhost", user="root", passwd="281299", database="esp_data")
        cur = myconn.cursor()
        logs.write_log(datetime.datetime.now().strftime("%d-%b-%Y_%H:%M:%S")+" Запуск python-скрипта для чтения данных из локального сервера и передачи в публичный ")
        #print(datetime.datetime.now().strftime("%d-%b-%Y_%H:%M:%S")+" Запуск python-скрипта для чтения данных из локального сервера и передачи в публичный ")
        try:
            cur.execute(
                "select id, HomeTemp, StreetTemp, HomeHum, StreetHum, Pressuare, WindSpeed, WindDirect, Rain, BatteryCharge, reading_time, MeasureTime from HomeWeatherStationIvnya")
            result = cur.fetchall()
            # for row in result:
            #    previous_id = row[0]
            # print(previous_id);
            #print("id    HomeTemp    StreetTemp    HomeHum    StreetHum    Pressuare    WindSpeed    WindDirect    Rain    BatteryCharge    reading_time    MeasureTime")
            for row in result:
                if HTTP_REQUEST.previous_id < row[0]:
                    payload = {'api_key': 'tPmAT5Ab3j7F9', 'id': row[0], 'HomeTemp': row[1],
                               'StreetTemp': row[2], 'HomeHum': row[3], 'StreetHum': row[4],
                               'Pressuare': row[5], 'WindSpeed': row[6], 'WindDirect': row[7],
                               'Rain': row[8], 'BatteryCharge': row[9], 'reading_time': row[10], 'MeasureTime': row[11]}
                    response_decoded_json = requests.post(HTTP_REQUEST.url, data=payload, headers=HTTP_REQUEST.header,timeout=1)
                    #print(
                    #    "%d       %s           %s           %s          %s            %s           %s           %s         %s         %s              %s               %s" % (
                    #    row[0], row[1], row[2], row[3], row[4], row[5], row[6], row[7], row[8], row[9], row[10], row[11]))
            logs.write_log(datetime.datetime.now().strftime("%d-%b-%Y_%H:%M:%S")+" Публичная БД была успешная обновлена! ")
            #print(datetime.datetime.now().strftime("%d-%b-%Y_%H:%M:%S")+" Публичная БД была успешная обновлена! ")
            previous_id = row[0]
        except:
            myconn.rollback()
            logs.write_log(datetime.datetime.now().strftime("%d-%b-%Y_%H:%M:%S")+" Чтение данных из локального сервера и передача в публичный не удалась! ОШИБКА! ")
            #print(datetime.datetime.now().strftime("%d-%b-%Y_%H:%M:%S")+" Чтение данных из локального сервера и передача в публичный не удалась! ОШИБКА! ")
        myconn.close()


