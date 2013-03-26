#ifdef _MSC_VER
#pragma warning( disable : 4503 4355 4786 )
#else
#include "config.h"
#endif

//#include "quickfix/FileStore.h"
#include "../utils/AgentControl.h"
#include "quickfix/MySQLStore.h"
#include "quickfix/SocketAcceptor.h"
#include "quickfix/SessionSettings.h"
#include "Application.h"
#include <string>
#include <iostream>
#include <fstream>


int main( int argc, char** argv )
{

 if ( argc != 2 )
  {
	std::cout << std::endl << "usage: " << argv[ 0 ]
	<< " AGENT_ID" << std::endl;
	return 0;
  }
  std::string AGENT_ID = argv[ 1 ];

  try
  {

   AgentControl agentControl(AGENT_ID);

   std::stringstream fix(agentControl.getFixConfiguration() + agentControl.getSessionConfiguration());

    FIX::SessionSettings settings( fix );

    Application application;
    FIX::MySQLStoreFactory  m_settings( settings );
    FIX::ScreenLogFactory logFactory( settings );
    FIX::SocketAcceptor acceptor( application, m_settings, settings, logFactory );

    FIX::TransactTime start_time;

    agentControl.updateExogenousTimes(start_time.getString());
    agentControl.setupPrices(start_time.getString());

    application.setAgentControl(agentControl);

    acceptor.start();
    while ( true )
    {
      std::string value;
      std::cin >> value;


      if ( value == "#symbols" )
        application.orderMatcher().display();
      else if( value == "#quit" )
        break;
      else if( value == "#ob" )
    	  application.orderMatcher().display( value );

      std::cout << std::endl;
    }
    acceptor.stop();

    return 0;
  }
  catch ( std::exception & e )
  {
    std::cout << e.what() << std::endl;
    return 1;
  }
}
