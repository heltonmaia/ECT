# Instalação do HIPI - Hadoop Image Processing Interface


#### 1. Verificar se o Java, gradle e hadoop estão instalados

O HIPI é escrito em Java e foi testado com o Java 7 e 8. Verifique sua versão do Java com o seguinte comando:

java -version

```
hduser@master:~$ java -version
java version "1.8.0_171"
Java(TM) SE Runtime Environment (build 1.8.0_171-b11)
Java HotSpot(TM) 64-Bit Server VM (build 25.171-b11, mixed mode)

```

Verifique se o hadoop estar instalado com o comando abaixo:

which hadoop

```
hduser@master:~$ which hadoop
/opt/hadoop/bin/hadoop

```
Verifique se o gradle estar instalado com o comando abaixo:

which gradle

```
hduser@master:~$ which gradle
/opt/gradle/gradle-4.7/bin/gradle

```

##### 2. Instalar o Gradle

sudo -i

wget https://downloads.gradle.org/distributions/gradle-4.7-bin.zip

mkdir /opt/gradle

unzip -d /opt/gradle gradle-4.7-bin.zip

ls /opt/gradle/gradle-4.7

```
hduser@master:~$ ls /opt/gradle/gradle-4.7
bin  getting-started.html  init.d  lib  LICENSE  media  NOTICE

```
export PATH=$PATH:/opt/gradle/gradle-4.7/bin

gradle -v

```
hduser@master:~$ gradle -v

------------------------------------------------------------
Gradle 4.7
------------------------------------------------------------

Build time:   2018-04-18 09:09:12 UTC
Revision:     b9a962bf70638332300e7f810689cb2febbd4a6c

Groovy:       2.4.12
Ant:          Apache Ant(TM) version 1.9.9 compiled on February 2 2017
JVM:          1.8.0_171 (Oracle Corporation 25.171-b11)
OS:           Linux 4.13.0-41-generic amd64
```


