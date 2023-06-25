import cv2

detector = cv2.CascadeClassifier('haarcascade_frontalface_alt.xml')
cap = cv2.VideoCapture(0)
#cap.set(cv2.CAP_PROP_FRAME_WIDTH, 640)
#cap.set(cv2.CAP_PROP_FRAME_HEIGHT, 480)

sampleNum = 0
Id = input('enter your id: ')
while True:
    ret, img = cap.read()
    gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    faces = detector.detectMultiScale(gray, 1.3, 5)
    for (x, y, w, h) in faces:
        cv2.rectangle(img, (x, y), (x + w, y + h), (255, 0, 0), 2)
        # incrementing sample number
        sampleNum = sampleNum + 1
        # saving the captured face in the dataset folder
        cv2.imwrite("dataSet/User." + str(Id) + '.' + str(sampleNum) + ".jpg", gray[y:y + h, x:x + w])  #
        cv2.imshow('frame', img)
        print(sampleNum);
    # wait for 100 miliseconds
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break
    # break if the sample number is morethan 20
    elif sampleNum > 200:
        break
cap.release()
cv2.destroyAllWindows()
