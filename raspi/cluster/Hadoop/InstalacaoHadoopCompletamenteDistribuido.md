# Instalação do Hadoop completamente distribuído

## Instalação do Hadoop na Raspberry PI 3 modelo B ou BeagleBone Black

#### Link para baixar imagem do raspbian para raspberry:

https://downloads.raspberrypi.org/raspbian/images/raspbian-2017-07-05/2017-07-05-raspbian-jessie.zip

#### Link para baixar imagem do bone-ubuntu-16.04.3-console-armhf para beaglebone black:

https://rcn-ee.net/rootfs/2018-02-09/microsd/bone-ubuntu-16.04.3-console-armhf-2018-02-09-2gb.img.xz


Para instalar imagem nos cartões foi utilizado o etcher. 

#### Link para baixar o etcher

https://etcher.io/

## Configuração para o master e nos

## Instalação das dependências na Rapberry e Beaglebone

sudo -i

apt-get update

apt-get upgrade

apt-get install  zlib1g zlib1g-dbg  zlib1g-dev zlibc libssl-dev lbzip2  libzip-dev  pbzip2 

apt-get install libfuse-dev libsnappy-dev libsnappy-java pkg-config libbz2-dev

apt-get install ssh build-essential  g++ autoconf automake libtool cmake pkgconf 

apt-get install zip unzip

## Instalação do java

Antes de iniciar  a instalação confira  se o java já veio instalado como de costume no Raspbian jessie mais recentes.

### Instalar o java na Rapberry e Beaglebone

#### 1ª opção de instalação do java (Raspberry)

sudo -i

apt-get install oracle-java8-jdk

#### Utilize a comando a seguir para selecionar a versão do java:

update-alternatives --config java

Selecione a opção /usr/lib/jvm/jdk-8-oracle-arm32-vfp-hflt/jre/bin/java.

#### Verifique se instalação foi realizada com sucesso:

java -version

```
hduser@node1:~ $ java -version
java version "1.8.0_65"
Java(TM) SE Runtime Environment (build 1.8.0_65-b17)
Java HotSpot(TM) Client VM (build 25.65-b01, mixed mode)

```

#### 2ª opção de instalação do java (Raspberry ou Beaglebone)

#### Baixar, criar diretório e descompactar o java:

sudo -i

mkdir /opt/jdk

####Entre no link abaixo e selecione a opção jdk-8u171-linux-arm32-vfp-hflt.tar.gz:

http://www.oracle.com/technetwork/java/javase/downloads/jdk8-downloads-2133151.html

sudo -i

mkdir /opt/jdk

tar -zxf jdk-8u171-linux-arm-vfp-hflt.tar.gz -C /opt/jdk

update-alternatives --install /usr/bin/java java  /opt/jdk/jdk1.8.0_171/bin/java 100

update-alternatives --install /usr/bin/javac javac /opt/jdk/jdk1.8.0_171/bin/javac 100

## Instalação do protobuf 2.5.0 na Rapberry e Beaglebone

### 1ª opção de instalação do protobuf

#### Baixar e descompactar o protobuf:

sudo -i

apt-get update

apt-get install dh-autoreconf

wget https://github.com/HemersonRafael/protobufOfCluster/archive/master.zip

unzip master.zip

cd protobufOfCluster-master

cd protobuf-2.5.0

#### Gere os arquivos de configuração da compilação:

./autogen.sh

./configure --prefix=/usr

#### Compilação e instalação do protobuf:

make

make check

make install

#### Verifique se instalação foi realizada com sucesso:

protoc --version
```
hduser@node1:~ $ protoc --version
libprotoc 2.5.0

```

## 2ª opção de instalação do protobuf

#### Baixar e descompactar o protobuf:

sudo -i

apt-get update

wget https://github.com/google/protobuf/releases/download/v2.5.0/protobuf-2.5.0.tar.gz

tar xzvf protobuf-2.5.0.tar.gz

cd protobuf-2.5.0

#### Gere os arquivos de configuração da compilação:

./configure --prefix=/usr

#### Compilação e instalação do protobuf:

make

make check

sudo make install

#### Verifique se instalação foi realizada com sucesso:

protoc --version
```
hduser@node1:~ $ protoc --version
libprotoc 2.5.0

```

## Instalação do Apache Maven na Rapberry e Beaglebone
    
#### Baixar e descompactar o apache maven: 
sudo -i

apt-get update 

cd /usr/local

wget http://ftp.unicamp.br/pub/apache/maven/maven-3/3.5.2/binaries/apache-maven-3.5.2-bin.tar.gz

tar xzf apache-maven-3.5.2-bin.tar.gz

ln -s apache-maven-3.5.2 apache-maven

Configuração das variáveis de ambientes, utilize o comando abaixo para criar o arquivo.

nano /etc/profile.d/apache-maven.sh

Adicione as variáveis abaixo ao arquivo apache-maven.sh

Para 1ª opção de instalação java:

```
export JAVA_HOME=/usr/lib/jvm/jdk-8-oracle-arm32-vfp-hflt
export M2_HOME=/usr/local/apache-maven
export MAVEN_HOME=/usr/local/apache-maven
export PATH=${M2_HOME}/bin:${PATH}
```

Para 2ª opção de instalação java:

```
export JAVA_HOME=/opt/jdk/jdk1.8.0_171/
export M2_HOME=/usr/local/apache-maven
export MAVEN_HOME=/usr/local/apache-maven
export PATH=${M2_HOME}/bin:${PATH}
```

Em seguida, saia e salve o arquivo com os comandos de tecla Ctrl + X, Y, enter.

#### Atualize as alterações utilize o comando a seguir: 

source /etc/profile.d/apache-maven.sh

#### Verifique se instalação foi realizada com sucesso:
              
mvn --version

```
hduser@node1:~ $ mvn --version
Apache Maven 3.5.2 (138edd61fd100ec658bfa2d307c43b76940a5d7d; 2017-10-18T04:58:13-03:00)
Maven home: /usr/local/apache-maven
Java version: 1.8.0_65, vendor: Oracle Corporation
Java home: /usr/lib/jvm/jdk-8-oracle-arm32-vfp-hflt/jre
Default locale: pt_BR, platform encoding: UTF-8
OS name: "linux", version: "4.9.35-v7+", arch: "arm", family: "unix"

```
## Configuração de rede na Rapberry e Beaglebone

#### Desativar o ipv6:

sudo -i

nano /etc/sysctl.conf

#### Altere o arquivo conforme as informações abaixo, caso não exista adicione:
```
net.ipv6.conf.all.disable_ipv6 = 1
net.ipv6.conf.default.disable_ipv6 = 1
net.ipv6.conf.lo.disable_ipv6 = 1
net.ipv6.conf.eth0.disable_ipv6 = 1
```
 **Nota:** Caso queira habilitar no futuro, troque o valor 1 por 0.

#### Em seguida reinicie o serviço com o comando abaixo:

