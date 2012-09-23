import smtplib
from sys import argv, stdout

server_port = 587
server_smtp = 'smtp.gmail.com'
user = { 'login': 'leonsilverchain.ugf@gmail.com', 'password': 'leonsilverchain', 'email': 'leonsilverchain.ugf@gmail.com' }
subject = 'Trabalho de Redes 2'
to = argv[1]
message = ''
for i in range (2, len(argv)):
    message += argv[i] + ' '

server = smtplib.SMTP(server_smtp, server_port)
server.ehlo()
server.starttls()
server.ehlo()
server.login (user['login'], user['password'])
server.sendmail(user['email'], to, message)
server.close()

