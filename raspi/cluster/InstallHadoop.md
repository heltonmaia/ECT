# Installing Hadoop on Raspberry PI 3 model B

#### Link to download image of raspbian

https://downloads.raspberrypi.org/raspbian/images/raspbian-2017-07-05/2017-07-05-raspbian-jessie.zip

Write image in micro sd card was utilized the etcher. 

#### Link to download etcher

https://etcher.io/

## Installing dependencies

sudo -i

apt-get update

apt-get upgrade

apt-get install  zlib1g zlib1g-dbg  zlib1g-dev zlibc libssl-dev lbzip2  libzip-dev  pbzip2 

apt-get install libfuse-dev libsnappy-dev libsnappy-java pkg-config libbz2-dev

apt-get install ssh build-essential  g++ autoconf automake libtool cmake pkgconf 

apt-get install zip unzip

## Installing java

*Before starting the installation check if java already be installed on Raspbian.*

#### Install java:

sudo -i

apt-get install oracle-java8-jdk

#### Use the following command to select the java version:

update-alternatives --config java

Select option  /usr/lib/jvm/jdk-8-oracle-arm32-vfp-hflt/jre/bin/java.

#### The following command verify that the installation was successful:

java -version

```
hduser@node1:~ $ java -version
java version "1.8.0_65"
Java(TM) SE Runtime Environment (build 1.8.0_65-b17)
Java HotSpot(TM) Client VM (build 25.65-b01, mixed mode)

```

## Installing protobuf 2.5.0

### 1st option to install protobuf

#### Download and  unpack  protobuf:

sudo -i

apt-get update

apt-get install dh-autoreconf

wget https://github.com/HemersonRafael/protobufOfCluster/archive/master.zip

unzip master.zip

cd protobufOfCluster-master

cd protobuf-2.5.0

#### Then generate the build configuration files:

./autogen.sh

./configure --prefix=/usr

#### Build and install protobuf

make

make check

make install

#### The following command verify that the installation was successful:

protoc --version
```
hduser@node1:~ $ protoc --version
libprotoc 2.5.0

```


### 2st option to install protobuf

#### Download and  install protobuf:

sudo -i

apt-get update

wget https://github.com/google/protobuf/releases/download/v2.5.0/protobuf-2.5.0.tar.gz

tar xzvf protobuf-2.5.0.tar.gz

cd protobuf-2.5.0

#### Then generate the build configuration files:

./configure --prefix=/usr

#### Build and unpack  protobuf

make

make check

sudo make install

#### The following command verify that the installation was successful:

protoc --version
```
hduser@node1:~ $ protoc --version
libprotoc 2.5.0

```

## Installing Apache Maven
    
#### Download and  unpack  apache maven: 

sudo -i

apt-get update  

cd /usr/local

wget http://ftp.unicamp.br/pub/apache/maven/maven-3/3.5.2/binaries/apache-maven-3.5.2-bin.tar.gz

tar xzf apache-maven-3.5.2-bin.tar.gz

ln -s apache-maven-3.5.2 apache-maven

Configuring environment variables, use the command below to create the file.

nano /etc/profile.d/apache-maven.sh

Add the variables below to apache-maven.sh

```
export JAVA_HOME=/usr/lib/jvm/jdk-8-oracle-arm32-vfp-hflt
export M2_HOME=/usr/local/apache-maven
export MAVEN_HOME=/usr/local/apache-maven
export PATH=${M2_HOME}/bin:${PATH}
```

#### To update the changes use the following command: 

source /etc/profile.d/apache-maven.sh

#### The following command verify that the installation was successful:
              
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
## Network setting on Raspberry

#### Disable ipv6:

sudo -i

nano /etc/sysctl.conf

#### Change the file according to the information below, if it does not exist add:

```
net.ipv6.conf.all.disable_ipv6 = 1
net.ipv6.conf.default.disable_ipv6 = 1
net.ipv6.conf.lo.disable_ipv6 = 1
net.ipv6.conf.eth0.disable_ipv6 = 1
```
 #### Then restart the service with the command below:
 
sysctl -p

## Configure network for static mode 

