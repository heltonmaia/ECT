# Instalação do Hadoop na Raspberry PI 3 modelo B

#### Link para baixar imagem do raspbian:

https://downloads.raspberrypi.org/raspbian/images/raspbian-2017-07-05/2017-07-05-raspbian-jessie.zip

Para instalar imagem no cartão foi utilizado o etcher. 

#### Link para baixar o etcher

https://etcher.io/

## Instalação das dependências necessárias

sudo -i

apt-get install  zlib1g zlib1g-dbg  zlib1g-dev zlibc libssl-dev lbzip2  libzip-dev  pbzip2 

apt-get install libfuse-dev libsnappy-dev libsnappy-java pkg-config libbz2-dev

apt-get install ssh build-essential  g++ autoconf automake libtool cmake pkgconf 

apt-get install zip unzip

## Instalação do java

Antes de iniciar  a instalação confira  se o java já veio instalado como de costume no Raspbian jessie mais recentes.

#### Instalar o java:

sudo -i

apt-get install oracle-java8-jdk

#### Utilize a comando a seguir para selecionar a versão do java:

update-alternatives --config java

Selecione a opção /usr/lib/jvm/jdk-8-oracle-arm32-vfp-hflt/jre/bin/java.

#### Para verificar se instalação foi realizada com sucesso:

java -version

## Instalação do protobuf 2.5.0

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

#### Para verificar se instalação foi realizada com sucesso:

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

#### Para verificar se instalação foi realizada com sucesso:

protoc --version
```
hduser@node1:~ $ protoc --version
libprotoc 2.5.0

```

## Instalação do Apache Maven
    
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

```
export JAVA_HOME=/usr/lib/jvm/jdk-8-oracle-arm32-vfp-hflt
export M2_HOME=/usr/local/apache-maven
export MAVEN_HOME=/usr/local/apache-maven
export PATH=${M2_HOME}/bin:${PATH}
```
Em seguida, saia e salve o arquivo com os comandos de tecla Ctrl + X, Y, enter.

#### Para atualizar as alterações utilize o comando a seguir: 

source /etc/profile.d/apache-maven.sh

#### Para verificar se instalação foi realizada com sucesso:
              
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
## Configuração de rede na Raspberry

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
iface eth0 inet static
address 192.168.1.103
netmask 255.255.255.0
gateway 192.168.1.1
```
#### Em seguida abra o arquivo hosts:

nano /etc/hosts

#### Adicione ao arquivo a linha abaixo e salve:
```
192.168.1.103   node1
```
#### Por fim abrir os arquivos hostname e substitua o nome Raspberry por node1:

nano /etc/hostname

Agora reset a Raspberry

## Configuração do usuário hadoop

#### Adicione um grupo, um usuário e, em seguida, adicione o usuário ao grupo:

sudo addgroup hadoop

sudo adduser --ingroup hadoop hduser

sudo adduser hduser sudo

#### Mude os usuários e crie a chave SSH sem senha:

su hduser

ssh-keygen -t rsa -P '' -f ~/.ssh/id_rsa

cat ~/.ssh/id_rsa.pub >> ~/.ssh/authorized_keys

Testar conexão ssh:

ssh node1

exit
  
## Instalação do Hadoop-2.7.5

#### Baixar e descompactar o hadoop:

sudo -i

wget http://ftp.unicamp.br/pub/apache/hadoop/common/hadoop-2.7.5/hadoop-2.7.5-src.tar.gz

tar -xvzf hadoop-2.7.5.tar.gz

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

patch < HADOOP-9320.patch


#### O comando a seguir dará início a processo de compilação:

sudo -i

cd hadoop-2.7.5-src

mvn package -Pdist,native -DskipTests -Dtar

cd hadoop-2.7.5-src/hadoop-dist/target/

cp -R hadoop-2.7.5 /opt/hadoop

cd /opt

chown -R hduser:hadoop hadoop

tar -zcvf /root/hadoop-2.7.5.armf.tar.gz hadoop 

(Para possíveis backup)

#### Adicione ao final de /etc/bash.bashrc as seguintes linhas de exportação:

su hduser

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

#### Descometa e atualiza as duas linhas de exportação do hadoop_env.sh:
 
export JAVA_HOME=/usr/lib/jvm/jdk-8-oracle-arm32-vfp-hflt

#### Para verificar se a compilação da biblioteca nativa foi realizada com sucesso:

su hduser

hadoop checknative -a

```
hduser@node1:~ $ hadoop checknative -a
18/01/07 17:50:09 INFO bzip2.Bzip2Factory: Successfully loaded & initialized native-bzip2 library system-native
18/01/07 17:50:09 INFO zlib.ZlibFactory: Successfully loaded & initialized native-zlib library
Native library checking:
hadoop:  true /opt/hadoop/lib/native/libhadoop.so.1.0.0
zlib:    true /lib/arm-linux-gnueabihf/libz.so.1
snappy:  true /usr/lib/libsnappy.so.1
lz4:     true revision:99
bzip2:   true /lib/arm-linux-gnueabihf/libbz2.so.1
openssl: true /usr/lib/arm-linux-gnueabihf/libcrypto.so
```
#### Para verificar se instalação foi realizada com sucesso:

su hduser

hadoop version

```
hduser@node1:~ $ hadoop version
Hadoop 2.7.5
Subversion Unknown -r Unknown
Compiled by root on 2018-01-05T22:55Z
Compiled with protoc 2.5.0
From source with checksum 9f118f95f47043332d51891e37f736e9
This command was run using /opt/hadoop/share/hadoop/common/hadoop-common-2.7.5.jar

