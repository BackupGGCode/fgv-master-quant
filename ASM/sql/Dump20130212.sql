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
INSERT INTO `agents` VALUES ('RANDTRADER01','active','random',1,1),('RANDTRADER02','active','random',1,2),('RANDTRADER03','active','random',1,3),('RANDTRADER04','active','random',1,4),('RANDTRADER05','active','random',1,5),('RANDTRADER06','active','random',1,6),('RANDTRADER07','active','random',1,7),('RANDTRADER08','active','random',1,8),('RANDTRADER09','active','random',1,9),('RANDTRADER10','active','random',1,10),('RANDTRADER11','active','random',1,11),('RANDTRADER12','active','random',1,12),('RANDTRADER13','active','random',1,13),('RANDTRADER14','active','random',1,14),('RANDTRADER15','active','random',1,15);
/*!40000 ALTER TABLE `agents` ENABLE KEYS */;
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
INSERT INTO `fix_config` VALUES (1,'[DEFAULT]\\nConnectionType=initiator\\nReconnectInterval=60\\nStartTime=00:00:00\\nEndTime=00:00:00\\nUseDataDictionary=Y\\nPersistMessages=Y\\nHeartBtInt=30\\nDataDictionary=../spec/FIX42.xml\\nMySQLStoreDatabase=quickfix\\nMySQLStoreUser=quickfix\\nMySQLStorePassword=quickfix\\nMySQLStoreHost=localhost\\nMySQLStorePort=3306\\nResetOnLogon=Y\\n[SESSION]\\nBeginString=FIX.4.2\\nSenderCompID=#USER#\\nTargetCompID=ORDERMATCH\\nSocketConnectHost=127.0.0.1\\nSocketConnectPort=5002');
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
  PRIMARY KEY (`id_agent`),
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
INSERT INTO `sessions` VALUES ('FIX.4.2','ORDERMATCH','BULLTRADER01','','2013-02-12 02:03:42',1,1),('FIX.4.2','ORDERMATCH','CLIENT1','','2013-02-12 21:49:16',15,25),('FIX.4.2','ORDERMATCH','CLIENT2','','2013-02-12 21:49:16',13,13),('FIX.4.2','ORDERMATCH','CLIENT3','','2013-02-12 02:03:42',1,1),('FIX.4.2','ORDERMATCH','FEEDER','','2013-02-12 02:03:42',1,1),('FIX.4.2','ORDERMATCH','RANDOMTRADER01','','2013-02-12 21:17:46',334,369),('FIX.4.2','ORDERMATCH','RANDOMTRADER02','','2013-02-12 21:17:47',19,19),('FIX.4.2','ORDERMATCH','RANDOMTRADER03','','2013-02-12 21:17:49',34,42),('FIX.4.2','ORDERMATCH','RANDOMTRADER04','','2013-02-12 21:17:46',19,19),('FIX.4.2','ORDERMATCH','RANDOMTRADER05','','2013-02-12 21:17:48',319,344),('FIX.4.2','ORDERMATCH','RANDOMTRADER06','','2013-02-12 21:17:47',29,33),('FIX.4.2','ORDERMATCH','RANDOMTRADER07','','2013-02-12 21:17:47',340,367),('FIX.4.2','ORDERMATCH','RANDOMTRADER08','','2013-02-12 21:17:48',21,22),('FIX.4.2','ORDERMATCH','RANDOMTRADER09','','2013-02-12 21:17:48',63,69),('FIX.4.2','ORDERMATCH','RANDOMTRADER10','','2013-02-12 21:17:47',19,20),('FIX.4.2','ORDERMATCH','RANDOMTRADER11','','2013-02-12 02:07:12',4,4),('FIX.4.2','ORDERMATCH','RANDOMTRADER12','','2013-02-12 02:03:44',1,1),('FIX.4.2','ORDERMATCH','RANDOMTRADER13','','2013-02-12 02:03:44',1,1),('FIX.4.2','ORDERMATCH','RANDOMTRADER14','','2013-02-12 02:03:44',1,1),('FIX.4.2','ORDERMATCH','RANDOMTRADER15','','2013-02-12 02:03:44',1,1),('FIX.4.2','ORDERMATCH','RANDOMTRADER16','','2013-02-12 02:03:44',1,1),('FIX.4.2','ORDERMATCH','RANDOMTRADER17','','2013-02-12 02:03:44',1,1),('FIX.4.2','ORDERMATCH','RANDOMTRADER18','','2013-02-12 02:03:45',1,1),('FIX.4.2','ORDERMATCH','RANDOMTRADER19','','2013-02-12 02:03:45',1,1),('FIX.4.2','ORDERMATCH','RANDOMTRADER20','','2013-02-12 02:03:45',1,1),('FIX.4.2','ORDERMATCH','RANDTRADER01','','2013-02-12 21:42:53',40,48),('FIX.4.2','ORDERMATCH','RANDTRADER02','','2013-02-12 21:42:54',41,44),('FIX.4.2','ORDERMATCH','RANDTRADER03','','2013-02-12 21:42:52',384,417),('FIX.4.2','ORDERMATCH','RANDTRADER04','','2013-02-12 21:42:52',31,31),('FIX.4.2','ORDERMATCH','RANDTRADER05','','2013-02-12 21:42:54',153,164),('FIX.4.2','ORDERMATCH','RANDTRADER06','','2013-02-12 21:42:52',55,59),('FIX.4.2','ORDERMATCH','RANDTRADER07','','2013-02-12 21:42:53',59,62),('FIX.4.2','ORDERMATCH','RANDTRADER08','','2013-02-12 21:42:53',165,188),('FIX.4.2','ORDERMATCH','RANDTRADER09','','2013-02-12 21:42:54',116,130),('FIX.4.2','ORDERMATCH','RANDTRADER10','','2013-02-12 21:42:54',48,56),('FIX.4.2','ORDERMATCH','RANDTRADER11','','2013-02-12 21:42:52',289,315),('FIX.4.2','ORDERMATCH','RANDTRADER12','','2013-02-12 21:42:53',54,56),('FIX.4.2','ORDERMATCH','RANDTRADER13','','2013-02-12 21:42:52',120,133),('FIX.4.2','ORDERMATCH','RANDTRADER14','','2013-02-12 21:42:53',407,446),('FIX.4.2','ORDERMATCH','RANDTRADER15','','2013-02-12 21:42:51',201,223),('FIX.4.2','ORDERMATCH','RANDTRADER16','','2013-02-12 21:36:45',1,1),('FIX.4.2','ORDERMATCH','RANDTRADER17','','2013-02-12 21:36:45',1,1),('FIX.4.2','ORDERMATCH','RANDTRADER18','','2013-02-12 21:36:45',1,1),('FIX.4.2','ORDERMATCH','RANDTRADER19','','2013-02-12 21:36:45',1,1),('FIX.4.2','ORDERMATCH','RANDTRADER20','','2013-02-12 21:36:45',1,1),('FIX.4.2','RANDOMTRADER01','ORDERMATCH','','2013-02-12 21:17:46',369,335),('FIX.4.2','RANDOMTRADER02','ORDERMATCH','','2013-02-12 21:17:46',19,19),('FIX.4.2','RANDOMTRADER03','ORDERMATCH','','2013-02-12 21:17:46',42,34),('FIX.4.2','RANDOMTRADER04','ORDERMATCH','','2013-02-12 21:17:46',19,19),('FIX.4.2','RANDOMTRADER05','ORDERMATCH','','2013-02-12 21:17:46',344,319),('FIX.4.2','RANDOMTRADER06','ORDERMATCH','','2013-02-12 21:17:46',33,29),('FIX.4.2','RANDOMTRADER07','ORDERMATCH','','2013-02-12 21:17:46',367,341),('FIX.4.2','RANDOMTRADER08','ORDERMATCH','','2013-02-12 21:17:46',22,21),('FIX.4.2','RANDOMTRADER09','ORDERMATCH','','2013-02-12 21:17:46',69,63),('FIX.4.2','RANDOMTRADER10','ORDERMATCH','','2013-02-12 21:17:46',20,19),('FIX.4.2','RANDOMTRADER11','ORDERMATCH','','2013-02-12 02:07:11',4,4),('FIX.4.2','RANDOMTRADER13','ORDERMATCH','','2013-02-11 19:44:29',7,8),('FIX.4.2','RANDOMTRADER14','ORDERMATCH','','2013-02-11 21:31:34',91,91),('FIX.4.2','RANDTRADER01','ORDERMATCH','','2013-02-12 21:54:34',48,40),('FIX.4.2','RANDTRADER02','ORDERMATCH','','2013-02-12 21:54:34',44,41),('FIX.4.2','RANDTRADER03','ORDERMATCH','','2013-02-12 21:54:34',417,384),('FIX.4.2','RANDTRADER04','ORDERMATCH','','2013-02-12 21:54:34',31,31),('FIX.4.2','RANDTRADER05','ORDERMATCH','','2013-02-12 21:54:34',164,153),('FIX.4.2','RANDTRADER06','ORDERMATCH','','2013-02-12 21:54:35',59,55),('FIX.4.2','RANDTRADER07','ORDERMATCH','','2013-02-12 21:54:34',62,59),('FIX.4.2','RANDTRADER08','ORDERMATCH','','2013-02-12 21:54:34',188,165),('FIX.4.2','RANDTRADER09','ORDERMATCH','','2013-02-12 21:54:34',130,116),('FIX.4.2','RANDTRADER10','ORDERMATCH','','2013-02-12 21:54:34',56,48),('FIX.4.2','RANDTRADER11','ORDERMATCH','','2013-02-12 21:54:34',315,289),('FIX.4.2','RANDTRADER12','ORDERMATCH','','2013-02-12 21:54:34',56,54),('FIX.4.2','RANDTRADER13','ORDERMATCH','','2013-02-12 21:54:34',133,120),('FIX.4.2','RANDTRADER14','ORDERMATCH','','2013-02-12 21:54:34',446,408),('FIX.4.2','RANDTRADER15','ORDERMATCH','','2013-02-12 21:54:34',223,201);
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
  `ticker` varchar(32) NOT NULL,
  `reference_stock_price` float NOT NULL,
  `cash` float NOT NULL,
  `number_stock` float NOT NULL,
  `percentual_max_neg` float NOT NULL,
  `cycle_time` float NOT NULL,
  `initial_time` float NOT NULL,
  PRIMARY KEY (`id_strategy`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `strategy`
--

LOCK TABLES `strategy` WRITE;
/*!40000 ALTER TABLE `strategy` DISABLE KEYS */;
INSERT INTO `strategy` VALUES (1,'FGV',100,10000,0,0.5,3,1),(2,'FGV',100,10000,0,0.2,3,1),(3,'FGV',100,10000,0,0.2,3,1),(4,'FGV',100,10000,0,0.4,3,1),(5,'FGV',100,10000,0,0.5,3,1),(6,'FGV',100,10000,100,0.5,3,1),(7,'FGV',100,10000,100,0.3,3,1),(8,'FGV',100,0,100,0.4,3,1),(9,'FGV',100,0,100,0.1,3,1),(10,'FGV',100,0,100,0.7,3,1),(11,'FGV',100,0,100,0.7,3,1),(12,'FGV',100,0,100,0.7,3,1),(13,'FGV',100,0,100,0.7,3,1),(14,'FGV',100,0,100,0.7,3,1),(15,'FGV',100,0,100,0.7,3,1);
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

-- Dump completed on 2013-02-12 20:45:00