#### The command will display the IP address of the machine:

hostname -I

#### Add to the interfaces file the static mode for eth0:

nano /etc/network/interfaces

#### In this case, the following configuration was used, which can change according to the need of each case.

```
iface eth0 inet static
address 192.168.1.103
netmask 255.255.255.0
gateway 192.168.1.1
```
#### Then edit the hosts file:

nano /etc/hosts

#### Add to file the line below and save:
```
192.168.1.103   node1
```
#### Finally open the hostname files and replace the Raspberry name with node1:

nano /etc/hostname

Reboot the Raspberry! 

## Creating a user for Hadoop

#### Add a group, a user and then add the user to the group

sudo addgroup hadoop

sudo adduser --ingroup hadoop hduser

sudo adduser hduser sudo

#### Switch users and create SSH key with no passphrase

su hduser

mkdir ~/.ssh

ssh-keygen -t rsa -P ""

cat ~/.ssh/id_rsa.pub > ~/.ssh/authorized_keys

#### Test the SSH connection

ssh node1

exit
  
## Installing Hadoop-2.7.5

#### Download and extrac hadoop:

sudo -i

wget http://ftp.unicamp.br/pub/apache/hadoop/common/hadoop-2.7.5/hadoop-2.7.5-src.tar.gz

tar -xvzf hadoop-2.7.5.tar.gz

cd hadoop-2.7.5-src

#### Configuration to instruct the build process for ARM architecture:

nano pom.xml

Em seguida, pressione Ctrl+Shift + - (Ctrl+ _) Insira o número da linha igual a 82. Adicione  entre  ``` <properties></properties>```  a tags a seguir:

```xml
<additionalparam>-Xdoclint:none</additionalparam>
```

#### You will also need to install the HADOOP-9320 patch:

sudo -i

cd hadoop-2.7.5-src/hadoop-common-project/hadoop-common/src

wget https://issues.apache.org/jira/secure/attachment/12570212/HADOOP-9320.patch

patch < HADOOP-9320.patch


#### The following command will begin the compilation process:

sudo -i

cd hadoop-2.7.5-src

mvn package -Pdist,native -DskipTests -Dtar

At the end of the process it is expected to be successful in all packages.

