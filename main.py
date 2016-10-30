import cv2
import sys
import serial
import time
import struct

cascPath = sys.argv[1]
faceCascade = cv2.CascadeClassifier(cascPath)

video_capture = cv2.VideoCapture(1)
ser = serial.Serial('/dev/ttyACM0', 9600)

while True:
    # Capture frame-by-frame
    ret, frame = video_capture.read()

    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

    faces = faceCascade.detectMultiScale(
        gray,
        scaleFactor=1.1,
        minNeighbors=5,
        minSize=(30, 30),
        flags=cv2.cv.CV_HAAR_SCALE_IMAGE
    )

    if(len(faces) > 0) :
        for (x, y, w, h) in faces:
            cv2.rectangle(frame, (x, y), (x+w, y+h), (0, 255, 0), 2)
            print 'X: ', x, ' Y: ', y

            status = "0"

            if(y < 150) :
                ser.write("1")
            if(y > 230) :
                ser.write("2")
            if(y < 230 or y > 150) :
                ser.write("3")
            if(x < 180) :
                ser.write("4")
            if(x > 380) :
                ser.write("5")
            if(x < 380 or x > 180):
                ser.write("6")
    else:
        print 'No Face'
        ser.write("0")

    # Display the resulting frame
    cv2.imshow('GLaDOS Eye', frame)

    if cv2.waitKey(1) & 0xFF == ord('q'):
        ser.close()
        break

# When everything is done, release the capture
video_capture.release()
cv2.destroyAllWindows()
