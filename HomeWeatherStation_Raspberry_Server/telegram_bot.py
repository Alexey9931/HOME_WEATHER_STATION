import time, datetime
import telepot
from telepot.loop import MessageLoop
import report
import LogsWriter

class Telegramm:
    def start_Tg_BOT(self):
        logs = LogsWriter.Logs()
        telegram_bot = telepot.Bot('5443734906:AAEaSLlrtKSQchGo1Yix5eRXqCJONtOZlnc')
        # print (telegram_bot.getMe())
        MessageLoop(telegram_bot, Telegramm.action).run_as_thread()
        logs.write_log(datetime.datetime.now().strftime("%d-%b-%Y_%H:%M:%S")+' Телеграмм-бот успешно запущен ')
        #print(datetime.datetime.now().strftime("%d-%b-%Y_%H:%M:%S")+' Телеграмм-бот успешно запущен ')
    def action(msg):
        chat_id = msg['chat']['id']
        command = msg['text']
        #print ('Received: %s' % command)
        if command == 'hi':
            telegram_bot.sendMessage(chat_id, str("Hi! CircuitDigest"))
        elif command == 'report':
            telegram_bot.sendDocument(chat_id, document=open('/home/alexey/HomeWeatherStationProject/GFG.pdf', 'rb'))
    def send_report_tg(self,start_time,end_time):
        logs = LogsWriter.Logs()
        try:
            telegram_bot = telepot.Bot('5443734906:AAEaSLlrtKSQchGo1Yix5eRXqCJONtOZlnc')
            #chat_id = msg['chat']['id']
            #command = msg['text']
            Report=report.MakeReport()
            file_name=Report.make_report(start_time,end_time)
            telegram_bot.sendMessage(-814491667, str("Привет от HomeWeatherStation😀! Твой отчет о состоянии погоды за прошедшие сутки с "+ start_time.strftime("%d/%b/%Y %Hч %Mмин %Sсек") + " по " + end_time.strftime("%d/%b/%Y %Hч %Mмин %Sсек") + " 👇"))
            telegram_bot.sendDocument(-814491667, document=open('/home/alexey/HomeWeatherStationProject/debug/'+file_name, 'rb'))
            logs.write_log(datetime.datetime.now().strftime("%d-%b-%Y_%H:%M:%S")+' Отправка отчета успешно завершена! ')
            #print(datetime.datetime.now().strftime("%d-%b-%Y_%H:%M:%S")+' Отправка отчета успешно завершена! ')
        except:
            logs.write_log(datetime.datetime.now().strftime("%d-%b-%Y_%H:%M:%S")+' Отправка отчета в Tg-bot не удалась! ОШИБКА! ')
            #print(datetime.datetime.now().strftime("%d-%b-%Y_%H:%M:%S")+' Отправка отчета в Tg-bot не удалась! ОШИБКА! ')