```

## Definir os arquivos de configuração para modo pseudo distribuído do hadoop

cd /opt/hadoop/etc/hadoop

### core-site

Abra o arquivo com nano ou outro editor de preferência:

sudo nano core-site.xml

Em seguida, substitua a tags <configuration></configuration> pelas abaixos:

```xml
<configuration>
  <property>
    <name>fs.default.name</name>
    <value>hdfs://node1:9000</value>
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
    <value>1</value>
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
</configuration>
```

#### yarn-site

sudo nano yarn-site.xml

```xml
<configuration>
    <property>
        <name>yarn.resourcemanager.resource-tracker.address</name>
        <value>node1:8025</value>
    </property>
    <property>
        <name>yarn.resourcemanager.scheduler.address</name>
        <value>node1:8035</value>
    </property>
    <property>
        <name>yarn.resourcemanager.address</name>
        <value>node1:8050</value>
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

#### Crie pastas e permissões para o HDFS

sudo mkdir -p /opt/hadoop/hadoop_data/hdfs/namenode

sudo mkdir -p /opt/hadoop/hadoop_data/hdfs/datanode

sudo chown hduser:hadoop /opt/hadoop/hadoop_data/hdfs -R

sudo chmod 750 /opt/hadoop/hadoop_data/hdfs

#### Formatar o HDFS

cd $HADOOP_INSTALL