```
...

[INFO] Reactor Summary:
[INFO] 
[INFO] Apache Hadoop Main ................................. SUCCESS [  7.786 s]
[INFO] Apache Hadoop Build Tools .......................... SUCCESS [  5.599 s]
[INFO] Apache Hadoop Project POM .......................... SUCCESS [  8.169 s]
[INFO] Apache Hadoop Annotations .......................... SUCCESS [ 12.486 s]
[INFO] Apache Hadoop Assemblies ........................... SUCCESS [  1.004 s]
[INFO] Apache Hadoop Project Dist POM ..................... SUCCESS [  5.103 s]
[INFO] Apache Hadoop Maven Plugins ........................ SUCCESS [ 14.080 s]
[INFO] Apache Hadoop MiniKDC .............................. SUCCESS [ 25.260 s]
[INFO] Apache Hadoop Auth ................................. SUCCESS [ 19.645 s]
[INFO] Apache Hadoop Auth Examples ........................ SUCCESS [ 12.382 s]
[INFO] Apache Hadoop Common ............................... SUCCESS [08:43 min]
[INFO] Apache Hadoop NFS .................................. SUCCESS [ 33.713 s]
[INFO] Apache Hadoop KMS .................................. SUCCESS [01:43 min]
[INFO] Apache Hadoop Common Project ....................... SUCCESS [  1.908 s]
[INFO] Apache Hadoop HDFS ................................. SUCCESS [18:41 min]
[INFO] Apache Hadoop HttpFS ............................... SUCCESS [02:14 min]
[INFO] Apache Hadoop HDFS BookKeeper Journal .............. SUCCESS [ 34.151 s]
[INFO] Apache Hadoop HDFS-NFS ............................. SUCCESS [ 18.870 s]
[INFO] Apache Hadoop HDFS Project ......................... SUCCESS [  0.186 s]
[INFO] hadoop-yarn ........................................ SUCCESS [  0.247 s]
[INFO] hadoop-yarn-api .................................... SUCCESS [04:29 min]
[INFO] hadoop-yarn-common ................................. SUCCESS [03:57 min]
[INFO] hadoop-yarn-server ................................. SUCCESS [  1.549 s]
[INFO] hadoop-yarn-server-common .......................... SUCCESS [01:04 min]
[INFO] hadoop-yarn-server-nodemanager ..................... SUCCESS [01:55 min]
[INFO] hadoop-yarn-server-web-proxy ....................... SUCCESS [ 20.086 s]
[INFO] hadoop-yarn-server-applicationhistoryservice ....... SUCCESS [ 29.019 s]
[INFO] hadoop-yarn-server-resourcemanager ................. SUCCESS [01:18 min]
[INFO] hadoop-yarn-server-tests ........................... SUCCESS [ 17.978 s]
[INFO] hadoop-yarn-client ................................. SUCCESS [ 22.427 s]
[INFO] hadoop-yarn-server-sharedcachemanager .............. SUCCESS [ 24.147 s]
[INFO] hadoop-yarn-applications ........................... SUCCESS [  0.359 s]
[INFO] hadoop-yarn-applications-distributedshell .......... SUCCESS [ 15.424 s]
[INFO] hadoop-yarn-applications-unmanaged-am-launcher ..... SUCCESS [ 12.780 s]
[INFO] hadoop-yarn-site ................................... SUCCESS [  0.346 s]
[INFO] hadoop-yarn-registry ............................... SUCCESS [ 29.259 s]
[INFO] hadoop-yarn-project ................................ SUCCESS [ 42.047 s]
[INFO] hadoop-mapreduce-client ............................ SUCCESS [  1.707 s]
[INFO] hadoop-mapreduce-client-core ....................... SUCCESS [01:35 min]
[INFO] hadoop-mapreduce-client-common ..................... SUCCESS [01:42 min]
[INFO] hadoop-mapreduce-client-shuffle .................... SUCCESS [ 12.791 s]
[INFO] hadoop-mapreduce-client-app ........................ SUCCESS [01:03 min]
[INFO] hadoop-mapreduce-client-hs ......................... SUCCESS [ 41.184 s]
[INFO] hadoop-mapreduce-client-jobclient .................. SUCCESS [ 52.799 s]
[INFO] hadoop-mapreduce-client-hs-plugins ................. SUCCESS [ 13.776 s]
[INFO] Apache Hadoop MapReduce Examples ................... SUCCESS [ 37.708 s]
[INFO] hadoop-mapreduce ................................... SUCCESS [ 27.087 s]
[INFO] Apache Hadoop MapReduce Streaming .................. SUCCESS [ 22.420 s]
[INFO] Apache Hadoop Distributed Copy ..................... SUCCESS [01:04 min]
[INFO] Apache Hadoop Archives ............................. SUCCESS [ 12.542 s]
[INFO] Apache Hadoop Rumen ................................ SUCCESS [ 28.560 s]
[INFO] Apache Hadoop Gridmix .............................. SUCCESS [ 18.383 s]
[INFO] Apache Hadoop Data Join ............................ SUCCESS [  7.268 s]
[INFO] Apache Hadoop Ant Tasks ............................ SUCCESS [  5.620 s]
[INFO] Apache Hadoop Extras ............................... SUCCESS [  8.909 s]
[INFO] Apache Hadoop Pipes ................................ SUCCESS [ 44.512 s]
[INFO] Apache Hadoop OpenStack support .................... SUCCESS [ 14.286 s]
[INFO] Apache Hadoop Amazon Web Services support .......... SUCCESS [05:11 min]
[INFO] Apache Hadoop Azure support ........................ SUCCESS [01:50 min]
[INFO] Apache Hadoop Client ............................... SUCCESS [01:26 min]
[INFO] Apache Hadoop Mini-Cluster ......................... SUCCESS [ 14.930 s]
[INFO] Apache Hadoop Scheduler Load Simulator ............. SUCCESS [ 37.110 s]
[INFO] Apache Hadoop Tools Dist ........................... SUCCESS [01:21 min]
[INFO] Apache Hadoop Tools ................................ SUCCESS [  0.343 s]
[INFO] Apache Hadoop Distribution ......................... SUCCESS [07:41 min]
[INFO] ------------------------------------------------------------------------
[INFO] BUILD SUCCESS
[INFO] ------------------------------------------------------------------------
[INFO] Total time: 01:20 h
[INFO] Finished at: 2018-01-06T00:14:08Z
[INFO] Final Memory: 85M/224M
[INFO] ------------------------------------------------------------------------

```

