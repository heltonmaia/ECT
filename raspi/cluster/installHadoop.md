# Instalação do Hadoop na raspberry

#### Link para baixar imagem do raspbian:

https://downloads.raspberrypi.org/raspbian/images/raspbian-2017-07-05/2017-07-05-raspbian-jessie.zip

Para instalar imagem no cartão foi utilizado o etcher. 

#### Link para baixar o etcher

https://etcher.io/

## Instalação das dependências necessárias

sudo apt-get install  zlib1g zlib1g-dbg  zlib1g-dev zlibc libssl-dev lbzip2  libzip-dev  pbzip2 

sudo apt-get install libfuse-dev libsnappy-dev libsnappy-java pkg-config libbz2-dev

sudo apt-get install ssh build-essential  g++ autoconf automake libtool cmake pkgconf 

sudo apt-get install zip unzip

## Instalação do java

Antes de iniciar  a instalação confira  se o java já veio instalado como de costume no Raspbian jessie mais recentes.

#### Instalar o java:

sudo apt-get install oracle-java8-jdk

#### Utilize a comando a seguir para selecionar a versão do java:

sudo update-alternatives --config java

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

## 2ª opção de instalação do protobuf

#### Baixar e descompactar o protobuf:

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

## Instalação do Apache Maven
    
#### Baixar e descompactar o apache maven: 
              
cd /usr/local

wget http://ftp.unicamp.br/pub/apache/maven/maven-3/3.5.2/binaries/apache-maven-3.5.2-bin.tar.gz

sudo tar xzf apache-maven-3.5.2-bin.tar.gz

sudo ln -s apache-maven-3.5.2 apache-maven

Configuração das variáveis de ambientes, utilize o comando abaixo para criar o arquivo.

sudo nano /etc/profile.d/apache-maven.sh

Adicione as variáveis abaixo ao arquivo apache-maven.sh

export JAVA_HOME=/usr/lib/jvm/java-8-oracle

export M2_HOME=/usr/local/apache-maven

export MAVEN_HOME=/usr/local/apache-maven

export PATH=${M2_HOME}/bin:${PATH}

Em seguida, saia e salve o arquivo com os comandos de tecla Ctrl + X, Y, enter.

#### Para atualizar as alterações utilize o comando a seguir: 

source /etc/profile.d/apache-maven.sh

#### Para verificar se instalação foi realizada com sucesso:
              
mvn -version


## Configuração de rede na Raspberry

#### Desativar o ipv6:

sudo nano /etc/sysctl.conf

#### Altere o arquivo conforme as informações abaixo, caso não exista adicione:

net.ipv6.conf.all.disable_ipv6 = 1

net.ipv6.conf.default.disable_ipv6 = 1

net.ipv6.conf.lo.disable_ipv6 = 1

net.ipv6.conf.eth0.disable_ipv6 = 1

 **Nota:** Caso queira habilitar no futuro, troque o valor 1 por 0.

#### Em seguida reinicie o serviço com o comando abaixo:

sudo sysctl -p

## Configurar rede para modo estático 

#### O comando exibirá o endereço de ip da máquina:

hostname -I

#### Adicione ao arquivo de interfaces o modo estático para o eth0:

sudo nano /etc/network/interfaces

#### Neste caso, foi utilizada a configuração abaixo, que pode mudar de acordo com a necessidade de cada caso.

iface eth0 inet static

address 192.168.1.103

netmask 255.255.255.0

gateway 192.168.1.1

#### Em seguida abra o arquivo hosts:

sudo nano /etc/hosts

#### Adicione ao arquivo a linha abaixo e salve:

192.168.1.103   node1

#### Por fim abrir os arquivos hostname e substitua o nome Raspberry por node1:

sudo nano /etc/hostname

Agora reset a Raspberry

Configuração do usuário hadoop

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

cd hadoop-2.7.5-src/hadoop-common-project/hadoop-common/src

wget https://issues.apache.org/jira/secure/attachment/12570212/HADOOP-9320.patch

patch < HADOOP-9320.patch


#### O comando a seguir dará início a processo de compilação:

mvn package -Pdist,native -DskipTests -Dtar

cd hadoop-2.7.5-src/hadoop-dist/target/

cp -R hadoop-2.7.5 /opt/hadoop

cd /opt

chown -R hduser:hadoop hadoop

tar -zcvf /root/hadoop-2.7.5.armf.tar.gz hadoop (Para possíveis backup)

#### Adicione ao final de /etc/bash.bashrc as seguintes linhas de exportação:

sudo nano /etc/bash.bashrc

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

#### Aplique essas alterações:

source ~/.bashrc

#### Variáveis de ambiente Hadoop:

sudo nano /opt/hadoop/etc/hadoop/hadoop-env.sh

#### Descometa e atualiza as duas linhas de exportação do hadoop_env.sh:
 
export JAVA_HOME=/usr/lib/jvm/jdk-8-oracle-arm32-vfp-hflt

#### Para verificar se a compilação da biblioteca nativa foi realizada com sucesso:

su hduser

hadoop checknative -a

#### Para verificar se instalação foi realizada com sucesso:

su hduser

hadoop version

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

#### Inicializar serviços do hadoop

cd $HADOOP_HOME/sbin

./start-dfs.sh

./start-yarn.sh

#### Lista serviços em execução

jps 

#### Finalizar serviços em execução

./stop-dfs.sh 

./stop-yarn.sh

## Testes de funcionamento do hadoop

### Exemplo do cálculo do valor de PI:

cd $HADOOP_INSTALL/bin

./hadoop jar /opt/hadoop/share/hadoop/mapreduce/hadoop-mapreduce-examples-2.7.5.jar pi 4 2

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