hdfs namenode -format
```
hduser@node1:/opt/hadoop $ hdfs namenode -format
18/01/07 18:05:11 INFO namenode.NameNode: STARTUP_MSG: 
/************************************************************
STARTUP_MSG: Starting NameNode
STARTUP_MSG:   host = node1/192.168.1.104
STARTUP_MSG:   args = [-format]
STARTUP_MSG:   version = 2.7.5
STARTUP_MSG:   classpath = /opt/hadoop/etc/hadoop:/opt/hadoop/share/hadoop/common/lib/jackson-jaxrs-1.9.13.jar:/opt/hadoop/share/hadoop/common/lib/guava-11.0.2.jar:/opt/hadoop/share/hadoop/common/lib/httpclient-4.2.5.jar:/opt/hadoop/share/hadoop/common/lib/apacheds-i18n-2.0.0-M15.jar:/opt/hadoop/share/hadoop/common/lib/jsch-0.1.54.jar:/opt/hadoop/share/hadoop/common/lib/slf4j-log4j12-1.7.10.jar:/opt/hadoop/share/hadoop/common/lib/commons-digester-1.8.jar:/opt/hadoop/share/hadoop/common/lib/xz-1.0.jar:/opt/hadoop/share/hadoop/common/lib/servlet-api-2.5.jar:/opt/hadoop/share/hadoop/common/lib/stax-api-1.0-2.jar:/opt/hadoop/share/hadoop/common/lib/jetty-sslengine-6.1.26.jar:/opt/hadoop/share/hadoop/common/lib/curator-framework-2.7.1.jar:/opt/hadoop/share/hadoop/common/lib/commons-configuration-1.6.jar:/opt/hadoop/share/hadoop/common/lib/paranamer-2.3.jar:/opt/hadoop/share/hadoop/common/lib/zookeeper-3.4.6.jar:/opt/hadoop/share/hadoop/common/lib/jets3t-0.9.0.jar:/opt/hadoop/share/hadoop/common/lib/slf4j-api-1.7.10.jar:/opt/hadoop/share/hadoop/common/lib/commons-math3-3.1.1.jar:/opt/hadoop/share/hadoop/common/lib/commons-io-2.4.jar:/opt/hadoop/share/hadoop/common/lib/jackson-xc-1.9.13.jar:/opt/hadoop/share/hadoop/common/lib/jaxb-impl-2.2.3-1.jar:/opt/hadoop/share/hadoop/common/lib/log4j-1.2.17.jar:/opt/hadoop/share/hadoop/common/lib/protobuf-java-2.5.0.jar:/opt/hadoop/share/hadoop/common/lib/hadoop-auth-2.7.5.jar:/opt/hadoop/share/hadoop/common/lib/commons-logging-1.1.3.jar:/opt/hadoop/share/hadoop/common/lib/jaxb-api-2.2.2.jar:/opt/hadoop/share/hadoop/common/lib/jsr305-3.0.0.jar:/opt/hadoop/share/hadoop/common/lib/commons-httpclient-3.1.jar:/opt/hadoop/share/hadoop/common/lib/commons-collections-3.2.2.jar:/opt/hadoop/share/hadoop/common/lib/jackson-mapper-asl-1.9.13.jar:/opt/hadoop/share/hadoop/common/lib/asm-3.2.jar:/opt/hadoop/share/hadoop/common/lib/httpcore-4.2.5.jar:/opt/hadoop/share/hadoop/common/lib/api-asn1-api-1.0.0-M20.jar:/opt/hadoop/share/hadoop/common/lib/netty-3.6.2.Final.jar:/opt/hadoop/share/hadoop/common/lib/jsp-api-2.1.jar:/opt/hadoop/share/hadoop/common/lib/commons-codec-1.4.jar:/opt/hadoop/share/hadoop/common/lib/gson-2.2.4.jar:/opt/hadoop/share/hadoop/common/lib/commons-lang-2.6.jar:/opt/hadoop/share/hadoop/common/lib/java-xmlbuilder-0.4.jar:/opt/hadoop/share/hadoop/common/lib/jetty-util-6.1.26.jar:/opt/hadoop/share/hadoop/common/lib/commons-net-3.1.jar:/opt/hadoop/share/hadoop/common/lib/apacheds-kerberos-codec-2.0.0-M15.jar:/opt/hadoop/share/hadoop/common/lib/junit-4.11.jar:/opt/hadoop/share/hadoop/common/lib/commons-cli-1.2.jar:/opt/hadoop/share/hadoop/common/lib/commons-compress-1.4.1.jar:/opt/hadoop/share/hadoop/common/lib/jersey-json-1.9.jar:/opt/hadoop/share/hadoop/common/lib/jettison-1.1.jar:/opt/hadoop/share/hadoop/common/lib/api-util-1.0.0-M20.jar:/opt/hadoop/share/hadoop/common/lib/jackson-core-asl-1.9.13.jar:/opt/hadoop/share/hadoop/common/lib/curator-recipes-2.7.1.jar:/opt/hadoop/share/hadoop/common/lib/hadoop-annotations-2.7.5.jar:/opt/hadoop/share/hadoop/common/lib/htrace-core-3.1.0-incubating.jar:/opt/hadoop/share/hadoop/common/lib/xmlenc-0.52.jar:/opt/hadoop/share/hadoop/common/lib/avro-1.7.4.jar:/opt/hadoop/share/hadoop/common/lib/jersey-core-1.9.jar:/opt/hadoop/share/hadoop/common/lib/commons-beanutils-1.7.0.jar:/opt/hadoop/share/hadoop/common/lib/jersey-server-1.9.jar:/opt/hadoop/share/hadoop/common/lib/jetty-6.1.26.jar:/opt/hadoop/share/hadoop/common/lib/activation-1.1.jar:/opt/hadoop/share/hadoop/common/lib/hamcrest-core-1.3.jar:/opt/hadoop/share/hadoop/common/lib/curator-client-2.7.1.jar:/opt/hadoop/share/hadoop/common/lib/mockito-all-1.8.5.jar:/opt/hadoop/share/hadoop/common/lib/commons-beanutils-core-1.8.0.jar:/opt/hadoop/share/hadoop/common/lib/snappy-java-1.0.4.1.jar:/opt/hadoop/share/hadoop/common/hadoop-common-2.7.5-tests.jar:/opt/hadoop/share/hadoop/common/hadoop-common-2.7.5.jar:/opt/hadoop/share/hadoop/common/hadoop-nfs-2.7.5.jar:/opt/hadoop/share/hadoop/hdfs:/opt/hadoop/share/hadoop/hdfs/lib/guava-11.0.2.jar:/opt/hadoop/share/hadoop/hdfs/lib/servlet-api-2.5.jar:/opt/hadoop/share/hadoop/hdfs/lib/commons-io-2.4.jar:/opt/hadoop/share/hadoop/hdfs/lib/log4j-1.2.17.jar:/opt/hadoop/share/hadoop/hdfs/lib/protobuf-java-2.5.0.jar:/opt/hadoop/share/hadoop/hdfs/lib/commons-logging-1.1.3.jar:/opt/hadoop/share/hadoop/hdfs/lib/leveldbjni-all-1.8.jar:/opt/hadoop/share/hadoop/hdfs/lib/jsr305-3.0.0.jar:/opt/hadoop/share/hadoop/hdfs/lib/jackson-mapper-asl-1.9.13.jar:/opt/hadoop/share/hadoop/hdfs/lib/asm-3.2.jar:/opt/hadoop/share/hadoop/hdfs/lib/commons-daemon-1.0.13.jar:/opt/hadoop/share/hadoop/hdfs/lib/netty-3.6.2.Final.jar:/opt/hadoop/share/hadoop/hdfs/lib/commons-codec-1.4.jar:/opt/hadoop/share/hadoop/hdfs/lib/commons-lang-2.6.jar:/opt/hadoop/share/hadoop/hdfs/lib/jetty-util-6.1.26.jar:/opt/hadoop/share/hadoop/hdfs/lib/commons-cli-1.2.jar:/opt/hadoop/share/hadoop/hdfs/lib/netty-all-4.0.23.Final.jar:/opt/hadoop/share/hadoop/hdfs/lib/jackson-core-asl-1.9.13.jar:/opt/hadoop/share/hadoop/hdfs/lib/htrace-core-3.1.0-incubating.jar:/opt/hadoop/share/hadoop/hdfs/lib/xmlenc-0.52.jar:/opt/hadoop/share/hadoop/hdfs/lib/jersey-core-1.9.jar:/opt/hadoop/share/hadoop/hdfs/lib/jersey-server-1.9.jar:/opt/hadoop/share/hadoop/hdfs/lib/jetty-6.1.26.jar:/opt/hadoop/share/hadoop/hdfs/lib/xml-apis-1.3.04.jar:/opt/hadoop/share/hadoop/hdfs/lib/xercesImpl-2.9.1.jar:/opt/hadoop/share/hadoop/hdfs/hadoop-hdfs-nfs-2.7.5.jar:/opt/hadoop/share/hadoop/hdfs/hadoop-hdfs-2.7.5.jar:/opt/hadoop/share/hadoop/hdfs/hadoop-hdfs-2.7.5-tests.jar:/opt/hadoop/share/hadoop/yarn/lib/jackson-jaxrs-1.9.13.jar:/opt/hadoop/share/hadoop/yarn/lib/guava-11.0.2.jar:/opt/hadoop/share/hadoop/yarn/lib/jersey-client-1.9.jar:/opt/hadoop/share/hadoop/yarn/lib/xz-1.0.jar:/opt/hadoop/share/hadoop/yarn/lib/servlet-api-2.5.jar:/opt/hadoop/share/hadoop/yarn/lib/stax-api-1.0-2.jar:/opt/hadoop/share/hadoop/yarn/lib/zookeeper-3.4.6.jar:/opt/hadoop/share/hadoop/yarn/lib/javax.inject-1.jar:/opt/hadoop/share/hadoop/yarn/lib/commons-io-2.4.jar:/opt/hadoop/share/hadoop/yarn/lib/jackson-xc-1.9.13.jar:/opt/hadoop/share/hadoop/yarn/lib/jaxb-impl-2.2.3-1.jar:/opt/hadoop/share/hadoop/yarn/lib/log4j-1.2.17.jar:/opt/hadoop/share/hadoop/yarn/lib/protobuf-java-2.5.0.jar:/opt/hadoop/share/hadoop/yarn/lib/commons-logging-1.1.3.jar:/opt/hadoop/share/hadoop/yarn/lib/leveldbjni-all-1.8.jar:/opt/hadoop/share/hadoop/yarn/lib/jaxb-api-2.2.2.jar:/opt/hadoop/share/hadoop/yarn/lib/jsr305-3.0.0.jar:/opt/hadoop/share/hadoop/yarn/lib/commons-collections-3.2.2.jar:/opt/hadoop/share/hadoop/yarn/lib/jackson-mapper-asl-1.9.13.jar:/opt/hadoop/share/hadoop/yarn/lib/asm-3.2.jar:/opt/hadoop/share/hadoop/yarn/lib/jersey-guice-1.9.jar:/opt/hadoop/share/hadoop/yarn/lib/netty-3.6.2.Final.jar:/opt/hadoop/share/hadoop/yarn/lib/commons-codec-1.4.jar:/opt/hadoop/share/hadoop/yarn/lib/commons-lang-2.6.jar:/opt/hadoop/share/hadoop/yarn/lib/jetty-util-6.1.26.jar:/opt/hadoop/share/hadoop/yarn/lib/commons-cli-1.2.jar:/opt/hadoop/share/hadoop/yarn/lib/commons-compress-1.4.1.jar:/opt/hadoop/share/hadoop/yarn/lib/guice-3.0.jar:/opt/hadoop/share/hadoop/yarn/lib/jersey-json-1.9.jar:/opt/hadoop/share/hadoop/yarn/lib/jettison-1.1.jar:/opt/hadoop/share/hadoop/yarn/lib/jackson-core-asl-1.9.13.jar:/opt/hadoop/share/hadoop/yarn/lib/jersey-core-1.9.jar:/opt/hadoop/share/hadoop/yarn/lib/jersey-server-1.9.jar:/opt/hadoop/share/hadoop/yarn/lib/jetty-6.1.26.jar:/opt/hadoop/share/hadoop/yarn/lib/activation-1.1.jar:/opt/hadoop/share/hadoop/yarn/lib/zookeeper-3.4.6-tests.jar:/opt/hadoop/share/hadoop/yarn/lib/aopalliance-1.0.jar:/opt/hadoop/share/hadoop/yarn/lib/guice-servlet-3.0.jar:/opt/hadoop/share/hadoop/yarn/hadoop-yarn-server-tests-2.7.5.jar:/opt/hadoop/share/hadoop/yarn/hadoop-yarn-registry-2.7.5.jar:/opt/hadoop/share/hadoop/yarn/hadoop-yarn-server-sharedcachemanager-2.7.5.jar:/opt/hadoop/share/hadoop/yarn/hadoop-yarn-applications-unmanaged-am-launcher-2.7.5.jar:/opt/hadoop/share/hadoop/yarn/hadoop-yarn-server-common-2.7.5.jar:/opt/hadoop/share/hadoop/yarn/hadoop-yarn-api-2.7.5.jar:/opt/hadoop/share/hadoop/yarn/hadoop-yarn-server-applicationhistoryservice-2.7.5.jar:/opt/hadoop/share/hadoop/yarn/hadoop-yarn-server-nodemanager-2.7.5.jar:/opt/hadoop/share/hadoop/yarn/hadoop-yarn-client-2.7.5.jar:/opt/hadoop/share/hadoop/yarn/hadoop-yarn-server-web-proxy-2.7.5.jar:/opt/hadoop/share/hadoop/yarn/hadoop-yarn-applications-distributedshell-2.7.5.jar:/opt/hadoop/share/hadoop/yarn/hadoop-yarn-common-2.7.5.jar:/opt/hadoop/share/hadoop/yarn/hadoop-yarn-server-resourcemanager-2.7.5.jar:/opt/hadoop/share/hadoop/mapreduce/lib/xz-1.0.jar:/opt/hadoop/share/hadoop/mapreduce/lib/paranamer-2.3.jar:/opt/hadoop/share/hadoop/mapreduce/lib/javax.inject-1.jar:/opt/hadoop/share/hadoop/mapreduce/lib/commons-io-2.4.jar:/opt/hadoop/share/hadoop/mapreduce/lib/log4j-1.2.17.jar:/opt/hadoop/share/hadoop/mapreduce/lib/protobuf-java-2.5.0.jar:/opt/hadoop/share/hadoop/mapreduce/lib/leveldbjni-all-1.8.jar:/opt/hadoop/share/hadoop/mapreduce/lib/jackson-mapper-asl-1.9.13.jar:/opt/hadoop/share/hadoop/mapreduce/lib/asm-3.2.jar:/opt/hadoop/share/hadoop/mapreduce/lib/jersey-guice-1.9.jar:/opt/hadoop/share/hadoop/mapreduce/lib/netty-3.6.2.Final.jar:/opt/hadoop/share/hadoop/mapreduce/lib/junit-4.11.jar:/opt/hadoop/share/hadoop/mapreduce/lib/commons-compress-1.4.1.jar:/opt/hadoop/share/hadoop/mapreduce/lib/guice-3.0.jar:/opt/hadoop/share/hadoop/mapreduce/lib/jackson-core-asl-1.9.13.jar:/opt/hadoop/share/hadoop/mapreduce/lib/hadoop-annotations-2.7.5.jar:/opt/hadoop/share/hadoop/mapreduce/lib/avro-1.7.4.jar:/opt/hadoop/share/hadoop/mapreduce/lib/jersey-core-1.9.jar:/opt/hadoop/share/hadoop/mapreduce/lib/jersey-server-1.9.jar:/opt/hadoop/share/hadoop/mapreduce/lib/hamcrest-core-1.3.jar:/opt/hadoop/share/hadoop/mapreduce/lib/aopalliance-1.0.jar:/opt/hadoop/share/hadoop/mapreduce/lib/guice-servlet-3.0.jar:/opt/hadoop/share/hadoop/mapreduce/lib/snappy-java-1.0.4.1.jar:/opt/hadoop/share/hadoop/mapreduce/hadoop-mapreduce-client-jobclient-2.7.5.jar:/opt/hadoop/share/hadoop/mapreduce/hadoop-mapreduce-client-app-2.7.5.jar:/opt/hadoop/share/hadoop/mapreduce/hadoop-mapreduce-client-hs-plugins-2.7.5.jar:/opt/hadoop/share/hadoop/mapreduce/hadoop-mapreduce-client-shuffle-2.7.5.jar:/opt/hadoop/share/hadoop/mapreduce/hadoop-mapreduce-client-core-2.7.5.jar:/opt/hadoop/share/hadoop/mapreduce/hadoop-mapreduce-examples-2.7.5.jar:/opt/hadoop/share/hadoop/mapreduce/hadoop-mapreduce-client-common-2.7.5.jar:/opt/hadoop/share/hadoop/mapreduce/hadoop-mapreduce-client-hs-2.7.5.jar:/opt/hadoop/share/hadoop/mapreduce/hadoop-mapreduce-client-jobclient-2.7.5-tests.jar:/opt/hadoop/contrib/capacity-scheduler/*.jar
STARTUP_MSG:   build = Unknown -r Unknown; compiled by 'root' on 2018-01-05T22:55Z
STARTUP_MSG:   java = 1.8.0_65
************************************************************/
18/01/07 18:05:12 INFO namenode.NameNode: registered UNIX signal handlers for [TERM, HUP, INT]
18/01/07 18:05:12 INFO namenode.NameNode: createNameNode [-format]
Formatting using clusterid: CID-b42dbd1b-5f69-4e43-931e-552df21b4c9e
18/01/07 18:05:16 INFO namenode.FSNamesystem: No KeyProvider found.
18/01/07 18:05:16 INFO namenode.FSNamesystem: fsLock is fair: true
18/01/07 18:05:16 INFO namenode.FSNamesystem: Detailed lock hold time metrics enabled: false
18/01/07 18:05:16 INFO blockmanagement.DatanodeManager: dfs.block.invalidate.limit=1000
18/01/07 18:05:16 INFO blockmanagement.DatanodeManager: dfs.namenode.datanode.registration.ip-hostname-check=true
18/01/07 18:05:16 INFO blockmanagement.BlockManager: dfs.namenode.startup.delay.block.deletion.sec is set to 000:00:00:00.000
18/01/07 18:05:16 INFO blockmanagement.BlockManager: The block deletion will start around 2018 jan 07 18:05:16
18/01/07 18:05:16 INFO util.GSet: Computing capacity for map BlocksMap
18/01/07 18:05:16 INFO util.GSet: VM type       = 32-bit
18/01/07 18:05:16 INFO util.GSet: 2.0% max memory 966.8 MB = 19.3 MB
18/01/07 18:05:16 INFO util.GSet: capacity      = 2^22 = 4194304 entries
18/01/07 18:05:16 INFO blockmanagement.BlockManager: dfs.block.access.token.enable=false
18/01/07 18:05:16 INFO blockmanagement.BlockManager: defaultReplication         = 1
18/01/07 18:05:16 INFO blockmanagement.BlockManager: maxReplication             = 512
18/01/07 18:05:16 INFO blockmanagement.BlockManager: minReplication             = 1
18/01/07 18:05:16 INFO blockmanagement.BlockManager: maxReplicationStreams      = 2
18/01/07 18:05:16 INFO blockmanagement.BlockManager: replicationRecheckInterval = 3000
18/01/07 18:05:16 INFO blockmanagement.BlockManager: encryptDataTransfer        = false
18/01/07 18:05:16 INFO blockmanagement.BlockManager: maxNumBlocksToLog          = 1000
18/01/07 18:05:16 INFO namenode.FSNamesystem: fsOwner             = hduser (auth:SIMPLE)
18/01/07 18:05:16 INFO namenode.FSNamesystem: supergroup          = supergroup
18/01/07 18:05:16 INFO namenode.FSNamesystem: isPermissionEnabled = true
18/01/07 18:05:16 INFO namenode.FSNamesystem: HA Enabled: false
18/01/07 18:05:16 INFO namenode.FSNamesystem: Append Enabled: true
18/01/07 18:05:18 INFO util.GSet: Computing capacity for map INodeMap
18/01/07 18:05:18 INFO util.GSet: VM type       = 32-bit
18/01/07 18:05:18 INFO util.GSet: 1.0% max memory 966.8 MB = 9.7 MB
18/01/07 18:05:18 INFO util.GSet: capacity      = 2^21 = 2097152 entries
18/01/07 18:05:18 INFO namenode.FSDirectory: ACLs enabled? false
18/01/07 18:05:18 INFO namenode.FSDirectory: XAttrs enabled? true
18/01/07 18:05:18 INFO namenode.FSDirectory: Maximum size of an xattr: 16384
18/01/07 18:05:18 INFO namenode.NameNode: Caching file names occuring more than 10 times
18/01/07 18:05:18 INFO util.GSet: Computing capacity for map cachedBlocks
18/01/07 18:05:18 INFO util.GSet: VM type       = 32-bit
18/01/07 18:05:18 INFO util.GSet: 0.25% max memory 966.8 MB = 2.4 MB
18/01/07 18:05:18 INFO util.GSet: capacity      = 2^19 = 524288 entries
18/01/07 18:05:18 INFO namenode.FSNamesystem: dfs.namenode.safemode.threshold-pct = 0.9990000128746033
18/01/07 18:05:18 INFO namenode.FSNamesystem: dfs.namenode.safemode.min.datanodes = 0
18/01/07 18:05:18 INFO namenode.FSNamesystem: dfs.namenode.safemode.extension     = 30000
18/01/07 18:05:18 INFO metrics.TopMetrics: NNTop conf: dfs.namenode.top.window.num.buckets = 10
18/01/07 18:05:18 INFO metrics.TopMetrics: NNTop conf: dfs.namenode.top.num.users = 10
18/01/07 18:05:18 INFO metrics.TopMetrics: NNTop conf: dfs.namenode.top.windows.minutes = 1,5,25
18/01/07 18:05:18 INFO namenode.FSNamesystem: Retry cache on namenode is enabled
18/01/07 18:05:18 INFO namenode.FSNamesystem: Retry cache will use 0.03 of total heap and retry cache entry expiry time is 600000 millis
18/01/07 18:05:18 INFO util.GSet: Computing capacity for map NameNodeRetryCache
18/01/07 18:05:18 INFO util.GSet: VM type       = 32-bit
18/01/07 18:05:18 INFO util.GSet: 0.029999999329447746% max memory 966.8 MB = 297.0 KB
18/01/07 18:05:18 INFO util.GSet: capacity      = 2^16 = 65536 entries
18/01/07 18:05:19 INFO namenode.FSImage: Allocated new BlockPoolId: BP-1128740-192.168.1.104-1515359118807
18/01/07 18:05:19 INFO common.Storage: Storage directory /opt/hadoop/hadoop_data/hdfs/namenode has been successfully formatted.
18/01/07 18:05:19 INFO namenode.FSImageFormatProtobuf: Saving image file /opt/hadoop/hadoop_data/hdfs/namenode/current/fsimage.ckpt_0000000000000000000 using no compression
18/01/07 18:05:19 INFO namenode.FSImageFormatProtobuf: Image file /opt/hadoop/hadoop_data/hdfs/namenode/current/fsimage.ckpt_0000000000000000000 of size 323 bytes saved in 0 seconds.
18/01/07 18:05:19 INFO namenode.NNStorageRetentionManager: Going to retain 1 images with txid >= 0
18/01/07 18:05:19 INFO util.ExitUtil: Exiting with status 0
18/01/07 18:05:19 INFO namenode.NameNode: SHUTDOWN_MSG: 
/************************************************************
SHUTDOWN_MSG: Shutting down NameNode at node1/192.168.1.104
************************************************************/

```