cd hadoop-2.7.5-src/hadoop-dist/target/

cp -R hadoop-2.7.5 /opt/hadoop

cd /opt

chown -R hduser:hadoop hadoop

tar -zcvf /root/hadoop-2.7.5.armf.tar.gz hadoop  (To backup)

#### Add to the end of /etc/bash.bashrc the following export lines:

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

#### Apply these changes:

source ~/.bashrc

#### Hadoop Environment Variables:

sudo nano /opt/hadoop/etc/hadoop/hadoop-env.sh

#### Uncomment and update the hadoop_env.sh export lines:
 
export JAVA_HOME=/usr/lib/jvm/jdk-8-oracle-arm32-vfp-hflt

#### To verify that the native library build was successful:

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
#### The following command verify that the installation was successful:

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

 ## Define the configuration files hadoop for pseudo distributed  mode

cd /opt/hadoop/etc/hadoop

### core-site

Open the file with nano or another editor of preference:

sudo nano core-site.xml

Then, replace the tags ```<configuration></configuration>``` with the lower ones.

```xml
<configuration>
  <property>
    <name>fs.default.name</name>
    <value>hdfs://node1:9000</value>
  </property>
</configuration>
```

In the same manner with the others:

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

#### Create folders and permissions for HDFS

sudo mkdir -p /opt/hadoop/hadoop_data/hdfs/namenode

sudo mkdir -p /opt/hadoop/hadoop_data/hdfs/datanode

sudo chown hduser:hadoop /opt/hadoop/hadoop_data/hdfs -R

sudo chmod 750 /opt/hadoop/hadoop_data/hdfs

#### Format HDFS

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

#### start services

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

#### List running services

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

#### Stop running services

cd $HADOOP_INSTALL/sbin

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

## Hadoop performance checks

### Run a Hadoop provided example, pi, which calculates the value of pi

cd $HADOOP_INSTALL/bin

./hadoop jar /opt/hadoop/share/hadoop/mapreduce/hadoop-mapreduce-examples-2.7.5.jar pi 4 2 

