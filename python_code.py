import serial               # add Serial library for Communication with Arduino
import time
import cv2
import mysql.connector  

mydb = mysql.connector.connect(
  host="localhost",
  user="root",
  passwd="",
  database="classroom"
)

mycursor = mydb.cursor()

def hashs(x):
    if x == '1':
        return "Computer Science"
    if x == '2':
        return "Mathematics"

cap=cv2.VideoCapture(0)
Arduino_Serial = serial.Serial('com6',9600)  #Create Serial port object called arduinoSerialData
time.sleep(2)

print Arduino_Serial.readline()                  #read the serial data and print it as line

print("Enter a choice.\n1:Enroll new student.\n2:Take Attendance\n3.Check Attendance ");
while True:
    var = raw_input() #get input from user

##          click and save an image with the users id at this stage       
    
    if (var == '1'): #if the value is 1
        Arduino_Serial.write('1') #send 1
        time.sleep(1)
        #print("\n\nAdafruit Fingerprint sensor enrollment")
        print("\n\nPlease type in the ID # (from 1 to 127) you want to save this finger as...")
        var2=raw_input()
        name=raw_input("Please Enter your Name  ")
        print("Look into the Camera and Smile, please! :) ")
        ret,img=cap.read()
        cv2.imwrite(var2+'.jpg',img)
        Arduino_Serial.write(var2) #send 1
        print("\n\nReady to Enroll new Fingerprint!")
        count=0
        while(count<12):
            strr = Arduino_Serial.readline()                  #read the serial data and print it as line
            print strr
            if(strr=="Stored!"):
                print("here")
            count+=1        
        sql = "INSERT INTO it_classroom (id ,name, img_src, attendance) VALUES ("+var2+" ,'"+name+"', '"+var2+".jpg', 0)"
        #val = (var2,name,var2+'.jpg',0)
        mycursor.execute(sql)
        mydb.commit()
        print ("New Fingerprint Added Successfully! ")
        
        
    if (var == '2'): #if the value is 2
        print("Enter the Subject Code:")
        print("1)Computer \n2)Maths")
        sub = raw_input()
        date = "04112018"
        Arduino_Serial.write('2') #send 2
        time.sleep(1)
        print("Waiting for valid finger...")
        time.sleep(1)
        print Arduino_Serial.readline()                  #read the serial data and print it as line
        count=0
        while(True):
            strr = Arduino_Serial.read()                  #read the serial data and print it as line
            print strr
            img = cv2.imread(strr+'.jpg')
            cv2.imshow('image',img)
            cv2.waitKey(0)== 27
            cv2.destroyAllWindows()
            sql = "INSERT INTO attendance_monitor (id , sub, date) VALUES ("+strr+" ,'"+sub+"', "+date+")"
            mycursor.execute(sql)
            mydb.commit()
            print("Success!") 
            
    if(var=='3'):
        var3=raw_input("\nEnter ID to check Attendence. ")
        query = "SELECT count(id),sub FROM attendance_monitor1 where id="+var3+" group by sub"
        mycursor.execute(query)

        myresult = mycursor.fetchall()

        for x in myresult:
            print "Attendance of subject ",hashs(x[1]),"is ",x[0],"."
