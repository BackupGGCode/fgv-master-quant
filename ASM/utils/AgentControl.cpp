/*
 * AgentControl.cpp
 *
 *  Created on: Feb 11, 2013
 *      Author: msaito
 */

#include "AgentControl.h"

AgentControl::AgentControl() {

}
AgentControl::AgentControl(std::string _agentID){
	this->agentID = _agentID;
}
std::string AgentControl::getFixConfiguration(){

	size_t row;
	std::stringstream sql;
	std::stringstream msg;
	std::string config_str;

	const std::string host = HOST;

	try {
		sql::Driver * driver = sql::mysql::get_driver_instance();
		std::auto_ptr< sql::Connection > con(driver->connect(host, USER, PASS));
		std::auto_ptr< sql::Statement > stmt(con->createStatement());

		std::string statement;
		statement = "SELECT config  FROM quickfix.agents a INNER JOIN quickfix.fix_config f ON a.id_fix_config = f.id_fix_config WHERE id_agent='#USER#'";
		std::string user("#USER#");
		statement.replace(statement.find(user),user.length(), this->agentID );

		std::auto_ptr< sql::ResultSet > res(stmt->executeQuery(statement));
		row = 0;
		while (res->next()) {
			config_str = res->getString("config");
			row++;
		}
		boost::replace_all(config_str, "#USER#", this->agentID);
		boost::replace_all(config_str, "\\n", "\n");


		/* Clean up */
		stmt.reset(NULL); /* free the object inside  */

		try {
			/*s This will implicitly assume that the host is 'localhost' */
			con.reset(driver->connect(host, USER, PASS));
		} catch (sql::SQLException &e) {
			std::cout << "#\t\t " << e.what() << " (MySQL error code: " << e.getErrorCode();
			std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
		}

		try {
			con.reset(driver->connect(host, USER, PASS));
		} catch (sql::SQLException &e) {
			std::cout << "#\t\t " << e.what() << " (MySQL error code: " << e.getErrorCode();
			std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
		}

		try {
			con.reset(driver->connect(host, USER, PASS));
		} catch (sql::SQLException &e) {
			std::cout <<"AgentControl::getFixConfiguration\n" << "#\t\t tcp://hostname_or_ip[:port] caused expected exception" << std::endl;
			std::cout << "#\t\t " << e.what() << " (MySQL error code: " << e.getErrorCode();
			std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
		}


	} catch (sql::SQLException &e) {
		std::cout <<"AgentControl::getFixConfiguration\n" << "# ERR: SQLException in " << __FILE__;
		std::cout << "# ERR: " << e.what();
		std::cout << " (MySQL error code: " << e.getErrorCode();
		std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;

	} catch (std::runtime_error &e) {

		std::cout <<"AgentControl::getFixConfiguration\n" << "# ERR: runtime_error in " << __FILE__;
		std::cout << "# ERR: " << e.what() << std::endl;

	}

	  return config_str;
}


std::string AgentControl::getSessionConfiguration(){

	size_t row;
	std::stringstream sql;
	std::stringstream msg;
	std::string config_str;

	const std::string host = HOST;

	try {
		sql::Driver * driver = sql::mysql::get_driver_instance();
		std::auto_ptr< sql::Connection > con(driver->connect(host, USER, PASS));
		std::auto_ptr< sql::Statement > stmt(con->createStatement());

		std::string statement;
		statement = "SELECT id_agent FROM quickfix.agents WHERE status='active' and id_strategy <> 0";

		std::auto_ptr< sql::ResultSet > res(stmt->executeQuery(statement));
		row = 0;
		while (res->next()) {
			config_str+="\n[SESSION]\nBeginString=FIX.4.2\nSenderCompID="+ this->agentID+"\nTargetCompID="+res->getString("id_agent")+"\n";
			row++;
		}

		//boost::replace_all(config_str, "\\n", "\n");

		/* Clean up */
		stmt.reset(NULL); /* free the object inside  */

		try {
			/*s This will implicitly assume that the host is 'localhost' */
			con.reset(driver->connect(host, USER, PASS));
		} catch (sql::SQLException &e) {
			std::cout << "#\t\t " << e.what() << " (MySQL error code: " << e.getErrorCode();
			std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
		}

		try {
			con.reset(driver->connect(host, USER, PASS));
		} catch (sql::SQLException &e) {
			std::cout <<"AgentControl::getSessionConfiguration\n" << "#\t\t " << e.what() << " (MySQL error code: " << e.getErrorCode();
			std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
		}

		try {
			con.reset(driver->connect(host, USER, PASS));
		} catch (sql::SQLException &e) {
			std::cout <<"AgentControl::getSessionConfiguration\n"<< "#\t\t tcp://hostname_or_ip[:port] caused expected exception" << std::endl;
			std::cout << "#\t\t " << e.what() << " (MySQL error code: " << e.getErrorCode();
			std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
		}


	} catch (sql::SQLException &e) {
		std::cout <<"AgentControl::getSessionConfiguration\n"<< "# ERR: SQLException in " << __FILE__;
		std::cout << "# ERR: " << e.what();
		std::cout << " (MySQL error code: " << e.getErrorCode();
		std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;

	} catch (std::runtime_error &e) {

		std::cout <<"AgentControl::getSessionConfiguration\n"<< "# ERR: runtime_error in " << __FILE__;
		std::cout << "# ERR: " << e.what() << std::endl;

	}

	  return config_str;
}



