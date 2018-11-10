import serial
import subprocess
from time import  gmtime, strftime, sleep

def execute(command):
    process = subprocess.Popen(command, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
    
    while process.returncode == None:
        process.poll()
        if process.returncode != None:
                process.kill()
    
    process.wait()
    output, errors= process.communicate()
    output = output.splitlines()
    return (output,errors)

def getInformation(data,key):
    for aux in data:
        aux = aux.decode("utf-8")
        information = aux.split(key)

        if(len(information)>1):
            break
    out = information[1]
    return(out)

def getTest(testcode):
    if testcode == 1:
        return(["/opt/hadoop/bin/hadoop","jar","/opt/hadoop/share/hadoop/mapreduce/hadoop-mapreduce-examples-2.7.5.jar","wordcount","/test100MB.txt","/result/"+str(cont)+"test100MBOut.txt"])
    elif testcode == 2:
        return(["/opt/hadoop/bin/hadoop","jar","/opt/hadoop/share/hadoop/mapreduce/hadoop-mapreduce-examples-2.7.5.jar","wordcount","/test200MB.txt","/result/"+str(cont)+"test200MBOut.txt"])
    elif testcode == 3:
        return(["/opt/hadoop/bin/hadoop","jar","/opt/hadoop/share/hadoop/mapreduce/hadoop-mapreduce-examples-2.7.5.jar","wordcount","/test300MB.txt","/result/"+str(cont)+"test300MBOut.txt"])
    elif testcode == 4:
        return(["/opt/hadoop/bin/hadoop","jar","/opt/hadoop/share/hadoop/mapreduce/hadoop-mapreduce-examples-2.7.5.jar","wordcount","/test400MB.txt","/result/"+str(cont)+"test400MBOut.txt"])
    elif testcode == 5:
        return(["/opt/hadoop/bin/hadoop","jar","/opt/hadoop/share/hadoop/mapreduce/hadoop-mapreduce-examples-2.7.5.jar","wordcount","/test500MB.txt","/result/"+str(cont)+"test500MBOut.txt"])
    elif testcode == 6:
        return(["/opt/hadoop/bin/hadoop","jar","/opt/hadoop/share/hadoop/mapreduce/hadoop-mapreduce-examples-2.7.5.jar","wordcount","/test600MB.txt","/result/"+str(cont)+"test600MBOut.txt"])
    elif testcode == 7:
        return(["/opt/hadoop/bin/hadoop","jar","/opt/hadoop/share/hadoop/mapreduce/hadoop-mapreduce-examples-2.7.5.jar","wordcount","/test700MB.txt","/result/"+str(cont)+"test700MBOut.txt"])
    elif testcode == 8:
        return(["/opt/hadoop/bin/hadoop","jar","/opt/hadoop/share/hadoop/mapreduce/hadoop-mapreduce-examples-2.7.5.jar","wordcount","/test800MB.txt","/result/"+str(cont)+"test800MBOut.txt"])
    elif testcode == 9:
        return(["/opt/hadoop/bin/hadoop","jar","/opt/hadoop/share/hadoop/mapreduce/hadoop-mapreduce-examples-2.7.5.jar","wordcount","/test900MB.txt","/result/"+str(cont)+"test900MBOut.txt"])
    elif testcode == 10:
        return(["/opt/hadoop/bin/hadoop","jar","/opt/hadoop/share/hadoop/mapreduce/hadoop-mapreduce-examples-2.7.5.jar","wordcount","/test1000MB.txt","/result/"+str(cont)+"test1000MBOut.txt"])
    elif testcode == 11:
        return(["/opt/hadoop/bin/hadoop","jar","/opt/hadoop/share/hadoop/mapreduce/hadoop-mapreduce-examples-2.7.5.jar","wordcount","/license.txt","/result/"+str(cont)+"license_out.txt"])
    elif testcode == 12:
        return(["/opt/hadoop/bin/hadoop","jar","/opt/hadoop/share/hadoop/mapreduce/hadoop-mapreduce-examples-2.7.5.jar","pi","4","2"])
    else:
        return(0)
def printInformationList(out):
    for aux in out:
        print(str(aux))
def checkPages():
    command = ["jps"]
    output,error = execute(command)
    printInformationList(output)
    print("error: "+error)

def checkNodesActive():
    command = ["yarn","node","-list"]
    output,error = execute(command)
    printInformationList(output)
    print("error: "+error)

def getFileToUploadHdfs(selectcode):
    if selectcode == 1:
        return(["hdfs","dfs","-copyFromLocal","/home/hduser/Documentos/file_test/test100MB.txt","/files/test100MB.txt"])
    elif selectcode == 2:
        return(["hdfs","dfs","-copyFromLocal","/home/hduser/Documentos/file_test/test200MB.txt","/files/test200MB.txt"])
    elif selectcode == 3:
        return(["hdfs","dfs","-copyFromLocal","/home/hduser/Documentos/file_test/test300MB.txt","/files/test300MB.txt"])
    elif selectcode == 4:
        return(["hdfs","dfs","-copyFromLocal","/home/hduser/Documentos/file_test/test400MB.txt","/files/test400MB.txt"])
    elif selectcode == 5:
        return(["hdfs","dfs","-copyFromLocal","/home/hduser/Documentos/file_test/test500MB.txt","/files/test500MB.txt"])
    elif selectcode == 6:
        return(["hdfs","dfs","-copyFromLocal","/home/hduser/Documentos/file_test/test600MB.txt","/files/test600MB.txt"])
    elif selectcode == 7:
        return(["hdfs","dfs","-copyFromLocal","/home/hduser/Documentos/file_test/test700MB.txt","/files/test700MB.txt"])
    elif selectcode == 8:
        return(["hdfs","dfs","-copyFromLocal","/home/hduser/Documentos/file_test/test800MB.txt","/files/test800MB.txt"])
    elif selectcode == 9:
        return(["hdfs","dfs","-copyFromLocal","/home/hduser/Documentos/file_test/test900MB.txt","/files/test900MB.txt"])
    elif selectcode == 10:
        return(["hdfs","dfs","-copyFromLocal","/home/hduser/Documentos/file_test/test1000MB.txt","/files/test1000MB.txt"])
    elif selectcode == 11:
        return(["hdfs","dfs","-copyFromLocal","/opt/hadoop/LICENSE.txt","/license.txt"])    
    else:
        return(0)

def uploadFileToHdfs(code):
   command = getFileToUploadHdfs(code)
   output,error = execute(command)
   printInformationList(output)
   print("error: "+error)

def showFilesHDFS():
    print ("HDFS /")
    command = ["hdfs","dfs","-ls","/"]
    output1 ,error1 =  execute(command)
    printInformationList(output1)
    print("error: "+error1)    
    
    print ("HDFS /result")
    command =["hdfs","dfs","-ls","/result"]
    output2 ,error2 =  execute(command)
    printInformationList(output2)
    print("error: "+error2)

    print ("HDFS /files")
    command = ["hdfs","dfs","-ls","/files"]
    output3 ,error3 =  execute(command)
    printInformationList(output3)
    print("error: "+error3)


def startHadoop():
    print ("stat Hadoop ")
    command = ["start-yarn.sh"]
    output1,error1 = execute(command)
    printInformationList(output1)
    print("error: "+error1)
    
    command = ["start-dfs.sh"]
    output2 ,error2 =  execute(command)
    printInformationList(output2)
    print("Erro: "+error2)
    checkPages()

def stopHadoop():
    print ("Stop Hadoop ")
    command = ["stop-yarn.sh"]
    output1,error1 = execute(command)
    printInformationList(output1)
    print("error: "+error1)
    
    
    command = ["stop-dfs.sh"]
    output2 ,error2 =  execute(command)
    printInformationList(output2)
    print("Erro: "+error2)
    checkPages()

def prepareHDFS():
    print("Preparando HDFS")
    command = ["hdfs","dfsadmin","-safemode","leave"]
    output1,error1 = execute(command)
    printInformationList(output1)
    print("error: "+error1)
    
    command = ["hdfs","fsck","-delete"]
    output2,error2 = execute(command)
    printInformationList(output2)
    print("error: "+error2)
    
    command = ["hdfs","dfs","-rm","-r","/result"]
    output3,error3 = execute(command)
    printInformationList(output3)
    print("error: "+error3)
    
    command = ["hdfs","dfs","-rm","-r","/files"]
    output4,error4 = execute(command)
    printInformationList(output4)
    print("error: "+error4)
    
    command = ["hdfs","dfs","-mkdir","/result"]
    output5,error5 = execute(command)
    printInformationList(output5)
    print("error: "+error5)
    
    command = ["hdfs","dfs","-mkdir","/files"]
    output6,error6 = execute(command)
    printInformationList(output6)
    print("error: "+error6)

def executeTest(n_test, codeTest, delay, delay_exec):
    cont = 0
    while(cont < n_test):
        print ("execucao" +str(cont) +"\n") 
    
        sleep(delay)
        ser.write(bytes("i","utf-8"))
        sleep(delay_exec)
        testli = getTest(11)
        start = strftime("%H:%M:%S", gmtime())
        saida, erro = execute(getTest(codeTest))
        stop = strftime("%H:%M:%S", gmtime())
    
        sleep(delay_exec)
        

        print("\nSAIDA1\n")
        print("\n")
        print(saida)
        
        application = getInformation(saida,'Submitted application ')    
        print(application)
        print("\nERRO\n")
        print(erro)
        print("\n")
        print("\nSAIDA2\n")
        print("\n")
        test = ["yarn", "application", "-status", application]
        saida1,erro1 = execute(test)
        
        print(saida1)
        print("\n")
        
        state = getInformation(saida1,'State : ')
        finalState = getInformation(saida1,'Final-State : ')
        if(state == 'FINISHED'):
            ser.write(bytes("t","utf-8"))
            if(finalState == 'SUCCEEDED'):
                pass
        
        
        print("\n")
        print(state)
        print(finalState)
        cont = cont + 1
        arquivo.writelines( start + "," + stop+ "\n")

def menu():
    option = -1
    while option != 0:
        print("_____________________________ TESTS MENU _____________________________")
        print("1  - Start the Hadoop")
        print("2  - Stop the Hadoop")
        print("3  - Show the files list in the HDFS")
        print("4  - Prepare the HDFS")
        print("5  - Execute the wordcount test with file size 100MB")
        print("6  - Execute the wordcount test with file size 200MB")
        print("7  - Execute the wordcount test with file size 300MB")
        print("8  - Execute the wordcount test with file size 400MB")
        print("9  - Execute the wordcount test with file size 500MB")
        print("10 - Execute the wordcount test with file size 600MB")
        print("11 - Execute the wordcount test with file size 700MB")
        print("12 - Execute the wordcount test with file size 800MB")
        print("13 - Execute the wordcount test with file size 900MB")
        print("14 - Execute the wordcount test with file size 1000MB")
        print("15 - Execute the wordcount test with file license.txt")
        print("16 - Execute the PI test")
        print("0  - Exit")

        while (option < 0 or option > 16) and n_test < 1 and delay_exec < 1:
            option = input("inform the option: ")
            n_test = input("inform the number of test: ")
            delay_exec = input("inform the delay for before and after (before = after): ")

        if option == 0:
            break
        elif option == 1:
            startHadoop()
        elif option == 2:
            stopHadoop()
        elif option == 3:
            showFilesHDFS()
        elif option == 4:
            prepareHDFS()
        elif option == 5:
            getFileToUploadHdfs(1)
            executeTest(n_test,1,10,60)
        elif option == 6:
            getFileToUploadHdfs(2)
            execute(getTest(2))
        elif option == 7:
            getFileToUploadHdfs(3)
            execute(getTest(3))
        elif option == 8:
            getFileToUploadHdfs(4)
            execute(getTest(4))
        elif option == 9:
            getFileToUploadHdfs(5)
            execute(getTest(5))
        elif option == 10:
            getFileToUploadHdfs(6)
            execute(getTest(6))
        elif option == 11:
            getFileToUploadHdfs(7)
            execute(getTest(7))
        elif option == 12:
            getFileToUploadHdfs(8)
            execute(getTest(8))
        elif option == 13:
            getFileToUploadHdfs(9)
            execute(getTest(9))
        elif option == 14:
            getFileToUploadHdfs(10)
            execute(getTest(10))
        elif option == 15:
            getFileToUploadHdfs(11)
            execute(getTest(11))
        elif option == 16:
            
        else:
            option = -1
        
    


ser = serial.Serial(port='/dev/ttyACM0',baudrate=9600,timeout=2)
delay = 10
delay_exec = 5
n_test = 1
cont = 0

file_name = "tempos" + strftime('%H.%M.%S_%d.%m.%Y') + ".csv"

while(ser.isOpen() == False):
    ser.open()
print("Comunicacao Serial Disponivel")

ser.reset_input_buffer()
ser.reset_output_buffer()

arquivo = open(file_name,'w')
arquivo.writelines("tempo_start,tempo_stop\n")

    
arquivo.close()


