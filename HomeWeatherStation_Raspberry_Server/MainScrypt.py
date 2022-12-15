import http_request
import time, datetime
import telegram_bot
import threading
import mysql.connector
import Email_bot
import LogsWriter

#Старт работы с логами и очистка файла с логами
logs=LogsWriter.Logs()
logs.clean_log()

logs.write_log("Запуск работы сервера для проекта HomeWeatherStation...")
#print("Запуск работы сервера для проекта HomeWeatherStation...")
http_req = http_request.HTTP_REQUEST()
#Первичная очистка публичной БД
http_req.clean_public_table()
#Запуск телеграмм-бота
tg=telegram_bot.Telegramm()

start_time_for_request=datetime.datetime.now()
start_time_for_tg=datetime.datetime.now()
#Запуск Email-бота
email_bot = Email_bot.Email()

while(1):
    diff_for_request=datetime.datetime.now()-start_time_for_request
    diff_for_tg = datetime.datetime.now() - start_time_for_tg
    #Обновление публичной БД каждые 60сек
    if (diff_for_request.seconds>60):
        http_req.send_data_from_local_to_public_server()
        start_time_for_request=datetime.datetime.now()
    #Отправка отчета в Tg и Email каждые 24 часа
    if (diff_for_tg.seconds>14400):
        now_time=datetime.datetime.now()
        tg.send_report_tg(start_time_for_tg,now_time)
        email_bot.sendMail(start_time_for_tg,now_time)
        start_time_for_tg=datetime.datetime.now()



