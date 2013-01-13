#include "config.h"
#include "quickfix/NullStore.h"
#include "quickfix/SocketInitiator.h"
#include "quickfix/SessionSettings.h"
#include "Application.h"
#include <string>
#include <iostream>
#include <fstream>


int main( int argc, char** argv )
{
  if ( argc != 2 ){
    std::cout << "usage: " << argv[ 0 ]
    << " FILE." << std::endl;
    return 0;
  }

  std::string file_FIX_config = argv[ 1 ];

  try
  {
    FIX::SessionSettings settings( file_FIX_config );
    FIX::NullStoreFactory nullStore;
    Application application;
    FIX::SocketInitiator initiator( application,nullStore, settings );

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