#### Inicializar serviços do hadoop

cd $HADOOP_HOME/sbin

./start-dfs.sh

```
hduser@node1:/opt/hadoop $ cd $HADOOP_HOME/sbin
hduser@node1:/opt/hadoop/sbin $ ./start-dfs.sh
Starting namenodes on [node1]
node1: starting namenode, logging to /opt/hadoop/logs/hadoop-hduser-namenode-node1.out
The authenticity of host 'localhost (127.0.0.1)' can't be established.
ECDSA key fingerprint is f9:eb:95:56:22:12:6e:2e:28:03:e9:ec:ec:83:dd:d5.
Are you sure you want to continue connecting (yes/no)? yes
localhost: Warning: Permanently added 'localhost' (ECDSA) to the list of known hosts.
localhost: starting datanode, logging to /opt/hadoop/logs/hadoop-hduser-datanode-node1.out
Starting secondary namenodes [0.0.0.0]
The authenticity of host '0.0.0.0 (0.0.0.0)' can't be established.
ECDSA key fingerprint is f9:eb:95:56:22:12:6e:2e:28:03:e9:ec:ec:83:dd:d5.
Are you sure you want to continue connecting (yes/no)? yes
0.0.0.0: Warning: Permanently added '0.0.0.0' (ECDSA) to the list of known hosts.
0.0.0.0: starting secondarynamenode, logging to /opt/hadoop/logs/hadoop-hduser-secondarynamenode-node1.out

```