sysctl -p

## Configurar rede para modo estático 

#### O comando exibirá o endereço de ip da máquina:

hostname -I

#### Adicione ao arquivo de interfaces o modo estático para o eth0:

nano /etc/network/interfaces

#### Neste caso, foi utilizada a configuração abaixo, que pode mudar de acordo com a necessidade de cada caso.
```
auto eth0
iface eth0 inet static
address 10.6.1.228
netmask 255.255.252.0
gateway 10.6.0.1
dns-nameserver 10.6.0.98
```
**Nota:** o endereço de ip deve ser configurando de acordo com o de cada placa.

#### Em seguida abra o arquivo hosts:

nano /etc/hosts

#### Adicione ao arquivo a linha abaixo e salve:
```
10.6.1.228	master
10.6.1.226 	node1
10.6.1.225 	node2
10.6.1.227 	node3
10.6.1.223 	node4
10.6.1.229      node5
10.6.1.230      node6
```
#### Por fim abrir os arquivos hostname e substitua o nome Raspberry por master:

nano /etc/hostname

**Nota:** Hostname deve ser configurando de acordo com o de cada placa, neste caso foi utilizado master para master e para nos node1, node2, node3, node4, node5 e node6.

**Agora reset a Raspberry**

## Criando usuário para Hadoop

#### Adicione um grupo, um usuário e, em seguida, adicione o usuário ao grupo:

sudo addgroup hadoop

sudo adduser --ingroup hadoop hduser

sudo adduser hduser sudo

## Instalação do Hadoop-2.7.6 Rapberry e Beaglebone

#### Baixar e descompactar o hadoop:

sudo -i

Link nacional para download:

http://ftp.unicamp.br/pub/apache/hadoop/common/

Link internacional para download:

http://www-eu.apache.org/dist/hadoop/common/

tar -xvzf hadoop-2.7.5-src.tar.gz

cd hadoop-2.7.5-src

#### Configuração para instruir o processo de compilação para arquitetura ARM:

nano pom.xml

Em seguida, pressione Ctrl+Shift + - (Ctrl+ _) Insira o número da linha igual a 82. Adicione  entre  ``` <properties></properties>```  a tags a seguir:

```xml
<additionalparam>-Xdoclint:none</additionalparam>
```

#### Também será necessária a instalação do patch HADOOP-9320:

sudo -i

cd hadoop-2.7.5-src/hadoop-common-project/hadoop-common/src

wget https://issues.apache.org/jira/secure/attachment/12570212/HADOOP-9320.patch

##### Se o link estiver inativo : 

sudo nano HADOOP-9320.patch

```
diff --git a/hadoop-common-project/hadoop-common/src/JNIFlags.cmake b/hadoop-common-project/hadoop-common/src/JNIFlags.cmake
index aba4c18..70a8d1c 100644
--- a/hadoop-common-project/hadoop-common/src/JNIFlags.cmake
+++ b/hadoop-common-project/hadoop-common/src/JNIFlags.cmake
@@ -34,37 +34,6 @@ if (JVM_ARCH_DATA_MODEL EQUAL 32)
     endif ()
 endif (JVM_ARCH_DATA_MODEL EQUAL 32)
 
-# Determine float ABI of JVM on ARM Linux
-if (CMAKE_SYSTEM_PROCESSOR MATCHES "^arm" AND CMAKE_SYSTEM_NAME STREQUAL "Linux")
-    find_program(READELF readelf)
-    if (READELF MATCHES "NOTFOUND")
-        message(WARNING "readelf not found; JVM float ABI detection disabled")
-    else (READELF MATCHES "NOTFOUND")
-        execute_process(
-            COMMAND ${READELF} -A ${JAVA_JVM_LIBRARY}
-            OUTPUT_VARIABLE JVM_ELF_ARCH
-            ERROR_QUIET)
-        if (NOT JVM_ELF_ARCH MATCHES "Tag_ABI_VFP_args: VFP registers")
-            message("Soft-float JVM detected")
-
-            # Test compilation with -mfloat-abi=softfp using an arbitrary libc function
-            # (typically fails with "fatal error: bits/predefs.h: No such file or directory"
-            # if soft-float dev libraries are not installed)
-            include(CMakePushCheckState)
-            cmake_push_check_state()
-            set(CMAKE_REQUIRED_FLAGS "${CMAKE_REQUIRED_FLAGS} -mfloat-abi=softfp")
-            include(CheckSymbolExists)
-            check_symbol_exists(exit stdlib.h SOFTFP_AVAILABLE)
-            if (NOT SOFTFP_AVAILABLE)
-                message(FATAL_ERROR "Soft-float dev libraries required (e.g. 'apt-get install libc6-dev-armel' on Debian/Ubuntu)")
-            endif (NOT SOFTFP_AVAILABLE)
-            cmake_pop_check_state()
-
-            set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mfloat-abi=softfp")
-        endif ()
-    endif (READELF MATCHES "NOTFOUND")
-endif (CMAKE_SYSTEM_PROCESSOR MATCHES "^arm" AND CMAKE_SYSTEM_NAME STREQUAL "Linux")
-
 IF("${CMAKE_SYSTEM}" MATCHES "Linux")
     #
     # Locate JNI_INCLUDE_DIRS and JNI_LIBRARIES.
@@ -115,3 +84,37 @@ IF("${CMAKE_SYSTEM}" MATCHES "Linux")
 ELSE()
     find_package(JNI REQUIRED)
 ENDIF()
+
+# Determine float ABI of JVM on ARM Linux
+if (CMAKE_SYSTEM_PROCESSOR MATCHES "^arm" AND CMAKE_SYSTEM_NAME STREQUAL "Linux")
+    find_program(READELF readelf)
+    if (READELF MATCHES "NOTFOUND")
+        message(WARNING "readelf not found; JVM float ABI detection disabled")
+    else (READELF MATCHES "NOTFOUND")
+        message(STATUS "Checking float ABI of ${JAVA_JVM_LIBRARY}")
+        execute_process(
+            COMMAND ${READELF} -A ${JAVA_JVM_LIBRARY}
+            OUTPUT_VARIABLE JVM_ELF_ARCH
+            ERROR_QUIET)
+        if (JVM_ELF_ARCH MATCHES "Tag_ABI_VFP_args: VFP registers")
+            message(STATUS "Hard-float JVM detected")
+        else ()
+            message(STATUS "Soft-float JVM detected")
+
+            # Test compilation with -mfloat-abi=softfp using an arbitrary libc function
+            # (typically fails with "fatal error: bits/predefs.h: No such file or directory"
+            # if soft-float dev libraries are not installed)
+            include(CMakePushCheckState)
+            cmake_push_check_state()
+            set(CMAKE_REQUIRED_FLAGS "${CMAKE_REQUIRED_FLAGS} -mfloat-abi=softfp")
+            include(CheckSymbolExists)
+            check_symbol_exists(exit stdlib.h SOFTFP_AVAILABLE)
+            if (NOT SOFTFP_AVAILABLE)
+                message(FATAL_ERROR "Soft-float dev libraries required (e.g. 'apt-get install libc6-dev-armel' on Debian/Ubuntu)")
+            endif (NOT SOFTFP_AVAILABLE)
+            cmake_pop_check_state()
+
+            set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mfloat-abi=softfp")
+        endif ()
+    endif (READELF MATCHES "NOTFOUND")
+endif (CMAKE_SYSTEM_PROCESSOR MATCHES "^arm" AND CMAKE_SYSTEM_NAME STREQUAL "Linux")

```

