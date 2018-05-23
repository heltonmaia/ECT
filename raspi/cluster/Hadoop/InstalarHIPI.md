# Instalação do HIPI - Hadoop Image Processing Interface


### 1. Verificar se o Java, gradle e hadoop estão instalados

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

##### Instalar o Gradle

sudo -i

wget https://downloads.gradle.org/distributions/gradle-4.7-bin.zip

mkdir /opt/gradle

unzip -d /opt/gradle gradle-4.7-bin.zip

ls /opt/gradle/gradle-4.7

```
hduser@master:~$ ls /opt/gradle/gradle-4.7
bin  getting-started.html  init.d  lib  LICENSE  media  NOTICE

```
Adicionar a variável ao path:

sudo nano /etc/bash.bashrc 

``` 
export PATH=$PATH:/opt/gradle/gradle-4.7/bin

```
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
### 2. Instalar HIPI 

Baixar o repositório do HIPI:

sudo su

cd /opt

git clone https://github.com/uvagfx/hipi.git

cd /opt/hipi

gradle

```
root@master:/opt/hipi# gradle
Starting a Gradle Daemon (subsequent builds will be faster)

> Task :core:compileJava
Note: /opt/hipi/core/src/main/java/org/hipi/imagebundle/mapreduce/HibRecordReader.java uses unchecked or unsafe operations.
Note: Recompile with -Xlint:unchecked for details.

> Task :install

Finished building the HIPI library along with all tools and examples.

BUILD SUCCESSFUL in 21s
15 actionable tasks: 15 executed

```

gradle clean tools:hibImport:jar

```
root@master:/opt/hipi# gradle clean tools:hibImport:jar

> Task :core:compileJava
Note: /opt/hipi/core/src/main/java/org/hipi/imagebundle/mapreduce/HibRecordReader.java uses unchecked or unsafe operations.
Note: Recompile with -Xlint:unchecked for details.

BUILD SUCCESSFUL in 2s
13 actionable tasks: 11 executed, 2 up-to-date

```

sudo mkdir -p /opt/hipi/examples/helloWorld/src/main/java/org/hipi/examples

cd /opt/hipi/examples/helloWorld

sudo nano build.gradle

```
jar{
        manifest{
                attributes("Main-Class":"org.hipi.examples.HelloWorld")
                }

}

```

cd /opt/hipi/examples/helloWorld/src/main/java/org/hipi/examples

sudo nano HelloWorld.java

```
package org.hipi.examples;

import org.apache.hadoop.conf.Configured;
import org.apache.hadoop.util.Tool;
import org.apache.hadoop.util.ToolRunner;

public class HelloWorld extends Configured implements Tool{

        public int run(String[] args) throws Exception{
                System.out.println("Hello HIPI!");
                return 0;

        }

        public static void main(String[] args) throws Exception {
                ToolRunner.run(new HelloWorld(), args);
                System.exit(0);

        }

}

```
sudo nano /opt/hipi/settings.gradle 

```
, ':examples:helloWorld'

```

cd /opt/hipi/examples/helloWorld

gradle jar

```
root@master:/opt/hipi/examples/helloWorld# gradle jar

BUILD SUCCESSFUL in 1s
2 actionable tasks: 2 executed

```
su  hduser

hadoop jar /opt/hipi/examples/helloWorld/build/libs/helloWorld.jar


```
hduser@master:~$ hadoop jar /opt/hipi/examples/helloWorld/build/libs/helloWorld.jar
Hello HIPI!

```