float AgentControl::getRate(std::string time){

	float rate = 0;
	std::string datetime;

	const std::string host = HOST;

	try {
		sql::Driver * driver = sql::mysql::get_driver_instance();
		std::auto_ptr< sql::Connection > con(driver->connect(host, USER, PASS));
		std::auto_ptr< sql::Statement > stmt(con->createStatement());



	    std::string format = "%Y%m%d-%H:%M:%S";
	    boost::posix_time::ptime ptime;
	    boost::posix_time::time_input_facet facet(format, 1);
	    std::stringstream ss1(time);
	    ss1.imbue(std::locale(ss1.getloc(), &facet));
	    ss1 >> ptime;


		std::string statement;
		statement = "SELECT simulation_time, rate FROM quickfix.rates WHERE simulation_time <='#TIME#' ORDER BY simulation_time DESC LIMIT 1";
		std::string time_tag("#TIME#");
		statement.replace(statement.find(time_tag),time_tag.length(), boost::posix_time::to_iso_string(ptime));

		std::auto_ptr< sql::ResultSet > res(stmt->executeQuery(statement));


		while (res->next()) {
			rate = res->getDouble("rate");
			datetime = res->getString("simulation_time");
		}

		//std::cout << "[AgentControl::getRate]  rate:"<< rate << " time:"<< time << "   datetime:"<< datetime <<std::endl;

		/* Clean up */
		stmt.reset(NULL); /* free the object inside  */

		try {
			/*s This will implicitly assume that the host is 'localhost' */
			con.reset(driver->connect(host, USER, PASS));
		} catch (sql::SQLException &e) {
			std::cout << "#\t\t " << e.what() << " (MySQL error code: " << e.getErrorCode();
			std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
		}

		try {
			con.reset(driver->connect(host, USER, PASS));
		} catch (sql::SQLException &e) {
			std::cout << "#\t\t " << e.what() << " (MySQL error code: " << e.getErrorCode();
			std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
		}

		try {
			con.reset(driver->connect(host, USER, PASS));
		} catch (sql::SQLException &e) {
			std::cout << "#\t\t tcp://hostname_or_ip[:port] caused expected exception" << std::endl;
			std::cout << "#\t\t " << e.what() << " (MySQL error code: " << e.getErrorCode();
			std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
		}

	} catch (sql::SQLException &e) {
		std::cout << "# ERR: SQLException in " << __FILE__;
		std::cout << "# ERR: " << e.what();
		std::cout << " (MySQL error code: " << e.getErrorCode();
		std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;

	} catch (std::runtime_error &e) {

		std::cout << "# ERR: runtime_error in " << __FILE__;
		std::cout << "# ERR: " << e.what() << std::endl;

	}

	  return rate;
}


std::string AgentControl::getStrategyConfiguration(){

	size_t row;
	std::stringstream sql;
	std::stringstream msg;
	std::string ticker;
	float reference_stock_price;
	float cash;
	float  number_stock;
	float percentual_max_neg;
	float cycle_time;
	float initial_time;
	float reference_exogenous;
	float reference_cov;
	float volatility;
	float  spread;

	const std::string host = HOST;
	std::stringstream strategy_config;


	try {
		sql::Driver * driver = sql::mysql::get_driver_instance();
		std::auto_ptr< sql::Connection > con(driver->connect(host, USER, PASS));
		std::auto_ptr< sql::Statement > stmt(con->createStatement());

		std::string statement;
		statement = "SELECT ticker, reference_stock_price, cash, number_stock, percentual_max_neg, cycle_time, initial_time, reference_exogenous, reference_cov, volatility, spread  FROM quickfix.strategy s inner join quickfix.agents a on s.id_strategy = a.id_strategy where id_agent='#USER#'";
		std::string user("#USER#");
		statement.replace(statement.find(user),user.length(), this->agentID );

		std::auto_ptr< sql::ResultSet > res(stmt->executeQuery(statement));
		row = 0;
		while (res->next()) {
			ticker = res->getString("ticker");
			reference_stock_price = res->getDouble("reference_stock_price");
			cash = res->getDouble("cash");
			number_stock = res->getDouble("number_stock");
			percentual_max_neg = res->getDouble("percentual_max_neg");
			cycle_time = res->getDouble("cycle_time");
			initial_time = res->getDouble("initial_time");
			reference_exogenous = res->getDouble("reference_exogenous");
			reference_cov = res->getDouble("reference_cov");
			volatility = res->getDouble("volatility");
			spread = res->getDouble("spread");
			row++;
		}

		strategy_config << std::fixed;
		strategy_config.precision(2);

		strategy_config << "TICKER = \"" << ticker << "\";\nREFERENCE_STOCK_PRICE = "<<reference_stock_price
						<<";\nCASH = "<<cash<<";\nNUMBER_STOCK = "<<number_stock<<";\nPERCENTUAL_MAX_NEG = "
						<<percentual_max_neg<<";\nCYCLE_TIME = "<<cycle_time
						<<";\nINITIAL_TIME = "<<initial_time
						<<";\nREFERENCE_EXOGENOUS = "<<reference_exogenous
						<<";\nREFERENCE_COV = "<<reference_cov
						<<";\nVOLATILITY = "<<volatility
						<<";\nSPREAD = "<< spread <<";";

		/* Clean up */
		stmt.reset(NULL); /* free the object inside  */

		try {
			/*s This will implicitly assume that the host is 'localhost' */
			con.reset(driver->connect(host, USER, PASS));
		} catch (sql::SQLException &e) {
			std::cout << "#\t\t " << e.what() << " (MySQL error code: " << e.getErrorCode();
			std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
		}

		try {
			con.reset(driver->connect(host, USER, PASS));
		} catch (sql::SQLException &e) {
			std::cout << "#\t\t " << e.what() << " (MySQL error code: " << e.getErrorCode();
			std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
		}

		try {
			con.reset(driver->connect(host, USER, PASS));
		} catch (sql::SQLException &e) {
			std::cout << "#\t\t tcp://hostname_or_ip[:port] caused expected exception" << std::endl;
			std::cout << "#\t\t " << e.what() << " (MySQL error code: " << e.getErrorCode();
			std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
		}


	} catch (sql::SQLException &e) {
		std::cout << "# ERR: SQLException in " << __FILE__;
		std::cout << "# ERR: " << e.what();
		std::cout << " (MySQL error code: " << e.getErrorCode();
		std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;

	} catch (std::runtime_error &e) {

		std::cout << "# ERR: runtime_error in " << __FILE__;
		std::cout << "# ERR: " << e.what() << std::endl;

	}

	  return strategy_config.str();
}




