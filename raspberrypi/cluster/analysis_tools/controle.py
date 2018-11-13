import serial
import subprocess
from time import  gmtime, strftime, sleep

def getTest(testcode, cont):
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
        return(["echo","invalid option"])

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
        return(["echo","invalid option"])

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

def printInformationList(out):
    for aux in out:
        print(str(aux.decode("utf-8")))

def checkPages():
    command = ["jps"]
    output,error = execute(command)
    printInformationList(output)
    print("error: " + str(error))

def checkNodesActive():
    command = ["yarn","node","-list"]
    output,error = execute(command)
    printInformationList(output)
    print("error: "+str(error))



def uploadFileToHdfs(code):
   command = getFileToUploadHdfs(code)
   output,error = execute(command)
   printInformationList(output)
   print("error: "+str(error))

def showFilesHDFS():
    print ("HDFS /")
    command = ["hdfs","dfs","-ls","/"]
    output1 ,error1 =  execute(command)
    printInformationList(output1)
    print("error: "+str(error1))  
    
    print ("HDFS /result")
    command =["hdfs","dfs","-ls","/result"]
    output2 ,error2 =  execute(command)
    printInformationList(output2)
    print("error: "+str(error2))

    print ("HDFS /files")
    command = ["hdfs","dfs","-ls","/files"]
    output3 ,error3 =  execute(command)
    printInformationList(output3)
    print("error: "+ str(error3))


def startHadoop():
    print ("stat DFS ")
    command = ["/opt/hadoop/sbin/start-dfs.sh"]
    output2 ,error2 =  execute(command)
    printInformationList(output2)
    print("Erro: " + str(error2))

    print ("stat YARN ")
    command = ["/opt/hadoop/sbin/start-yarn.sh"]
    output1,error1 = execute(command)
    printInformationList(output1)
    print("error: " + str(error1))
        
    checkPages()

def stopHadoop():
    print ("Stop YARN")
    command = ["stop-yarn.sh"]
    output1,error1 = execute(command)
    printInformationList(output1)
    print("error: " + str(error1))
    print ("Stop DFS")
    command = ["stop-dfs.sh"]
    output2 ,error2 =  execute(command)
    printInformationList(output2)
    print("Erro: "+str(error2))
    
    checkPages()

def prepareHDFS():
    print("Preparando HDFS")
    command = ["hdfs","dfsadmin","-safemode","leave"]
    output1,error1 = execute(command)
    printInformationList(output1)
    print("error: " + str(error1))
    
    command = ["hdfs","fsck","-delete"]
    output2,error2 = execute(command)
    printInformationList(output2)
    print("error: "+str(error2))
    
    command = ["hdfs","dfs","-rm","-r","/result"]
    output3,error3 = execute(command)
    printInformationList(output3)
    print("error: "+ str(error3))
    
    command = ["hdfs","dfs","-rm","-r","/files"]
    output4,error4 = execute(command)
    printInformationList(output4)
    print("error: "+ str(error4))
    
    command = ["hdfs","dfs","-mkdir","/result"]
    output5,error5 = execute(command)
    printInformationList(output5)
    print("error: "+ str(error5))
    
    command = ["hdfs","dfs","-mkdir","/files"]
    output6,error6 = execute(command)
    printInformationList(output6)
    print("error: "+ str(error6))

def executeTest(n_test, codeTest, delay_exec, file_log):
    cont = 0
    while(cont < n_test):
        print_exec = "execucao" +str(cont) +"\n"
        print (print_exec) 
    
        sleep(10)
        serial_arduino.write(bytes("i","utf-8"))
        sleep(delay_exec)
        
        start = strftime("%H:%M:%S", gmtime())
        saida_exec, erro_exec = execute(getTest(codeTest,cont))
        stop = strftime("%H:%M:%S", gmtime())
    
        sleep(delay_exec)
        

        print("SAIDA_EXEC: " + str(saida_exec))
        print("ERRO_EXEC: " + str(erro_exec))
        
        state = ''
        state_final = ''
        
        while state != 'FINISHED':
            application = getInformation(saida_exec,'Submitted application ')    
            print(application)
            
        
            test = ["yarn", "application", "-status", application]
            saida_test, erro_test = execute(test)
            
            print("SAIDA_TEST: " + str(saida_test))
            print("ERRO_TEST: " + str(erro_test))
                 
            state = getInformation(saida_test,'State : ')
            finalState = getInformation(saida_test,'Final-State : ')
            if(state == 'FINISHED'):
                serial_arduino.write(bytes("t","utf-8"))
                if(finalState == 'SUCCEEDED'):
                    pass
            
            
            print("STATE: " + str(state))
            print("STATE_FINAL: " + str(finalState))

        cont = cont + 1
        file_log.writelines(print_exec + '\n' + application + "\n\n")
        file_main.writelines( start + "," + stop + "," + state + "," + state_final + "\n")