patch < HADOOP-9320.patch


#### O comando a seguir iniciará o processo de compilação:

sudo -i

cd hadoop-2.7.5-src

#### Sem o debug ativo:

mvn package -Pdist,native -DskipTests -Dtar

#### Com o debug ativo:

mvn package -Pdist,native -DskipTests -Dtar -C

**OBS:** Devido a placa Beaglebone Black trava muito durante o processo de compilação e prasentar erros não contidos. Foi utilizado o hadoop compilado na Raspberry.

Ao final do processo espera-se obter sucesso em todos os pacotes.

```
...

[INFO] Reactor Summary:
[INFO] 
[INFO] Apache Hadoop Main ................................. SUCCESS [  4.556 s]
[INFO] Apache Hadoop Build Tools .......................... SUCCESS [  3.305 s]
[INFO] Apache Hadoop Project POM .......................... SUCCESS [  4.577 s]
[INFO] Apache Hadoop Annotations .......................... SUCCESS [  9.350 s]
[INFO] Apache Hadoop Assemblies ........................... SUCCESS [  0.605 s]
[INFO] Apache Hadoop Project Dist POM ..................... SUCCESS [  3.970 s]
[INFO] Apache Hadoop Maven Plugins ........................ SUCCESS [ 11.488 s]
[INFO] Apache Hadoop MiniKDC .............................. SUCCESS [ 25.797 s]
[INFO] Apache Hadoop Auth ................................. SUCCESS [ 23.513 s]
[INFO] Apache Hadoop Auth Examples ........................ SUCCESS [ 12.303 s]
[INFO] Apache Hadoop Common ............................... SUCCESS [07:45 min]
[INFO] Apache Hadoop NFS .................................. SUCCESS [ 22.117 s]
[INFO] Apache Hadoop KMS .................................. SUCCESS [ 59.410 s]
[INFO] Apache Hadoop Common Project ....................... SUCCESS [  0.243 s]
[INFO] Apache Hadoop HDFS ................................. SUCCESS [18:21 min]
[INFO] Apache Hadoop HttpFS ............................... SUCCESS [01:28 min]
[INFO] Apache Hadoop HDFS BookKeeper Journal .............. SUCCESS [ 18.934 s]
[INFO] Apache Hadoop HDFS-NFS ............................. SUCCESS [ 12.570 s]
[INFO] Apache Hadoop HDFS Project ......................... SUCCESS [  0.326 s]
[INFO] hadoop-yarn ........................................ SUCCESS [  0.267 s]
[INFO] hadoop-yarn-api .................................... SUCCESS [03:25 min]
[INFO] hadoop-yarn-common ................................. SUCCESS [02:07 min]
[INFO] hadoop-yarn-server ................................. SUCCESS [  1.810 s]
[INFO] hadoop-yarn-server-common .......................... SUCCESS [ 36.513 s]
[INFO] hadoop-yarn-server-nodemanager ..................... SUCCESS [01:05 min]
[INFO] hadoop-yarn-server-web-proxy ....................... SUCCESS [ 10.687 s]
[INFO] hadoop-yarn-server-applicationhistoryservice ....... SUCCESS [ 23.032 s]
[INFO] hadoop-yarn-server-resourcemanager ................. SUCCESS [01:17 min]
[INFO] hadoop-yarn-server-tests ........................... SUCCESS [ 18.416 s]
[INFO] hadoop-yarn-client ................................. SUCCESS [ 19.259 s]
[INFO] hadoop-yarn-server-sharedcachemanager .............. SUCCESS [ 12.614 s]
[INFO] hadoop-yarn-applications ........................... SUCCESS [  0.401 s]
[INFO] hadoop-yarn-applications-distributedshell .......... SUCCESS [  9.533 s]
[INFO] hadoop-yarn-applications-unmanaged-am-launcher ..... SUCCESS [  6.555 s]
[INFO] hadoop-yarn-site ................................... SUCCESS [  0.320 s]
[INFO] hadoop-yarn-registry ............................... SUCCESS [ 15.895 s]
[INFO] hadoop-yarn-project ................................ SUCCESS [ 21.087 s]
[INFO] hadoop-mapreduce-client ............................ SUCCESS [  0.904 s]
[INFO] hadoop-mapreduce-client-core ....................... SUCCESS [01:10 min]
[INFO] hadoop-mapreduce-client-common ..................... SUCCESS [01:07 min]
[INFO] hadoop-mapreduce-client-shuffle .................... SUCCESS [ 11.664 s]
[INFO] hadoop-mapreduce-client-app ........................ SUCCESS [ 32.561 s]
[INFO] hadoop-mapreduce-client-hs ......................... SUCCESS [ 21.120 s]
[INFO] hadoop-mapreduce-client-jobclient .................. SUCCESS [ 29.503 s]
[INFO] hadoop-mapreduce-client-hs-plugins ................. SUCCESS [  7.440 s]
[INFO] Apache Hadoop MapReduce Examples ................... SUCCESS [ 19.081 s]
[INFO] hadoop-mapreduce ................................... SUCCESS [ 13.507 s]
[INFO] Apache Hadoop MapReduce Streaming .................. SUCCESS [ 12.883 s]
[INFO] Apache Hadoop Distributed Copy ..................... SUCCESS [ 38.020 s]
[INFO] Apache Hadoop Archives ............................. SUCCESS [  7.752 s]
[INFO] Apache Hadoop Rumen ................................ SUCCESS [ 14.757 s]
[INFO] Apache Hadoop Gridmix .............................. SUCCESS [ 12.597 s]
[INFO] Apache Hadoop Data Join ............................ SUCCESS [  6.833 s]
[INFO] Apache Hadoop Ant Tasks ............................ SUCCESS [  5.518 s]
[INFO] Apache Hadoop Extras ............................... SUCCESS [  8.335 s]
[INFO] Apache Hadoop Pipes ................................ SUCCESS [ 37.754 s]
[INFO] Apache Hadoop OpenStack support .................... SUCCESS [ 14.012 s]
[INFO] Apache Hadoop Amazon Web Services support .......... SUCCESS [ 16.093 s]
[INFO] Apache Hadoop Azure support ........................ SUCCESS [ 15.936 s]
[INFO] Apache Hadoop Client ............................... SUCCESS [ 43.220 s]
[INFO] Apache Hadoop Mini-Cluster ......................... SUCCESS [  9.258 s]
[INFO] Apache Hadoop Scheduler Load Simulator ............. SUCCESS [ 19.958 s]
[INFO] Apache Hadoop Tools Dist ........................... SUCCESS [ 48.610 s]
[INFO] Apache Hadoop Tools ................................ SUCCESS [  0.241 s]
[INFO] Apache Hadoop Distribution ......................... SUCCESS [04:20 min]
[INFO] ------------------------------------------------------------------------
[INFO] BUILD SUCCESS
[INFO] ------------------------------------------------------------------------
[INFO] Total time: 56:16 min
[INFO] Finished at: 2018-05-02T16:00:03-03:00
[INFO] Final Memory: 83M/224M
[INFO] ------------------------------------------------------------------------

```