void AgentControl::setPortfolio(std::string time, float cash, float  number_stock, float  number_exogenous){

	std::stringstream insert;
	std::stringstream update;
	std::stringstream replace;
	std::stringstream msg;
	int affected_rows = 0;

	const std::string host = HOST;

	try {
		sql::Driver * driver = sql::mysql::get_driver_instance();
		std::auto_ptr< sql::Connection > con(driver->connect(host, USER, PASS));
		std::auto_ptr< sql::Statement > stmt(con->createStatement());


	    std::string format = "%Y%m%d-%H:%M:%S";
	    boost::posix_time::ptime ptime;
	    boost::posix_time::time_input_facet facet(format, 1);
	    std::stringstream ss1(time);
	    ss1.imbue(std::locale(ss1.getloc(), &facet));
	    ss1 >> ptime;



		/* Usage of UPDATE */

		replace << "REPLACE INTO quickfix.portfolio (time, id_agent, number_stock, cash, number_exogenous) VALUES ('"<< boost::posix_time::to_iso_string(ptime) <<"','"<< this->agentID <<"',"<< number_stock << ","<< cash << ","<< number_exogenous <<")";
		//std::cout << replace.str();
		affected_rows = stmt->execute(replace.str());
/*
		update << "UPDATE quickfix.portfolio SET number_stock =" <<number_stock<<", cash="<< cash <<" WHERE id_agent = '"<< this->agentID << "'";
		affected_rows = stmt->executeUpdate(update.str());
		if (affected_rows != 1) {
			insert << "INSERT INTO quickfix.portfolio (id_agent, number_stock, cash) VALUES ('"<< this->agentID <<"',"<< number_stock << ","<< cash <<")";
			stmt->execute(insert.str());
		}
*/
		/* Clean up */
		stmt.reset(NULL); /* free the object inside  */

		try {
			/*s This will implicitly assume that the host is 'localhost' */
			con.reset(driver->connect(host, USER, PASS));
		} catch (sql::SQLException &e) {
			std::cout << "#\t\t " << e.what() << " (MySQL error code: " << e.getErrorCode();
			std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
		}

		try {
			con.reset(driver->connect(host, USER, PASS));
		} catch (sql::SQLException &e) {
			std::cout << "#\t\t " << e.what() << " (MySQL error code: " << e.getErrorCode();
			std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
		}

		try {
			con.reset(driver->connect(host, USER, PASS));
		} catch (sql::SQLException &e) {
			std::cout << "#\t\t tcp://hostname_or_ip[:port] caused expected exception" << std::endl;
			std::cout << "#\t\t " << e.what() << " (MySQL error code: " << e.getErrorCode();
			std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
		}

	} catch (sql::SQLException &e) {
		std::cout << "# ERR: SQLException in " << __FILE__;
		/* Use what() (derived from std::runtime_error) to fetch the error message */
		std::cout << "# ERR: " << e.what();
		std::cout << " (MySQL error code: " << e.getErrorCode();
		std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
		std::cout << "not ok 1 - examples/connect.php" << std::endl;

	} catch (std::runtime_error &e) {

		std::cout << "# ERR: runtime_error in " << __FILE__;
		std::cout << "# ERR: " << e.what() << std::endl;
		std::cout << "not ok 1 - examples/connect.php" << std::endl;

	}

}