```
hduser@node1:cd $HADOOP_INSTALL/bin
hduser@node1:/opt/hadoop/bin $ ./hadoop jar /opt/hadoop/share/hadoop/mapreduce/hadoop-mapreduce-examples-2.7.5.jar pi 4 2
Number of Maps  = 4
Samples per Map = 2
Wrote input for Map #0
Wrote input for Map #1
Wrote input for Map #2
Wrote input for Map #3
Starting Job
18/01/08 22:00:49 INFO client.RMProxy: Connecting to ResourceManager at node1/192.168.1.104:8050
18/01/08 22:00:53 INFO input.FileInputFormat: Total input paths to process : 4
18/01/08 22:00:54 INFO mapreduce.JobSubmitter: number of splits:4
18/01/08 22:00:55 INFO mapreduce.JobSubmitter: Submitting tokens for job: job_1515459417185_0001
18/01/08 22:00:58 INFO impl.YarnClientImpl: Submitted application application_1515459417185_0001
18/01/08 22:00:59 INFO mapreduce.Job: The url to track the job: http://node1:8088/proxy/application_1515459417185_0001/
18/01/08 22:00:59 INFO mapreduce.Job: Running job: job_1515459417185_0001
18/01/08 22:01:58 INFO mapreduce.Job: Job job_1515459417185_0001 running in uber mode : false
18/01/08 22:01:58 INFO mapreduce.Job:  map 0% reduce 0%
18/01/08 22:02:44 INFO mapreduce.Job:  map 25% reduce 0%
18/01/08 22:02:44 INFO mapreduce.Job: Task Id : attempt_1515459417185_0001_m_000001_0, Status : FAILED
Container killed on request. Exit code is 137
Container exited with a non-zero exit code 137
Killed by external signal

18/01/08 22:03:11 INFO mapreduce.Job:  map 75% reduce 0%
18/01/08 22:03:28 INFO mapreduce.Job:  map 100% reduce 0%
18/01/08 22:03:30 INFO mapreduce.Job:  map 100% reduce 100%
18/01/08 22:03:31 INFO mapreduce.Job: Job job_1515459417185_0001 completed successfully
18/01/08 22:03:32 INFO mapreduce.Job: Counters: 51
	File System Counters
		FILE: Number of bytes read=94
		FILE: Number of bytes written=611857
		FILE: Number of read operations=0
		FILE: Number of large read operations=0
		FILE: Number of write operations=0
		HDFS: Number of bytes read=1048
		HDFS: Number of bytes written=215
		HDFS: Number of read operations=19
		HDFS: Number of large read operations=0
		HDFS: Number of write operations=3
	Job Counters 
		Failed map tasks=1
		Launched map tasks=5
		Launched reduce tasks=1
		Other local map tasks=1
		Data-local map tasks=4
		Total time spent by all maps in occupied slots (ms)=607748
		Total time spent by all reduces in occupied slots (ms)=33332
		Total time spent by all map tasks (ms)=151937
		Total time spent by all reduce tasks (ms)=16666
		Total vcore-milliseconds taken by all map tasks=303874
		Total vcore-milliseconds taken by all reduce tasks=33332
		Total megabyte-milliseconds taken by all map tasks=38895872
		Total megabyte-milliseconds taken by all reduce tasks=2133248
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
		GC time elapsed (ms)=2807
		CPU time spent (ms)=9550
		Physical memory (bytes) snapshot=719986688
		Virtual memory (bytes) snapshot=1523646464
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
Job Finished in 164.174 seconds
Estimated value of Pi is 3.50000000000000000000

```

### Exemplo wordCount:

#### Copy the file,check HDFS for the file then run wordCount on the file:

hdfs dfs -copyFromLocal /opt/hadoop/LICENSE.txt /license.txt

hdfs dfs -ls /

cd /opt/hadoop/bin

./hadoop jar /opt/hadoop/share/hadoop/mapreduce/hadoop-mapreduce-examples-2.7.5.jar wordcount /license.txt /license-out.txt

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
#### to view the Wordcount result follow the steps below:

hdfs dfs -copyToLocal /license-out.txt ~/

