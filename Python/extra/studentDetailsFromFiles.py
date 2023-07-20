# return student details as name: sambit chakraborty and other in new lines from a file student_lab_details.txt

def getStudentDetails(filename):
    with open(filename) as f:
        for line in f:
            print(line)

filename = 'student_lab_details.txt'
getStudentDetails(filename)

# output
# name: sambit chakraborty
# roll: 123
