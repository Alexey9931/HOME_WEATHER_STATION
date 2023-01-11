import time, datetime
import telepot
import mysql.connector
from telepot.loop import MessageLoop
import report
import LogsWriter

CHAT_ID = -814491667
BOT_ID = '5443734906:AAEaSLlrtKSQchGo1Yix5eRXqCJONtOZlnc'
#Параметры локальной БД в phpmyadmin
HOST = "localhost"  #Имя хоста
USER = "root"   #Имя пользователя в phpmyadmin
PASSWORD = "281299" #Пароль в phpmyadmin
DATABASE = "esp_data"   #Имя базы данных в phpmyadmin

class Telegramm:
    street_temp = ""
    street_hum = ""
    home_temp = ""
    home_hum = ""
    pressure = ""
    wind_speed = ""
    wind_direct = ""
    rain = ""
    telegram_bot = None

    def start_Tg_BOT(self):
        logs = LogsWriter.Logs()
        try:
            Telegramm.telegram_bot = telepot.Bot(BOT_ID)
            MessageLoop(Telegramm.telegram_bot, Telegramm.action).run_as_thread()
            Telegramm.telegram_bot.sendMessage(CHAT_ID,str("📢Доброго времени суток!\n"
                                                    "⚡️Удаленный сервер для работы с HomeWeatherStation успешно запущен!⚡️\n"
                                                    "💡Для получения дополнительной информации и помощи введите команду \"Help\"."))

            logs.write_log("OK!    "+datetime.datetime.now().strftime("%d-%b-%Y_%H:%M:%S")+' Телеграмм-бот успешно запущен ')
        except:
            logs.write_log("ERROR! " + datetime.datetime.now().strftime("%d-%b-%Y_%H:%M:%S") + ' Телеграмм-бот не удалось запустить! ')
    def action(msg):
        try:
            #telegram_bot = telepot.Bot('5443734906:AAEaSLlrtKSQchGo1Yix5eRXqCJONtOZlnc')
            #chat_id = msg['chat']['id']
            command = msg['text']
            #print ('Received: %s' % command)
            if command == 'Help':
                try:
                    Telegramm.telegram_bot.sendMessage(CHAT_ID, str("🚨Служба поддержки к вашим услугам!\n"
                                                          "Основные поддерживаемые команды👇\n"
                                                          "🔹\"Help\" - Вызов службы поддержки\n"
                                                          "🔹\"MoreInfo\" - Информация о проекте\n"
                                                          "🔹\"NowWeather\" - Текущая погода(последнее измерение)\n"
                                                          "🔹\"Logs\" - Журнал со служебной информацией о работе сервера*\n"
                                                          "*Для разработчиков"))
                except:
                    pass
            elif command == 'MoreInfo':
                try:
                    Telegramm.telegram_bot.sendMessage(CHAT_ID, str("⚡️Проект HomeWeatherStation - Домашняя метеостанция⚡️\n"
                                                          "📌 Данное устройство предназначено для измерения основных метеорологических "
                                                          "параметров (температура, влажность, давление, параметры ветра,осадки)"
                                                          " внутри помещения и на улице в режиме реального времени.\n📌 Измерительная "
                                                          "система состоит из уличной"
                                                          " станции - для мониторинга погоды на улице и домашнего приемного устройства - "
                                                          "для проведения измерений в помещении. \n📌 Также возможности данного проекта (при наличии подключения к Wi-Fi и доступа к сети Интернет)"
                                                          "предполагают доступ к удаленному публичному серверу "
                                                          "для передачи показаний в базу данных, рассылки отчетов с результатами измерений "
                                                          "в Telegram, на электронную почту, а также для передачи данных в "
                                                          "мобильное приложение для устройств на ОС Android - \"HomeWeatherStationApp\"."))
                except:
                    pass
            elif command == 'NowWeather':
                try:
                    myconn = mysql.connector.connect(host=HOST, user=USER, passwd=PASSWORD,database=DATABASE)
                    cur = myconn.cursor()
                    cur.execute(
                        "select id, HomeTemp, StreetTemp, HomeHum, StreetHum, Pressuare, WindSpeed, WindDirect, Rain, BatteryCharge, reading_time, MeasureTime from HomeWeatherStationIvnya")
                    result = cur.fetchall()
                    for row in result:
                        Telegramm.street_temp = row[2]
                        Telegramm.street_hum = row[4]
                        Telegramm.home_temp = row[1]
                        Telegramm.home_hum = row[3]
                        Telegramm.pressure = row[5]
                        Telegramm.wind_speed = row[6]
                        Telegramm.wind_direct = row[7]
                        Telegramm.rain = row[8]
                    Telegramm.telegram_bot.sendMessage(CHAT_ID,str("❗️Текущее состояние погоды на момент последнего измерения👇\n"
                                                 "🔻На улице:\n"
                                                 "      🌡ТЕМПЕРАТУРА         " + Telegramm.street_temp + " °C\n"
                                                 "      💧ВЛАЖНОСТЬ           " + Telegramm.street_hum + " %\n"
                                                 "      ☔️КОЛ-ВО ОСАДКОВ      " + Telegramm.rain + " %\n"
                                                 "      🌬СКОРОСТЬ ВЕТРА      " + Telegramm.wind_speed + " м/с\n"
                                                 "      🚩НАПРАВЛЕНИЕ ВЕТРА   " + Telegramm.wind_direct + "\n"
                                                 "🔻В помещении:\n"
                                                 "      🌡ТЕМПЕРАТУРА         " + Telegramm.home_temp + " °C\n"
                                                 "      💧ВЛАЖНОСТЬ           " + Telegramm.home_hum + " %\n"
                                                 "      🧭АТМ.ДАВЛЕНИЕ        " + Telegramm.pressure + " мм.рт.ст"))
                except:
                    myconn.rollback()
                finally:
                    myconn.close()
            elif command == 'Logs':
                try:
                    Telegramm.telegram_bot.sendMessage(CHAT_ID, str("🛠️Журнал с информацией о работе ПО сервера👇"))
                    Telegramm.telegram_bot.sendDocument(CHAT_ID, document=open('/home/alexey/HomeWeatherStationProject/debug/logs.txt', 'rb'))
                except:
                    pass
            #elif command == 'report':
            #    telegram_bot.sendDocument(chat_id, document=open('/home/alexey/HomeWeatherStationProject/GFG.pdf', 'rb'))
        except:
            pass
    def send_report_tg(self,file_name,start_time,end_time):
        logs = LogsWriter.Logs()
        try:
            #chat_id = msg['chat']['id']
            #command = msg['text']
            Telegramm.telegram_bot.sendMessage(CHAT_ID, str("‼️Привет от HomeWeatherStation😀!\n📎Твой отчет о состоянии погоды за прошедшие сутки с "+ start_time.strftime("%d/%b/%Y %Hч %Mмин %Sсек") + " по " + end_time.strftime("%d/%b/%Y %Hч %Mмин %Sсек") + " 👇"))
            time.sleep(2)
            Telegramm.telegram_bot.sendDocument(CHAT_ID, document=open('/home/alexey/HomeWeatherStationProject/debug/'+file_name, 'rb'))
            logs.write_log("OK!    "+ datetime.datetime.now().strftime("%d-%b-%Y_%H:%M:%S")+' Отправка отчета в Tg-bot успешно завершена! ')
            #print(datetime.datetime.now().strftime("%d-%b-%Y_%H:%M:%S")+' Отправка отчета успешно завершена! ')
            Result = True
        except:
            logs.write_log("ERROR! "+ datetime.datetime.now().strftime("%d-%b-%Y_%H:%M:%S")+' Отправка отчета в Tg-bot не удалась! ')
            Result = False
            #print(datetime.datetime.now().strftime("%d-%b-%Y_%H:%M:%S")+' Отправка отчета в Tg-bot не удалась! ОШИБКА! ')
        return  Result
    def send_wifi_error_tg(self):
        logs = LogsWriter.Logs()
        try:
            #telegram_bot = telepot.Bot('5443734906:AAEaSLlrtKSQchGo1Yix5eRXqCJONtOZlnc')
            Telegramm.telegram_bot.sendMessage(CHAT_ID, str("‼СООБЩЕНИЕ ОБ ОШИБКЕ!\nВ течение некоторого времени отсутствовало Wi-Fi соединение!\n"
                                                     "Возможны сбои в работе сервера (нарушены процедуры обновления БД и отправки отчетов)!"))
            time.sleep(2)
            telegram_bot.sendMessage(CHAT_ID,str("✅На данный момент работа сервера успешно восстановлена!"))
        except:
            logs.write_log("ERROR! "+ datetime.datetime.now().strftime("%d-%b-%Y_%H:%M:%S")+' Отправка сообщения об ошибке в Tg-bot не удалась! ')


