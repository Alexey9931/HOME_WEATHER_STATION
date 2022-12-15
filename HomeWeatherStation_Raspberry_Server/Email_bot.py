import smtplib
import mimetypes
import email
import email.mime.application
import email.mime.multipart
import report
import LogsWriter
import time, datetime

class Email:
    fromaddr = "gorlovalex12@mail.ru"  # измените этот email адрес на тот, который необходим вам
    toaddr = "gorlovalex12@mail.ru"

    def readFile(self,start_time,end_time):
        Report = report.MakeReport()
        file_name = "debug/"+Report.make_report(start_time, end_time)
        with open(file_name) as file_object:
            contents = file_object.read()
        return contents

    def sendMail(self,start_time, end_time):
        logs = LogsWriter.Logs()
        Report = report.MakeReport()
        logs.write_log(datetime.datetime.now().strftime("%d-%b-%Y_%H:%M:%S") + " Запуск отправки отчета на email")
        msg = email.mime.multipart.MIMEMultipart()
        msg['Subject'] = 'HomeWeatherStation отчет за сутки'
        msg['From'] = 'gorlovalex12@mail.ru'
        msg['To'] = 'gorlovalex12@mail.ru'

        file_name = "debug/" + Report.make_report(start_time, end_time)
        file = open(file_name,'rb')
        att = email.mime.application.MIMEApplication(file.read(), _subtype="pdf")
        file.close()
        att.add_header('Content-Disposition', 'attachment', filename=file_name)
        msg.attach(att)

        server = smtplib.SMTP('smtp.mail.ru', 587)
        server.starttls()
        server.login(Email.fromaddr, "TMMVBr51s5reyqe8gzV4")
        server.sendmail(Email.fromaddr, Email.toaddr, msg.as_string())
        server.quit()
        logs.write_log(datetime.datetime.now().strftime("%d-%b-%Y_%H:%M:%S")+ " Отчет на email отправлен!")
        #print(datetime.datetime.now().strftime("%d-%b-%Y_%H:%M:%S")+ " Отчет на email отправлен!")