void AgentControl::updateExogenousTimes(std::string start_time){

	std::stringstream insert;

	std::stringstream select;
	std::stringstream msg;
	int rows = 0;

	const std::string host = HOST;

	try {
		sql::Driver * driver = sql::mysql::get_driver_instance();
		std::auto_ptr< sql::Connection > con(driver->connect(host, USER, PASS));
		std::auto_ptr< sql::Statement > stmt(con->createStatement());

	    std::string format = "%Y%m%d-%H:%M:%S";
	    boost::posix_time::ptime time;
	    boost::posix_time::time_input_facet facet(format, 1);
	    std::stringstream ss1(start_time);
	    ss1.imbue(std::locale(ss1.getloc(), &facet));
	    ss1 >> time;



	    //std::cout << "Time: " << boost::posix_time::to_iso_string(time) << std::endl;


	    //TARGET:: 0000-00-00 00:00:00
	    //TERMINAL :: 20130217-15:20:55

	    select << "SELECT time FROM quickfix.exogenous";



		rows = 0;
		std::auto_ptr< sql::ResultSet > res(stmt->executeQuery(select.str()));

		std::stringstream update;
		update << "INSERT INTO quickfix.exogenous (simulation_time, time) VALUES ";

		while (res->next()) {

			std::string format_sql = "%H:%M:%S";
			boost::posix_time::time_duration time_sql;
			boost::posix_time::time_input_facet facet_sql(format_sql, 1);
			std::stringstream ss_sql(res->getString("time"));
			ss_sql.imbue(std::locale(ss_sql.getloc(), &facet_sql));
			ss_sql >> time_sql;
		    update << "('" <<boost::posix_time::to_iso_string(time+time_sql) <<"','"<< res->getString("time")<< "'), ";

			rows++;
		}
		update << "ON DUPLICATE KEY UPDATE simulation_time=VALUES(simulation_time),time=VALUES(time)";

		std::string update_str = update.str();

		std::string remove_last_comma("), ON");
		update_str.replace(update_str.find(remove_last_comma),remove_last_comma.length(), ") ON");

	    stmt->executeUpdate(update_str);

		stmt.reset(NULL); /* free the object inside  */

		try {
			/*s This will implicitly assume that the host is 'localhost' */
			con.reset(driver->connect(host, USER, PASS));
		} catch (sql::SQLException &e) {
			std::cout << "#\t\t " << e.what() << " (MySQL error code: " << e.getErrorCode();
			std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
		}

		try {
			con.reset(driver->connect(host, USER, PASS));
		} catch (sql::SQLException &e) {
			std::cout << "#\t\t " << e.what() << " (MySQL error code: " << e.getErrorCode();
			std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
		}

		try {
			con.reset(driver->connect(host, USER, PASS));
		} catch (sql::SQLException &e) {
			std::cout << "#\t\t tcp://hostname_or_ip[:port] caused expected exception" << std::endl;
			std::cout << "#\t\t " << e.what() << " (MySQL error code: " << e.getErrorCode();
			std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
		}

	} catch (sql::SQLException &e) {
		std::cout << "# ERR: SQLException in " << __FILE__;
		/* Use what() (derived from std::runtime_error) to fetch the error message */
		std::cout << "# ERR: " << e.what();
		std::cout << " (MySQL error code: " << e.getErrorCode();
		std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
		std::cout << "not ok 1 - examples/connect.php" << std::endl;

	} catch (std::runtime_error &e) {

		std::cout << "# ERR: runtime_error in " << __FILE__;
		std::cout << "# ERR: " << e.what() << std::endl;
		std::cout << "not ok 1 - examples/connect.php" << std::endl;

	}

}


void AgentControl::updatePrices(std::string time, float price, float quantity){

	std::stringstream insert;
	int affected_rows = 0;

	const std::string host = HOST;

	try {
		sql::Driver * driver = sql::mysql::get_driver_instance();
		std::auto_ptr< sql::Connection > con(driver->connect(host, USER, PASS));
		std::auto_ptr< sql::Statement > stmt(con->createStatement());

	    std::string format = "%Y%m%d-%H:%M:%S";
	    boost::posix_time::ptime ptime;
	    boost::posix_time::time_input_facet facet(format, 1);
	    std::stringstream ss1(time);
	    ss1.imbue(std::locale(ss1.getloc(), &facet));
	    ss1 >> ptime;


		insert << "INSERT INTO quickfix.prices (time, volume, price) VALUES ('"<< boost::posix_time::to_iso_string(ptime) <<"',"<< quantity << ","<< price <<")";
		affected_rows = stmt->execute(insert.str());

		/* Clean up */
		stmt.reset(NULL); /* free the object inside  */

		try {
			/*s This will implicitly assume that the host is 'localhost' */
			con.reset(driver->connect(host, USER, PASS));
		} catch (sql::SQLException &e) {
			std::cout << "#\t\t " << e.what() << " (MySQL error code: " << e.getErrorCode();
			std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
		}

		try {
			con.reset(driver->connect(host, USER, PASS));
		} catch (sql::SQLException &e) {
			std::cout << "#\t\t " << e.what() << " (MySQL error code: " << e.getErrorCode();
			std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
		}

		try {
			con.reset(driver->connect(host, USER, PASS));
		} catch (sql::SQLException &e) {
			std::cout << "#\t\t tcp://hostname_or_ip[:port] caused expected exception" << std::endl;
			std::cout << "#\t\t " << e.what() << " (MySQL error code: " << e.getErrorCode();
			std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
		}

	} catch (sql::SQLException &e) {
		std::cout << "# ERR: SQLException in " << __FILE__;
		/* Use what() (derived from std::runtime_error) to fetch the error message */
		std::cout << "# ERR: " << e.what();
		std::cout << " (MySQL error code: " << e.getErrorCode();
		std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
		std::cout << "not ok 1 - examples/connect.php" << std::endl;

	} catch (std::runtime_error &e) {

		std::cout << "# ERR: runtime_error in " << __FILE__;
		std::cout << "# ERR: " << e.what() << std::endl;
		std::cout << "not ok 1 - examples/connect.php" << std::endl;

	}

}



