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

		config_str.replace(config_str.find(user),user.length(), this->agentID );
		boost::replace_all(config_str, "\\n", "\n");
		//std::cout<<std::endl << "CONFIG = " << config_str <<std::endl;

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

	  return config_str;
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

	const std::string host = HOST;
	std::stringstream strategy_config;


	try {
		sql::Driver * driver = sql::mysql::get_driver_instance();
		std::auto_ptr< sql::Connection > con(driver->connect(host, USER, PASS));
		std::auto_ptr< sql::Statement > stmt(con->createStatement());

		std::string statement;
		statement = "SELECT ticker, reference_stock_price, cash, number_stock, percentual_max_neg, cycle_time, initial_time FROM quickfix.strategy s inner join quickfix.agents a on s.id_strategy = a.id_strategy where id_agent='#USER#'";
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
			row++;
		}

		strategy_config << std::fixed;
		strategy_config.precision(2);

		strategy_config << "TICKER = \"" << ticker << "\";\nREFERENCE_STOCK_PRICE = "<<reference_stock_price
						<<";\nCASH = "<<cash<<";\nNUMBER_STOCK = "<<number_stock<<";\nPERCENTUAL_MAX_NEG = "
						<<percentual_max_neg<<";\nCYCLE_TIME = "<<cycle_time
						<<";\nINITIAL_TIME = "<<initial_time<<";";

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




void AgentControl::setPortfolio(float cash, float  number_stock){

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

		/* Usage of UPDATE */

		replace << "REPLACE INTO quickfix.portfolio (id_agent, number_stock, cash) VALUES ('"<< this->agentID <<"',"<< number_stock << ","<< cash <<")";
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
