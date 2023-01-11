import subprocess
import http_request
import time, datetime
import telegram_bot
import threading
import mysql.connector
import Email_bot
import LogsWriter
import report
import interface

TIME_UPDATE_DATA_BASE = 60 #время обновления публичной БД в сек
TIME_SEND_TG_AND_EMAIL = 86400 #время отправки данных в телеграмм и Email в сек

Wi_Fi_Error_Flag = False

def check_wifi_connection():
    ps = subprocess.Popen(['iwgetid'], stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
    try:
        output = subprocess.check_output(('grep', 'ESSID'), stdin=ps.stdout)
        #logs.write_log("OK!    " + datetime.datetime.now().strftime("%d-%b-%Y_%H:%M:%S ") + output)
        return True
    except subprocess.CalledProcessError:
        # grep did not match any lines
        #logs.write_log("ERROR! "+ datetime.datetime.now().strftime("%d-%b-%Y_%H:%M:%S")+" Отсутствует wi-fi соединение!")
        return False
interface.start_window_interface()
#Старт работы с логами и очистка файла с логами
logs=LogsWriter.Logs()
logs.clean_log()
logs.write_log("OK!    "+"Запуск работы сервера для проекта HomeWeatherStation...")
#Проверка wi-fi соединения
if check_wifi_connection() != True:
    logs.write_log("ERROR! " + datetime.datetime.now().strftime("%d-%b-%Y_%H:%M:%S") + " Отсутствует wi-fi соединение!")
    exit()
else:
    logs.write_log("OK!    " + datetime.datetime.now().strftime("%d-%b-%Y_%H:%M:%S") + " wi-fi соединение успешно установлено!")
#Запуск телеграмм-бота
tg=telegram_bot.Telegramm()
tg.start_Tg_BOT()

http_req = http_request.HTTP_REQUEST()
#Проверка локальной БД на необходимость очистки
http_req.clean_local_table()
#Первичная очистка публичной БД
http_req.clean_public_table()

start_time_for_request=datetime.datetime.now()
start_time_for_tg=datetime.datetime.now()
#Запуск Email-бота
email_bot = Email_bot.Email()
#Обновление публичной БД первый раз
http_req.send_data_from_local_to_public_server()
while(1):
    diff_for_request=datetime.datetime.now()-start_time_for_request
    diff_for_tg = datetime.datetime.now() - start_time_for_tg
    #Отправка сообщения в Tg, если не было Wi-Fi,а при этом должны были отправляться отчеты
    if (check_wifi_connection() != False) and (Wi_Fi_Error_Flag==True):
        time.sleep(60)
        tg.send_wifi_error_tg()
        Wi_Fi_Error_Flag = False
    #Обновление публичной БД каждые 60сек
    if (diff_for_request.seconds > TIME_UPDATE_DATA_BASE):
        if (check_wifi_connection() != False) and (Wi_Fi_Error_Flag!=True):
            http_req.send_data_from_local_to_public_server()
            Wi_Fi_Error_Flag = False
        else:
            logs.write_log("ERROR! " + datetime.datetime.now().strftime("%d-%b-%Y_%H:%M:%S") + " Отсутствует wi-fi соединение!")
            Wi_Fi_Error_Flag=True
        start_time_for_request=datetime.datetime.now()
    #Отправка отчета в Tg и Email каждые 24 часа
    if (diff_for_tg.seconds > TIME_SEND_TG_AND_EMAIL):
        if (check_wifi_connection() != False) and (Wi_Fi_Error_Flag!=True):
            now_time=datetime.datetime.now()
            #Формириование отчета
            Report = report.MakeReport()
            time.sleep(5)
            pdf_report_file_name = Report.make_report(start_time_for_tg, now_time)
            #Отправка в Tg
            if tg.send_report_tg(pdf_report_file_name,start_time_for_tg, now_time) == False:
                time.sleep(2)
                logs.write_log("OK!    " + datetime.datetime.now().strftime("%d-%b-%Y_%H:%M:%S") + ' 2-я попытка отправки отчета в Tg-bot! ')
                time.sleep(2)
                if tg.send_report_tg(pdf_report_file_name,start_time_for_tg, now_time) == False:
                    logs.write_log("OK!    " + datetime.datetime.now().strftime("%d-%b-%Y_%H:%M:%S") + ' 3-я попытка отправки отчета в Tg-bot! ')
                    time.sleep(2)
                    tg.send_report_tg(pdf_report_file_name, start_time_for_tg, now_time)
                    time.sleep(2)
            # Отправка на Email
            email_bot.sendMail(pdf_report_file_name)
            time.sleep(2)
            Wi_Fi_Error_Flag = False
            # Проверка локальной и публичной БД на необходимость очистки
            if http_req.clean_local_table() == True:
                http_req.clean_public_table()
        else:
            logs.write_log("ERROR! " + datetime.datetime.now().strftime("%d-%b-%Y_%H:%M:%S") + " Отсутствует wi-fi соединение!")
            Wi_Fi_Error_Flag = True
        start_time_for_tg = datetime.datetime.now()