void AgentControl::setupPorfolio(void){


	std::stringstream del;

	float price=0;
	const std::string host = HOST;

	try {
		sql::Driver * driver = sql::mysql::get_driver_instance();
		std::auto_ptr< sql::Connection > con(driver->connect(host, USER, PASS));
		std::auto_ptr< sql::Statement > stmt(con->createStatement());

	    del << "DELETE FROM quickfix.portfolio WHERE time <> ''";
		stmt->execute(del.str());

		/* Clean up */
		stmt.reset(NULL); /* free the object inside  */

		try {
			/*s This will implicitly assume that the host is 'localhost' */
			con.reset(driver->connect(host, USER, PASS));
		} catch (sql::SQLException &e) {
			std::cout << "#\t\t " << e.what() << " (MySQL error code: " << e.getErrorCode();
			std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
		}

		try {
			con.reset(driver->connect(host, USER, PASS));
		} catch (sql::SQLException &e) {
			std::cout << "#\t\t " << e.what() << " (MySQL error code: " << e.getErrorCode();
			std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
		}

		try {
			con.reset(driver->connect(host, USER, PASS));
		} catch (sql::SQLException &e) {
			std::cout << "#\t\t tcp://hostname_or_ip[:port] caused expected exception" << std::endl;
			std::cout << "#\t\t " << e.what() << " (MySQL error code: " << e.getErrorCode();
			std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
		}

	} catch (sql::SQLException &e) {
		std::cout << "# ERR: SQLException in " << __FILE__;
		/* Use what() (derived from std::runtime_error) to fetch the error message */
		std::cout << "# ERR: " << e.what();
		std::cout << " (MySQL error code: " << e.getErrorCode();
		std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
		std::cout << "not ok 1 - examples/connect.php" << std::endl;

	} catch (std::runtime_error &e) {

		std::cout << "# ERR: runtime_error in " << __FILE__;
		std::cout << "# ERR: " << e.what() << std::endl;
		std::cout << "not ok 1 - examples/connect.php" << std::endl;

	}

}



void AgentControl::setupPrices(std::string time){


	std::stringstream select;
	std::stringstream del;
	std::stringstream insert;

	float price=0;
	const std::string host = HOST;

	try {
		sql::Driver * driver = sql::mysql::get_driver_instance();
		std::auto_ptr< sql::Connection > con(driver->connect(host, USER, PASS));
		std::auto_ptr< sql::Statement > stmt(con->createStatement());

	    std::string format = "%Y%m%d-%H:%M:%S";
	    boost::posix_time::ptime ptime;
	    boost::posix_time::time_input_facet facet(format, 1);
	    std::stringstream ss1(time);
	    ss1.imbue(std::locale(ss1.getloc(), &facet));
	    ss1 >> ptime;


	    select << "SELECT reference_stock_price FROM quickfix.strategy s inner join quickfix.agents a on s.id_strategy = a.id_strategy where id_agent='"<< this->agentID<<"'";

		std::auto_ptr< sql::ResultSet > res(stmt->executeQuery(select.str()));
		while (res->next()) {
			price = res->getDouble("reference_stock_price");
		}

	    del << "DELETE FROM quickfix.prices WHERE time <> ''";
		stmt->execute(del.str());

		insert << "INSERT INTO quickfix.prices (time, volume, price) VALUES ('"<< boost::posix_time::to_iso_string(ptime) <<"',0,"<< price <<")";
		stmt->execute(insert.str());

		/* Clean up */
		stmt.reset(NULL); /* free the object inside  */

		try {
			/*s This will implicitly assume that the host is 'localhost' */
			con.reset(driver->connect(host, USER, PASS));
		} catch (sql::SQLException &e) {
			std::cout << "#\t\t " << e.what() << " (MySQL error code: " << e.getErrorCode();
			std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
		}

		try {
			con.reset(driver->connect(host, USER, PASS));
		} catch (sql::SQLException &e) {
			std::cout << "#\t\t " << e.what() << " (MySQL error code: " << e.getErrorCode();
			std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
		}

		try {
			con.reset(driver->connect(host, USER, PASS));
		} catch (sql::SQLException &e) {
			std::cout << "#\t\t tcp://hostname_or_ip[:port] caused expected exception" << std::endl;
			std::cout << "#\t\t " << e.what() << " (MySQL error code: " << e.getErrorCode();
			std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
		}

	} catch (sql::SQLException &e) {
		std::cout << "# ERR: SQLException in " << __FILE__;
		/* Use what() (derived from std::runtime_error) to fetch the error message */
		std::cout << "# ERR: " << e.what();
		std::cout << " (MySQL error code: " << e.getErrorCode();
		std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
		std::cout << "not ok 1 - examples/connect.php" << std::endl;

	} catch (std::runtime_error &e) {

		std::cout << "# ERR: runtime_error in " << __FILE__;
		std::cout << "# ERR: " << e.what() << std::endl;
		std::cout << "not ok 1 - examples/connect.php" << std::endl;

	}

}



