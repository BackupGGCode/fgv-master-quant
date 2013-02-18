#include "config.h"
#include "quickfix/MySQLStore.h"
#include "quickfix/SocketInitiator.h"
#include "quickfix/SessionSettings.h"
#include "Application.h"
#include "Strategy.h"
#include "AgentControl.h"
#include <string>
#include <sstream>


int main( int argc, char** argv )
{
 if ( argc != 2 )
  {
    std::cout << std::endl << "usage: " << argv[ 0 ]
    << " AGENT_ID" << std::endl;
    return 0;
  }
  std::string AGENT_ID = argv[ 1 ];


  try{


	  AgentControl agentControl(AGENT_ID);
	  std::stringstream fix(agentControl.getFixConfiguration());

	  std::cout << agentControl.getFixConfiguration() <<std::endl;

	  FIX::SessionSettings settings( fix );

	  Strategy strategy(agentControl.getStrategyConfiguration());
	  strategy.setAgentControl(agentControl);

	  Application application;
	  application.setStrategy(strategy);

	  FIX::MySQLStoreFactory  m_settings( settings );
	  FIX::SocketInitiator initiator( application, m_settings, settings );

	  initiator.start();



	  application.run();

	  initiator.stop();

    return 0;
  }
  catch ( std::exception & e )
  {
    std::cout << e.what();
    return 1;
  }
}