cd hadoop-2.7.5-src/hadoop-dist/target/

cp -R hadoop-2.7.5 /opt/hadoop

cd /opt

chown -R hduser:hadoop hadoop

tar -zcvf /root/hadoop-2.7.5.armf.tar.gz hadoop 

(Para possíveis backup)

#### Adicione ao final de /etc/bash.bashrc as seguintes linhas de exportação:

su hduser

sudo cp -a /etc/bash.bashrc /etc/bash.bashrc.original

sudo nano /etc/bash.bashrc

```
#HADOOP VARIABLES START
export JAVA_HOME=/usr/lib/jvm/jdk-8-oracle-arm32-vfp-hflt
export HADOOP_HOME=/opt/hadoop
export HADOOP_INSTALL=$HADOOP_HOME
export PATH=$PATH:$HADOOP_HOME/bin
export PATH=$PATH:$HADOOP_HOME/sbin
export HADOOP_MAPRED_HOME=$HADOOP_HOME
export HADOOP_COMMON_HOME=$HADOOP_HOME
export HADOOP_HDFS_HOME=$HADOOP_HOME
export YARN_HOME=$HADOOP_HOME
export HADOOP_OPTS="$HADOOP_OPTS -Djava.net.preferIPv4Stack=true -Djava.security.krb5.realm= -Djava.security.krb5.kdc= -Djava.library.path=/opt/hadoop/lib/native"
#HADOOP VARIABLES END
```

#### Aplique essas alterações:

source ~/.bashrc

#### Variáveis de ambiente Hadoop:

sudo nano /opt/hadoop/etc/hadoop/hadoop-env.sh

#### Descometa e atualiza a  linha de exportação do hadoop_env.sh:
 
export JAVA_HOME=/usr/lib/jvm/jdk-8-oracle-arm32-vfp-hflt

#### Para verificar se a compilação da biblioteca nativa foi realizada com sucesso:

su hduser

hadoop checknative -a

```
hduser@node1:~ $ hadoop checknative -a
18/05/04 13:03:23 INFO bzip2.Bzip2Factory: Successfully loaded & initialized native-bzip2 library system-native
18/05/04 13:03:23 INFO zlib.ZlibFactory: Successfully loaded & initialized native-zlib library
Native library checking:
hadoop:  true /opt/hadoop/lib/native/libhadoop.so.1.0.0
zlib:    true /lib/arm-linux-gnueabihf/libz.so.1
snappy:  true /usr/lib/libsnappy.so.1
lz4:     true revision:99
bzip2:   true /lib/arm-linux-gnueabihf/libbz2.so.1
openssl: true /usr/lib/arm-linux-gnueabihf/libcrypto.so
```
#### Verifique se instalação foi realizada com sucesso:

su hduser

hadoop version

```
hduser@node1:~ $ hadoop version
Hadoop 2.7.5
Subversion Unknown -r Unknown
Compiled by root on 2018-05-02T18:05Z
Compiled with protoc 2.5.0
From source with checksum 71e2695531cb3360ab74598755d036
This command was run using /opt/hadoop/share/hadoop/common/hadoop-common-2.7.5.jar
```

## Definir os arquivos de configuração para modo distribuído do hadoop

cd /opt/hadoop/etc/hadoop

### core-site

Abra o arquivo com nano ou outro editor de preferência:

sudo nano core-site.xml

Em seguida, substitua a tags <configuration></configuration> pelas abaixos:

```xml

<configuration>
  <property>
    <name>fs.default.name</name>
    <value>hdfs://master:9000</value>
  </property>
  <property>
    <name>dfs.permissions</name>
    <value>false</value>
  </property>
</configuration>

```

Da mesma maneira com os demais:

#### hdfs-site

sudo nano hdfs-site.xml

```xml
<configuration>
  <property>
    <name>dfs.replication</name>
    <value>3</value>
  </property>
  <property>
    <name>dfs.blocksize</name>
    <value>5242880</value>
  </property>
  <property>
    <name>dfs.namenode.name.dir</name>
    <value>file:/opt/hadoop/hadoop_data/hdfs/namenode</value>
  </property>
  <property>
    <name>dfs.datanode.name.dir</name>
    <value>file:/opt/hadoop/hadoop_data/hdfs/datanode</value>
  </property>
  <property>
    <name>dfs.permissions</name>
    <value>false</value>
  </property>
  <property>
    <name>dfs.datanode.use.datanode.hostname</name>
    <value>false</value>
  </property>
  <property>
    <name>dfs.namenode.datanode.registration.ip-hostname-check</name>
    <value>false</value>
  </property>
  <property>
    <name>dfs.namenode.http-address</name>
    <value>master:50070</value>
  </property>
  <property>
    <name>dfs.namenode.secondary.http-address</name>
    <value>master:50090</value>
  </property>
</configuration>

```

#### yarn-site

sudo nano yarn-site.xml

```xml
<configuration>
    <property>
        <name>yarn.resourcemanager.resource-tracker.address</name>
        <value>master:8031</value>
    </property>
    <property>
        <name>yarn.resourcemanager.scheduler.address</name>
        <value>master:8030</value>
    </property>
    <property>
        <name>yarn.resourcemanager.address</name>
        <value>master:8032</value>
    </property>
    <property>
        <name>yarn.nodemanager.aux-services</name>
        <value>mapreduce_shuffle</value>
    </property>
    <property>
        <name>yarn.nodemanager.resource.cpu-vcores</name>
        <value>4</value>
    </property>
    <property>
        <name>yarn.nodemanager.resource.memory-mb</name>
        <value>768</value>
    </property>
    <property>
        <name>yarn.scheduler.minimum-allocation-mb</name>
        <value>64</value>
    </property>
    <property>
        <name>yarn.scheduler.maximum-allocation-mb</name>
        <value>256</value>
    </property>
    <property>
        <name>yarn.scheduler.minimum-allocation-vcores</name>
        <value>1</value>
    </property>
    <property>
        <name>yarn.scheduler.maximum-allocation-vcores</name>
        <value>4</value>
    </property>
    <property>
        <name>yarn.nodemanager.vmem-check-enabled</name>
        <value>true</value>
    </property>
    <property>
        <name>yarn.nodemanager.pmem-check-enabled</name>
        <value>true</value>
    </property>
    <property>
        <name>yarn.nodemanager.vmem-pmem-ratio</name>
        <value>2.1</value>
    </property>
</configuration>
```

