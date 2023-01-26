import requests
import time, datetime
import mysql.connector
import LogsWriter


MAX_TABLE_INDEX = 350 #Максимальное кол-во строк в БД, после которой происходит очистка
#Параметры локальной БД в phpmyadmin
HOST = "localhost"  #Имя хоста
USER = "root"   #Имя пользователя в phpmyadmin
PASSWORD = "281299" #Пароль в phpmyadmin
DATABASE = "esp_data"   #Имя базы данных в phpmyadmin

class HTTP_REQUEST:
    header = {"Content-type": "application/x-www-form-urlencoded"}
    url = "http://alexgorlov99.ru/post-esp-data.php"
    url_clean_table = "http://alexgorlov99.ru/remove_table.php"
    previous_id = 0
    previous_id_1 = 0
    def clean_local_table(self,editor_journal):
        RESULT = False
        logs = LogsWriter.Logs()
        logs.write_log("OK!    " + datetime.datetime.now().strftime("%d-%b-%Y_%H:%M:%S") + " Запуск скрипта для проверки локальной базы данных")
        editor_journal.configure(state='normal')
        editor_journal.insert("insert", "OK    " + datetime.datetime.now().strftime("\t%d-%b-%Y_%H:%M:%S") + "\t\t\tЗапуск скрипта для проверки локальной базы данных\n")
        editor_journal.configure(state='disabled')
        try:
            myconn = mysql.connector.connect(host=HOST, user=USER, passwd=PASSWORD, database=DATABASE)
            cur = myconn.cursor()
            cur.execute(
                "select id, HomeTemp, StreetTemp, HomeHum, StreetHum, Pressuare, WindSpeed, WindDirect, Rain, BatteryCharge, reading_time, MeasureTime from HomeWeatherStationIvnya")
            result = cur.fetchall()
            for row in result:
                last_index = int(row[0])
            if last_index > MAX_TABLE_INDEX:
                RESULT = True
                cur.execute("TRUNCATE TABLE HomeWeatherStationIvnya")
                HTTP_REQUEST.previous_id = 0
                HTTP_REQUEST.previous_id_1 = 0
                logs.write_log("OK!    "+datetime.datetime.now().strftime("%d-%b-%Y_%H:%M:%S")+" Локальная база данных очищена! ")
                editor_journal.configure(state='normal')
                editor_journal.insert("insert", "OK    "+datetime.datetime.now().strftime("\t%d-%b-%Y_%H:%M:%S")+"\t\t\tЛокальная база данных очищена! \n")
                editor_journal.configure(state='disabled')
        except:
            myconn.rollback()
            logs.write_log("ERROR! " + datetime.datetime.now().strftime("%d-%b-%Y_%H:%M:%S") + " Не удалось проверить локальную базу данных!")
            editor_journal.configure(state='normal')
            editor_journal.insert("insert", "ERROR " + datetime.datetime.now().strftime("\t%d-%b-%Y_%H:%M:%S") + "\t\t\tНе удалось проверить локальную базу данных!\n")
            editor_journal.configure(state='disabled')
        finally:
            myconn.close()
        return RESULT
    def clean_public_table(self,editor_journal):
        logs = LogsWriter.Logs()
        try:
            #Очистка таблицы публичного сервера
            payload = {'api_key': 'tPmAT5Ab3j7F9'}
            response_decoded_json = requests.post(HTTP_REQUEST.url_clean_table, data=payload, headers=HTTP_REQUEST.header,timeout=120)
            logs.write_log("OK!    "+datetime.datetime.now().strftime("%d-%b-%Y_%H:%M:%S")+" Публичная база данных очищена! ")
            editor_journal.configure(state='normal')
            editor_journal.insert("insert", "OK    "+datetime.datetime.now().strftime("\t%d-%b-%Y_%H:%M:%S")+"\t\t\tПубличная база данных очищена! \n")
            editor_journal.configure(state='disabled')
            #print(datetime.datetime.now().strftime("%d-%b-%Y_%H:%M:%S")+ " Публичная база данных очищена! ")
        except:
            logs.write_log("ERROR! "+datetime.datetime.now().strftime("%d-%b-%Y_%H:%M:%S")+" Публичную базу данных не удалось очистить! Превышено время ожидания!")
            editor_journal.configure(state='normal')
            editor_journal.insert("insert", "ERROR "+datetime.datetime.now().strftime("\t%d-%b-%Y_%H:%M:%S")+"\t\t\tПубличную базу данных не удалось очистить! Превышено время ожидания!\n")
            editor_journal.configure(state='disabled')
            #print(datetime.datetime.now().strftime("%d-%b-%Y_%H:%M:%S")+" Публичную базу данных не удалось очистить! ")
    def send_data_from_local_to_public_server(self,editor_journal,editor_table_BD):
        read_flag = False
        logs = LogsWriter.Logs()
        logs.write_log("OK!    " + datetime.datetime.now().strftime("%d-%b-%Y_%H:%M:%S") + " Запуск скрипта для чтения данных из локального сервера и передачи в публичный ")
        editor_journal.configure(state='normal')
        editor_journal.insert("insert", "OK    " + datetime.datetime.now().strftime("\t%d-%b-%Y_%H:%M:%S") + "\t\t\tЗапуск скрипта для чтения данных из локального сервера и передачи в публичный \n")
        editor_journal.configure(state='disabled')
        try:
            myconn = mysql.connector.connect(host=HOST, user=USER, passwd=PASSWORD, database=DATABASE)
            cur = myconn.cursor()
            cur.execute(
                "select id, HomeTemp, StreetTemp, HomeHum, StreetHum, Pressuare, WindSpeed, WindDirect, Rain, BatteryCharge, reading_time, MeasureTime from HomeWeatherStationIvnya")
            result = cur.fetchall()
            for row in result:
                if HTTP_REQUEST.previous_id_1 < row[0]:
                    editor_table_BD.configure(state='normal')
                    #editor_table_BD.insert("insert","%s     %s    %s    %s          %s      %s             %s        %s     %s     %s  %s  %s\n" % (row[0], row[1], row[2], row[3], row[4], row[5], row[6], row[7], row[8], row[9], row[10], row[11]))
                    editor_table_BD.insert("insert","%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t  %s\n" % (row[0], row[1], row[2], row[3], row[4], row[5], row[6], row[7], row[8], row[9], row[10], row[11]))
                    editor_table_BD.configure(state='disabled')
            HTTP_REQUEST.previous_id_1 = row[0]
        except:
            read_flag = True
            myconn.rollback()
            logs.write_log("ERROR! " + datetime.datetime.now().strftime("%d-%b-%Y_%H:%M:%S") + " Чтение данных из локального сервера не удалось! Превышено время ожидания!")
            editor_journal.configure(state='normal')
            editor_journal.insert("insert", "ERROR " + datetime.datetime.now().strftime("\t%d-%b-%Y_%H:%M:%S") + "\t\t\tЧтение данных из локального сервера не удалось! Превышено время ожидания!\n")
            logs.write_log("ERROR! " + datetime.datetime.now().strftime("%d-%b-%Y_%H:%M:%S") + " Публичную БД обновить не удалось!")
            editor_journal.insert("insert", "ERROR " + datetime.datetime.now().strftime("\t%d-%b-%Y_%H:%M:%S") + "\t\t\tПубличную БД обновить не удалось!\n")
            editor_journal.configure(state='disabled')
        finally:
            myconn.close()

        if(read_flag == False):
            send_flag = False
            for row in result:
                if HTTP_REQUEST.previous_id < row[0]:
                    payload = {'api_key': 'tPmAT5Ab3j7F9', 'id': row[0], 'HomeTemp': row[1],
                                'StreetTemp': row[2], 'HomeHum': row[3], 'StreetHum': row[4],
                                'Pressuare': row[5], 'WindSpeed': row[6], 'WindDirect': row[7],
                                'Rain': row[8], 'BatteryCharge': row[9], 'reading_time': row[10], 'MeasureTime': row[11]}
                    try:
                        response_decoded_json = requests.post(HTTP_REQUEST.url, data=payload, headers=HTTP_REQUEST.header,timeout=120)
                    except:
                        logs.write_log("ERROR! " + datetime.datetime.now().strftime("%d-%b-%Y_%H:%M:%S") + " Передача данных в публичный сервер не удалась! Превышено время ожидания!")
                        editor_journal.configure(state='normal')
                        editor_journal.insert("insert", "ERROR " + datetime.datetime.now().strftime("\t%d-%b-%Y_%H:%M:%S") + "\t\t\tПередача данных в публичный сервер не удалась! Превышено время ожидания!\n")
                        logs.write_log("ERROR! " + datetime.datetime.now().strftime("%d-%b-%Y_%H:%M:%S") + " Публичную БД обновить не удалось!")
                        editor_journal.insert("insert", "ERROR " + datetime.datetime.now().strftime("\t%d-%b-%Y_%H:%M:%S") + "\t\t\tПубличную БД обновить не удалось!\n")
                        editor_journal.configure(state='disabled')
                        send_flag = True
                        break
            HTTP_REQUEST.previous_id = row[0]
            if (send_flag == False):
                logs.write_log("OK!    "+ datetime.datetime.now().strftime("%d-%b-%Y_%H:%M:%S")+" Публичная БД была успешно обновлена! ")
                editor_journal.configure(state='normal')
                editor_journal.insert("insert", "OK    "+ datetime.datetime.now().strftime("\t%d-%b-%Y_%H:%M:%S")+"\t\t\tПубличная БД была успешно обновлена! \n")
                editor_journal.configure(state='disabled')

