
import sys
import os
from urllib2 import urlopen

if len (sys.argv) < 7:
    print ('<login> <pass> <action> <start> <end> <outputfile>')
elif len (sys.argv) == 7:
    ilogin = 1
    ipass = 2
    iaction = 3
    istart = 4
    iend = 5
    ioutputfile = 6
    error_codes = [ 110, 120, 210, 220, 230, 310, 320, 410, 420 ]
    error_code = { 
                     110: "Access denied. All parameters missing",
                     120: "Only GET request allowed",
                     210: "One of more parameters missing",
                     220: "Wrong date format",
                     230: "Dates interval must be under 30 days",
                     310: "Connection error. Incorrect Login/Password",
                     320: "Specified campaign doesn't belong to specified affiliate",
                     410: "No lead during this period or campaign",
                     420: "No sale during this period or campaign"
                 }

    for i in error_codes: terminal.cout ('warning', "["+str(i)+"]"+ "\t"+error_code[i])

    output = "http://api.afilio.com.br/?login="+sys.argv[ilogin]+"&pass="+sys.argv[ipass]+"&action="+sys.argv[iaction]+"&start="+sys.argv[istart]+"&end="+sys.argv[iend]+"&plateform=afi"
    print ('Abrindo url:\t' + output)
    open(sys.argv[ioutputfile], 'w').write(urlopen(output).read())
    print ('Arquivo Salvo\t\t'+sys.argv[ioutputfile])

else:
    print ("Muitos parametros!")
    for i in sys.argv: terminal.cout ('warning', i)