float AgentControl::getLastPrice(void){


	std::stringstream select;
	float price = 0;
	const std::string host = HOST;

	try {
		sql::Driver * driver = sql::mysql::get_driver_instance();
		std::auto_ptr< sql::Connection > con(driver->connect(host, USER, PASS));
		std::auto_ptr< sql::Statement > stmt(con->createStatement());

		select << "SELECT p.price FROM quickfix.prices p ORDER BY p.time DESC LIMIT 1";

		std::auto_ptr< sql::ResultSet > res(stmt->executeQuery(select.str()));

		while (res->next()) {
			price = res->getDouble("price");
		}

		std::cout << std::endl << "[AgentControl::getLastPrice] :"<< price << std::endl;

		/* Clean up */
		stmt.reset(NULL); /* free the object inside  */

		try {
			/*s This will implicitly assume that the host is 'localhost' */
			con.reset(driver->connect(host, USER, PASS));
		} catch (sql::SQLException &e) {
			std::cout << "#\t\t " << e.what() << " (MySQL error code: " << e.getErrorCode();
			std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
		}

		try {
			con.reset(driver->connect(host, USER, PASS));
		} catch (sql::SQLException &e) {
			std::cout << "#\t\t " << e.what() << " (MySQL error code: " << e.getErrorCode();
			std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
		}

		try {
			con.reset(driver->connect(host, USER, PASS));
		} catch (sql::SQLException &e) {
			std::cout << "#\t\t tcp://hostname_or_ip[:port] caused expected exception" << std::endl;
			std::cout << "#\t\t " << e.what() << " (MySQL error code: " << e.getErrorCode();
			std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
		}

	} catch (sql::SQLException &e) {
		std::cout << "# ERR: SQLException in " << __FILE__;
		std::cout << "# ERR: " << e.what();
		std::cout << " (MySQL error code: " << e.getErrorCode();
		std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;

	} catch (std::runtime_error &e) {

		std::cout << "# ERR: runtime_error in " << __FILE__;
		std::cout << "# ERR: " << e.what() << std::endl;

	}

	return price;

}




float* AgentControl::getLastNPrices(int N, int& tam){

	size_t row;
	std::stringstream select;
	float* array;
	const std::string host = HOST;

	try {
		sql::Driver * driver = sql::mysql::get_driver_instance();
		std::auto_ptr< sql::Connection > con(driver->connect(host, USER, PASS));
		std::auto_ptr< sql::Statement > stmt(con->createStatement());


		//SELECT g.price FROM (SELECT p.time, p.price FROM prices p ORDER BY p.time DESC LIMIT 7) g ORDER BY g.time ASC
		select << "SELECT g.price FROM (SELECT p.time, p.price FROM quickfix.prices p ORDER BY p.time DESC LIMIT "<< N <<" ) g ORDER BY g.time ASC";
		//select << "SELECT p.price FROM quickfix.prices p ORDER BY p.time DESC LIMIT " << N;

		//std::cout << std::endl  << "[AgentControl::getLastNPrices] SQL:" << select.str() << std::endl;

		std::auto_ptr< sql::ResultSet > res(stmt->executeQuery(select.str()));

		int size = res->rowsCount();

		if(size > 0 ){
			array = new float[size];
			row = 0;
			while (res->next()) {
				array[row] = res->getDouble("price");
				row++;
			}
			tam=row;
			//std::cout << std::endl << "[AgentControl::getLastNPrices] tam:"<< tam <<" size:"<< size << std::endl;

		}

		/* Clean up */
		stmt.reset(NULL); /* free the object inside  */

		try {
			/*s This will implicitly assume that the host is 'localhost' */
			con.reset(driver->connect(host, USER, PASS));
		} catch (sql::SQLException &e) {
			std::cout <<"AgentControl::getLastNPrices\n"<< "#\t\t " << e.what() << " (MySQL error code: " << e.getErrorCode();
			std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
		}

		try {
			con.reset(driver->connect(host, USER, PASS));
		} catch (sql::SQLException &e) {
			std::cout <<"AgentControl::getLastNPrices\n"<< "#\t\t " << e.what() << " (MySQL error code: " << e.getErrorCode();
			std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
		}

		try {
			con.reset(driver->connect(host, USER, PASS));
		} catch (sql::SQLException &e) {
			std::cout <<"AgentControl::getLastNPrices\n" << "#\t\t tcp://hostname_or_ip[:port] caused expected exception" << std::endl;
			std::cout << "#\t\t " << e.what() << " (MySQL error code: " << e.getErrorCode();
			std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
		}

		 return array;

	} catch (sql::SQLException &e) {
		std::cout << "# ERR: SQLException in " << __FILE__;
		std::cout << "# ERR: " << e.what();
		std::cout << " (MySQL error code: " << e.getErrorCode();
		std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;

	} catch (std::runtime_error &e) {

		std::cout << "# ERR: runtime_error in " << __FILE__;
		std::cout << "# ERR: " << e.what() << std::endl;

	}



}