#### mapred-site

cp mapred-site.xml.template mapred-site.xml

sudo nano mapred-site.xml

```xml
<configuration>
    <property>
      <name>mapred.job.tracker</name>
      <value>master:9001</value>
    </property>
    <property>
        <name>mapreduce.framework.name</name>
        <value>yarn</value>
    </property>
    <property>
        <name>mapreduce.map.memory.mb</name>
        <value>256</value>
    </property>
    <property>
        <name>mapreduce.map.java.opts</name>
        <value>-Xmx204m</value>
    </property>
    <property>
        <name>mapreduce.map.cpu.vcores</name>
        <value>2</value>
    </property>
    <property>
        <name>mapreduce.reduce.memory.mb</name>
        <value>128</value>
    </property>
    <property>
        <name>mapreduce.reduce.java.opts</name>
        <value>-Xmx102m</value>
    </property>
    <property>
        <name>mapreduce.reduce.cpu.vcores</name>
        <value>2</value>
    </property>
    <property>
        <name>yarn.app.mapreduce.am.resource.mb</name>
        <value>128</value>
    </property>
    <property>
        <name>yarn.app.mapreduce.am.command-opts</name>
        <value>-Xmx102m</value>
    </property>
    <property>
        <name>yarn.app.mapreduce.am.resource.cpu-vcores</name>
        <value>1</value>
    </property>
    <property>
        <name>mapreduce.job.maps</name>
        <value>4</value>
    </property>
    <property>
        <name>mapreduce.job.reduces</name>
        <value>4</value>
    </property>
</configuration>

```
#### Adicione todos hostname dos slaves. salvar e fechar.

sudo nano /opt/hadoop/etc/hadoop/slaves

````
node1
node2
node3
node4
node5
node6

````

**OBS1.:** para diminuir o trabalho e ganhar tempo o ideal é criar uma imagem do sistema do master para gravar nós. Outra opção é cópiar por meio de SCP.


#### Cópia hadoop do master para node1

su hduser

sudo scp -r /opt/hadoop hduser@10.6.1.226:/home/hduser

sudo cd /home/hduser

sudo mv hadoop /opt

#### Cópia hadoop do master para node2

su hduser

sudo scp -r /opt/hadoop hduser@10.6.1.225:/home/hduser

sudo cd /home/hduser

sudo mv hadoop /opt

#### Cópia hadoop do master para node3

su hduser

sudo scp -r /opt/hadoop hduser@10.6.1.227:/home/hduser

sudo cd /home/hduser

sudo mv hadoop /opt

#### Cópia hadoop do master para node4

su hduser

sudo scp -r /opt/hadoop hduser@10.6.1.223:/home/hduser

sudo cd /home/hduser

sudo mv hadoop /opt

#### Cópia hadoop do master para node5

su hduser

sudo scp -r /opt/hadoop hduser@10.6.1.229:/home/hduser

sudo cd /home/hduser

sudo mv hadoop /opt

#### Cópia hadoop do master para node6

su hduser

sudo scp -r /opt/hadoop hduser@10.6.1.230:/home/hduser

sudo cd /home/hduser

sudo mv hadoop /opt

# Etapas apenas para o master

### Crie a chave SSH sem senha:

#### Gerar um novo par de chaves públicas e privadas SSH no computador local é o primeiro passo para a autenticação com um servidor remoto sem uma senha.

su hduser

mkdir ~/.ssh

ssh-keygen -t rsa -P ""

#### Adicionar a chave pública ao authorized_keys

cat ~/.ssh/id_rsa.pub > ~/.ssh/authorized_keys

Testar conexão ssh:

ssh master

exit

**OBS2.:** a cópia da chave de ssh do master para nos deve ser feito após a realização dos passos anteriores em cada 

#### O ssh-copy-id é um script utilizado para copia sua chave pública ssh para um host remoto; anexando-o ao seu remote_keys autorizado.  Utilize  o comando para cópia o chave do master para nos:

#### Utilize  o comando para cópia o chave do master para node1:

ssh-copy-id -i $HOME/.ssh/id_rsa.pub hduser@10.6.1.226

Testar conexão ssh:

ssh 10.6.1.226 ou ssh node1

exit

#### Utilize  o comando para cópia o chave do master para node2:

ssh-copy-id -i $HOME/.ssh/id_rsa.pub hduser@10.6.1.225

Testar conexão ssh:

ssh 10.6.1.225 ou ssh node2

exit

#### Utilize  o comando para cópia o chave do master para node3:

ssh-copy-id -i $HOME/.ssh/id_rsa.pub hduser@10.6.1.227

Testar conexão ssh:

ssh 10.6.1.227 ou ssh node3

exit

#### Utilize  o comando para cópia o chave do master para node4:

ssh-copy-id -i $HOME/.ssh/id_rsa.pub hduser@10.6.1.223

Testar conexão ssh:

ssh 10.6.1.223 ou ssh node4

exit

#### Utilize  o comando para cópia o chave do master para node5:

ssh-copy-id -i $HOME/.ssh/id_rsa.pub hduser@10.6.1.229

Testar conexão ssh:

ssh 10.6.1.229 ou ssh node5

exit

#### Utilize  o comando para cópia o chave do master para node6:

ssh-copy-id -i $HOME/.ssh/id_rsa.pub hduser@10.6.1.230

Testar conexão ssh:

ssh 10.6.1.230 ou ssh node6

exit

#### Crie pastas e permissões para o HDFS

sudo mkdir -p /opt/hadoop/hadoop_data/hdfs/namenode

sudo mkdir -p /opt/hadoop/hadoop_data/hdfs/datanode

sudo chown hduser:hadoop /opt/hadoop/hadoop_data/hdfs -R

sudo chmod 750 /opt/hadoop/hadoop_data/hdfs

#### Formatar o HDFS

cd $HADOOP_INSTALL

```
hduser@node1:/opt/hadoop $ hdfs namenode -format
18/05/07 13:00:06 INFO namenode.NameNode: STARTUP_MSG: 
/************************************************************
STARTUP_MSG: Starting NameNode
STARTUP_MSG:   host = master/10.6.1.228
STARTUP_MSG:   args = [-format]
STARTUP_MSG:   version = 2.7.5
STARTUP_MSG:   classpath = /opt/hadoop/etc/hadoop:/opt/hadoop/share/hadoop/common/lib/log4j-1.2.17.jar:/opt/hadoop/share/hadoop/common/lib/jetty-util-6.1.26.jar
...

STARTUP_MSG:   build = Unknown -r Unknown; compiled by 'root' on 2018-05-02T18:07Z
STARTUP_MSG:   java = 1.8.0_171
************************************************************/

...

18/05/07 13:00:08 INFO util.ExitUtil: Exiting with status 0
18/05/07 13:00:08 INFO namenode.NameNode: SHUTDOWN_MSG: 
/************************************************************
SHUTDOWN_MSG: Shutting down NameNode at master/10.6.1.228
************************************************************/


```

