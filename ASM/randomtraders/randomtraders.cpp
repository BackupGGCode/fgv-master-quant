#include "config.h"
#include "quickfix/MySQLStore.h"
#include "quickfix/SocketInitiator.h"
#include "quickfix/SessionSettings.h"
#include "Application.h"
#include "Strategy.h"
#include <string>
#include <iostream>
#include <fstream>


int main( int argc, char** argv )
{
  if ( argc != 3 )
  {
    std::cout << "usage: " << argv[ 0 ]
    << " FILE." << std::endl;
    return 0;
  }
  std::string file_FIX = argv[ 1 ];
  std::string file_strategy = argv[ 2 ];
  //std::string file_profile = argv[ 3 ];

  try
  {
    FIX::SessionSettings settings( file_FIX );

    Application application;
    FIX::MySQLStoreFactory  m_settings( settings );
    FIX::SocketInitiator initiator( application, m_settings, settings );

    initiator.start();

    Strategy strategy(file_strategy, application);
    strategy.run();
    //application.runBOT();
    initiator.stop();

    return 0;
  }
  catch ( std::exception & e )
  {
    std::cout << e.what();
    return 1;
  }
}