float* AgentControl::getPrices(std::string time1, std::string time2, int& tam){

	size_t row;
	std::stringstream select;
	float* array;
	const std::string host = HOST;

	try {
		sql::Driver * driver = sql::mysql::get_driver_instance();
		std::auto_ptr< sql::Connection > con(driver->connect(host, USER, PASS));
		std::auto_ptr< sql::Statement > stmt(con->createStatement());


	    std::string format = "%Y%m%d-%H:%M:%S";
	    boost::posix_time::time_input_facet facet(format, 1);

	    boost::posix_time::ptime ptime1;
	    std::stringstream ss1(time1);
	    ss1.imbue(std::locale(ss1.getloc(), &facet));
	    ss1 >> ptime1;

	    boost::posix_time::ptime ptime2;
	    std::stringstream ss2(time2);
	    ss2.imbue(std::locale(ss2.getloc(), &facet));
	    ss2 >> ptime2;

		select << "SELECT price FROM quickfix.prices WHERE time >= '"<< boost::posix_time::to_iso_string(ptime1) <<"' AND time<='"<<boost::posix_time::to_iso_string(ptime2)<<"'";
		//std::cout << std::endl << select.str() << std::endl;
		std::auto_ptr< sql::ResultSet > res(stmt->executeQuery(select.str()));

		int size = res->rowsCount();

		if( size > 0 ){
			array = new float[size];
			row = 0;
			while (res->next()) {
				array[row] = res->getDouble("price");
				row++;
			}
			tam=row;
			//std::cout << std::endl << "[AgentControl::getPrices] tam:"<< tam <<" size:"<< size << std::endl;

		}else{
			std::stringstream select2;
			select2 << "SELECT price FROM quickfix.prices ORDER BY time DESC LIMIT 1";
			//std::cout << std::endl << select2.str() << std::endl;
			std::auto_ptr< sql::ResultSet > res2(stmt->executeQuery(select2.str()));
			size = res2->rowsCount();
			array = new float[size];
			row = 0;
			while (res2->next()) {
				array[row] = res2->getDouble("price");
				row++;
			}
			tam=row;
			//std::cout << std::endl << "[AgentControl::getPrices] tam:"<< tam <<" size:"<< size << std::endl;
		}
		/* Clean up */
		stmt.reset(NULL); /* free the object inside  */

		try {
			/*s This will implicitly assume that the host is 'localhost' */
			con.reset(driver->connect(host, USER, PASS));
		} catch (sql::SQLException &e) {
			std::cout <<"AgentControl::getPrices\n" <<"#\t\t " << e.what() << " (MySQL error code: " << e.getErrorCode();
			std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
		}

		try {
			con.reset(driver->connect(host, USER, PASS));
		} catch (sql::SQLException &e) {
			std::cout <<"AgentControl::getPrices\n"<< "#\t\t " << e.what() << " (MySQL error code: " << e.getErrorCode();
			std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
		}

		try {
			con.reset(driver->connect(host, USER, PASS));
		} catch (sql::SQLException &e) {
			std::cout <<"AgentControl::getPrices\n"<< "#\t\t tcp://hostname_or_ip[:port] caused expected exception" << std::endl;
			std::cout << "#\t\t " << e.what() << " (MySQL error code: " << e.getErrorCode();
			std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
		}



		 return array;

	} catch (sql::SQLException &e) {
		std::cout << "# ERR: SQLException in " << __FILE__;
		std::cout << "# ERR: " << e.what();
		std::cout << " (MySQL error code: " << e.getErrorCode();
		std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;

	} catch (std::runtime_error &e) {

		std::cout << "# ERR: runtime_error in " << __FILE__;
		std::cout << "# ERR: " << e.what() << std::endl;

	}



}


float* AgentControl::getExogenousValues(std::string time1, std::string time2, int& tam){

	size_t row;
	std::stringstream select;

	const std::string host = HOST;

	try {
		sql::Driver * driver = sql::mysql::get_driver_instance();
		std::auto_ptr< sql::Connection > con(driver->connect(host, USER, PASS));
		std::auto_ptr< sql::Statement > stmt(con->createStatement());


	    std::string format = "%Y%m%d-%H:%M:%S";
	    boost::posix_time::ptime ptime1;
	    boost::posix_time::time_input_facet facet(format, 1);
	    std::stringstream ss1(time1);
	    ss1.imbue(std::locale(ss1.getloc(), &facet));
	    ss1 >> ptime1;

	    boost::posix_time::ptime ptime2;
	    std::stringstream ss2(time2);
	    ss2.imbue(std::locale(ss2.getloc(), &facet));
	    ss2 >> ptime2;

		select << "SELECT value FROM quickfix.exogenous WHERE simulation_time >= '"<< boost::posix_time::to_iso_string(ptime1) <<"' AND simulation_time<='"<<boost::posix_time::to_iso_string(ptime2)<<"'";

		//std::cout << std::endl << select.str() << std::endl;

		std::auto_ptr< sql::ResultSet > res(stmt->executeQuery(select.str()));

		int size = res->rowsCount();

		float* array = new float[size];

		row = 0;
		while (res->next()) {
			array[row] = res->getDouble("value");
			row++;
		}

		tam=row;
		//std::cout << std::endl << "[AgentControl::getRates] tam:"<< tam <<" size:"<< size << std::endl;

		/* Clean up */
		stmt.reset(NULL); /* free the object inside  */

		try {
			/*s This will implicitly assume that the host is 'localhost' */
			con.reset(driver->connect(host, USER, PASS));
		} catch (sql::SQLException &e) {
			std::cout <<"AgentControl::getExogenousValues\n"<< "#\t\t " << e.what() << " (MySQL error code: " << e.getErrorCode();
			std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
		}

		try {
			con.reset(driver->connect(host, USER, PASS));
		} catch (sql::SQLException &e) {
			std::cout <<"AgentControl::getExogenousValues\n"<< "#\t\t " << e.what() << " (MySQL error code: " << e.getErrorCode();
			std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
		}

		try {
			con.reset(driver->connect(host, USER, PASS));
		} catch (sql::SQLException &e) {
			std::cout <<"AgentControl::getExogenousValues\n"<< "#\t\t tcp://hostname_or_ip[:port] caused expected exception" << std::endl;
			std::cout << "#\t\t " << e.what() << " (MySQL error code: " << e.getErrorCode();
			std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
		}



		 return array;

	} catch (sql::SQLException &e) {
		std::cout << "# ERR: SQLException in " << __FILE__;
		std::cout << "# ERR: " << e.what();
		std::cout << " (MySQL error code: " << e.getErrorCode();
		std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;

	} catch (std::runtime_error &e) {

		std::cout << "# ERR: runtime_error in " << __FILE__;
		std::cout << "# ERR: " << e.what() << std::endl;

	}


}




