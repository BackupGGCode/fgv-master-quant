#include "config.h"
#include "quickfix/MySQLStore.h"
#include "quickfix/SocketInitiator.h"
#include "quickfix/SessionSettings.h"
#include "Application.h"
#include <string>
#include <iostream>
#include <fstream>


int main( int argc, char** argv )
{
  if ( argc != 2 )
  {
    std::cout << "usage: " << argv[ 0 ]
    << " FILE." << std::endl;
    return 0;
  }
  std::string file_FIX_config = argv[ 1 ];
  //std::string file_strategy = argv[ 2 ];

  try
  {
    FIX::SessionSettings settings( file_FIX_config );

    Application application;
    FIX::MySQLStoreFactory  m_settings( settings );
    FIX::SocketInitiator initiator( application, m_settings, settings );

    initiator.start();

    application.runBOT();
    initiator.stop();

    return 0;
  }
  catch ( std::exception & e )
  {
    std::cout << e.what();
    return 1;
  }
}
