CREATE DATABASE  IF NOT EXISTS `quickfix` /*!40100 DEFAULT CHARACTER SET latin1 */;
USE `quickfix`;
-- MySQL dump 10.13  Distrib 5.5.29, for Linux (x86_64)
--
-- Host: localhost    Database: quickfix
-- ------------------------------------------------------
-- Server version	5.5.29

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `agents`
--

DROP TABLE IF EXISTS `agents`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `agents` (
  `id_agent` varchar(64) NOT NULL,
  `status` varchar(32) NOT NULL,
  `type` varchar(32) NOT NULL,
  `id_fix_config` int(11) NOT NULL,
  `id_strategy` int(11) NOT NULL,
  PRIMARY KEY (`id_agent`),
  KEY `id_fix_config_fk_idx` (`id_fix_config`),
  KEY `id_strategy_idx` (`id_strategy`),
  CONSTRAINT `id_fix_config_fk` FOREIGN KEY (`id_fix_config`) REFERENCES `fix_config` (`id_fix_config`) ON DELETE NO ACTION ON UPDATE NO ACTION,
  CONSTRAINT `id_strategy` FOREIGN KEY (`id_strategy`) REFERENCES `strategy` (`id_strategy`) ON DELETE NO ACTION ON UPDATE NO ACTION
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `agents`
--

LOCK TABLES `agents` WRITE;
/*!40000 ALTER TABLE `agents` DISABLE KEYS */;
INSERT INTO `agents` VALUES ('BBTRADER01','desactive','bband',1,24),('CLIENT1','active','banzai',1,1),('MARKETMAKER','active','mm',1,25),('MVTRADER01','desactive','mv',1,16),('ORDERMATCH','desactive','ordermatch',2,0),('RANDTRADER01','active','random',1,1),('RANDTRADER02','active','random',1,2),('RANDTRADER03','active','random',1,3),('RANDTRADER04','active','random',1,4),('RANDTRADER05','active','random',1,5),('RANDTRADER06','desactive','random',1,6),('RANDTRADER07','desactive','random',1,7),('RANDTRADER08','desactive','random',1,8),('RANDTRADER09','desactive','random',1,9),('RANDTRADER10','desactive','random',1,10),('RANDTRADER11','desactive','random',1,11),('RANDTRADER12','desactive','random',1,12),('RANDTRADER13','desactive','random',1,13),('RANDTRADER14','desactive','random',1,14),('RANDTRADER15','desactive','random',1,15),('RANDTRADER16','desactive','random',1,17),('RANDTRADER17','desactive','random',1,18),('RANDTRADER18','desactive','random',1,19),('RANDTRADER19','desactive','random',1,20),('RANDTRADER20','active','random',1,21),('RANDTRADER21','desactive','random',1,22),('RANDTRADER22','desactive','random',1,23);
/*!40000 ALTER TABLE `agents` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `exogenous`
--

DROP TABLE IF EXISTS `exogenous`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `exogenous` (
  `time` time NOT NULL,
  `value` float NOT NULL,
  `simulation_time` datetime DEFAULT NULL,
  PRIMARY KEY (`time`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `exogenous`
--

LOCK TABLES `exogenous` WRITE;
/*!40000 ALTER TABLE `exogenous` DISABLE KEYS */;
/*!40000 ALTER TABLE `exogenous` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `fix_config`
--

DROP TABLE IF EXISTS `fix_config`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `fix_config` (
  `id_fix_config` int(11) NOT NULL,
  `config` text NOT NULL,
  PRIMARY KEY (`id_fix_config`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `fix_config`
--

LOCK TABLES `fix_config` WRITE;
/*!40000 ALTER TABLE `fix_config` DISABLE KEYS */;
INSERT INTO `fix_config` VALUES (1,'[DEFAULT]\\nConnectionType=initiator\\nReconnectInterval=60\\nStartTime=00:00:00\\nEndTime=00:00:00\\nUseDataDictionary=Y\\nPersistMessages=Y\\nHeartBtInt=30\\nDataDictionary=../spec/FIX42.xml\\nMySQLStoreDatabase=quickfix\\nMySQLStoreUser=quickfix\\nMySQLStorePassword=quickfix\\nMySQLStoreHost=localhost\\nMySQLStorePort=3306\\nResetOnLogon=Y\\n[SESSION]\\nBeginString=FIX.4.2\\nSenderCompID=#USER#\\nTargetCompID=ORDERMATCH\\nSocketConnectHost=127.0.0.1\\nSocketConnectPort=5002'),(2,'[DEFAULT]\\nConnectionType=acceptor\\nSocketAcceptPort=5002\\nSocketReuseAddress=Y\\nStartTime=00:00:00\\nEndTime=00:00:00\\nDataDictionary=../spec/FIX42.xml\\nPersistMessages=Y\\nHeartBtInt=30\\nMySQLStoreDatabase=quickfix\\nMySQLStoreUser=quickfix\\nMySQLStorePassword=quickfix\\nMySQLStoreHost=localhost\\nMySQLStorePort=3306\\nResetOnLogon=Y');
/*!40000 ALTER TABLE `fix_config` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `messages`
--

DROP TABLE IF EXISTS `messages`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `messages` (
  `beginstring` char(8) NOT NULL,
  `sendercompid` varchar(64) NOT NULL,
  `targetcompid` varchar(64) NOT NULL,
  `session_qualifier` varchar(64) NOT NULL,
  `msgseqnum` int(11) NOT NULL,
  `message` blob NOT NULL,
  PRIMARY KEY (`beginstring`,`sendercompid`,`targetcompid`,`session_qualifier`,`msgseqnum`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `messages`
--

LOCK TABLES `messages` WRITE;
/*!40000 ALTER TABLE `messages` DISABLE KEYS */;
/*!40000 ALTER TABLE `messages` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `portfolio`
--

DROP TABLE IF EXISTS `portfolio`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `portfolio` (
  `id_agent` varchar(64) NOT NULL,
  `number_stock` float NOT NULL DEFAULT '0',
  `cash` float NOT NULL DEFAULT '0',
  `number_exogenous` float DEFAULT NULL,
  `time` datetime NOT NULL,
  PRIMARY KEY (`id_agent`,`time`),
  KEY `if_agent_fk_idx` (`id_agent`),
  CONSTRAINT `if_agent_fk` FOREIGN KEY (`id_agent`) REFERENCES `agents` (`id_agent`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `portfolio`
--

LOCK TABLES `portfolio` WRITE;
/*!40000 ALTER TABLE `portfolio` DISABLE KEYS */;
/*!40000 ALTER TABLE `portfolio` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `prices`
--

DROP TABLE IF EXISTS `prices`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `prices` (
  `time` datetime NOT NULL DEFAULT '0000-00-00 00:00:00',
  `price` float DEFAULT NULL,
  `volume` float DEFAULT NULL,
  PRIMARY KEY (`time`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `prices`
--

LOCK TABLES `prices` WRITE;
/*!40000 ALTER TABLE `prices` DISABLE KEYS */;
/*!40000 ALTER TABLE `prices` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `sessions`
--

DROP TABLE IF EXISTS `sessions`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `sessions` (
  `beginstring` char(8) NOT NULL,
  `sendercompid` varchar(64) NOT NULL,
  `targetcompid` varchar(64) NOT NULL,
  `session_qualifier` varchar(64) NOT NULL,
  `creation_time` datetime NOT NULL,
  `incoming_seqnum` int(11) NOT NULL,
  `outgoing_seqnum` int(11) NOT NULL,
  PRIMARY KEY (`beginstring`,`sendercompid`,`targetcompid`,`session_qualifier`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `sessions`
--

LOCK TABLES `sessions` WRITE;
/*!40000 ALTER TABLE `sessions` DISABLE KEYS */;
/*!40000 ALTER TABLE `sessions` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `strategy`
--

DROP TABLE IF EXISTS `strategy`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `strategy` (
  `id_strategy` int(11) NOT NULL,
  `ticker` varchar(32) NOT NULL DEFAULT 'FGV',
  `reference_stock_price` float NOT NULL DEFAULT '100',
  `cash` float NOT NULL,
  `number_stock` float NOT NULL,
  `percentual_max_neg` float DEFAULT NULL,
  `cycle_time` float NOT NULL DEFAULT '3',
  `initial_time` float NOT NULL DEFAULT '1',
  `reference_exogenous` float DEFAULT NULL,
  `reference_cov` varchar(45) DEFAULT NULL,
  PRIMARY KEY (`id_strategy`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `strategy`
--

LOCK TABLES `strategy` WRITE;
/*!40000 ALTER TABLE `strategy` DISABLE KEYS */;
INSERT INTO `strategy` VALUES (0,'',100,0,0,0,0,0,NULL,NULL),(1,'FGV',100,10000,100,1,6,4,NULL,NULL),(2,'FGV',100,10000,100,1,5,5,NULL,NULL),(3,'FGV',100,10000,100,1,7,3,NULL,NULL),(4,'FGV',100,10000,100,1,6,4,NULL,NULL),(5,'FGV',100,10000,100,1,5,5,NULL,NULL),(6,'FGV',100,10000,100,1,7,3,NULL,NULL),(7,'FGV',100,10000,100,1,5,4,NULL,NULL),(8,'FGV',100,10000,100,1,6,5,NULL,NULL),(9,'FGV',100,10000,100,1,7,3,NULL,NULL),(10,'FGV',100,10000,100,1,6,4,NULL,NULL),(11,'FGV',100,10000,100,1,5,5,NULL,NULL),(12,'FGV',100,10000,100,1,7,3,NULL,NULL),(13,'FGV',100,10000,100,1,6,4,NULL,NULL),(14,'FGV',100,10000,100,1,5,5,NULL,NULL),(15,'FGV',100,10000,100,1,7,3,NULL,NULL),(16,'FGV',100,1000000,10000,1,7,3,100,'-1.0'),(17,'FGV',100,10000,100,1,5,5,0,''),(18,'FGV',100,10000,100,1,7,3,0,''),(19,'FGV',100,10000,100,1,6,4,0,''),(20,'FGV',100,10000,100,1,5,5,NULL,NULL),(21,'FGV',100,10000,100,1,7,3,0,NULL),(22,'FGV',100,10000,100,1,6,4,0,''),(23,'FGV',100,10000,100,1,9,2,0,''),(24,'FGV',100,10000,100,0.5,7,3,0,'0'),(25,'FGV',100,1000000,10000,0.2,5,1,0,'0');
/*!40000 ALTER TABLE `strategy` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2013-03-29 20:42:08