#### Inicializar serviços do Hadoop

cd $HADOOP_HOME/sbin

./start-dfs.sh

```
hduser@master:~$ start-dfs.sh
Starting namenodes on [master]
master: starting namenode, logging to /opt/hadoop/logs/hadoop-hduser-namenode-master.out
node3: starting datanode, logging to /opt/hadoop/logs/hadoop-hduser-datanode-node3.out
node2: starting datanode, logging to /opt/hadoop/logs/hadoop-hduser-datanode-node2.out
node4: starting datanode, logging to /opt/hadoop/logs/hadoop-hduser-datanode-node4.out
node1: starting datanode, logging to /opt/hadoop/logs/hadoop-hduser-datanode-node1.out
node6: starting datanode, logging to /opt/hadoop/logs/hadoop-hduser-datanode-node6.out
node5: starting datanode, logging to /opt/hadoop/logs/hadoop-hduser-datanode-node5.out
Starting secondary namenodes [master]
master: starting secondarynamenode, logging to /opt/hadoop/logs/hadoop-hduser-secondarynamenode-master.out

```

./start-yarn.sh

```
hduser@master:~$ start-yarn.sh
starting yarn daemons
starting resourcemanager, logging to /opt/hadoop/logs/yarn-hduser-resourcemanager-master.out
node3: starting nodemanager, logging to /opt/hadoop/logs/yarn-hduser-nodemanager-node3.out
node1: starting nodemanager, logging to /opt/hadoop/logs/yarn-hduser-nodemanager-node1.out
node4: starting nodemanager, logging to /opt/hadoop/logs/yarn-hduser-nodemanager-node4.out
node2: starting nodemanager, logging to /opt/hadoop/logs/yarn-hduser-nodemanager-node2.out
node6: starting nodemanager, logging to /opt/hadoop/logs/yarn-hduser-nodemanager-node6.out
node5: starting nodemanager, logging to /opt/hadoop/logs/yarn-hduser-nodemanager-node5.out

```

#### Lista serviços em execução

jps 

```
hduser@master:~$ jps
30400 NameNode
13724 Jps
30638 SecondaryNameNode
30799 ResourceManager


```
```
hduser@node1:~ $ jps
23862 NodeManager
2235 Jps
23725 DataNode

```

#### Finalizar serviços em execução

cd $HADOOP_INSTALL/sbin

./stop-dfs.sh 

```
hduser@master:~$ stop-dfs.sh
Stopping namenodes on [master]
master: stopping namenode
node2: stopping datanode
node1: stopping datanode
node4: stopping datanode
node5: stopping datanode
node6: stopping datanode
node3: stopping datanode
Stopping secondary namenodes [master]
master: stopping secondarynamenode


```

./stop-yarn.sh
```
hduser@master:~$ stop-yarn.sh
stopping yarn daemons
stopping resourcemanager
node1: stopping nodemanager
node3: stopping nodemanager
node2: stopping nodemanager
node4: stopping nodemanager
node5: stopping nodemanager
node6: stopping nodemanager
no proxyserver to stop


```

## Testes de funcionamento do hadoop

### Exemplo do cálculo do valor de PI:

cd $HADOOP_INSTALL/bin

./hadoop jar /opt/hadoop/share/hadoop/mapreduce/hadoop-mapreduce-examples-2.7.5.jar pi 4 2 

```
hduser@master:~$ hadoop jar /opt/hadoop/share/hadoop/mapreduce/hadoop-mapreduce-examples-2.7.5.jar pi 4 2 
Number of Maps  = 4
Samples per Map = 2
Wrote input for Map #0
Wrote input for Map #1
Wrote input for Map #2
Wrote input for Map #3
Starting Job
18/05/17 17:39:57 INFO client.RMProxy: Connecting to ResourceManager at master/10.6.1.228:8032
18/05/17 17:39:58 INFO input.FileInputFormat: Total input paths to process : 4
18/05/17 17:39:58 INFO mapreduce.JobSubmitter: number of splits:4
18/05/17 17:39:58 INFO mapreduce.JobSubmitter: Submitting tokens for job: job_1526583257838_0003
18/05/17 17:39:59 INFO impl.YarnClientImpl: Submitted application application_1526583257838_0003
18/05/17 17:39:59 INFO mapreduce.Job: The url to track the job: http://master:8088/proxy/application_1526583257838_0003/
18/05/17 17:39:59 INFO mapreduce.Job: Running job: job_1526583257838_0003
18/05/17 17:40:29 INFO mapreduce.Job: Job job_1526583257838_0003 running in uber mode : false
18/05/17 17:40:29 INFO mapreduce.Job:  map 0% reduce 0%
18/05/17 17:40:44 INFO mapreduce.Job:  map 50% reduce 0%
18/05/17 17:40:51 INFO mapreduce.Job:  map 100% reduce 0%
18/05/17 17:41:00 INFO mapreduce.Job:  map 100% reduce 100%
18/05/17 17:41:01 INFO mapreduce.Job: Job job_1526583257838_0003 completed successfully
18/05/17 17:41:01 INFO mapreduce.Job: Counters: 50
	File System Counters
		FILE: Number of bytes read=94
		FILE: Number of bytes written=611486
		FILE: Number of read operations=0
		FILE: Number of large read operations=0
		FILE: Number of write operations=0
		HDFS: Number of bytes read=1048
		HDFS: Number of bytes written=215
		HDFS: Number of read operations=19
		HDFS: Number of large read operations=0
		HDFS: Number of write operations=3
	Job Counters 
		Launched map tasks=4
		Launched reduce tasks=1
		Data-local map tasks=3
		Rack-local map tasks=1
		Total time spent by all maps in occupied slots (ms)=252176
		Total time spent by all reduces in occupied slots (ms)=23762
		Total time spent by all map tasks (ms)=63044
		Total time spent by all reduce tasks (ms)=11881
		Total vcore-milliseconds taken by all map tasks=126088
		Total vcore-milliseconds taken by all reduce tasks=23762
		Total megabyte-milliseconds taken by all map tasks=16139264
		Total megabyte-milliseconds taken by all reduce tasks=1520768
	Map-Reduce Framework
		Map input records=4
		Map output records=8
		Map output bytes=72
		Map output materialized bytes=112
		Input split bytes=576
		Combine input records=0
		Combine output records=0
		Reduce input groups=2
		Reduce shuffle bytes=112
		Reduce input records=8
		Reduce output records=0
		Spilled Records=16
		Shuffled Maps =4
		Failed Shuffles=0
		Merged Map outputs=4
		GC time elapsed (ms)=2578
		CPU time spent (ms)=9530
		Physical memory (bytes) snapshot=744419328
		Virtual memory (bytes) snapshot=1524695040
		Total committed heap usage (bytes)=502022144
	Shuffle Errors
		BAD_ID=0
		CONNECTION=0
		IO_ERROR=0
		WRONG_LENGTH=0
		WRONG_MAP=0
		WRONG_REDUCE=0
	File Input Format Counters 
		Bytes Read=472
	File Output Format Counters 
		Bytes Written=97
Job Finished in 64.386 seconds
Estimated value of Pi is 3.50000000000000000000


```