cat ~/license-out.txt/part-r-00000
```
hduser@node1:/opt/hadoop/bin $ cat  ~/license-out.txt/part-r-00000
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
(a) the	1
(an	1
(and	3
(b) otherwise	1
(based	1
(d)	5
(except	7
(excluding	5
(http://code.google.com/p/leveldb/),	1
(i) the	1
(if	4
-	13
---------------------------------------------------------------------	1
/*	1
0.52	1
034819	1
1	1
1.10. Original	1
1.11.	1
1.12. Source	1
1.4.	1
1.4. Executable means	1
1.7.10	1
1.8.	1
1.8. Licensable means	1
1. Definitions. 	1
1995),	4
2.1	3
2.1(a)	1
2.5	1
2001-2016,	1
2005,	1
2012	1
227.7202-4	2
3.	4
3.2.	2
3.6.	2
4.1.	2
4.3,	2
6.1	1
6.3.	2
7.	4
9	1
<COPYRIGHT	1
<organization>	1
=============	1
A	23
ACCEPTANCE	1
ACCOMPANYING	1
ALL	3
ALLOW	2
APPENDIX:	1
APPLICABLE	2
AUTHOR	2
AUTHORIZED	2
Additional	3
All	13
Availability	2
BE	19
BUT	29
BY	12
Bozhanov	1
By	1
C.	2
C.F.R.	8
CAUSED	13
CHARACTER	2
COMMON	2
COMPUTER	2
CONSEQUENTIAL	17
Catholique	1
Claims	6
Claims means	1
Code.	3
Commission	1
Contracts	2
Contributions.	2
Contributor.	8
Contributor:	1
Core	3
D3	1
DFAR,	2
DISCLAIMED.	12
DISCLAIMER	5
DISCLAIMER. 	1
DO	2
Database	1
Derivative	17
Developer)	2
Disclaimer	1
EXEMPLARY,	13
EXPRESSLY	2
Entity	3
European	1
Everyone	1
External	1
FIT	2
FOR	48
FORTH	2
For	18
Foundation	4
GOODWILL,	2
Group.	1
Group:	2
Hamcrest	1
INCLUDING	5
INCLUDING,	17
INJURY	2
IS”	1
Institute	1
Jakub	1
LEGAL	2
LIABILITY	6
LIABILITY,	31
LIABLE	19
LICENSE	6
LOSS	14
Larger	10
Legal	3
License	54
License,	10
License. 	9
Licensed	3
Licensor	8
Licensor,	1
MAY	2
Modifications.	3
NON-INFRINGING.	2
NONINFRINGEMENT.	5
NOR	1
Niels	1
Nothing	2
Notices.	2
Notwithstanding	5
OF	168
ON	16
OR	169
Object	4
Obligations. 	1
OneLab	1
PART	2
PROVIDED	21
Participant.	1
Patents"	1
Patents.	1
Pawel	1
Permission	6
Program;	1
RECIPIENT	1
RECIPIENT'S	1
RESULTING	2
RI	1
RIGHTS	2
RISK	2
Recipient	11
Recipient's	6
Red	1
Redistribution	12
Required	2
Rights	2
SERVICES;	12
SHOULD	2
SOFTWARE	32
SOFTWARE,	14
SPECIAL,	15
SUCH	23
Sale	2
Section	9
Sections 2.1	1
Sections 2.1(a)	1
Sections 6.1	1
Section 2.1(b)	1
Software	72
Software,	21
Software. 	2
Software means	2
Source	28
State	1
THAT	2
THE	116
TO	15
TO,	24
Terms.	2
That	1
The	44
To	1
URIs	1
United	5
Version;	2
Versions	2
Version”	1
WHETHER	20
While	2
Work.	1
YOU.	3
York	1
You.	2
You:	2
Your	27
a	128
above	30
above,	8
absence	2
acceptance	1
accordance	1
account	1
actions	1
add	2
additional	4
admission	2
against	14
against,	1
agrees	2
all	29
alleging	5
allow	2
alone.	1
along	1
also	5
always	3
and/or	36
and 	2
appear.	1
applicable	9
appropriate	1
archives.	1
assign	1
at	12
attempt	2
attorneys	1
author	1
authorized	2
authorship,	2
available	31
avoid	1
b)	5
be	48
before	1
below	4
beyond	2
binaries	3
boilerplate	1
brackets	1
brackets!)	1
breach.	2
brought	2
bundles	11
but	7
by	113
by,	5
calculation	1
cannot	1
cause	5
caused	5
cease	1
character	1
choose	6
claims	10
claims,	8
clause	4
clear	6
code.	2
common	5
compiler	1
compliance	10
computer	11
consequential	2
construed	3
contains	5
content	1
continue	3
control	7
control,	2
conversions	1
conveyed	4
copies	13
copying	1
creation	2
damage	1
days	4
defined	5
definition,	4
delete	2
deleted	2
derivative	5
derived	9
devices. 	1
different	5
differs	2
disclaimer	12
disclaims	2
do	13
document. 	1
easier	1
entity	14
entity,	3
entity. 	1
errors,	1
exchange. 	1
executed	1
expiration	2
expressly	4
expressly,	1
external	1
fails	1
files.	1
following	60
for	59
for,	3
forth	6
forum	1
full	1
given	3
goodwill,	1
granted:	4
grantor.	1
grants	9
grossly	1
hadoop-hdfs-project/hadoop-hdfs/src/main/webapps/static/bootstrap-3.0.2	1
hadoop-tools/hadoop-sls/src/main/html/css/bootstrap.min.css	1
hadoop-tools/hadoop-sls/src/main/html/js/thirdparty/d3-LICENSE	1
hadoop-tools/hadoop-sls/src/main/html/js/thirdparty/d3.v3.js	1
hadoop-tools/hadoop-sls/src/main/html/js/thirdparty/jquery.js	1
hardware)	1
hereby	20
herein.	3
hereto,	1
hold	1
https://groups.google.com/forum/#!forum/lz4c	1
ii)	2
improving	1
inability	1
includes	7
including	20
including,	3
indemnify	5
indemnify,	1
indirectly	5
indirectly,	2
infringements	4
institute	1
intended	3
issue	1
it	19
item,	1
itself	4
least	1
legal	7
leveldbjni	1
leveldbjni-all	1
liability	15
liability. 	1
liable	1
libraries	1
license	45
license,	2
license: 	2
licensed	1
licensee)	1
licenses;	1
limitations	1
lists,	1
loss	2
made.	1
makes	7
making	1
making,	4
management	3
manner.	1
many	2
material	1
may	48
mechanical	1
meet	1
modifications:	1
must:	1
name	11
native	1
nature,	2
negligent	1
nor	8
nothing	1
number.	3
object	4
obligations	5
obligations,	1
obtaining	5
obtaining,	1
of	399
of,	8
offers	1
official	1
on	37
or	270
or,	1
owned	3
owner.	1
part	12
partners	1
per	1
percent	3
perform,	6
permission	6
permit	5
power,	3
practice,	2
preferred	1
preferred,	1
previous	4
product.	2
programs	1
project	2
prospectively	2
provide	2
provided	36
provision	9
qualify,	1
received.	1
recipient's	1
recipients'	1
regulations	2
remainder	1
represents	3
reproduce	13
reproduce,	6
required	5
reserves	1
resulting	2
revision	1
rights	56
sale	1
sale,	4
section	1
section,	1
secure	1
see:	1
separable	1
separate	4
service	1
should	4
snappy	1
software	42
soon	1
source	33
source,	1
special,	2
src/google/protobuf/stubs/atomicops_internals_power.h.	1
state	1
stated	3
submitted.	1
such	87
suitable	1
syntax	1
terminate	7
terminate,	1
terms.	1
that	116
the	649
thereof);	3
thereof.	2
those	9
through	6
time.	3
to	241
to,	2
tracking	1
trademark	2
trademark,	1
transfer	2
translation	1
understands	1
understood,	1
user	2
validly	2
value	2
versions	3
viewable	1
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

## Problems with running jobs in hadoop?

#### Clue 1:

Make sure all 6 services have been initialized, if ipv6 is disabled, the static network settings and the hadoop configuration files. If all is correct reboot the board, when it is connected again start hadoop services. Finally, try re-executing the job.

#### Clue 2:

In case the job initialization occurs, but the  present fault over the process. One of the most common causes is the safe mode active . In some situations the HDFS enters into safe mode preventing the execution of the tasks as in the example below.

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

#### To check if safe mode is active use the following command:

hdfs dfsadmin -safemode get

```
hduser@node1:/opt/hadoop/bin $ hdfs dfsadmin -safemode get
Safe mode is ON

```

#### If it is active or use the command below to deactivate:

hdfs dfsadmin -safemode leave

```
hduser@node1:/opt/hadoop/bin $ hdfs dfsadmin -safemode leave
Safe mode is OFF

```
## Accessing Hadoop on Browser

A nice way to get information about hadoop applications, nodes, storage, and tools is by using the  browser through the urls below:

Locally on board:

http://node1:50070

http://node1:8088

Externally the board, but on the same network:

http://192.168.1.104:50070

http://192.168.1.104:8088

## Inspiration

http://data.andyburgin.co.uk/post/157450047463/running-hue-on-a-raspberry-pi-hadoop-cluster

http://www.widriksson.com/raspberry-pi-2-hadoop-2-cluster/

https://medium.com/@jasonicarter/how-to-hadoop-at-home-with-raspberry-pi-part-1-3b71f1b8ac4e

https://www.tutorialspoint.com/hadoop/