def inputTest():
    n_test = -1
    delay_exec = -1
    while n_test < 1 and delay_exec < 1:
        n_test = int(input("inform the number of test: "))
        delay_exec = int(input("inform the delay for before and after to the execution (before = after): "))

    return n_test, delay_exec
    
def menu(file_main, file_log):
    option     = -1
    while option != 0:
        option     = -1
        n_test     = -1
        delay_exec = -1
        print("_____________________________ TESTS MENU _____________________________")
        print("0  - Exit")
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
        print("17 - Check the node active")
        print("18 - Check the pages")
        

        while (option < 0 or option > 18) and n_test < 1 and delay_exec < 1:
            option = int(input("inform the option: "))

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
            n_test, delay_exec = inputTest()
            getFileToUploadHdfs(1)
            executeTest(n_test, 1, delay_exec, file_log)
        elif option == 6:
            n_test, delay_exec = inputTest()
            getFileToUploadHdfs(2)
            executeTest(n_test, 2, delay_exec, file_log)
        elif option == 7:
            n_test, delay_exec = inputTest()
            getFileToUploadHdfs(3)
            executeTest(n_test, 3, delay_exec, file_log)
        elif option == 8:
            n_test, delay_exec = inputTest()
            getFileToUploadHdfs(4)
            executeTest(n_test, 4, delay_exec, file_log)
        elif option == 9:
            n_test, delay_exec = inputTest()
            getFileToUploadHdfs(5)
            executeTest(n_test, 5, delay_exec, file_log)
        elif option == 10:
            n_test, delay_exec = inputTest()
            getFileToUploadHdfs(6)
            executeTest(n_test, 6, delay_exec, file_log)
        elif option == 11:
            n_test, delay_exec = inputTest()
            getFileToUploadHdfs(7)
            executeTest(n_test, 7, delay_exec, file_log)
        elif option == 12:
            n_test, delay_exec = inputTest()
            getFileToUploadHdfs(8)
            executeTest(n_test, 8, delay_exec, file_log)
        elif option == 13:
            n_test, delay_exec = inputTest()
            getFileToUploadHdfs(9)
            executeTest(n_test, 9, delay_exec, file_log)
        elif option == 14:
            n_test, delay_exec = inputTest()
            getFileToUploadHdfs(10)
            executeTest(n_test, 10, delay_exec, file_log)
        elif option == 15:
            n_test, delay_exec = inputTest()
            getFileToUploadHdfs(11)
            executeTest(n_test, 11, delay_exec, file_log)
        elif option == 16:
            n_test, delay_exec = inputTest()
            executeTest(n_test, 12, delay_exec, file_log)
        elif option == 17:
            checkNodesActive()
        elif option ==18:
            checkPages()
        else:
            option = -1
           
serial_arduino = serial.Serial(port='/dev/ttyACM0',baudrate=9600,timeout=2)

file_name_main = "time" + strftime('%H.%M.%S_%d.%m.%Y') + ".csv"
file_name_log  = "log"    + strftime('%H.%M.%S_%d.%m.%Y') + ".txt"

while(serial_arduino.isOpen() == False):
    serial_arduino.open()

print("Communication Serial Available")

serial_arduino.reset_input_buffer()
serial_arduino.reset_output_buffer()

file_main = open(file_name_main,'w')
file_main.writelines("time_start,time_stop,state,state_final\n")
file_log  = open(file_name_log,'w')

menu(file_main,file_log)
    
file_main.close()
file_log.close()