### Exemplo wordCount:

#### Copie o arquivo, verifique HDFS para o arquivo, então execute WordCount no arquivo:

hdfs dfs -copyFromLocal /opt/hadoop/LICENSE.txt /license.txt

hdfs dfs -ls /

cd /opt/hadoop/bin

./hadoop jar /opt/hadoop/share/hadoop/mapreduce/hadoop-mapreduce-examples-2.7.6.jar wordcount /license.txt /license-out.txt

```

hduser@node1:/opt/hadoop/bin $ ./hadoop jar /opt/hadoop/share/hadoop/mapreduce/hadoop-mapreduce-examples-2.7.5.jar wordcount /license.txt /license-out.txt
18/01/08 22:37:04 INFO client.RMProxy: Connecting to ResourceManager at node1/192.168.1.104:8050
18/01/08 22:37:07 INFO input.FileInputFormat: Total input paths to process : 1
18/01/08 22:37:08 INFO mapreduce.JobSubmitter: number of splits:1
18/01/08 22:37:08 INFO mapreduce.JobSubmitter: Submitting tokens for job: job_1515459417185_0002
18/01/08 22:37:09 INFO impl.YarnClientImpl: Submitted application application_1515459417185_0002
18/01/08 22:37:09 INFO mapreduce.Job: The url to track the job: http://node1:8088/proxy/application_1515459417185_0002/
18/01/08 22:37:09 INFO mapreduce.Job: Running job: job_1515459417185_0002
18/01/08 22:37:32 INFO mapreduce.Job: Job job_1515459417185_0002 running in uber mode : false
18/01/08 22:37:32 INFO mapreduce.Job:  map 0% reduce 0%
18/01/08 22:37:49 INFO mapreduce.Job:  map 100% reduce 0%
18/01/08 22:38:17 INFO mapreduce.Job:  map 100% reduce 100%
18/01/08 22:38:19 INFO mapreduce.Job: Job job_1515459417185_0002 completed successfully
18/01/08 22:38:20 INFO mapreduce.Job: Counters: 49
	File System Counters
		FILE: Number of bytes read=29655
		FILE: Number of bytes written=669267
		FILE: Number of read operations=0
		FILE: Number of large read operations=0
		FILE: Number of write operations=0
		HDFS: Number of bytes read=86518
		HDFS: Number of bytes written=22239
		HDFS: Number of read operations=15
		HDFS: Number of large read operations=0
		HDFS: Number of write operations=8
	Job Counters 
		Launched map tasks=1
		Launched reduce tasks=4
		Data-local map tasks=1
		Total time spent by all maps in occupied slots (ms)=57352
		Total time spent by all reduces in occupied slots (ms)=189936
		Total time spent by all map tasks (ms)=14338
		Total time spent by all reduce tasks (ms)=94968
		Total vcore-milliseconds taken by all map tasks=28676
		Total vcore-milliseconds taken by all reduce tasks=189936
		Total megabyte-milliseconds taken by all map tasks=3670528
		Total megabyte-milliseconds taken by all reduce tasks=12155904
	Map-Reduce Framework
		Map input records=1594
		Map output records=12580
		Map output bytes=135125
		Map output materialized bytes=29655
		Input split bytes=94
		Combine input records=12580
		Combine output records=1914
		Reduce input groups=1914
		Reduce shuffle bytes=29655
		Reduce input records=1914
		Reduce output records=1914
		Spilled Records=3828
		Shuffled Maps =4
		Failed Shuffles=0
		Merged Map outputs=4
		GC time elapsed (ms)=2395
		CPU time spent (ms)=13500
		Physical memory (bytes) snapshot=413200384
		Virtual memory (bytes) snapshot=1211461632
		Total committed heap usage (bytes)=187437056
	Shuffle Errors
		BAD_ID=0
		CONNECTION=0
		IO_ERROR=0
		WRONG_LENGTH=0
		WRONG_MAP=0
		WRONG_REDUCE=0
	File Input Format Counters 
		Bytes Read=86424
	File Output Format Counters 
		Bytes Written=22239

```
#### Para visualizar o resultado do wordcount siga os passos a seguir:

hdfs dfs -copyToLocal /license-out.txt ~/

cat ~/license-out.txt/part-r-00000

```
hduser@master:/opt/hadoop/bin $ cat  ~/license-out.txt/part-r-00000
"Contributor"	2
"Derivative	1
"Legal	1
"License");	1
"Licensed	1
"Work"	1
"You"	1
"submitted"	1
("AGREEMENT").	1
(1) for	2
(MIT)	1
(NOT	2

...

was	4
whether	9
which	32
which,	2
whom	8
within	20
work.	2
worldwide,	4
would	1
xmlenc	1
your	4
“Executable”	1
“Larger	1
“Licensable”	1
“Participant”)	1
“Source	1


```

## Problemas com a execução de tarefas no hadoop?

#### Dica 1:

Confira se todos os 6 serviços foram inicializados, se o ipv6 estar desabilitado, as configurações de rede estática e os arquivos de configuração do hadoop. Estando tudo correto reinicie a placa, quando estiver ligada novamente inicie os serviços do hadoop. Por fim, tente reexecutar a tarefa.

#### Dica 2:

Caso ocorra a inicialização da execução, mas a presente falha ao longo do processo uma das causas mais comum é o safe modo ativo. Em algumas situações o HDFS entra em modo de segurança impedindo a execução das tarefas como no exemplo abaixo.

