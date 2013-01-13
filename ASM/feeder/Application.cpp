#include "config.h"
#include "Application.h"
#include "quickfix/Session.h"
#include <iostream>

void Application::onLogon( const FIX::SessionID& sessionID )
{
  std::cout << std::endl << "Logon - " << sessionID << std::endl;
  this->senderCompID = sessionID.getSenderCompID();
  this->targetCompID = sessionID.getTargetCompID();

}

void Application::onLogout( const FIX::SessionID& sessionID )
{
  std::cout << std::endl << "Logout - " << sessionID << std::endl;
}

void Application::fromApp( const FIX::Message& message, const FIX::SessionID& sessionID )
throw( FIX::FieldNotFound, FIX::IncorrectDataFormat, FIX::IncorrectTagValue, FIX::UnsupportedMessageType )
{
  crack( message, sessionID );
  //std::cout << std::endl << "IN: " << message.toXML() << std::endl;

}

void Application::toApp( FIX::Message& message, const FIX::SessionID& sessionID )
throw( FIX::DoNotSend )
{
  try
  {
    FIX::PossDupFlag possDupFlag;
    message.getHeader().getField( possDupFlag );
    if ( possDupFlag ) throw FIX::DoNotSend();
  }
  catch ( FIX::FieldNotFound& ) {}

  //std::cout << std::endl << "OUT: " << message.toXML()  << std::endl;
}

void Application::onMessage( const FIX42::Quote& message, const FIX::SessionID& ) {
	FIX::Symbol symbol;
	FIX::BidPx bidPx;
	FIX::OfferPx offerPx;
	FIX::BidSize bidSize;
	FIX::OfferSize offerSize;

	message.get(symbol);
	message.get(bidPx);
	message.get(offerPx);
	message.get(bidSize);
	message.get(offerSize);

	std::cout << "symbol:" << symbol
			<< "\nbidPx:" << bidPx
			<< "\nbidSize:" << bidSize
			<< "\nofferPx:" << offerPx
			<< "\nofferSize:" << offerSize
			<<std::endl;
}

void Application::run(){

  while ( true ) {
    std::string value;
    std::cin >> value;

    if( value == "#quit" )
      break;

  }
}


