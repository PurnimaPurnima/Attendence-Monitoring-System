## The code works for python 2.x 

# Attendence-Monitoring-System
we use a fingerprint sensor to give attendance  and maintain a database for the same
![attence_monitoring](https://user-images.githubusercontent.com/34301506/47965326-ab02a580-e06b-11e8-8d34-0e4dc5f5f3fe.png)


# 1.Enroll: It is used at the time of student registration
This is used to add details of  new student to our databse.
the camera captures image of the student and  name along with student id is stored
# 2.Give atttendence:
This section asks the student to select the subject first and then give the attendence for the same 
# 3.Check attendence:
This section diplays the attendence of a student based on the student unique id ,so that student can track his attendence.


# Files:
## 1.arduino files:
A.original
B.code_with_lcd_display
## 2. python code.py

 
# Instructions to follow:

1. first connect the tx and rx of the finger print module to to pin 2,3 of arduino respectively .Also connect vcc and gnd

2. Next,open  folder arduino files/original/orignal.ino:
 upload the code to the arduino
# Also note the com port used for serial communication  in my case com6
3. finally open python_code.py  and set the com port to the port on your pc and run the code while 



# libraries required :
1. pyserial: install using >pip install pyserial
2. opencv : install using > pip install python-opencv
3. mysql : install using > pip install mysql-connector 