```

hduser@node1:/opt/hadoop/bin $ ./hadoop jar /opt/hadoop/share/hadoop/mapreduce/hadoop-mapreduce-examples-2.7.5.jar pi 4 2
Number of Maps  = 4
Samples per Map = 2
org.apache.hadoop.ipc.RemoteException(org.apache.hadoop.hdfs.server.namenode.SafeModeException): Cannot create directory /user/hduser/QuasiMonteCarlo_1515458168837_676260225/in. Name node is in safe mode.
The reported blocks 0 needs additional 40 blocks to reach the threshold 0,9990 of total blocks 40.
The number of live datanodes 1 has reached the minimum number 0. Safe mode will be turned off automatically once the thresholds have been reached.
	at org.apache.hadoop.hdfs.server.namenode.FSNamesystem.checkNameNodeSafeMode(FSNamesystem.java:1335)
	at org.apache.hadoop.hdfs.server.namenode.FSNamesystem.mkdirs(FSNamesystem.java:3866)
	at org.apache.hadoop.hdfs.server.namenode.NameNodeRpcServer.mkdirs(NameNodeRpcServer.java:984)
	at org.apache.hadoop.hdfs.protocolPB.ClientNamenodeProtocolServerSideTranslatorPB.mkdirs(ClientNamenodeProtocolServerSideTranslatorPB.java:634)
	at org.apache.hadoop.hdfs.protocol.proto.ClientNamenodeProtocolProtos$ClientNamenodeProtocol$2.callBlockingMethod(ClientNamenodeProtocolProtos.java)
	at org.apache.hadoop.ipc.ProtobufRpcEngine$Server$ProtoBufRpcInvoker.call(ProtobufRpcEngine.java:616)
	at org.apache.hadoop.ipc.RPC$Server.call(RPC.java:982)
	at org.apache.hadoop.ipc.Server$Handler$1.run(Server.java:2217)
	at org.apache.hadoop.ipc.Server$Handler$1.run(Server.java:2213)
	at java.security.AccessController.doPrivileged(Native Method)
	at javax.security.auth.Subject.doAs(Subject.java:422)
	at org.apache.hadoop.security.UserGroupInformation.doAs(UserGroupInformation.java:1754)
	at org.apache.hadoop.ipc.Server$Handler.run(Server.java:2213)

	at org.apache.hadoop.ipc.Client.call(Client.java:1476)
	at org.apache.hadoop.ipc.Client.call(Client.java:1413)
	at org.apache.hadoop.ipc.ProtobufRpcEngine$Invoker.invoke(ProtobufRpcEngine.java:229)
	at com.sun.proxy.$Proxy10.mkdirs(Unknown Source)
	at org.apache.hadoop.hdfs.protocolPB.ClientNamenodeProtocolTranslatorPB.mkdirs(ClientNamenodeProtocolTranslatorPB.java:563)
	at sun.reflect.NativeMethodAccessorImpl.invoke0(Native Method)
	at sun.reflect.NativeMethodAccessorImpl.invoke(NativeMethodAccessorImpl.java:62)
	at sun.reflect.DelegatingMethodAccessorImpl.invoke(DelegatingMethodAccessorImpl.java:43)
	at java.lang.reflect.Method.invoke(Method.java:497)
	at org.apache.hadoop.io.retry.RetryInvocationHandler.invokeMethod(RetryInvocationHandler.java:191)
	at org.apache.hadoop.io.retry.RetryInvocationHandler.invoke(RetryInvocationHandler.java:102)
	at com.sun.proxy.$Proxy11.mkdirs(Unknown Source)
	at org.apache.hadoop.hdfs.DFSClient.primitiveMkdir(DFSClient.java:3014)
	at org.apache.hadoop.hdfs.DFSClient.mkdirs(DFSClient.java:2984)
	at org.apache.hadoop.hdfs.DistributedFileSystem$21.doCall(DistributedFileSystem.java:1047)
	at org.apache.hadoop.hdfs.DistributedFileSystem$21.doCall(DistributedFileSystem.java:1043)
	at org.apache.hadoop.fs.FileSystemLinkResolver.resolve(FileSystemLinkResolver.java:81)
	at org.apache.hadoop.hdfs.DistributedFileSystem.mkdirsInternal(DistributedFileSystem.java:1061)
	at org.apache.hadoop.hdfs.DistributedFileSystem.mkdirs(DistributedFileSystem.java:1036)
	at org.apache.hadoop.fs.FileSystem.mkdirs(FileSystem.java:1880)
	at org.apache.hadoop.examples.QuasiMonteCarlo.estimatePi(QuasiMonteCarlo.java:282)
	at org.apache.hadoop.examples.QuasiMonteCarlo.run(QuasiMonteCarlo.java:355)
	at org.apache.hadoop.util.ToolRunner.run(ToolRunner.java:70)
	at org.apache.hadoop.examples.QuasiMonteCarlo.main(QuasiMonObs.: As vezesteCarlo.java:363)
	at sun.reflect.NativeMethodAccessorImpl.invoke0(Native Method)
	at sun.reflect.NativeMethodAccessorImpl.invoke(NativeMethodAccessorImpl.java:62)
	at sun.reflect.DelegatingMethodAccessorImpl.invoke(DelegatingMethodAccessorImpl.java:43)
	at java.lang.reflect.Method.invoke(Method.java:497)
	at org.apache.hadoop.util.ProgramDriver$ProgramDescription.invoke(ProgramDriver.java:71)
	at org.apache.hadoop.util.ProgramDriver.run(ProgramDriver.java:144)
	at org.apache.hadoop.examples.ExampleDriver.main(ExampleDriver.java:74)
	at sun.reflect.NativeMethodAccessorImpl.invoke0(Native Method)
	at sun.reflect.NativeMethodAccessorImpl.invoke(NativeMethodAccessorImpl.java:62)
	at sun.reflect.DelegatingMethodAccessorImpl.invoke(DelegatingMethodAccessorImpl.java:43)
	at java.lang.reflect.Method.invoke(Method.java:497)
	at org.apache.hadoop.util.RunJar.run(RunJar.java:221)
	at org.apache.hadoop.util.RunJar.main(RunJar.java:136)

```

#### Para consultar se safe mode estar ativo utilize o comando a seguir:

hdfs dfsadmin -safemode get

```
hduser@node1:/opt/hadoop/bin $ hdfs dfsadmin -safemode get
Safe mode is ON

```

#### Caso esteja ativo o utilize o comando abaixo para desativar:

hdfs dfsadmin -safemode leave

```
hduser@node1:/opt/hadoop/bin $ hdfs dfsadmin -safemode leave
Safe mode is OFF

```
## Acessar informações do hadoop pelo browser

Um forma agradável de obter informações sobre aplicações, nós, armazenamento e ferramentas do hadoop é utilizando o navegador de internet por meio dos links abaixo:

Localmente na placa:

http://master:50070

http://master:50090

http://master:8088


Externamente a placa, mas na mesma rede:

http://10.6.1.228:50070

http://10.6.1.228:50090

http://10.6.1.228:8088

## Referências:

http://hadoop.apache.org/

http://maven.apache.org/

http://data.andyburgin.co.uk/post/157450047463/running-hue-on-a-raspberry-pi-hadoop-cluster

http://www.widriksson.com/raspberry-pi-2-hadoop-2-cluster/

https://medium.com/@jasonicarter/how-to-hadoop-at-home-with-raspberry-pi-part-1-3b71f1b8ac4e

https://www.tutorialspoint.com/hadoop/

http://hadoop.praveendeshmane.co.in/hadoop/hadoop-2-6-4-fully-distributed-mode-installation-on-ubuntu-14-04.jsp

https://github.com/google/protobuf