AgentControl::~AgentControl() {

}

int AgentControl::run(){
	/* sql::ResultSet.rowsCount() returns size_t */
	size_t row;
	std::stringstream sql;
	std::stringstream msg;
	int affected_rows;

	const std::string host = DB;

	try {
		sql::Driver * driver = sql::mysql::get_driver_instance();
		/* Using the Driver to create a connection */
		std::auto_ptr< sql::Connection > con(driver->connect(host, USER, PASS));

		/* Creating a "simple" statement - "simple" = not a prepared statement */
		std::auto_ptr< sql::Statement > stmt(con->createStatement());

		{
			/* Fetching again but using type convertion methods */
			std::auto_ptr< sql::ResultSet > res(stmt->executeQuery("SELECT id FROM test ORDER BY id DESC"));
			std::cout << "#\t Fetching 'SELECT id FROM test ORDER BY id DESC' using type conversion" << std::endl;
			row = 0;
			while (res->next()) {
				std::cout << "#\t\t Fetching row " << row;
				std::cout << "#\t id (int) = " << res->getInt("id");
				std::cout << "#\t id (boolean) = " << res->getBoolean("id");
				std::cout << "#\t id (long) = " << res->getInt64("id") << std::endl;
				row++;
			}
		}

		/* Usage of UPDATE */
		stmt->execute("INSERT INTO test(id, label) VALUES (100, 'z')");
		affected_rows = stmt->executeUpdate("UPDATE test SET label = 'y' WHERE id = 100");
		std::cout << "#\t UPDATE indicates " << affected_rows << " affected rows" << std::endl;
		if (affected_rows != 1) {
			msg.str("");
			msg << "Expecting one row to be changed, but " << affected_rows << "change(s) reported";
			throw std::runtime_error(msg.str());
		}

		{
			std::auto_ptr< sql::ResultSet > res(stmt->executeQuery("SELECT id, label FROM test WHERE id = 100"));

			res->next();
			if ((res->getInt("id") != 100) || (res->getString("label") != "y")) {
				msg.str("Update must have failed, expecting 100/y got");
				msg << res->getInt("id") << "/" << res->getString("label");
				throw std::runtime_error(msg.str());
			}

			std::cout << "#\t\t Expecting id = 100, label = 'y' and got id = " << res->getInt("id");
			std::cout << ", label = '" << res->getString("label") << "'" << std::endl;
		}

		/* Clean up */
		stmt.reset(NULL); /* free the object inside  */

		std::cout << "#" << std::endl;
		std::cout << "#\t Demo of connection host syntax" << std::endl;
		try {
			/*s This will implicitly assume that the host is 'localhost' */
			//host = "unix://path_to_mysql_socket.sock";
			con.reset(driver->connect(host, USER, PASS));
		} catch (sql::SQLException &e) {
			std::cout << "#\t\t unix://path_to_mysql_socket.sock caused expected exception" << std::endl;
			std::cout << "#\t\t " << e.what() << " (MySQL error code: " << e.getErrorCode();
			std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
		}

		try {
			//host = "tcp://hostname_or_ip[:port]";
			con.reset(driver->connect(host, USER, PASS));
		} catch (sql::SQLException &e) {
			std::cout << "#\t\t tcp://hostname_or_ip[:port] caused expected exception" << std::endl;
			std::cout << "#\t\t " << e.what() << " (MySQL error code: " << e.getErrorCode();
			std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
		}

		try {
			/*
			Note: in the MySQL C-API host = localhost would cause a socket connection!
			Not so with the C++ Connector. The C++ Connector will translate
			tcp://localhost into tcp://127.0.0.1 and give you a TCP connection
			host = "tcp://localhost[:port]";
			*/
			con.reset(driver->connect(host, USER, PASS));
		} catch (sql::SQLException &e) {
			std::cout << "#\t\t tcp://hostname_or_ip[:port] caused expected exception" << std::endl;
			std::cout << "#\t\t " << e.what() << " (MySQL error code: " << e.getErrorCode();
			std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
		}

		std::cout << "# done!" << std::endl;

	} catch (sql::SQLException &e) {
		/*
		The MySQL Connector/C++ throws three different exceptions:

		- sql::MethodNotImplementedException (derived from sql::SQLException)
		- sql::InvalidArgumentException (derived from sql::SQLException)
		- sql::SQLException (derived from std::runtime_error)
		*/
		std::cout << "# ERR: SQLException in " << __FILE__;
		/* Use what() (derived from std::runtime_error) to fetch the error message */
		std::cout << "# ERR: " << e.what();
		std::cout << " (MySQL error code: " << e.getErrorCode();
		std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
		std::cout << "not ok 1 - examples/connect.php" << std::endl;

		return EXIT_FAILURE;
	} catch (std::runtime_error &e) {

		std::cout << "# ERR: runtime_error in " << __FILE__;
		std::cout << "# ERR: " << e.what() << std::endl;
		std::cout << "not ok 1 - examples/connect.php" << std::endl;

		return EXIT_FAILURE;
	}




return 0;
}