./start-yarn.sh

```
hduser@node1:/opt/hadoop/sbin $ ./start-yarn.sh
starting yarn daemons
starting resourcemanager, logging to /opt/hadoop/logs/yarn-hduser-resourcemanager-node1.out
localhost: starting nodemanager, logging to /opt/hadoop/logs/yarn-hduser-nodemanager-node1.out

```

#### Lista serviços em execução

jps 

```
hduser@node1:/opt/hadoop/sbin $ jps
2209 Jps
2082 NodeManager
1992 ResourceManager
1819 SecondaryNameNode
1661 DataNode
1567 NameNode

```

#### Finalizar serviços em execução

./stop-dfs.sh 

```
hduser@node1:/opt/hadoop/sbin $ ./stop-dfs.sh
Stopping namenodes on [node1]
node1: stopping namenode
localhost: stopping datanode
Stopping secondary namenodes [0.0.0.0]
0.0.0.0: stopping secondarynamenode

```

./stop-yarn.sh
```
hduser@node1:/opt/hadoop/sbin $ ./stop-yarn.sh
stopping yarn daemons
stopping resourcemanager
localhost: stopping nodemanager
no proxyserver to stop

```

## Testes de funcionamento do hadoop

### Exemplo do cálculo do valor de PI:

cd $HADOOP_INSTALL/bin

./hadoop jar /opt/hadoop/share/hadoop/mapreduce/hadoop-mapreduce-examples-2.7.5.jar pi 2 4

### Exemplo wordCount:

#### Copie o arquivo, verifique HDFS para o arquivo, então execute WordCount no arquivo:

hdfs dfs -copyFromLocal /opt/hadoop/LICENSE.txt /license.txt

hdfs dfs -ls /

cd /opt/hadoop/bin

./hadoop jar /opt/hadoop/share/hadoop/mapreduce/hadoop-mapreduce-examples-2.7.5.jar wordcount /license.txt /license-out.txt

#### Para visualizar o resultado do wordcount siga os passos a seguir:

hdfs dfs -copyToLocal /license-out.txt ~/

nano ~/license-out.txt/part-r-00000

## Referências:

http://data.andyburgin.co.uk/post/157450047463/running-hue-on-a-raspberry-pi-hadoop-cluster

http://www.widriksson.com/raspberry-pi-2-hadoop-2-cluster/

https://medium.com/@jasonicarter/how-to-hadoop-at-home-with-raspberry-pi-part-1-3b71f1b8ac4e

https://www.tutorialspoint.com/hadoop/

